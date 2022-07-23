// Jaylen McKinney CS2060
// Program that sells T-shirts for a fundraiser

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

// function prototype
int validPin(int pin);
int tShirtPrice(int price);
int charityPercent(int percent);
char tShirtSize(char size);
char tShirtColor(char color);
void payment(const int price);
void recipt(const int price, const int percent, const char size, const char color, const double currentCharityAmount);
int totalPrice(int price);


int main(void) {
	
	// initializing variables
	int pinNum = 0;
	int priceAmount = 0;
	int percentAmount = 0;
	int quitProgram = 0;
	int finalPrice = 0;
	double charityPercentToDecimal = 0;
	double amountToCharity = 0;
	char userSize = 0;
	char userColor = 0;
	bool exit = false;

	// Jumps to validPin function. Sets pinNum equal to what validPin returns
	pinNum = validPin(pinNum);

	// Check if pinNum equals the required PIN
	if (pinNum == 81405)
	{
		puts("PIN Accepted");
		// Jumps to tShirtPrice function. Sets priceAmount equal to what tShirtPrice returns
		priceAmount = tShirtPrice(priceAmount);

		// Jumps to charityPercent function. Sets percentAmount equal to what charityPercent returns
		percentAmount = charityPercent(percentAmount);

		puts("------T-Shirt Fundraiser------");
		printf("Buy a shirt and %d will go to charity\n", percentAmount);
		printf("Shirt price is $%.2f\n", (double)priceAmount);

		// Jumps to tShirtSize function. Sets userSize equal to what tShirtSize returns
		userSize = tShirtSize(userSize);
		charityPercentToDecimal = (double)percentAmount / 100;
		
	} // end if

	// If PIN is not correct, exits program
	else
	{
		puts("Exiting fundraiser app.");
		puts("Program exited with code: 0");
		return 0;
	} // end else

	// While loop to ask for size, color, credit card info, and recipt of customer(s)
	while (exit == false)
	{
		// If the user does not quit the program, continue to ask customer for selling info
		if (userSize != 'q' && userSize != 'Q')
		{
			userColor = tShirtColor(userColor);
			payment(priceAmount);
			finalPrice = totalPrice(priceAmount);
			amountToCharity = (double)finalPrice * charityPercentToDecimal;
			recipt(priceAmount, percentAmount, userSize, userColor, amountToCharity);
			

			userSize = tShirtSize(userSize);
			
		} // end if

		// If user wishes to quit, confirm by entering correct PIN number
		else
		{
			quitProgram = validPin(quitProgram);

			// If the PIN is correct, print the total sales and funds raised for charity
			if (quitProgram == 81405)
			{
				printf("Total shirt sales: $%.2f\n", (double)finalPrice);
				printf("Total amount raised for charity: $%.2f", amountToCharity);
				exit = true;
			} // end if

			// If the PIN was incorrect, continue to ask user for selling info
			else
			{
				userSize = tShirtSize(userSize);
			} // end else
		} // end else
	} // end while
	
	
	// Exit program
	return 0;
} // end main

// Function to get the valid pin from the user
int validPin(int pin) {

	// Initializing functions
	int counter = 0;
	int enterPin = 0;

	// Checks 3 times for if the PIN is correct
	// If PIN is incorrect 3 times exits program or continues to ask user for selling info
	while (counter < 3) 
	{
		puts("Enter pin:");
		enterPin = scanf("%d", &pin);
		while ((getchar()) != '\n');

		// Checks if PIN entered is invalid
		if (enterPin != 1)
		{
			counter += 1;
			puts("Invalid pin entered");
		} // end if

		// Checks if PIN is valid
		else if (pin == 81405)
		{
			// I need to fix this later...
			break;
		} // end else

		// If PIN is not correct, try again
		else
		{
			counter += 1;
			puts("Invalid pin entered");
		} // end else
	}// end while

	// Returns PIN to main
	return pin;
} // end of function


