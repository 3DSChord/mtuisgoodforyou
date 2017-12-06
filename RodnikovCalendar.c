/* Практическая работа №3 */
/* Вечный календарь. Определение дня недели для произвольной даты. */
/* Студент: Родников Илья */
/* Группа: ИКБО-05-17 */
/* Language: C */
/* Windows compiler: Microsoft Visual C++ 2010 Express */
/* Linux compiler: gcc -std=c89 -Wall -Werror -Wextra */

#include "stdio.h"

/*
calculating week day
day - day of the month
month - month of the year. 1 - January, 2 - February etc.
year - year
gregorian If true use Gregorian calendar else use Julian calendar
return week day 0 - Sunday, 1 - Monday etc.
*/
int weekDay(int day, int month, int year, int gregorian);

int main(void)
{
	unsigned char c;
	int dd, mm, yyyy, dayNumber;
	dd=1;
	mm=1;
	yyyy=1970;
	dayNumber=0;
	printf("Enter day number (1-31): ");
	scanf("%d", &dd);
	printf("Enter month number (1-12): ");
	scanf("%d", &mm);
	printf("Enter year number (1-5999): ");
	scanf("%d", &yyyy);

	dayNumber=weekDay(dd, mm, yyyy, 1);
	if ((dayNumber>=0) && (dayNumber<=6)) {
		printf("Week day number: %d - ", dayNumber);
		switch(dayNumber){
		case 0:
			printf("Sunday");
			break;
		case 1:
			printf("Monday");
			break;
		case 2:
			printf("Tuesday");
			break;
		case 3:
			printf("Wednesday");
			break;
		case 4:
			printf("Thursday");
			break;
		case 5:
			printf("Friday");
			break;
		case 6:
			printf("Saturday");
			break;
		default:
			printf("Unknown");
			break;
		}
		printf("\n");
	}
	printf("Press [Enter] to exit.\n");
	while ((c = getchar()) != '\n') {};
	clearerr(stdin);
	getchar();
	return 0;
}

int weekDay(int day, int month, int year, int gregorian){
	int c;
	if(month>2){
		month-=2;
	}
	else{
		month+=10;
		year--;
	};
	c=year/100;
	return (day+(13*month-1)/5+5*(year%100)/4+(gregorian ? 21*c/4:5+6*c))%7;
}