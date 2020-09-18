#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int split = 0;
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
	case 4:
		printf("Terminal DnD roller version 0.2\n");
		return;
	default:
		break;
	}
	printf("DnD roll on the terminal\n");
	printf("Flags:\n");
	printf("\t-s: do not combine rolls\n");
	printf("Examples:\n");
	printf("\troll 1d6: rolls a d6 and returns the value\n");
	printf("\troll 2d10: rolls two d10 and returns the value\n");
	printf("\troll 1d12+2: rolls a d12, adds 2 to the result and returns the value\n");
	printf("\troll 1d10-1: rolls a d10, subtracts 1 from the result and returns the value\n");
}

int chkstr(char* roll)
{
	//Check if the roll command is malformed
	char* c = roll;
	int d = 0;
	int sign = 0;
	while(*c != 0)
	{
		int i = (int) *c;
		if(i < 48 || i > 57)
			if(i != 100 && i != 43 && i != 45)
				return 1;
		if(i == 100)
			d = d + 1;
		if(i == 43 || i == 45)
			sign = sign + 1;
		c = c + 1;
	}
	//Check if 'd' or sign is used more than once
	if(d > 1 || sign > 1)
		return 1;
	return 0;
}

int parse(char* roll)
{
	//Parse roll argument for number of die, faces of die, and modifier
	int i = 0;
	int number, die;
	int sign = 1;
	int mod = 0;
	char* c;
	if(chkstr(roll) > 0)
		return 1;
	if(strpbrk(roll, "-"))
		sign = -1;
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
			return 1;
		}
		c = strtok (NULL,"d+-");
		i = i + 1;
	}
	
	if(number == 0 || die == 0)
		return 1;

	int value = 0;
	int temp = 0;
	srand((unsigned int)time(NULL));
	if(split)
	{
		for(int j = 0; j < number; j = j + 1)
		{
			temp = rand() % die + 1;
			if(sign < 0)
				printf("%i ", temp - mod);
			else
				printf("%i ", temp + mod);
		}
		printf("\n");
	}
	else
	{
		for(int j = 0; j < number; j = j + 1)
		{
			temp = rand() % die + 1;
			value = value + temp;
		}

		if(sign < 0)
			printf("(%i-%i)=%i\n", value, mod, value - mod);
		else
			printf("(%i+%i)=%i\n", value, mod, value + mod);
	}
	return 0;
}

int main(int argc, char *argv[])
{
	if(argc > 1 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0))
	{
		help(0);
		return 0;
	}
	if(argc > 1 && (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-V") == 0))
	{
		help(4);
		return 0;
	}
	switch(argc)
	{
	case 1:
		help(1);
		break;
	case 2:
		if(parse(argv[1]))
		{
			help(3);
			return 1;
		}
		break;
	case 3:
		if(strcmp(argv[1], "-s") == 0)
			split = 1;
		if(parse(argv[2]))
		{
			help(3);
			return 1;
		}
		break;
	default:
		help(2);
		return 1;
	}
}