// Function to get the t-shirt price
int tShirtPrice(int price)
{

	// Initializing variables
	int enterPrice = 0;
	double priceFloat = 0;
	bool inputSuccess = false;
	char yesOrNo;

	puts("Enter the selling price of the t-shirt");

	// Asks for price until user confirms price
	while (inputSuccess == false)
	{
		// Asks for price
		enterPrice = scanf("%d", &price);

		// Clears the input buffer
		while ((getchar()) != '\n');

		// If the price is not an integer, input again
		if (enterPrice != 1)
		{
			puts("Invalid value entered for price");
			puts("Enter the selling price of the t-shirt");
		} // end if

		// If the price is negative, input again
		else if (price < 0)
		{
			puts("Price must be a positive number");
			puts("Enter the selling price of the t-shirt");
		} // end else if

		// If the price is valid, confirm price
		else if (enterPrice == 1)
		{
			// Turns the price into a decimal
			priceFloat = (double)price;

			printf("Is $%.2f the price of the shirt?\n", priceFloat);
			puts("Enter (y)es or (n)o");
			scanf(" %c", &yesOrNo);

			// Confirms if user wants to use price. Asks again if invalid input entered
			while (yesOrNo != 'y' && yesOrNo != 'Y' && yesOrNo != 'n' && yesOrNo != 'Y')
			{
				while ((getchar()) != '\n');
				puts("Invalid value entered. Enter (y)es or (n)o");
				scanf(" %c", &yesOrNo);
			} // end while
			if (yesOrNo == 'y' || yesOrNo == 'Y')
			{
				printf("Shirt price set to $%.2f\n" , priceFloat);
				inputSuccess = true;
			} // end if
			else if (yesOrNo == 'n' || yesOrNo == 'N')
			{
				puts("Enter the selling price of the t-shirt");
			} // end else if
		} // end else if
	} // end while

	// Returns price to main
	return price;
} // end of function


// Function to get the percent used for charity
int charityPercent(int percent)
{
    // Initializing variables
	int enterPercent = 0;
	bool inputSuccess = false;
	char yesOrNo;

	puts("Enter the fundraiser percentage of the t-shirt sales");

	// Gets the input from user and asks them to confirm it
	while (inputSuccess == false)
	{
		// Gets percent from user
		enterPercent = scanf("%d", &percent);
		while ((getchar()) != '\n');

		// If the percent is not an integer, try again
		if (enterPercent != 1)
		{
			puts("Invalid value entered for price");
			puts("Enter the fundraiser percentage of the t-shirt sales");
		} // end if

		// Is the percent is negative, try again
		else if (percent < 0 || percent > 100)
		{
			puts("Percent must be between 0 and 100");
			puts("Enter the fundraiser percentage of the t-shirt sales");
		} // end else if

		// If the percent is valid, confirm percent
		else if (enterPercent == 1)
		{
			printf("Is %d%% the correct fundraiser percentage?\n", percent);
			puts("Enter (y)es or (n)o");
			scanf(" %c", &yesOrNo);

			// Confirms if user wants to use percent. Asks again if invalid input entered
			while (yesOrNo != 'y' && yesOrNo != 'Y' && yesOrNo != 'n' && yesOrNo != 'Y')
			{
				while ((getchar()) != '\n');
				puts("Invalid value entered. Enter (y)es or (n)o");
				scanf(" %c", &yesOrNo);
			} // end while

			if (yesOrNo == 'y' || yesOrNo == 'Y')
			{
				printf("Fundraiser percent set to %d%%\n", percent);
				inputSuccess = true;
			} // end if

			else if (yesOrNo == 'n' || yesOrNo == 'N')
			{
				puts("Enter the fundraiser percentage of the t-shirt sales");
			} // end else if

		} // end else if
	} // end while
	return percent;
} // end of function

