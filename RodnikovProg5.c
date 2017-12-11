/* ������������ ������ �5 */
/* ������ ��������. */
/* �������: �������� ���� */
/* ������: ����-05-17 */
/* Language: C */
/* Windows compiler: Microsoft Visual C++ 2010 Express */
/* Linux compiler: gcc -std=c89 -Wall -Werror -Wextra */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

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

void trim (unsigned char *cs);
void initTape(Tape *a, size_t initialSize);
void freeTape(Tape *a);
void incTape(Tape *a);

int main(void)
{
	char c;
	FILE *ptr_file;
	unsigned char buf[1000];
	Tape b;

	printf("----- TURING COMPUTER -----\n");

	initTape(&b, 1000);

	ptr_file =fopen("input.txt","r");
	if (!ptr_file)
		return 1;

	while (fgets((char *)buf,1000, ptr_file)!=NULL) {
		trim(buf);
		if (buf[0] != '\0') {
			printf("%s\n",buf);
			if (strcmp((char *)buf, "movl") == 0) 
			{
				printf("������� ����� �� ���� ������\n");
			} 
			else if (strcmp((char *)buf, "movr") == 0)
			{
				printf("������� ������ �� ���� ������\n");
			}
			/* more else if clauses */
			else if (strcmp((char *)buf, "inc") == 0)
			{
				printf("��������� �������� �� �������� ������\n");
				incTape(&b);
				printf("%d\n", b.headValue);
			}
			else if (strcmp((char *)buf, "dec") == 0)
			{
				printf("��������� �������� �� �������� ������\n");
			}
			else if (strcmp((char *)buf, "print") == 0)
			{
				printf("����� �������� �� �������� ������ �� �����\n");
			}
			else if (strcmp((char *)buf, "get") == 0)
			{
				printf("������� 1 ���� � ���������� � �������� � ������� ������\n");
			}
			else if (strcmp((char *)buf, "printc") == 0)
			{
				printf("����� �������� ������� ������ ��� ASCII-������� (��������, 65 ������ ���� �������� ��� A)\n");
			}
			else if (strcmp((char *)buf, "begin") == 0)
			{
				printf("������� �� ��������� �� ��������������� ����������� end ����������, ���� � ������� ������ ������� 0\n");
			}
			else if (strcmp((char *)buf, "end") == 0)
			{
				printf("���� � ������� ������ �� 0, �� ������� ������� �� ����������, ��������� �� ��������������� ����������� begin\n");
			}
			else /* default: */
			{
				if (buf[0] == '*') printf("������-�����������\n");
				else printf("����������� �������\n");
			}
		}
		buf[0] = '\0';
	}

	fclose(ptr_file);

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
if (a->headPos == 0) {
	a->startCell++;
	a->headValue = a->startCell;
}
if (a->headPos > 0) {
	a->headValue++;
	a->rightArray[a->headPos-1]++;
}
if (a->headPos < 0) {
	a->headValue++;
	a->leftArray[-(a->headPos+1)]++;
}
}

