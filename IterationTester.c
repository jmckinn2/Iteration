// Jaylen McKinney CS2060
// Program that sells T-shirts for a fundraiser


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MIN_PRICE 20
#define MAX_PRICE 50
#define MIN_PERCENT 5
#define MAX_PERCENT 20

double inputValue(int minimum, int maximum);
char characterInput(const char* allowed, const char* prompt);
void payment(const double price);



int main(void)
{
	double priceAmount = 0;
	double percentAmount = 0;
	const char tShirtSizePrompt[] = "Enter t-shirt size: (s)mall, (m)edium, (l)arge, e(x)tra-large. Enter q to quit";
	const char tShirtColorPrompt[] = "Enter t-shirt color: blac(k), (w)hite, (r)ed, (o)range, (b)lue, (p)urple.";
	char allowedSizes[] = { "smlxq" };
	char allowedColors[] = { "kwrobp" };
	char tShirtSize = 0;
	char tShirtColor = 0;

	puts("Enter selling price for t-shirts.");
	priceAmount = inputValue(MIN_PRICE, MAX_PRICE);
	puts("Enter percent of sales sent to charity");
	percentAmount = inputValue(MIN_PERCENT, MAX_PERCENT);


	tShirtSize = characterInput(allowedSizes, tShirtSizePrompt);
	tShirtColor = characterInput(allowedColors, tShirtColorPrompt);


	payment(priceAmount);



	return 0;
}

double inputValue(int minimum, int maximum)
{
	char userInput[50];
	double value = 0;
	bool valid = false;

	while (valid == false)
	{
		fgets(userInput, sizeof(userInput), stdin);
		value = strtod(userInput, NULL);
		if (value >= minimum && value <= maximum)
		{
			valid = true;
		}
		else
		{
			printf("Value must be between %d and %d. Please try again.\n", minimum, maximum);
		}
	}
	return value;
}


char characterInput(const char *allowed, const char *prompt)
{
	char letter = 0;
	bool valid = false;

	while (valid == false)
	{
		puts(prompt);
		scanf("%c", &letter);
		while ((getchar()) != '\n');
		valid = strchr(allowed, tolower(letter)) != NULL;
		
		if (valid == false)
		{
			puts("Invalid input entered");
		}
	}

	return letter;
}


void payment(const double price)
{
	// Initializing variables
	int counter = 0;
	int validCardNumber = 0;
	int creditCardPart1 = 0;
	int creditCardPart2 = 0;
	int creditCardPart3 = 0;
	int creditCardPart4 = 0;
	char creditCard[50] = "";
	bool inputSuccess = false;



	while (inputSuccess == false)
	{
		printf("Your cost is %.2f. Enter your zip code to complete payment\n", price);
		fgets(creditCard, sizeof(creditCard), stdin);
		creditCard[strlen(creditCard) - 1] = '\0';
		validCardNumber = sscanf(creditCard, "%4d-%4d-%4d-%4d", &creditCardPart1, &creditCardPart2, &creditCardPart3, &creditCardPart4);

		if (validCardNumber == 4 && strlen(creditCard) == 19)
		{
			puts("Credit card accepted");
			inputSuccess = true;
		}
		else
		{
			puts("Invalid value entered");
			counter++;
		}
		if (counter == 4)
		{
			inputSuccess = true;
		}




	}
}// end of function