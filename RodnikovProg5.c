/* Практическая работа №5 */
/* Машина Тьюринга. */
/* Студент: Родников Илья */
/* Группа: ИКБО-05-17 */
/* Language: C */
/* Windows compiler: Microsoft Visual C++ 2010 Express */
/* Linux compiler: gcc -std=c89 -Wall -Werror -Wextra */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

#define MAX_EXEC_OPS 100000

typedef struct {
	int startCell;
	int headPos;
	int headValue;
	int *leftArray;
	size_t leftUsed;
	size_t leftSize;
	int *rightArray;
	size_t rightUsed;
	size_t rightSize;
} Tape;

struct sysCommands {
	int id;
	char command[10];
	char description[200];
} sc[10] = {
	{1, "movl", "переход влево на одну ячейку"},
	{2, "movr", "переход вправо на одну ячейку"},
	{3, "inc", "инкремент значения по текущему адресу"},
	{4, "dec", "декремент значения по текущему адресу"},
	{5, "print", "вывод значения по текущему адресу на экран"},
	{6, "get", "считать 1 байт с клавиатуры и записать в текущую ячейку"},
	{7, "printc", "вывод значения текущей ячейки как ASCII-символа (например, 65 должно быть выведено как A)"},
	{8, "begin", "переход на следующую за соответствующей инструкцией end инструкцию, если в текущей ячейке записан 0"},
	{9, "end", "если в текущей ячейке не 0, то переход обратно на инструкцию, следующую за соответствующей инструкцией begin"},
	{10, "*", "строка-комментарий"}
};

typedef struct {
	int commandId;
	int nextStep;
} progLine;

void trim (unsigned char *cs);
void initTape(Tape *a, size_t initialSize);
void freeTape(Tape *a);
void movlTape(Tape *a);
void movrTape(Tape *a);
void incTape(Tape *a);
void decTape(Tape *a);
void printTape(Tape *a);
void getTape(Tape *a);
void printcTape(Tape *a);
void dumpTape(Tape *a);

int getCommandId(char *s);
void printCommandDescription(char *s);
void printCommandById(int id);
void printCommands(void);
void printProgramCodes(progLine *p, int lineCount);
void setProgramNextStep(progLine *p, int lineCount);
void executeProgram(Tape *a, progLine *p);

int main(void)
{
	char c;
	FILE *ptr_file;
	unsigned char buf[1000];
	Tape b;
	progLine *programText;
	int programLineCount, programLineUsed;

	printf("----- TURING MACHINE -----\n");
	printCommands();

	printf("----- READING FILE ./INPUT.TXT -----\n");
	ptr_file =fopen("./input.txt","r");
	if (!ptr_file) {
	printf("----- CANNOT READ FILE ./INPUT.TXT -----\n");
		return 1;
	}

	programLineCount = 10;
	programText = (progLine *)malloc(programLineCount * sizeof(progLine));
	programLineUsed = 0;

	initTape(&b, 10);

	while (fgets((char *)buf,1000, ptr_file)!=NULL) {
		trim(buf);
		if (buf[0] != '\0') {
			printf("%s - ",buf);
			printCommandDescription((char *)buf);
			printf("\n");

			programText[programLineUsed].commandId = getCommandId((char *)buf);
			programText[programLineUsed].nextStep = 0;
			programLineUsed++;
			if (programLineCount == programLineUsed) {
				programLineCount += 10;
				programText = (progLine *)realloc(programText, programLineCount * sizeof(progLine));
			};

			buf[0] = '\0';
		};
	};

	printf("----- STOP READING FILE ./INPUT.TXT -----\n");
	fclose(ptr_file);

	setProgramNextStep(programText, programLineUsed);
	printProgramCodes(programText, programLineUsed);
	executeProgram(&b, programText);
	free(programText);
	dumpTape(&b);
	freeTape(&b);
	clearerr(stdin);
	while ((c = getchar()) != '\n') {};
	return 0;
}

void trim (unsigned char *cs)
{
	unsigned char *p;
	size_t len = strlen((char *)cs);
	for (p = cs + len - 1; isspace (*p); --p) /* nothing */ ;
	p[1] = '\0';
	for (p = cs; isspace (*p); ++p) /* nothing */ ;
	memmove (cs, p, len - (size_t) (p - cs) + 1);
}

void initTape(Tape *a, size_t initialSize) {
	a->startCell = 0;
	a->headPos = 0;
	a->headValue = 0;
	a->leftArray = (int *)malloc(initialSize * sizeof(int));
	a->leftUsed = 0;
	a->leftSize = initialSize;
	a->rightArray = (int *)malloc(initialSize * sizeof(int));
	a->rightUsed = 0;
	a->rightSize = initialSize;
}

