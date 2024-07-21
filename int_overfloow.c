#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/*
Version "secured" of the challenge
*/

void rules_explanation(void)
{
	printf("==========================================\n");
	printf("+> The rules are very simple:           <+\n");
	printf("+> The one that take the last match win <+\n");
	printf("==========================================\n");
}

int check_decision(char decision)   // no cheat :(
{
	return (decision >= 1 && decision <= 3);
}

int human_turn(int *nb_matches) 
{
	unsigned int decision = 0;
	char buffer[10];

	printf("How many matches do you want to take ? (1-3)\n");
	fgets(buffer, sizeof(buffer), stdin);
	
	decision = strtoul(buffer, NULL, 10); // string to unsigned long

	if (!check_decision(decision)) 
	{
		printf("Are you trying to cheat ??\n");
		return 0;
	}

	*nb_matches -= decision;
	printf("You've taken %i match(es)\n", decision);

	return 1;
}

void computer_turn(int *nb_matches) 
{
	unsigned int decision = 0;

	if (*nb_matches == 4) 
	{
		decision = 4;
		*nb_matches = 0;

		printf("HUMMM\n");
		sleep(1);

		printf("HUMMMMMMMMMMM\n");
		sleep(1);

		printf("Wait, I got this !\n");
		sleep(1);
	}
	else if (*nb_matches % 4 == 0) 
	{
		decision = 1;
		*nb_matches -= decision;
	}
	else 
	{
		decision = (*nb_matches % 4);
		*nb_matches -= decision;
	}

	printf("The computer has taken %i match(es)\n", decision);
}

int main(void)
{
	// We set the number of matches
	srand(time(NULL)); 
	char pass[80];                     // password from fd
	FILE *fd;                          // pasword file stream
	int nb_matches = 10 + rand() % 40; // randValue : 10 to 50
	int turn = 0;
	
	// Game settings
	rules_explanation();
	printf("There are %u match(es)\n", nb_matches);
	
	// Now we begin the game
	while (nb_matches > 0) // while nb... bigger than zero
	{
		if (turn == 0) 
		{
			if (human_turn(&nb_matches))
			{
				turn = 1;
			}
			else
			{
				turn = 0;
			}
		}
		else 
		{
			computer_turn(&nb_matches);
			turn = 0;
		}

		printf("there are %i match(es) remaining\n", nb_matches);
	}
	
	if (!turn) // turn must be TRUE
	{
		printf("You lose !\n");
	}
	else	// Game win! get flag. (maybe?)
	{
		printf("How did you do this ?\n");
		printf("password is : \n");

		fd = fopen(".password", "r");
		fgets(pass, sizeof(pass), fd);

		printf("%s", pass);
		printf("You win !\n");
	}

	return EXIT_SUCCESS;
}