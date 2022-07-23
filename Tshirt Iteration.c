// Jaylen McKinney CS2060
// Program that sells T-shirts for a fundraiser

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

// defining global variables
#define MIN_PRICE 20
#define MAX_PRICE 50
#define MIN_PERCENT 5
#define MAX_PERCENT 20
#define MAX_PIN_TRIES 4
#define CARD_NUMBER_LENGTH 20
#define PIN_NUMBER 81405
#define SIZE 50

// global file pointer
FILE* totalPtr;

// creating a struct to store the info of the fundraiser
typedef struct node
{
	double price;
	double priceTotal;
	double percent;
	double charityTotal;

	char* fundraiserName;
	struct node* nextPtr;

}Fundraiser;



// function prototypes
int validPin(int pin);
int fundraiserCounter(int count);
double validateFloat(int minimum, int maximum, const char *promptOne, const char *promptTwo);
char validateChar(const char* allowed, const char* prompt);
void insertNode(Fundraiser** headPtr, char* fundName, double fundPrice, double fundPercent);
void printLinkedList(Fundraiser* listPtr);
Fundraiser* getFundraiser(Fundraiser** headPtr, char *fundName);
void payment(Fundraiser * headPtr);
void totalPriceandPercent(Fundraiser **headPtr, Fundraiser *listPtr);
void receipt(Fundraiser** headPtr, const char size, const char color, char* fundName);
void totalToFile(Fundraiser** headPtr);



