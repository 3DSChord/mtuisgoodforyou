/* Практическая работа №4 */
/* Умножение целочисленных матриц размерностью до 10*10. */
/* Студент: Родников Илья */
/* Группа: ИКБО-05-17 */
/* Language: C */
/* Windows compiler: Microsoft Visual C++ 2010 Express */
/* Linux compiler: gcc -std=c89 -Wall -Werror -Wextra */

/* Пример запуска программы: */
/*
Enter the number of rows and columns (max 10x10) of the left matrix:
3 2
Enter the integer elements of the left matrix:
-1 4
3 5
-2 6
Enter the number of rows and columns (max 10x10) of the right matrix:
2 2
Enter the integer elements of the right matrix:
1 4
7 -1
Left matrix:
-1      4
3       5
-2      6
Right matrix:
1       4
7       -1
Product of entered matrices:
27      -8
38      7
40      -14
Press [Enter] to exit...
*/

#include <stdio.h>

int main()
{
	int leftRows, leftColumns, rightRows, rightColumns, c, d, k, sum = 0;
	int leftMatrix[100], rightMatrix[100], resultMatrix[100];

	printf("Enter the number of rows and columns (max 10x10) of the left matrix:\n");
	scanf("%d%d", &leftRows, &leftColumns);
	printf("Enter the integer elements of the left matrix:\n");

	for (c = 0; c < leftRows; c++)
		for (d = 0; d < leftColumns; d++)
			scanf("%d", &leftMatrix[c*leftColumns+d]);

	printf("Enter the number of rows and columns (max 10x10) of the right matrix:\n");
	scanf("%d%d", &rightRows, &rightColumns);

	if (leftColumns != rightRows)
		printf("Matrices with entered orders can't be multiplied with each other.\n");
	else
	{
		printf("Enter the integer elements of the right matrix:\n");

		for (c = 0; c < rightRows; c++)
			for (d = 0; d < rightColumns; d++)
				scanf("%d", &rightMatrix[c*rightColumns+d]);

		for (c = 0; c < leftRows; c++) {
			for (d = 0; d < leftColumns; d++) {
				for (k = 0; k < rightRows; k++) {
					sum += leftMatrix[c*leftColumns+k]*rightMatrix[k*rightColumns+d];
				}

				resultMatrix[c*leftRows+d] = sum;
				sum = 0;
			}
		}

		printf("Left matrix:\n");

		for (c = 0; c < leftRows; c++) {
			for (d = 0; d < leftColumns; d++)
				printf("%d\t", leftMatrix[c*leftColumns+d]);

			printf("\n");
		}

		printf("Right matrix:\n");

		for (c = 0; c < rightRows; c++) {
			for (d = 0; d < rightColumns; d++)
				printf("%d\t", rightMatrix[c*rightColumns+d]);

			printf("\n");
		}

		printf("Product of entered matrices:\n");

		for (c = 0; c < leftRows; c++) {
			for (d = 0; d < rightColumns; d++)
				printf("%d\t", resultMatrix[c*leftRows+d]);

			printf("\n");
		}
	}
	clearerr(stdin);
	getchar();
	clearerr(stdin);
	printf("Press [Enter] to exit...\n");
	while ((c = getchar()) != '\n') {};

	return 0;
}