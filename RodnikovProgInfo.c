#include <stdio.h>
#include <stdlib.h>

int main(){
	int i, j, n, M, N, tmp;
	char choice, char_A = (char)'A', char_M = (char)'M';
	int a[100];
	/* int b[100]; */
	int c[2];
	srand(123);
	printf("----- ENTER NUMBER OF ELEMENTS -----\n");
	scanf("%d", &n);
	while ((choice = getchar()) != '\n') {};
	printf("----- ENTER <<A>> FOR AUTO-INPUT OR <<M>> FOR MANUAL -----\n");
	choice = getchar();
	if (choice == char_A){
		for(i = 0; i<n; i++)
		{
			a[i] = 0 + rand() % 100;
		}
		for(i = 0; i<n; i++)
		{
			printf("%d\n", a[i]);
		}
	}
	else if (choice == char_M){
		for (i = 0; i<n; i++) 
		{
			printf("a[%d] = ", i);
			scanf("%d", &a[i]);
		}
		for(i = 0; i<n; i++)
		{
			printf("%d\n", a[i]);
		}
	}
	for(i = 0; i < n-1; i++) { 
		for(j = 0; j < n - 1 - i; j++) { 
			if(a[j] > a[j+1]) { 
				tmp = a[j];
				a[j] = a[j+1] ;
				a[j+1] = tmp; 
			}
		}
	}
	printf("----- ENTER N-th MAX AND M-th MIN -----\n");
	scanf("%d %d", &N, &M);
	c[0] = a[M - 1];
	c[1] = a[n - N];
	printf("max = %d\n", c[1]);
	printf("min = %d\n", c[0]);
	while ((choice = getchar()) != '\n') {};
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
	for (i = 0; i<n; i++){
		if((i != M - 1) && (i != n - N)) printf("%d ", a[i]);
	}
	printf("\n");
	for (i = 0; i<2; i++){
		printf("%d ", c[i]);
	}
	while ((choice = getchar()) != '\n') {};
	return 0;
}
