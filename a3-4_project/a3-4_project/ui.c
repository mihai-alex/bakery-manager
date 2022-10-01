#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

UI* createUI(Controller* cont) {
	UI* ui = malloc(sizeof(UI));
	if (ui == NULL) {
		return NULL;
	}
	ui->cont = cont;
	return ui;
}

void destroyUI(UI* ui) {
	if (ui == NULL) {
		return;
	}
	destroyController(ui->cont);
	free(ui);
}

/*
	Reads an integer number from the keyboard. Asks for number while read errors encountered.
	Input: the message to be displayed when asking the user for input.
	Returns the number.
*/
int readIntegerNumber(const char* message) {
	char str[16] = { 0 };
	int res = 0;
	int flag = 0;
	int r = 0;
	while (flag == 0) {
		printf(message);
		int scanf_result = scanf("%15s", str);
		r = sscanf(str, "%d", &res); // reads data from str and stores them as integer, if possible
		flag = (r == 1); // returns 1 if successful
		if (flag == 0)
			printf("\nError reading number!\n");
	}
	return res;
}

/*
	Reads a real number from the keyboard. Asks for number while read errors encountered.
	Input: the message to be displayed when asking the user for input.
	Returns the number.
*/
double readRealNumber(const char* message) {
	char str[16] = { 0 };
	double res = 0;
	int flag = 0;
	int r = 0;
	while (flag == 0) {
		printf(message);
		int scanf_result = scanf("%15s", str);
		r = sscanf(str, "%lf", &res); // reads data from str and stores them as integer, if possible
		flag = (r == 1); // returns 1 if successful
		if (flag == 0)
			printf("\nError reading real value!\n");
	}
	return res;
}

void readString(const char* message, char* str) {
	printf(message);
	int scanf_result = scanf("%s", str);
	if (strcmp(str, "all") == 0) {
		str[0] = str[1] = str[2] = '\0';
	}
}

void readStringWithSpaces(const char* message, char* str) {
	printf(message);
	int scanf_result = scanf("%[^\n]", str);
}

int isValidSubcommand(subcommand) {
	if (subcommand >= 1 && subcommand <= 2) {
		return 1;
	}
	return 0;
}

int isValidCommand(command) {
	if (command >= 0 && command <= 8) {
		return 1;
	}
	return 0;
}

void addMaterialUI(UI* ui) {
	char name[50] = { 0 };
	char supplier[50] = { 0 };
	double quantity = { 0 };
	int day = 0, month = 0, year = 0;
	int scanf_result = 0;
	int was_added = 0;
	
	printf("Input the name: ");
	scanf_result = scanf("%49s", name);
	printf("Input the supplier: ");
	scanf_result = scanf("%49s", supplier);
	printf("Input the quantity: ");
	scanf_result = scanf("%lf", &quantity);
	printf("Input the expiration day: ");
	scanf_result = scanf("%d", &day);
	printf("Input the expiration month: ");
	scanf_result = scanf("%d", &month);
	printf("Input the expiration year: ");
	scanf_result = scanf("%d", &year);

	was_added = addMaterialByName(ui->cont, name, supplier, quantity, day, month, year);
	if (was_added == 0) {
		printf("\nThe material already exists! The new quantity was added to the old quantity.");
	}
	else {
		printf("\nThe material was added.");
	}
}

void deleteMaterialUI(UI* ui) {
	char name[50] = { 0 };
	int scanf_result = 0;
	int was_deleted = 0;

	printf("Input the name of the material to be deleted: ");
	scanf_result = scanf("%49s", name);

	was_deleted = deleteMaterialByName(ui->cont, name);
	if (was_deleted == 0) {
		printf("\nThe material does not exist, so it was not deleted!");
	}
	else {
		printf("\nThe material was deleted");
	}
}

void updateMaterialUI(UI* ui) {
	char name[50] = { 0 };
	char supplier[50] = { 0 };
	double quantity = { 0 };
	int day = 0, month = 0, year = 0;
	int scanf_result = 0;
	int was_updated = 0;

	printf("Input name of the material to be updated: ");
	scanf_result = scanf("%49s", name);
	printf("Input the updated supplier: ");
	scanf_result = scanf("%49s", supplier);
	printf("Input the updated quantity: ");
	scanf_result = scanf("%lf", &quantity);
	printf("Input the updated expiration day: ");
	scanf_result = scanf("%d", &day);
	printf("Input the updated expiration month: ");
	scanf_result = scanf("%d", &month);
	printf("Input the updated expiration year: ");
	scanf_result = scanf("%d", &year);

	was_updated = updateMaterialByName(ui->cont, name, supplier, quantity, day, month, year);
	if (was_updated == 0) {
		printf("\nThe material does not exist, so it was not updated!");
	}
	else {
		printf("\nThe material was updated.");
	}
}

