/* Практическая работа №2 */
/* Калькулятор с обратной бесскобочной логикой вычислений (стек). */
/* Студент: Родников Илья */
/* Группа: ИКБО-05-17 */
/* Language: C */
/* Windows compiler: Microsoft Visual C++ 2010 Express */
/* Linux compiler: gcc -std=c89 -Wall -Werror -Wextra */

#include "stdlib.h"
#include "stdio.h"
#include "malloc.h"
#include "ctype.h"

typedef double T;

typedef struct Stack_tag {
	T *data;
	size_t size;
	size_t top;
} Stack_t;

#define INIT_SIZE 10

#define MULTIPLIER 2

Stack_t* createStack();
void deleteStack(Stack_t **stack);
void resize(Stack_t *stack);
void push(Stack_t *stack, T value);
T pop(Stack_t *stack);
T peek(const Stack_t *stack);
void implode(Stack_t *stack);
void printStack(Stack_t *stack);

int main (void)
{
	Stack_t *s = createStack();

	char buf[81] = "";
	char c;
	T result = (T)0.00;

	char arithOperator;
	double firstNumber,secondNumber;

	printStack(s);

	while (!((buf[0] == 'q') || (buf[0] == 'Q'))) {
		result = (T)0.00;
		printf("Enter a number or [Q]uit or [q]uit to go further: ");
		if ( fgets( buf, sizeof buf, stdin ) != NULL )
		{
			char *chk;
			T tmp = strtod( buf, &chk );
			if ((buf[0] == 'q') || (buf[0] == 'Q')) break;
			if ( isspace( *chk ) || *chk == 0 ) {
				result = tmp;
				push(s, result);
				printf("Stack size: %lu, last entered value: %20.8f\n", s->top, peek(s));
			}
			else
				fprintf( stderr, "%s is not a valid floating-point number\n", buf );
		}
	} /* while */

	printStack(s);

	arithOperator = ' ';

	while (!((arithOperator ==  'q') || (arithOperator == 'Q'))) {
		if (s->top < 2) {
			printf("Stack size is less than 2. No more actions are possible. Run the program again.\nPress [Enter] to exit.");
			getchar();
			break;
		}
		printf("Enter an operator (+, -, *, /) or [Q] or [q] to quit: ");
		scanf("%c", &arithOperator);
		switch(arithOperator)
		{
		case '+':
			secondNumber = pop(s);
			firstNumber = pop(s);
			result = firstNumber + secondNumber;
			printf("%.8lf %c %.8lf = %.8lf\n", firstNumber, arithOperator,secondNumber, result);
			push(s, result);
			printStack(s);
			break;
		case '-':
			secondNumber = pop(s);
			firstNumber = pop(s);
			result = firstNumber - secondNumber;
			printf("%.8lf %c %.8lf = %.8lf\n", firstNumber, arithOperator,secondNumber, result);
			push(s, result);
			printStack(s);
			break;
		case '*':
			secondNumber = pop(s);
			firstNumber = pop(s);
			result = firstNumber * secondNumber;
			printf("%.8lf %c %.8lf = %.8lf\n", firstNumber, arithOperator,secondNumber, result);
			push(s, result);
			printStack(s);
			break;
		case '/':
			secondNumber = pop(s);
			firstNumber = pop(s);
			result = firstNumber / secondNumber;
			printf("%.8lf %c %.8lf = %.8lf\n", firstNumber, arithOperator,secondNumber, result);
			push(s, result);
			printStack(s);
			break;
			/* operator doesn't match any case constant (+, -, *, /) */
		default:
			printf("Error! operator is not correct\n");
			clearerr(stdin);
			getchar();
			continue;
		}
		clearerr(stdin);
		getchar();
	} /* while */

	deleteStack(&s);
	while ((c = getchar()) != '\n') {};
	clearerr(stdin);
	getchar();

	return 0;

}

#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY   -102

Stack_t* createStack() {
	Stack_t *out = NULL;
	out = (Stack_t *)malloc(sizeof(Stack_t));
	if (out == NULL) {
		exit(OUT_OF_MEMORY);
	}
	out->size = INIT_SIZE;
	out->data = (T *)malloc(out->size * sizeof(T));
	if (out->data == NULL) {
		free(out);
		exit(OUT_OF_MEMORY);
	}
	out->top = 0;
	return out;
}

void deleteStack(Stack_t **stack) {
	free((*stack)->data);
	free(*stack);
	*stack = NULL;
}

void resize(Stack_t *stack) {
	stack->size *= MULTIPLIER;
	stack->data = (T *)realloc(stack->data, stack->size * sizeof(T));
	if (stack->data == NULL) {
		exit(STACK_OVERFLOW);
	}
}

void push(Stack_t *stack, T value) {
	if (stack->top >= stack->size) {
		resize(stack);
	}
	stack->data[stack->top] = value;
	stack->top++;
}

T pop(Stack_t *stack) {
	if (stack->top == 0) {
		exit(STACK_UNDERFLOW);
	}
	stack->top--;
	return stack->data[stack->top];
}

T peek(const Stack_t *stack) {
	if (stack->top <= 0) {
		exit(STACK_UNDERFLOW);
	}
	return stack->data[stack->top - 1];
}

void implode(Stack_t *stack) {
	stack->size = stack->top;
	stack->data = (T *)realloc(stack->data, stack->size * sizeof(T));
}

void printStack(Stack_t *stack) {
	int i;
	int j;
	j = stack->top;
	if (j == 0) { printf("%s", "Stack is empty!\n"); }  else printf("Stack size: %d\n", j ) ;
	for (i = 0; i < j; i++) {
		printf("%d: %20.8f\n", i, stack->data[i]);
	}
}
