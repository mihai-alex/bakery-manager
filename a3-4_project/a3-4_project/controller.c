#include "controller.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

Controller* createController(Repository* repo) {
	Controller* cont = (Controller*)malloc(sizeof(Controller));
	if (cont == NULL) {
		return NULL;
	}
	cont->repo = repo;
	cont->undo_stack = createDynamicArray(CAPACITY, destroyRepo);
	cont->redo_stack = createDynamicArray(CAPACITY, destroyRepo);
	return cont;
}

void destroyController(Controller* cont) {
	if (cont == NULL) {
		return;
	}
	destroyRepo(cont->repo);
	destroyDynamicArray(cont->undo_stack);
	destroyDynamicArray(cont->redo_stack);
	free(cont);
}

int addMaterialByName(Controller* cont, char* name, char* supplier, double quantity,
	int day, int month, int year) {
	Date* expiration_date = createDate(day, month, year);
	Material* m = createMaterial(name, supplier, quantity, expiration_date);
	int was_added = add(cont->repo, m);
	if (was_added == 0) {
		destroyMaterial(m);
	}
	return was_added;
}

int deleteMaterialByName(Controller* cont, char* name) {
	int index = findPosition(cont->repo, name);
	if (index == -1) {
		return 0;
	}
	destroyMaterial(getElement(cont->repo, index));
	for (int i = index; i < getLength(cont->repo) - 1; i++) {
		cont->repo->materials->elems[i] = cont->repo->materials->elems[i + 1];
	}
	cont->repo->materials->length--;
	return 1;
}

int updateMaterialByName(Controller* cont, char* name, char* supplier, double quantity,
	int day, int month, int year) {
	int index = findPosition(cont->repo, name);
	if (index == -1) {
		return 0;
	}
	destroyMaterial(getElement(cont->repo, index));
	Date* expiration_date = createDate(day, month, year);
	Material* new_material = createMaterial(name, supplier, quantity, expiration_date);
	cont->repo->materials->elems[index] = new_material;
	return 1;
}

Repository* getRepo(Controller* cont) {
	return cont->repo;
}

Date* getCurrentDate() {
	time_t current_time = time(NULL);
	struct tm* current_date = localtime(&current_time);
	int day = current_date->tm_mday;
	int month = current_date->tm_mon + 1; // months start from 0
	int year = current_date->tm_year + 1900; // years start from 1900
	return createDate(day, month, year);
}

int isExpired(Date* expiration_date, Date* current_date) {
	if (current_date->year > expiration_date->year) {
		return 1;
	}
	else if (current_date->year == expiration_date->year &&
		current_date->month > expiration_date->month) {
		return 1;
	}
	else if (current_date->year == expiration_date->year &&
		current_date->month == expiration_date->month &&
		current_date->day > expiration_date->day) {
		return 1;
	}
	return 0;
}

Date* copyDate(Date* d) {
	int day = d->day;
	int month = d->month;
	int year = d->year;
	Date* new_date = createDate(day, month, year);
	return new_date;
}

Material* copyMaterial(Material* m) {
	char name[100] = { 0 };
	strcpy(name, m->name);
	char supplier[100] = { 0 };
	strcpy(supplier, m->supplier);
	double quantity = m->quantity;
	Date* expiration_date = copyDate(m->expiration_date);
	Material* new_material = createMaterial(name, supplier, quantity, expiration_date);
	return new_material;
}

Repository* filterExpiredByStringInName(Controller* cont, char* str) {
	Date* current_date = getCurrentDate();
	Repository* result = createRepo();
	if (strlen(str) == 0) {
		for (int i = 0; i < getLength(cont->repo); i++) {
			if (isExpired(getElement(cont->repo, i)->expiration_date, current_date)) {
				Material* material_copy = copyMaterial(getElement(cont->repo, i));
				add(result, material_copy);
			}
		}
	}
	else {
		for (int i = 0; i < getLength(cont->repo); i++) {
			if (isExpired(getElement(cont->repo, i)->expiration_date, current_date) &&
				strstr(getElement(cont->repo, i)->name, str)) {
				Material* material_copy = copyMaterial(getElement(cont->repo, i));
				add(result, material_copy);
			}
		}
	}
	destroyDate(current_date);
	return result;
}

void sortAscendingByQuantity(Repository* repo) {
	for (int i = 0; i < getLength(repo) - 1; i++) {
		for (int j = i + 1; j < getLength(repo); j++) {
			if (getElement(repo, i)->quantity > getElement(repo, j)->quantity) {
				Material* temp = repo->materials->elems[i];
				repo->materials->elems[i] = repo->materials->elems[j];
				repo->materials->elems[j] = temp;
			}
		}
	}
}

int areInOrderAscending(double first, double second) {
	if (first <= second) {
		return 1;
	}
	return 0;
}

int areInOrderDescending(double first, double second) {
	if (first >= second) {
		return 1;
	}
	return 0;
}

void sortByQuantityGeneric(Repository* repo, CompareFunctionType areInOrder) {
	for (int i = 0; i < getLength(repo) - 1; i++) {
		for (int j = i + 1; j < getLength(repo); j++) {
			if (areInOrder(getElement(repo, i)->quantity, getElement(repo, j)->quantity) == 0) {
				Material* temp = repo->materials->elems[i];
				repo->materials->elems[i] = repo->materials->elems[j];
				repo->materials->elems[j] = temp;
			}
		}
	}
}

