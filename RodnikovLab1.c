/* Лабораторная работа №1 */
/* Знакомство с языком C. Написание конвертера температур. */
/* Студент: Родников Илья */
/* Группа: ИКБО-05-17 */
/* Language: C */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>

float cel2kel (float fcel) {return fcel + 273.15;};
float kel2cel (float fkel) {return fkel - 273.15;};
float cel2far (float fcel) {return fcel * 9 / 5 + 32;};
float far2cel (float ffar) {return (ffar - 32) * 5 / 9;};
int printresults (unsigned char c1, unsigned char c2, unsigned char c3, float f1, float f2, float f3) {
  if (((c1 == 'K') && (f1 < 0)) || ((c2 == 'K') && (f2 < 0)) || ((c3 == 'K') && (f3 < 0))) {
    printf("Temperature value in K is invalid!\n\n");
    return 1;
  }
  printf("%.2f ", f1);
  printf("%c:\n", c1);
  printf("%.2f ", f2);
  printf("%c\n", c2);
  printf("%.2f ", f3);
  printf("%c\n\n", c3);
  return 0;
};

int main(int argc, char* argv[])
{
  int retvalue = 0;
  float fa, fc, fk, ff;
  unsigned char c = ' ';
  if (argc == 1) {
		printf("Enter value in degrees\n");
		scanf("%f", &fa);
		printf("Enter char C, K or F or press Enter key\n");
		c = getch();
  }
  if ((argc == 2) || (argc == 3)) {
		fa = atof(argv[1]);
  }
  if (argc == 3) {
		c = argv[2][0];
  }
  if (argc > 3) {
    printf("Invalid number of arguments!\n\n");
    return 1;
  }
  c = toupper(c);
  if ((c != ' ') && (c != 'C') && (c != 'K') && (c != 'F')) {c = ' ';};
  if ((c == 'C') || (c == ' ')) {
    fc = fa;
    fk = cel2kel(fc);
    ff = cel2far(fc);
	retvalue = printresults('C', 'F', 'K', fc, ff, fk);
  }
  if ((c == 'F') || (c == ' ')) {
    ff = fa;
    fc = far2cel(ff);
    fk = cel2kel(fc);
	retvalue = printresults('F', 'C', 'K', ff, fc, fk);
  }
  if ((c == 'K') || (c == ' ')) {
    fk = fa;
    fc = kel2cel(fk);
    ff = cel2far(fc);
	retvalue = printresults('K', 'C', 'F', fk, fc, ff);
  }
return retvalue;
}
