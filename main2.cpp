#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct student
{
	long Id;
	char Name[10];
	char Sex;
	int Age;
	char Note[100];
	struct student *next;
};