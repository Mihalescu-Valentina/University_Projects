#include "UI.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include"Repository.h"


UI* createUI(Repository* r)
{
	UI* ui = (UI*)malloc(sizeof(UI));
	ui->repo = r;

	return ui;
}



void destroyUI(UI* ui)
{
	// first destroy the Repo
	destroy_repo(ui->repo);
	// free the UI memory
	free(ui);
}

/*
	Prints the available menu for the problem
	Input: -
	Output: the menu is printed at the console
*/
void printMenu()
{
	printf("\n**********************************************************\n");
	printf("1 - add an offer.\n");
	printf("2 - remove an offer.\n");
	printf("3 - update an offer.\n");
	printf("4 - list all the offers.\n");
	printf("5 -display all the tourism offers that contain a certain string.\n");
	printf("0 - to exit.\n");
	printf("\n**********************************************************\n");
}

/*
	Verifies if the given command is valid (is either 1, 2, 3,4 or 0)
	Input: command - integer
	Output: 1 - if the command is valid
	0 - otherwise
*/
int validCommand(int command)
{
	if (command >= 0 && command <= 6)
		return 1;
	return 0;
}

/*
	Reads an integer number from the keyboard. Asks for number while read errors encoutered.
	Input: the message to be displayed when asking the user for input.
	Returns the number.
*/
int readIntegerNumber(const char* message)
{
	char s[16];
	int res = 0;
	int flag = 0;
	int r = 0;

	while (flag == 0)
	{
		printf(message);
		scanf("%s", s);

		r = sscanf(s, "%d", &res);	// reads data from s and stores them as integer, if possible; returns 1 if successful
		flag = (r == 1);
		if (flag == 0)
			printf("Error reading number!\n");
	}
	return res;
}

/*
	Reads a string with spaces from the standard input.
	Input:	message - string, message to be shown to the user.
			maxStrSize - the maximum size for the string to be read
	Output: the string that was read.
*/
void readStringWithSpaces(const char* message, int maxStrSize, char str[])
{
	printf(message);
	fgets(str, maxStrSize, stdin);
	// the newline is also read so we must eliminate it from the string
	size_t size = strlen(str) - 1;
	if (str[size] == '\n')
		str[size] = '\0';
}

int add_offer_UI(UI* ui)
{
	// read the offer's data
	char destination[50], type[50],date[50];
	int price;

	fgetc(stdin); // read the newline, to prevent it from going further to fgets
	readStringWithSpaces("Please input the type of the offer: ", 50, type);
	readStringWithSpaces("Please input the destination: ", 50, destination);
	readStringWithSpaces("Please input the departure date using the format dd-mm-yyyy: ", 50, date);
	printf("Please input the price (in euros): ");
	scanf("%d", &price);

	Offer *offer = create_offer(type, destination, date, price);
	return add_offer_repo(ui->repo, offer);
}




int update_offer_ui(UI *ui)
{
	char destination[50], type[50], date[50],destination_init[50],date_init[50];
	int price;

	fgetc(stdin); // read the newline, to prevent it from going further to fgets
	readStringWithSpaces("Please input the initial destination of the offer: ", 50, destination_init);
	readStringWithSpaces("Please input the initial departure date of the offer: ", 50, date_init);
	readStringWithSpaces("Please input the type of the offer: ", 50, type);
	readStringWithSpaces("Please input the destination: ", 50, destination);
	readStringWithSpaces("Please input the departure date using the format dd-mm-yyyy: ", 50, date);
	printf("Please input the price (in euros): ");
	scanf("%d", &price);
	

	//Offer* offer = create_offer(type, destination, date, price);
	return update_offer_repo(ui->repo, destination_init,date_init,type,destination,date,price);
}