void printRepository(Repository* repo) {
	char str[1000] = { 0 };
	printf("\n");
	for (int i = 0; i < getLength(repo); i++) {
		materialToString(getElement(repo, i), str);
		printf("%s\n\n", str);
	}
}

void listExpiredMaterialsUI(UI* ui, char* str) {
	Repository* expired = filterExpiredByStringInName(ui->cont, str);
	printRepository(expired);
	destroyRepo(expired);
}

void listShortNameMaterialsUI(UI* ui) {
	Repository* filtered = genericFilter(ui->cont, &hasShortName);
	printRepository(filtered);
	destroyRepo(filtered);
}

void listInShortSupplyUI(UI* ui, char* supplier, double value) {
	Repository* in_short_supply = filterInShortSupply(ui->cont, supplier, value);
	printRepository(in_short_supply);
	destroyRepo(in_short_supply);
}

void listInShortSupplyGenericUI(UI* ui, char* supplier, double value, int subcommand) {
	Repository* in_short_supply = NULL;
	if (subcommand == 1) {
		in_short_supply = filterInShortSupplyGeneric(ui->cont, supplier, value, 
			areInOrderAscending);
	}
	else if (subcommand == 2) {
		in_short_supply = filterInShortSupplyGeneric(ui->cont, supplier, value,
			areInOrderDescending);
	}
	printRepository(in_short_supply);
	destroyRepo(in_short_supply);
}

void listAllMaterialsUI(UI* ui) {
	printRepository(ui->cont->repo);
}

void printMenu() {
	printf("\n--------------------------------------------------------------------------------------\n");
	printf("Enter a command:\n");
	printf("\t1. add a material\n");
	printf("\t2. delete a material\n");
	printf("\t3. update a material\n");
	printf("\t4. filter (choose a criteria):\n");
	printf("\t\t1. list expired materials which have names that contain a given string\n");
	printf("\t\t\t-> input string \"all\" to list all expired materials regardless of name\n");
	printf("\t\t2. list materials which have short names (up to 5 characters)\n");
	printf("\t5. list all materials\n");
	printf("\t6. display all materials from a given supplier, which are in short supply\n");
	printf("\t   (quantity less than a given value). Choose sorting criteria by quantity:\n");
	printf("\t\t-> input a supplier, followed by a value \n");
	printf("\t\t\t1. Choose ascending sorting\n");
	printf("\t\t\t2. Choose descending sorting\n");
	printf("\t7. undo\n");
	printf("\t8. redo\n");
	printf("\t0. exit");
	printf("\n--------------------------------------------------------------------------------------\n");
}

void startUI(UI* ui) {
	assignRandomMaterials(ui->cont->repo);

	char str[100] = { 0 }, temp = 0;
	int command = 0, subcommand = 0, scanf_result = 0, undo_result = 0, redo_result = 0;
	double value = 0;

	while (1) {
		printMenu();
		command = readIntegerNumber("Input command: ");
		while (isValidCommand(command) == 0) {
			printf("Input a valid command!\n");
			command = readIntegerNumber("Input command: ");
		}
		if (command == 0) {
			break;
		}
		switch (command) {
		case 1:
			clearRedo(ui->cont);
			addToUndo(ui->cont);
			addMaterialUI(ui);
			break;
		case 2:
			clearRedo(ui->cont);
			addToUndo(ui->cont);
			deleteMaterialUI(ui);
			break;
		case 3:
			clearRedo(ui->cont);
			addToUndo(ui->cont);
			updateMaterialUI(ui);
			break;
		case 4:
			subcommand = readIntegerNumber("Input subcommand: ");
			while (isValidSubcommand(subcommand) == 0) {
				printf("Input a valid subcommand!\n");
				subcommand = readIntegerNumber("Input subcommand: ");
			}
			if (subcommand == 1) {
				readString("Input a string: ", str);
				listExpiredMaterialsUI(ui, str);
			}
			else if (subcommand == 2) {
				listShortNameMaterialsUI(ui);
			}
			break;
		case 5:
			listAllMaterialsUI(ui);
			break;
		case 6:
			// reading a throwaway char to clear the buffer, so that the double value 
			// can be successfully read next (because an int was previously read when
			// getting the command number)
			temp = 0;
			scanf_result = scanf("%c", &temp);

			readStringWithSpaces("Input a supplier: ", str);
			value = readRealNumber("Input a real value: ");

			subcommand = readIntegerNumber("Input subcommand: ");
			while (isValidSubcommand(subcommand) == 0) {
				printf("Input a valid subcommand!\n");
				subcommand = readIntegerNumber("Input subcommand: ");
			}

			listInShortSupplyGenericUI(ui, str, value, subcommand);
			break;
		case 7:
			undo_result = undo(ui->cont);
			if (undo_result == -1) {
				printf("\nThere is nothing to undo!\n");
			}
			break;
		case 8:
			redo_result = redo(ui->cont);
			if (redo_result == -1) {
				printf("\nThere is nothing to redo!\n");
			}
			break;
		}
	}
}