void freeTape(Tape *a) {
	free(a->leftArray);
	a->leftArray = NULL;
	a->leftUsed = 0;
	a->leftSize = 0;
	free(a->rightArray);
	a->rightArray = NULL;
	a->rightUsed = 0;
	a->rightSize = 0;
	a->startCell = 0;
	a->headPos = 0;
	a->headValue = 0;
}

void incTape(Tape *a) {
	a->headValue = (a->headValue == 255) ? 0 : a->headValue + 1;
	if (a->headPos == 0) {
		a->startCell = a->headValue;
	}
	if (a->headPos > 0) {
		a->rightArray[a->headPos-1] = a->headValue;
	}
	if (a->headPos < 0) {
		a->leftArray[-(a->headPos+1)] = a->headValue;
	}
}

void decTape(Tape *a) {
	a->headValue = (a->headValue == 0) ? 0 : a->headValue - 1;
	if (a->headPos == 0) {
		a->startCell = a->headValue;
	}
	if (a->headPos > 0) {
		a->rightArray[a->headPos-1] = a->headValue;
	}
	if (a->headPos < 0) {
		a->leftArray[-(a->headPos+1)] = a->headValue;
	}
}

void printTape(Tape *a) {
	printf("\nprint: %d\n", a->headValue);
}

void printcTape(Tape *a) {
	char c = a->headValue;
	printf("\nprintc: %c\n", c);
}

void movlTape(Tape *a) {
	if (a->headPos < 0) {
		if (a->leftUsed == a->leftSize) {
			a->leftSize += 10;
			a->leftArray = (int *)realloc(a->leftArray, a->leftSize * sizeof(int));
			a->rightArray[a->leftUsed] = 0;
		}
		a->headPos = a->headPos - 1;
		if((-a->headPos) > (int)(a->leftUsed)) {
			a->leftArray[a->leftUsed] = 0;
			a->leftUsed += 1;
		}
		a->headValue = a->leftArray[-(a->headPos+1)];
	}

	if (a->headPos == 0) {
		a->headPos = -1;
		if (a->leftUsed == 0) {
			a->leftUsed = 1;
			a->leftArray[0] = 0;
		}
		a->headValue = a->leftArray[0];
	}

	if (a->headPos == 1) {
		a->headPos = 0;
		a->headValue = a->startCell;
	}

	if (a->headPos > 1) {
		a->headPos = a->headPos - 1;
		a->headValue = a->rightArray[a->headPos];
	}
}

void movrTape(Tape *a) {
	if (a->headPos > 0) {
		if (a->rightUsed == a->rightSize) {
			a->rightSize += 10;
			a->rightArray = (int *)realloc(a->rightArray, a->rightSize * sizeof(int));
			a->rightArray[a->rightUsed] = 0;
		}
		a->headPos = a->headPos + 1;
		if((a->headPos) > (int)(a->rightUsed)) {
			a->rightArray[a->rightUsed] = 0;
			a->rightUsed += 1;
		}
		a->headValue = a->rightArray[a->headPos-1];
	}

	if (a->headPos == 0) {
		a->headPos = 1;
		if (a->rightUsed == 0) {
			a->rightUsed = 1;
			a->rightArray[0] = 0;
		}
		a->headValue = a->rightArray[0];
	}

	if (a->headPos == -1) {
		a->headPos = 0;
		a->headValue = a->startCell;
	}

	if (a->headPos < -1) {
		a->headPos = a->headPos + 1;
		a->headValue = a->leftArray[-(a->headPos+1)];
	}
}

void getTape(Tape *a) {
	char c;
	int i;
	printf("Enter one ASCII byte/character (A-Z, a-z): ");
	scanf("%c", &c);
	printf("\n");
	i = (int)c;
	a->headValue = i;
	if (a->headPos == 0) a->startCell = i;
	if (a->headPos > 0) a->rightArray[a->headPos-1] = i;
	if (a->headPos < 0) a->leftArray[-(a->headPos+1)] = i;
}

void dumpTape(Tape *a) {
	unsigned int i;
	int p;
	p = a->headPos;
	printf("*** CURRENT TAPE STATE ***\n");
	/* print a ruler */
	printf("POSTN");
	for (i = a->leftUsed; i > 0; i--) printf((p == -(int)i) ? "[%3d]" : "%4d ", -(int)i);
	printf("  (0)");
	for (i = 1; i < a->rightUsed + 1; i++) printf((p == (int)i) ? "[%+3d]" : "%+4d ", i);
	printf("\n");
	/* print the tape values */
	printf("VALUE");
	for (i = a->leftUsed; i > 0; i--) printf((p == -(int)i) ? "[%3d]" : "%4d ", a->leftArray[i-1]);
	printf("(%3d)", a->startCell);
	for (i = 1; i < a->rightUsed + 1; i++) printf((p == (int)i) ? "[%3d]" : "%4d ", a->rightArray[i-1]);
	printf("\n");
	/* print the tape header position */
	printf("HEAD:");
	p = a->headPos;
	for (i = a->leftUsed; i > 0; i--) (p == -(int)i) ? printf("[^^^]") :  printf("[---]");
	(p == 0) ? printf("[^^^]") :  printf("[---]");
	for (i = 1; i < a->rightUsed + 1; i++) (p == (int)i) ? printf("[^^^]") :  printf("[---]");
	printf("\n");
}