int delete_offer_UI(UI* ui)
{
	// read the offer's data
	char destination[50], type[50], date[50];
	int price;

	fgetc(stdin); // read the newline, to prevent it from going further to fgets
	readStringWithSpaces("Please input the destination: ", 50, destination);
	readStringWithSpaces("Please input the departure date using the format dd-mm-yyyy: ", 50, date);

	//Offer* offer = create_offer(type, destination, date, price);
	return delete_offer_repo(ui->repo, destination,date);
}

void put_offers(UI *ui)
{   
	Offer* o1 = create_offer("mountain", "China", "09-08-2022", 1000);
	//printf("%s", o1->type);
	add_offer_repo(ui->repo, o1);
	//printf("%d",get_price(get_offer_on_pos(ui->repo, 0)));
	Offer* o2 = create_offer("seaside", "Roma", "04-06-2022", 2006);
	add_offer_repo(ui->repo, o2);
	Offer* o3 = create_offer("mountain", "Washington", "05-08-2022", 900);
	add_offer_repo(ui->repo, o3);
	Offer* o4 = create_offer("city break", "Torino", "05-02-2022", 888);
	add_offer_repo(ui->repo, o4);
	Offer* o5 = create_offer("seaside", "Peru", "12-02-2022", 600);
	add_offer_repo(ui->repo, o5);
	Offer* o6 = create_offer("city break", "Ukraine", "01-02-2022", 100);
	add_offer_repo(ui->repo, o6);



}



void listAllOffers(UI* ui)
{
	if (ui == NULL)
		return;
	Repository* repo = ui->repo;
	int length = length_repo(repo);
	for (int i = 0; i < length; i++)
	{
		Offer* offer = get_offer_on_pos(repo,i);
		char offerString[500];
		//toString(offer, offerString);
		//printf("alo");
		printf("%s %s %s %d \n", offer->type, offer->destination, offer->date, offer->price);
		//printf("%s\n", offerString);
	}
}

void contain_string(UI* ui, char* string)
{
	if (ui == NULL)
		return;

	//printf("%d", repo->v->capacity);
	for (int i = 0; i < length_repo(ui->repo); i++)
	{
		Offer* offer = get_offer_on_pos(ui->repo, i);
		if (strcmp(string, "") != 0 && (strstr(get_type(get_offer_on_pos(ui->repo, i)), string) != NULL || strstr(get_date(get_offer_on_pos(ui->repo, i)), string) != NULL || strstr(get_destination(get_offer_on_pos(ui->repo, i)), string) != NULL))
		{
			printf("%s %s %s %d \n", offer->type, offer->destination, offer->date, offer->price);

		}
		else
			if (strcmp(string, "") == 0)
			{
				sort_vector(ui->repo->v);
				listAllOffers(ui);
				break;

			}



	}

}

/*int undoUI(UI* ui)
{
	return undo(ui->repo);
}*/

void startUI(UI* ui)
{
	put_offers(ui);
	while (1)
	{
		printMenu();
		
		

		int command = readIntegerNumber("Input command: ");
		

		//printf("% d", command);
		
		while (validCommand(command) == 0)
		{
			printf("Please input a valid command!\n");
			command = readIntegerNumber("Input command: ");
		}
		if (command == 0)
			break;
		switch (command)
		{
		case 1:
		{

			int res = add_offer_UI(ui);
			if (res == 1)
				printf("Offer successfully added.\n");
			else
				printf("Error! Offer could not be added, as there is another offer with the same symbol combination!\n");
			break;
		}
		case 2:
		{
			
			int ok=delete_offer_UI(ui);
			if (ok == -1) 
				printf("This element does not exist!");
			break;
		}
		case 3:
		{    
		
			update_offer_ui(ui);
			//listAllOffers(ui);
			break;
		}
		case 4:
		{
			listAllOffers(ui);
			break;
		}

		case 5:
		{    
			char string[50];
			fgetc(stdin); // read the newline, to prevent it from going further to fgets
			readStringWithSpaces("Please input the string: ", 50, string);
			contain_string(ui,string);
			//listAllOffers(ui);
			break;
		}
		}
	}
}