// Function to get the t-shirt size from the user
char tShirtSize(char size)
{
	// Initializing variables
	bool inputSuccess = false;
	
	// Asks for the users shirt size
	while (inputSuccess == false)
	{
		puts("Enter the shirt size (s)mall, (m)edium, (l)arge, or e(x)tra-large. Enter q to quit:");
		scanf(" %c", &size);
		while ((getchar()) != '\n');

		// Checks if the user entered a valid value
		switch (size)
		{
		// If s entered, set size to small
		case 'S':
		case 's':
			printf("Shirt size is %c\n", size);
			inputSuccess = true;
			break;

		// If m entered, set size to medium
		case 'M':
		case 'm':
			printf("Shirt size is %c\n", size);
			inputSuccess = true;
			break;

		// If l entered, set size to large
		case 'L':
		case 'l':
			printf("Shirt size is %c\n", size);
			inputSuccess = true;
			break;

		// If x entered, set size to extra large
		case 'X':
		case 'x':
			printf("Shirt size is %c\n", size);
			inputSuccess = true;
			break;

		// If q entered, quit program
		case 'Q':
		case 'q':
			inputSuccess = true;
			break;

		// If wrong input entered, ask user to try again
		default:
			puts("Invalid input entered.");
			break;
	
		} // end switch
	}// end while

	// Return size to main
	return size;
} // end of function

// Function to set color of t-shirt for user
char tShirtColor(char color)
{
	// Initializing variables
	bool inputSuccess = false;

	// Asks for color of user's shirt
	while (inputSuccess == false)
	{
		puts("Enter the shirt color (w)hite or (b)lack: ");
		scanf(" %c", &color);
		while ((getchar()) != '\n');

		// Checks if the user entered a valid value
		switch (color)
		{

		// If w entered, set color to white
		case 'w':
		case 'W':
			printf("Shirt color is %c\n", color);
			inputSuccess = true;
			break;

		// If b entered, set color to black
		case 'b':
		case 'B':
			printf("Shirt color is %c\n", color);
			inputSuccess = true;
			break;

		// If wrong input entered, have user try again
		default:
			puts("Invalid input entered.");
			break;
		} // end switch
	} // end while

	// Return color to main
	return color;
} // end of function

// Function to get the credit card info for payment
void payment(int price)
{
	// Initializing variables
	double priceDouble = 0;
	int counter = 0;
	int zipCode = 0;
	bool inputSuccess = false;
	priceDouble = (double)price;
	

	while (inputSuccess == false)
	{
		counter = 0;
		printf("Your cost is %.2f. Enter your zip code to complete payment\n", priceDouble);
		scanf("%d", &zipCode);

		// While loop to see if credit card number(zip code) is 5 digits
		while (zipCode != 0)
		{
			zipCode /= 10;
			counter++;
		} // end while

		if (counter == 5)
		{
			inputSuccess = true;
		} // end if
		else
		{
			puts("Zipcode must be 5 digits");
		} // end else
	} // end while

} // end of function

// Function to print out recipt
void recipt(const int price, const int percent, const char size, const char color, const double currentCharityAmount)
{
	// Initializing variables
	char yesOrNo;
	double priceDouble = 0;
	bool inputSuccessful = false;
	priceDouble = (double)price;
	srand( (unsigned int)time(NULL));

	
	while (inputSuccessful == false)
	{
		puts("Would you like your recipt? (Y)es or (N)o.");
		scanf(" %c", &yesOrNo);
		while ((getchar()) != '\n');
		switch (yesOrNo)
		{

		// If y entered, print recipt
		case 'y':
		case 'Y':
			printf("Recipt# %d\n", 1000 + (rand() % 9999));
			printf("T-Shirt   size:%c   color:%c   cost:$%.2f\n", size, color, priceDouble);
			printf("%d%% of your cost will be donated to charity.\n", percent);
			puts("Thank you for you support.");
			printf("Current amount raised for charity is %.2f\n", currentCharityAmount);
			inputSuccessful = true;
			break;

		// If n entered, do not print out recipt
		case 'N':
		case 'n':
			inputSuccessful = true;
			break;

		// If wrong value entered, have user try again
		default:
			puts("Invalid input entered");
			break;
		} // end switch
	} // end while
} // end of function


// Function to get total sales of shirts
int totalPrice(int price)
{

	static int addedPrices = 0;

	// Add the current price to the prices added together
	addedPrices += price;

	// return the added prices to main
	return addedPrices;
} // end of function

