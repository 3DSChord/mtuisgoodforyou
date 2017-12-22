#include <stdio.h>
#include <stdlib.h>

int main(){
	int i, j, n, M, N, tmp;
	char choice, char_A = (char)'A', char_M = (char)'M', t;
	int a[100];
	/* int b[100]; */
	int c[2];
	srand(123);
	choice = '\0';
	n = 0;
	while((n < 4) || (n > 100)) {
		printf("----- ENTER NUMBER OF ELEMENTS -----\n");
		scanf(" %d", &n);
		while ((t = getchar()) != '\n') {};
		if((n < 4) || (n > 100)) printf("Entered value %d is not valid.\n", n);
	}
	printf("Array of %d elements is to be filled.\n", n);
	while ((choice != 'Q') && (choice != 'q')) {
		printf("----- ENTER <<A>> FOR AUTO-INPUT OR <<M>> FOR MANUAL, <<Q>> TO QUIT -----\n");
		/* choice = getchar(); */
		scanf(" %c", &choice);
		while ((t = getchar()) != '\n') {};
		if (choice == char_A){
			for(i = 0; i<n; i++)
			{
				a[i] = 0 + rand() % 100;
			}
		}
		else if (choice == char_M){
			for (i = 0; i<n; i++) 
			{
				printf("a[%d] = ", i);
				scanf(" %d", &a[i]);
			}
		}
		if((choice == char_A) || (choice == char_M)) {
			printf("----- ARRAY OF %d ELEMENTS -----\n", n);
			for(i = 0; i<n; i++)
			{
				printf("%d ", a[i]);
			}
			printf("\nSorting the array ...\n");
			for(i = 0; i < n-1; i++) { 
				for(j = 0; j < n - 1 - i; j++) { 
					if(a[j] > a[j+1]) { 
						tmp = a[j];
						a[j] = a[j+1] ;
						a[j+1] = tmp; 
					}
				}
			}
			break;
		}
	} /* while */
	if ((choice == 'Q') || (choice == 'q')) {printf("Quitting the program...\n"); return 1;};
	N = 0;
	M = 0;
	while((N < 1) || (N > n) || (M < 1) || (M > n)) {
		printf("----- ENTER N-th MAX AND M-th MIN OF %d ELEMENTS -----\n", n);
		scanf(" %d %d", &N, &M);
        while ((t = getchar()) != '\n') {};
		if((N < 1) || (N > n)) printf("Invalid value N = %d\n", N);
		if((M < 1) || (M > n)) printf("Invalid value M = %d\n", M);
	}
	c[0] = a[M - 1];
	c[1] = a[n - N];
	printf("max = %d\n", c[1]);
	printf("min = %d\n", c[0]);
/*	for(i = 0; i<n; i++)
	{
		if ((i != M-1) && (i != n - N))
		{
			b[i] = a[i];
		}
		else {
			b[i] = a[i];
			if (i == M-1) c[0] = a[i];
			if (i == n - N) c[1] = a[i];
		}
	}*/
	printf("----- ARRAY OF %d ELEMENTS -----\n", ((M - 1) != (n - N)) ? n - 2:n - 1);
	for (i = 0; i<n; i++){
		if((i != M - 1) && (i != n - N)) printf("%d ", a[i]);
	}
	printf("\n");
	printf("----- EXCLUDED %d-th MAX = %d AND %d-th MIN = %d -----\n", N, c[1], M, c[0]);
/*	for (i = 0; i<2; i++){
		printf("%d ", c[i]);
	} */
	printf("Press [Enter] to exit...\n");
	while ((choice = getchar()) != '\n') {};
	return 0;
}
