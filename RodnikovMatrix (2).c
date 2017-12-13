/* Практическая работа №4 */
/* Умножение целочисленных матриц размерностью до 10*10. */
/* Студент: Родников Илья */
/* Группа: ИКБО-05-17 */
/* Language: C */
/* Windows compiler: Microsoft Visual C++ 2010 Express */
/* Linux compiler: gcc -std=c89 -Wall -Werror -Wextra */

/*
***** РЕАЛИЗАЦИЯ АЛГОРИТМА МАНИПУЛИРОВАНИЯ ДАННЫМИ.
*1. Создать произвольный массив m x n, заполнить его, вывести на экран m > 3, n > 4.
*2. Поменять местами первую и последнюю строки, развернув их, вывести результат.
*3. Удалить строку и столбец на пересечении которых находится наименьший элемент массива, вывести результат.
*4. Создать второй массив вручную. Форматирование: пробел - конец элемента, запятая - конец строки, точка - окончание ввода.
*5. Перемножить получившиеся матрицы, вывести на экран.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_DIM_SIZE 10
#define MIN_ROW_SIZE 4
#define MIN_COL_SIZE 5

void printMatrix(int *M, int mrows, int mcols);

int main()
{
	int leftRows, leftColumns, rightRows, rightColumns, c, d, k, r, minrow, mincol, sum = 0;
	int leftMatrix[MAX_DIM_SIZE*MAX_DIM_SIZE], rightMatrix[MAX_DIM_SIZE*MAX_DIM_SIZE], resultMatrix[MAX_DIM_SIZE*MAX_DIM_SIZE];
	time_t t;

	srand((unsigned) time(&t));
	r=rand();
	leftRows = r % (MAX_DIM_SIZE - MIN_ROW_SIZE) + MIN_ROW_SIZE;
	r=rand();
	leftColumns = r % (MAX_DIM_SIZE - MIN_COL_SIZE) + MIN_COL_SIZE;

	printf("Randomly generated matrix of the integer (0..99) elements (%dx%d):\n", leftRows, leftColumns);
	for (c = 0; c < leftRows; c++)
		for (d = 0; d < leftColumns; d++) {
			r = rand();
			leftMatrix[c*leftColumns+d] = r % 100;
		}

		printMatrix((int *)&leftMatrix, leftRows, leftColumns);

		printf("Change 1st and %dth rows and reversing them:\n", leftRows);
		for (d=0; d < leftColumns; d++) {
			c = leftMatrix[d];
			k = (leftRows - 1)*leftColumns + (leftColumns - d) - 1;
			leftMatrix[d] = leftMatrix[k];
			leftMatrix[k] = c;
		}

		printMatrix((int *)&leftMatrix, leftRows, leftColumns);

		printf("Finding a row and a column with the lowest element value and delete them:\n");
		minrow = 0;
		mincol = 0;
		k = leftMatrix[0];
		for (c = 0; c < leftRows; c++)
			for (d = 0; d < leftColumns; d++) {
				r = leftMatrix[c*leftColumns+d];
				if (r < k) {
					minrow = c;
					mincol = d;
					k = r;
				}
			}
			printf("Found a row %d and a column %d with the lowest element value of %d\n and now will delete them:\n", minrow + 1, mincol + 1, k);
			for (c = 0; c < leftRows; c++)
				for (d = 0; d < leftColumns; d++) {
					if (c == minrow) continue;
					if (d == mincol) continue;
					r = ((c < minrow)? c : c - 1);
					k = ((d < mincol)? d : d - 1);
					leftMatrix[r*(leftColumns-1)+k] = leftMatrix[c*leftColumns+d];
				}
				leftRows--;
				leftColumns--;

		printMatrix((int *)&leftMatrix, leftRows, leftColumns);

		printf("Enter the number of rows and columns (max %dx%d) of the right matrix:\n", MAX_DIM_SIZE, MAX_DIM_SIZE);
				scanf("%d%d", &rightRows, &rightColumns);

		if (leftColumns != rightRows)
			printf("Matrices with entered orders can't be multiplied with each other.\n");
		else
		{
			printf("Enter the integer elements of the right matrix:\n");

			for (c = 0; c < rightRows; c++)
				for (d = 0; d < rightColumns; d++)
					scanf("%d", &rightMatrix[c*rightColumns+d]);

			sum = 0;
			for (c = 0; c < leftRows; c++) {
				for (d = 0; d < rightColumns; d++) {
					for (k = 0; k < leftColumns; k++) {
						sum += leftMatrix[c*leftColumns+k]*rightMatrix[k*rightColumns+d];
					}

					resultMatrix[c*rightColumns+d] = sum;
					sum = 0;
				}
			}

			printf("Left matrix:\n");

			printMatrix((int *)&leftMatrix, leftRows, leftColumns);

			printf("Right matrix:\n");

			printMatrix((int *)&rightMatrix, rightRows, rightColumns);

			printf("Product of entered matrices:\n");

			printMatrix((int *)&resultMatrix, leftRows, rightColumns);
		}
		clearerr(stdin);
		getchar();
		clearerr(stdin);
		printf("Press [Enter] to exit...\n");
		while ((c = getchar()) != '\n') {};

		return 0;
}

void printMatrix(int *M, int mrows, int mcols){
	int c, d;
	for (c = 0; c < mrows; c++) {
		for (d = 0; d < mcols; d++)
			printf("%d\t", M[c*mcols+d]);
		printf("\n");
	}
}