Repository* filterInShortSupplyGeneric(Controller* cont, char* supplier, double value, 
	CompareFunctionType areInOrder) {
	Repository* result = createRepo();
	for (int i = 0; i < getLength(cont->repo); i++) {
		if (getElement(cont->repo, i)->quantity < value &&
			strcmp(getElement(cont->repo, i)->supplier, supplier) == 0) {
			Material* material_copy = copyMaterial(getElement(cont->repo, i));
			add(result, material_copy);
		}
	}
	sortByQuantityGeneric(result, areInOrder);
	return result;
}

Repository* filterInShortSupply(Controller* cont, char* supplier, double value) {
	Repository* result = createRepo();
	for (int i = 0; i < getLength(cont->repo); i++) {
		if (getElement(cont->repo, i)->quantity < value &&
			strcmp(getElement(cont->repo, i)->supplier, supplier) == 0) {
			Material* material_copy = copyMaterial(getElement(cont->repo, i));
			add(result, material_copy);
		}
	}
	sortAscendingByQuantity(result);
	return result;
}

int isExpiredByStringInName(Material* m, char* str) {
	Date* current_date = getCurrentDate();
	if (strlen(str) == 0) {
		if (isExpired(m->expiration_date, current_date)) {
			destroyDate(current_date);
			return 1;
		}
	}
	else {
		if (isExpired(m->expiration_date, current_date) &&
			strstr(m->name, str)) {
			destroyDate(current_date);
			return 1;
		}
	}
	destroyDate(current_date);
	return 0;
}

int hasShortName(Material* m) {
	if (strlen(getName(m)) <= 5) {
		return 1;
	}
	return 0;
}

Repository* genericFilter(Controller* cont, FilterFunctionType toFilter) {
	Repository* result = createRepo();
	for (int i = 0; i < getLength(cont->repo); i++) {
		if (toFilter(getElement(cont->repo, i)) == 1) {
			Material* material_copy = copyMaterial(getElement(cont->repo, i));
			add(result, material_copy);
		}
	}
	sortAscendingByQuantity(result);
	return result;
}

void assignRandomMaterials(Repository* repo) {
	char name[100] = { 0 }, supplier[100] = { 0 };
	char names[20][25] = {
		"milk",
		"honey",
		"flour",
		"salt",
		"sugar",
		"cheese",
		"oil",
		"water",
		"glaze",
		"eggs",
		"vanilla",
		"chocolate",
		"peaches",
		"apples",
		"berries",
		"strawberries",
		"coconuts",
		"nuts",
		"almonds",
		"grapes"
	};
	char suppliers[20][25] = {
		"Maxi",
		"Lidl",
		"Carrefour",
		"Auchan",
		"Kaufland",
		"Profi",
		"Mega",
		"Pitar",
		"Dencopan",
		"Label",
		"Foods",
		"Campbell",
		"Warehouse",
		"Generic",
		"BBB",
		"Wonderbake",
		"Store",
		"Nameless",
		"Factory",
		"Penny"
	};
	srand(time(NULL));
	int counter = 0;
	while (counter < 10) {
		int was_added = 0;
		int day = rand() % 28 + 1; // day from 1 to 28
		int month = rand() % 12 + 1; // month from 1 to 12
		int year = rand() % 21 + 2010; // year from 2010 to 2030
		Date* date = createDate(day, month, year);
		double quantity = rand() % 1001; // quantity from 0 to 1000
		strcpy(name, names[rand() % 20]);
		strcpy(supplier, suppliers[rand() % 20]);
		Material* material = createMaterial(name, supplier, quantity, date);
		if (findPosition(repo, name) == -1) {
			add(repo, material);
			counter++;
		}
		else {
			destroyMaterial(material);
		}
	}
	return repo;
}

// undo/redo functionalities below:

Repository* copyRepository(Repository* repo) {
	Repository* repo_copy = createRepo();
	for (int i = 0; i < getLength(repo); i++) {
		Material* material_copy = copyMaterial(getElement(repo, i));
		add(repo_copy, material_copy);
	}
	return repo_copy;
}

void addToUndo(Controller* cont) {
	Repository* undo_element = copyRepository(cont->repo);
	addToDynamicArray(cont->undo_stack, undo_element);
}

int undo(Controller* cont) {
	if (cont->undo_stack->length == 0) {
		return -1; // nothing to undo!
	}
	addToRedo(cont);
	destroyRepo(cont->repo);
	cont->repo = copyRepository(cont->undo_stack->elems[cont->undo_stack->length - 1]);
	deleteFromDynamicArray(cont->undo_stack, cont->undo_stack->length - 1);
	return 1;
}

void clearRedo(Controller* cont) {
	destroyDynamicArray(cont->redo_stack);
	cont->redo_stack = createDynamicArray(CAPACITY, destroyRepo);
}

void addToRedo(Controller* cont) {
	Repository* redo_element = copyRepository(cont->repo);
	addToDynamicArray(cont->redo_stack, redo_element);
}

int redo(Controller* cont) {
	if (cont->redo_stack->length == 0) {
		return -1; // nothing to undo!
	}
	addToUndo(cont);
	destroyRepo(cont->repo);
	cont->repo = copyRepository(cont->redo_stack->elems[cont->redo_stack->length - 1]);
	deleteFromDynamicArray(cont->redo_stack, cont->redo_stack->length - 1);
	return 1;
}