int getCommandId(char *s) {
	int i = 0, f = -1;
	char c[2];
	c[0] = s[0];
	c[1] = '\0';
	for (i = 0; i < 10; i++) {
		if ((strcmp(s, sc[i].command) == 0) || (strcmp((char *)c, sc[i].command) == 0)) {
			f = sc[i].id;
			break;
		}
	}
	return f;
}

void printCommandDescription(char *s) {
	int i = 0, f = -1;
	char c[2];
	c[0] = s[0];
	c[1] = '\0';
	for (i = 0; i < 10; i++) {
		if ((strcmp(s, sc[i].command) == 0) || (strcmp((char *)c, sc[i].command) == 0)) {
			f = i;
			break;
		}
	}
	if (f == -1) printf("неизвестная команда");
	else printf("%s", sc[f].description);

	return;
}

void printCommandById(int id) {
	int i = 0, f = -1;
	for(i = 0; i < 10; i++) {
		if(id == sc[i].id) {
			f = i;
			break;
		};
	};
	if (f == -1) printf("неизвестная команда");
	else printf("%s (%s)", sc[f].command, sc[f].description);
	return;
}

void printCommands(void){
	int i = 0;
	printf("----- SYSTEM OF COMMANDS -----\n");
	for (i = 0; i < 10; i++) {
		printf("%d) %s: %s\n", sc[i].id, sc[i].command, sc[i].description);
	}

	return;
}

void printProgramCodes(progLine *p, int lineCount) {
	int i;
	printf("----- START OF PROGRAM PRINTOUT -----\n");
	printf("LINE  CMD NEXT   COMMAND DESCRIPTION\n");
	for(i = 0; i < lineCount; i++) {
		printf("%4d: %3d %4d - ", i, p[i].commandId, p[i].nextStep);
		printCommandById(p[i].commandId);
		printf("\n");
	}
	printf("----- END OF PROGRAM PRINTOUT -----\n");
	return;
}

void setProgramNextStep(progLine *p, int lineCount) {
	int i, j, b;
	for(i = 0; i < lineCount; i++) {
		if(p[i].commandId == 9) continue;
		if(p[i].commandId == 8) {
			b = 1;
			for(j = i + 1; j < lineCount; j++) {
				if(p[j].commandId == 8) {
					b++;
					continue;
				}; /* if */
				if(p[j].commandId == 9) {
					if (b == 1) {
						p[i].nextStep = j + 1;
						p[j].nextStep = i + 1;
						break;
					} else
						b--;
				}; /* if */
			}; /* for */
		} else
			for(j = i + 1; j < lineCount; j++)
				if(p[j].commandId != 10) {
					p[i].nextStep = j;
					break;
				};
	};
	return;
}

void executeProgram(Tape *a, progLine *p) {
	int i, e;
	i = 0;
	e = 1;
	printf("----- START PROGRAM EXECUTION -----\n");
	while(e <= MAX_EXEC_OPS) {
		if((e > 1) && (i == 0)) break;
		printf("step: %d, line: %d, command: %d", e, i, p[i].commandId);
		switch(p[i].commandId) {
		case 1:
			movlTape(a);
			i = p[i].nextStep;
			break;
		case 2:
			movrTape(a);
			i = p[i].nextStep;
			break;
		case 3:
			incTape(a);
			i = p[i].nextStep;
			break;
		case 4:
			decTape(a);
			i = p[i].nextStep;
			break;
		case 5:
			printTape(a);
			i = p[i].nextStep;
			break;
		case 6:
			getTape(a);
			i = p[i].nextStep;
			break;
		case 7:
			printcTape(a);
			i = p[i].nextStep;
			break;
		case 8:
			/* begin */
			i = (a->headValue == 0) ? p[i].nextStep : i + 1; 
			break;
		case 9:
			/* end */
			i = (a->headValue != 0) ? p[i].nextStep : i + 1; 
			break;
		case 10:
			/* comment */
			i = p[i].nextStep;
			break;
		default:
			i = p[i].nextStep;
			break;
		};
		printf(", tape head pos: %d, tape head value: %d\n", a->headPos, a->headValue);
		e++;
	};
	printf("----- END OF PROGRAM EXECUTION -----\n");

	return;
}
