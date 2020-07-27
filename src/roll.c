#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void help(int error)
{
	// General error reporting, handles all error messages
	switch(error)
	{
	case 1:
		printf("Not enough arguments\n");
		break;
	case 2:
		printf("Too many arguments\n");
		break;
	case 3:
		printf("Roll was malformed\n");
		break;
	default:
		break;
	}
	printf("DnD roll on the terminal\n");
	printf("Examples:\n");
	printf("\troll 1d6: rolls a d6 and returns the value\n");
	printf("\troll 2d10: rolls two d10 and returns the value\n");
	printf("\troll 1d12+2: rolls a d12, adds 2 to the result and returns the value\n");
	printf("\troll 1d10-1: rolls a d10, subtracts 1 from the result and returns the value\n");
}

void parse(char* roll)
{
	int i = 0;
	int number, die;
	int sign = 1;
	int mod = 0;
	char* c;
	c = strtok(roll, "d+-");
	while(c != NULL)
	{
		switch(i)
		{
		case 0:
			number = atoi(c);
			break;
		case 1:
			die = atoi(c);
			break;
		case 2:
			mod = atoi(c);
			break;
		default:
			help(3);
			return;
		}
		c = strtok (NULL,"d+-");
		i = i + 1;
	}
	int value = 0;
	srand((unsigned int)time(NULL));
	if(strpbrk(roll, "-"))
		sign = -1;
	for(int j = 0; j < number; j = j + 1)
	{
		int temp = rand() % die + 1;
		value = value + temp;
	}
	printf("%i\n", value + mod * sign);
}

int main(int argc, char *argv[])
{
	if(argc > 1 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0))
		help(0);
	switch(argc)
	{
	case 1:
		help(1);
		break;
	case 2:
		parse(argv[1]);
		break;
	default:
		help(2);
		break;
	}		
}

