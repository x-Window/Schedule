/*Program that stores details of sections in a student's schedule
 * and identifies any time overlaps between classes.
 * 
 * Andrew Li, July 15
 */ 

#include <stdio.h>
//Uses bits to create a week calendar for which each 1 is a day
#define MONDAY 1
#define TUESDAY MONDAY << 1
#define WEDNESDAY TUESDAY << 1
#define THURSDAY WEDNESDAY << 1
#define FRIDAY THURSDAY << 1
#define SATURDAY FRIDAY << 1
#define SUNDAY SATURDAY << 1
//Language; 1 for German and 0 for English output
#define LANG 0

//Creates section struct with specified and efficient bit memory per variable
typedef struct section{
	char name[20];
	unsigned int days_of_week:7;
	unsigned int start_hour:5;
	unsigned int start_minute:6;
	unsigned int end_hour:5;
	unsigned int end_minute:6;
}section;

//Schedule of sections, days are merged together bitwise using OR
section schedule[] = { 
{"ECON 101", MONDAY | WEDNESDAY, 9,	15,	11, 35},
{"PHYS 002", TUESDAY | THURSDAY, 10, 25, 13, 00},
{"COMSC 079C", MONDAY, 7, 45, 9, 30},
{"ACCTG 0063A",	WEDNESDAY | FRIDAY, 10, 15, 12, 35},
{"CHEM 001", TUESDAY | THURSDAY, 17, 00, 19, 25},
{"MATH 017", ((MONDAY | TUESDAY) | WEDNESDAY) | THURSDAY, 13, 05, 15, 45},
{"ART 099",	TUESDAY | THURSDAY,	12, 05, 16, 35}
};

const int ARRAY_LENGTH = 7;

//Displays abbrieviated dates per language
#if LANG == 0
char days[8][3] = {"M", "T", "W", "Th", "F", "Sa", "Su"}; 
#elif LANG == 1
char days[8][3] = {"Mo", "Di", "Mi", "Do", "Fr", "Sa", "So"}; 
#endif
/*
 * The has_conflict() function returns true if there is a time conflict
 * between the two sections; false if there is no conflict.
 */
_Bool has_conflict(struct section sect_a, struct section sect_b){
	if((sect_a.end_hour > sect_b.end_hour) || ((sect_a.end_hour == sect_b.end_hour)&&(sect_a.end_minute > sect_b.end_minute))){
		if(((sect_a.start_hour < sect_b.end_hour) || ((sect_a.start_hour == sect_b.end_hour)&&(sect_a.start_minute < sect_b.end_minute))) && ((sect_a.days_of_week & sect_b.days_of_week) != 0)){
			return 1;
		}
	}
	return 0;
}
/*
 * The display() function prints the information about the given section;
 * It displays the section name, the days it meets, and the beginning
 * and ending time in 24-hour notation.
 */
void display(struct section sect){
	//Iterates through 7 bits to identify weekdays/weekends
	printf("%s ", sect.name);
	unsigned int decider;
	unsigned int i = 0;
	for(decider = 0x01; decider <= 0x40; decider*=2){
		if(sect.days_of_week & decider){
			printf("%s", days[i]);
		}
		i++;
	}
	if(sect.start_hour < 10){
		printf(" (0%d", sect.start_hour);
	}
	else{
		printf(" (%d", sect.start_hour);
	}
	if(sect.start_minute < 10){
		printf("0%d", sect.start_minute);
	}
	else{
		printf("%d", sect.start_minute);
	}
	printf("-");
	if(sect.end_hour < 10){
		printf("0%d", sect.end_hour);
	}
	else{
		printf("%d", sect.end_hour);
	}
	if(sect.end_minute < 10){
		printf("0%d)", sect.end_minute);
	}
	else{
		printf("%d)", sect.end_minute);
	}
	}
int main(void){
	//Displays which two sections have conflicts
	for(int j = 0; j < ARRAY_LENGTH; j++){
		for(int i = 0; i < ARRAY_LENGTH; i++){
			if(j != i){
				if(has_conflict(schedule[j], schedule[i])){
					display(schedule[j]);
					#if LANG == 0
					printf(" conflicts with ");
					#elif LANG == 1
					printf(" steht in Konflikt mit ");
					#endif
					display(schedule[i]);
					printf("\n");
				}
			}
		}
	}
	return 0;
}