int main(void) {

	// initializing variables
	int pinNum = 0;
	int counter = 0;
	double priceAmount = 0;
	double percentAmount = 0;
	int quitProgram = 0;
	const char tShirtPricePromptOne[] = "Enter selling price for t - shirts.";
	const char tShirtPricePromptTwo[] = "Price";
	const char tShirtPercentPromptOne[] = "Enter percent of sales sent to charity";
	const char tShirtPercentPromptTwo[] = "Percent";
	const char tShirtSizePrompt[] = "Enter t-shirt size: (s)mall, (m)edium, (l)arge, e(x)tra-large. Enter q to quit";
	const char tShirtColorPrompt[] = "Enter t-shirt color: blac(k), (w)hite, (r)ed, (o)range, (b)lue, (p)urple.";
	char allowedSizes[] = { "smlxq" };
	char allowedColors[] = { "kwrobp" };
	char * nameOfFundraiser = NULL;
	char tShirtSize = 0;
	char tShirtColor = 0;
	bool exit = false;

	// nodes for linked list, currently pointing to NULL
	Fundraiser* firstPtr = NULL;
	Fundraiser* currentFundraiserPtr = NULL;

	
	

	

	// Jumps to validPin function. Sets pinNum equal to what validPin returns
	pinNum = validPin(pinNum);

	// Check if pinNum equals the required PIN
	if (pinNum == PIN_NUMBER)
	{
		puts("PIN Accepted");

		// Gets the number of fundraisers to be supported
		counter = fundraiserCounter(counter);
		
		for (int i = 1; i <= counter; i++)
		{
			// Allocates memory for nameOfFundraiser
			nameOfFundraiser = malloc(sizeof(char) * 100);

			printf("Enter name of fundraiser %d\n", i);
			scanf("%s", nameOfFundraiser);
			while ((getchar()) != '\n');

			// Jumps to validateFloat function for admin to input price or percent to charity
			priceAmount = validateFloat(MIN_PRICE, MAX_PRICE, tShirtPricePromptOne, tShirtPricePromptTwo);
			percentAmount = validateFloat(MIN_PERCENT, MAX_PERCENT, tShirtPercentPromptOne, tShirtPercentPromptTwo);

			// Insert current info into node of linked list
			insertNode(&firstPtr, nameOfFundraiser, priceAmount, percentAmount);
		}

		// Prints the supported fundraisers
		printLinkedList(firstPtr);
		


	} // end if

	// If PIN is not correct, exits program
	else
	{
		puts("Exiting fundraiser app.");
		puts("Program exited with code: 0");
		return 0;
	} // end else

	// While loop to ask for size, color, credit card info, and receipt of customer(s)
	while (exit == false)
	{
		// While list is empty, ask user for fundraiser they would like to support
		while (currentFundraiserPtr == NULL)
		{ 
			nameOfFundraiser = malloc(sizeof(char) * 100);
			puts("Enter the name of the fundraiser you would like to support.");
			scanf("%s", nameOfFundraiser);
			while ((getchar()) != '\n');
			currentFundraiserPtr = getFundraiser(&firstPtr, nameOfFundraiser);
		}
		
		// Gets the size of the t-shirt
		tShirtSize = validateChar(allowedSizes, tShirtSizePrompt);

		// If the user does not quit the program, continue to ask customer for selling info
		if (tShirtSize != 'q' && tShirtSize != 'Q')
		{
			// Jumps to validateChar function for customer to enter color of shirt
			tShirtColor = validateChar(allowedColors, tShirtColorPrompt);

			// Jumps to payment function
			payment(currentFundraiserPtr);

			// totalPrice function return all prices added up and stores it in finalPrice
			totalPriceandPercent(&firstPtr, currentFundraiserPtr);

			

			// Asks user if they want receipt
			receipt(&firstPtr, tShirtSize, tShirtColor, nameOfFundraiser);

			// Resets currentFundraiserPtr for next fundraiser
			currentFundraiserPtr = NULL;
		} // end if

		// If user wishes to quit, confirm by entering correct PIN number
		else
		{
			quitProgram = validPin(quitProgram);

			// If the PIN is correct, print the total sales and funds raised for charity to a file
			if (quitProgram == PIN_NUMBER)
			{
				totalToFile(&firstPtr);
				exit = true;
			} // end if
			else
			{
				// Resets currentFundraiserPtr for next fundraiser
				currentFundraiserPtr = NULL;
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
	bool inputSuccess = false;

	// Checks 3 times for if the PIN is correct
	// If PIN is incorrect 4 times exits program or continues to ask user for selling info
	while (counter < MAX_PIN_TRIES && inputSuccess == false)
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
		else if (pin == PIN_NUMBER)
		{
			inputSuccess = true;
		} // end else

		// If PIN is not correct, try again and increment counter
		else
		{
			counter += 1;
			puts("Invalid pin entered");
		} // end else

	}// end while

	// Returns PIN to main
	return pin;
} // end of function



// Function to get number of fundraisers supported
int fundraiserCounter(int count)
{
	// Initializing variables
	bool inputSuccess = false;
	int enterCount = 0;

	// Checks if input was valid or invalid
	while (inputSuccess == false)
	{
		puts("Enter number of fundraisers");
		enterCount = scanf("%d", &count);
		while ((getchar()) != '\n');

		// If invalid, display error message
		if (enterCount != 1)
		{
			puts("Invalid value entered");
		} // end if

		// If negative, display error message
		else if (count < 0)
		{
			puts("Value must be positive.");
		} // end else if

	
		else if (enterCount == 1)
		{
			inputSuccess = true;
		}  // end else if

	} // end while

	// Return count to main
	return count;
} // end of function

// Function that gets a valid price or percent to charity from admin
double validateFloat(int minimum, int maximum, const char *promptOne, const char *promptTwo)
{
	// Initializing variables
	char userInput[SIZE];
	double value = 0;
	bool valid = false;
	char yesOrNo = 0;
	
	// Gets an input from the admin
	puts(promptOne);
	printf("Value must be between %d and %d\n", minimum, maximum);
	fgets(userInput, SIZE, stdin);

	// While the inputs are invalid, continue to loop until valid input found
	while (valid == false)
	{

		// Converts the string input into a decimal
		value = strtod(userInput, NULL);

		// Checks to see if the admin's input was within range
		if (value >= minimum && value <= maximum)
		{
			puts("Is this correct? Enter (Y)es or (N)o.");
			scanf(" %c", &yesOrNo);
			while ((getchar()) != '\n');
			switch (yesOrNo)
			{

			// If y entered, return value
			case 'y':
			case 'Y':
				printf("%s set to %.2f\n", promptTwo, value);
				valid = true;
				break;
				// If n entered, ask for value again
			case 'N':
			case 'n':
				puts(promptOne);
				printf("Value must be between %d and %d\n", minimum, maximum);
				fgets(userInput, SIZE, stdin);
				break;
				// If wrong value entered, have user try again
			default:
				puts("Invalid input entered");
				break;
			} // end switch

		} // end if
		else
		{
		printf("Invalid value entered.\nValue must be between %d and %d.\n", minimum, maximum);
		fgets(userInput, SIZE, stdin);
		} // end else

	} // end while

	return value;

} // end of function



// Function to insert current information into a linked list
void insertNode(Fundraiser** headPtr, char* fundName, double fundPrice, double fundPercent)
{
	// Allocating memory
	Fundraiser* nodePtr = malloc(sizeof(Fundraiser));

	// If memory was successfully allocated
	if (nodePtr != NULL)
	{
		// Store these values in the node
		nodePtr->fundraiserName = fundName;
		nodePtr->price = fundPrice;
		nodePtr->percent = fundPercent;
		nodePtr->priceTotal = 0;
		nodePtr->charityTotal = 0;
		nodePtr->nextPtr = NULL;

		// Create pointers for the current and previous nodes
		Fundraiser* previousPtr = NULL;
		Fundraiser* currentPtr = *headPtr;

		// Sorts the list in alphabetical order
		while (currentPtr != NULL && strcmp(currentPtr->fundraiserName, fundName) < 0)
		{
			// moves on to the next node
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		} // end while

		// Inserts first node
		if (previousPtr == NULL)
		{
			*headPtr = nodePtr;
		} // end if

		else
		{
			// set previousPtr to point to current node
			previousPtr->nextPtr = nodePtr;

		} // end else

		// Puts node into list
		nodePtr->nextPtr = currentPtr;
	} // end if

	// Memory allocation failed
	else
	{
		puts("No memory was allocated");
	} // end else
} // end of function



// Function to print out the linked list
void printLinkedList(Fundraiser* listPtr)
{
	// If the linked list is not empty
	if (listPtr != NULL)
	{
		// currentPtr set to first node in list
		Fundraiser* currentPtr = listPtr;
		puts("Fundraiser details:");

		// Loop through linked list until NULL is found
		while (currentPtr != NULL)
		{
			// Print out info and move to next node
			printf("Name: %s\n Price of t-shirt: $%.2f\n Percent to charity: %.1f%%\n\n", currentPtr->fundraiserName, currentPtr->price, currentPtr->percent);
			currentPtr = currentPtr->nextPtr;
		} // end while
		puts("");
	} // end if


	// linked list is empty
	else
	{
		puts("List is empty");
	} // end else

} // end of function



// Function to get the fundraiser that the customer chose
Fundraiser* getFundraiser(Fundraiser** headPtr, char* fundName)
{
	// Pointers to figure out where correct fundraiser is
	Fundraiser* previousPtr = NULL;
	Fundraiser* currentPtr = *headPtr;
	
	// If the fundraiser name and linked list name match, display info
	if (currentPtr != NULL && strcmp(currentPtr->fundraiserName, fundName) == 0)
	{
		puts("--------T-shirt Fundraiser--------");
		printf("Buy a shirt and %.1f will go to %s.\n", currentPtr->percent, currentPtr->fundraiserName);
		printf("Shirt price is $%.2f.\n", currentPtr->price);
	} // end if


	else
	{
		// Go through list until match is found
		while (currentPtr != NULL && strcmp(currentPtr->fundraiserName, fundName) != 0)
		{
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		} // end while

		// If match is found, display info
		if (currentPtr != NULL)
		{
			puts("--------T-shirt Fundraiser--------");
			printf("Buy a shirt and %.1f will go to %s.\n", currentPtr->percent, currentPtr->fundraiserName);
			printf("Shirt price is $%.2f.\n", currentPtr->price);
		} // end if

		// Fundraiser was not found
		else
		{
			puts("Fundraiser not found.");
			return NULL;
		} // end else
	} // end else

	return currentPtr;

}


// Function that gets a valid shirt color or size from customer
char validateChar(const char* allowed, const char* prompt)
{

	// Initializing variables
	char letter = 0;
	bool valid = false;

	// While the inputs are invalid, continue to loop until valid input found
	while (valid == false)
	{
		// Prompts user to enter character
		puts(prompt);
		scanf("%c", &letter);

		// Clearing the input buffer
		while ((getchar()) != '\n');

		// Searches for the correct character with the given string and user's input. If not found, valid is set to false
		valid = strchr(allowed, tolower(letter)) != NULL;

		// Outputs error message
		if (valid == false)
		{
			puts("Invalid input entered");
		} // end if
	} // end while

	return letter;
} // end of function





// Function to accept payment from customer
void payment(Fundraiser* headPtr)
{
	// Initializing variables
	int validCardNumber = 0;
	int creditCardPart1 = 0;
	int creditCardPart2 = 0;
	int creditCardPart3 = 0;
	int creditCardPart4 = 0;
	char creditCard[50] = "";
	bool inputSuccess = false;

	// If list is not empty
	if (headPtr != NULL)
	{
		// Point to first node in list
		Fundraiser* currentPtr = headPtr;

		// Loops until valid credit card number entered
		while (inputSuccess == false)
		{
			printf("Your cost is $%.2f. Enter your credit card number(####-####-####-####) to complete payment\n", currentPtr->price);

			// Gets the credit card number from the user
			fgets(creditCard, sizeof(creditCard), stdin);

			// Removes the new line character from string
			creditCard[strlen(creditCard) - 1] = '\0';

			// Checks to see if the user inputted the credit card number in the correct format
			validCardNumber = sscanf(creditCard, "%d-%d-%d-%d", &creditCardPart1, &creditCardPart2, &creditCardPart3, &creditCardPart4);

			// If the credit card number is formatted correctly, accept the value
			if (validCardNumber == 4 && strlen(creditCard) == CARD_NUMBER_LENGTH - 1)
			{
				puts("Credit card accepted");
				inputSuccess = true;
			} // end if

			// else output error message
			else
			{
				puts("Invalid value entered");

			} // end else


		} // end while
		
	}
	// linked list is empty
	else
	{
		puts("Node is empty");
	}
	// Loops until credit card number is in correct format
		
}// end of function



// Function to get total sales of shirts
void totalPriceandPercent(Fundraiser** headPtr, Fundraiser* listPtr)
{
	Fundraiser* previousPtr = NULL;
	Fundraiser* currentPtr = *headPtr;
	double charityPercentToDecimal = 0;

	if (currentPtr != NULL && listPtr != NULL)
	{
		charityPercentToDecimal = listPtr->percent / 100;
		if (strcmp(currentPtr->fundraiserName, listPtr->fundraiserName) == 0)
		{
			currentPtr->priceTotal = currentPtr->priceTotal + listPtr->price;
			currentPtr->charityTotal = listPtr->price * charityPercentToDecimal;
		}
		else
		{
			while (currentPtr != NULL && strcmp(currentPtr->fundraiserName, listPtr->fundraiserName) != 0)
			{
				previousPtr = currentPtr;
				currentPtr = currentPtr->nextPtr;
			}
			if (currentPtr != NULL)
			{
				currentPtr->priceTotal = currentPtr->priceTotal + listPtr->price;
				currentPtr->charityTotal = listPtr->price * charityPercentToDecimal;
			}
			else
			{
				puts("Node not found.");
			}
		}
	}

} // end of function





// Function to print out receipt
void receipt(Fundraiser** headPtr, const char size, const char color, char* fundName)
{
	// Creates a file to append all the receipts to
	char path[] = "C:\\Users\\jaken\\OneDrive\\Desktop\\CS2060\\tshirtapp\\receipt.txt";
	totalPtr = fopen(path, "a");

	// points to previous and current node
	Fundraiser* previousPtr = NULL;
	Fundraiser* currentPtr = *headPtr;

	
	// Initializing variables
	char yesOrNo;
	bool inputSuccessful = false;
	srand((unsigned int)time(NULL));
	int randomNumber = 1000+(rand()%9999);

	// Loops until user decides whether or not they want receipt
	while (inputSuccessful == false)
	{
		puts("Would you like your receipt? (Y)es or (N)o.");
		scanf(" %c", &yesOrNo);
		while ((getchar()) != '\n');
		switch (yesOrNo)
		{

			// If y entered, print receipt
		case 'y':
		case 'Y':
			//Checks if list is empty and finds match with name
			if (currentPtr != NULL && strcmp(currentPtr->fundraiserName, fundName) == 0)
			{
				printf("receipt# %d\n", randomNumber);
				printf("T-Shirt   size:%c   color:%c   cost:$%.2f\n", size, color, currentPtr->price);
				printf("%.1f%% of your cost will be donated to charity.\n", currentPtr->percent);
				puts("Thank you for you support.");
				printf("Current amount raised for charity is $%.2f\n", currentPtr->charityTotal);
		
			} // end if

			else
			{
				// Goes through list until a match is found
				while (currentPtr != NULL && strcmp(currentPtr->fundraiserName, fundName) != 0)
				{
					previousPtr = currentPtr;
					currentPtr = currentPtr->nextPtr;
				} // end while

				// If a match is found, display the info
				if (currentPtr != NULL)
				{
					printf("receipt# %d\n", randomNumber);
					printf("T-Shirt   size:%c   color:%c   cost:$%.2f\n", size, color, currentPtr->price);
					printf("%.1f%% of your cost will be donated to charity.\n", currentPtr->percent);
					puts("Thank you for you support.");
					printf("Current amount raised for charity is $%.2f\n", currentPtr->charityTotal);
			
				} // end if

				// list is empty
				else
				{
					puts("Fundraiser not found.");
			
				} // end else

				
			} // end else

			// Exits loop
			inputSuccessful = true;

			break;

			// If n entered, do not print out receipt
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

	// Outputs error message if file does not exist
	if (totalPtr == NULL)
	{
		puts("File could not be created");
	} // end if

	// Prints the receipt to file and then closes file
	else if(currentPtr != NULL)
	{
		fprintf(totalPtr, "%s %d\n", "Receipt#", randomNumber);
		fprintf(totalPtr, "%s %s %c %s %c %s %.2f\n", "T-Shirt", "size:", size, "color:", color, "cost:", currentPtr->price);
		fprintf(totalPtr, "%.1f %s\n", currentPtr->percent, "% of your cost will be donated to charity.");
		fprintf(totalPtr, "%s\n", "Thank you for your support!");
		fprintf(totalPtr, "%s %.2f\n\n", "Current amount raised for charity is $", currentPtr->charityTotal);

		printf("Printed to file %s\n", path);
		fclose(totalPtr);
	} // end else

	// list is empty
	else
	{
		puts("List is empty.");
		fclose(totalPtr);
	} // end else
	

} // end of function






// Function to output the total sales of each fundraiser to a file
void totalToFile(Fundraiser** headPtr)
{
	// points to previous and current node
	Fundraiser* previousPtr = NULL;
	Fundraiser* currentPtr = *headPtr;

	// Creates a file to write to
	char path[] = "C:\\Users\\jaken\\OneDrive\\Desktop\\CS2060\\tshirtapp\\tshirtfund.txt";
	totalPtr = fopen(path, "w");

	// The file was not created
	if (totalPtr == NULL)
	{
		puts("File could not be created");
	} // end if

	// Checks if list is not empty
	else if (currentPtr != NULL)
	{
		// Prints the receipt to file and then closes file
		while (currentPtr != NULL)
		{
			printf("Total sales of %s fundraiser: $%.2f\n", currentPtr->fundraiserName, currentPtr->priceTotal);
			printf("Total amount raised to charity: $%.2f\n\n", currentPtr->charityTotal);

			fprintf(totalPtr, "%s %s %s %.2f\n", "Total sales of ", currentPtr->fundraiserName, " fundraiser: $", currentPtr->priceTotal);
			fprintf(totalPtr, "%s %.2f\n\n", "Total amount raised to charity: $", currentPtr->charityTotal);
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
			
		} // end while
		fclose(totalPtr);
	} // end else if
	
	// list is empty
	else
	{
		puts("List is empty.");
		fclose(totalPtr);
	} // end else
	
} // end of function