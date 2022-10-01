#include "controller.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void test_createController() {
	Repository* r = createRepo();
	Controller* c = createController(r);
	assert(c != NULL);
	assert(c->repo != NULL);
	destroyController(c);
}

void test_addMaterialByName() {
	Repository* r = createRepo();
	Controller* c = createController(r);
	int add_result = addMaterialByName(c, "abc", "def", 6, 11, 11, 2011);
	assert(add_result == 1);
	assert(c->repo->materials->length == 1);
	assert(strcmp(getElement(c->repo, 0)->name, "abc") == 0);
	assert(strcmp(getElement(c->repo, 0)->supplier, "def") == 0);
	assert(getElement(c->repo, 0)->quantity == 6);
	destroyController(c);
}

void test_deleteMaterialByName() {
	Repository* r = createRepo();
	Controller* c = createController(r);
	int add_result = addMaterialByName(c, "abc", "def", 6, 11, 11, 2011);
	assert(add_result == 1);
	assert(getLength(r) == 1);
	deleteMaterialByName(c, "abc");
	assert(getLength(r) == 0);
	destroyController(c);
}

void test_updateMaterialByName() {
	Repository* r = createRepo();
	Controller* c = createController(r);
	int add_result = addMaterialByName(c, "abc", "def", 6, 11, 11, 2011);
	updateMaterialByName(c, "abc", "xyz", 1, 2, 4, 2000);
	assert(strcmp(getElement(c->repo, 0)->supplier, "xyz") == 0);
	assert(getElement(c->repo, 0)->quantity == 1);
	assert(getElement(c->repo, 0)->expiration_date->day == 2);
	assert(getElement(c->repo, 0)->expiration_date->month == 4);
	assert(getElement(c->repo, 0)->expiration_date->year == 2000);
	destroyController(c);
}

void test_getCurrentDate() {
	Date* current = getCurrentDate();
	time_t current_time = time(NULL);
	struct tm* current_date = localtime(&current_time);
	int day = current_date->tm_mday;
	int month = current_date->tm_mon + 1; // months start from 0
	int year = current_date->tm_year + 1900; // years start from 1900
	assert(current->day == day);
	assert(current->month == month);
	assert(current->year == year);
	destroyDate(current);
}

void test_isExpired() {
	Date* exp = createDate(11, 10, 1999);
	Date* curr = createDate(12, 10, 1999);
	assert(isExpired(exp, curr) == 1);
	destroyDate(exp);
	destroyDate(curr);

	exp = createDate(11, 10, 1999);
	curr = createDate(10, 10, 1999);
	assert(isExpired(exp, curr) == 0);
	destroyDate(exp);
	destroyDate(curr);

	exp = createDate(11, 10, 1999);
	curr = createDate(11, 11, 1999);
	assert(isExpired(exp, curr) == 1);
	destroyDate(exp);
	destroyDate(curr);

	exp = createDate(11, 11, 1999);
	curr = createDate(11, 10, 1999);
	assert(isExpired(exp, curr) == 0);
	destroyDate(exp);
	destroyDate(curr);

	exp = createDate(11, 11, 1999);
	curr = createDate(11, 11, 1999);
	assert(isExpired(exp, curr) == 0);
	destroyDate(exp);
	destroyDate(curr);

	exp = createDate(11, 11, 2000);
	curr = createDate(11, 11, 1999);
	assert(isExpired(exp, curr) == 0);
	destroyDate(exp);
	destroyDate(curr);

	exp = createDate(11, 11, 1999);
	curr = createDate(11, 11, 2000);
	assert(isExpired(exp, curr) == 1);
	destroyDate(exp);
	destroyDate(curr);
}

void test_copyDate() {
	Date* original = createDate(11, 10, 1999);
	Date* copy = copyDate(original);
	assert(original->day == copy->day);
	assert(original->month == copy->month);
	assert(original->year == copy->year);
	destroyDate(original);
	destroyDate(copy);
}

void test_copyMaterial() {
	Date* d = createDate(11, 11, 2011);
	Material* m = createMaterial("abc", "def", 5, d);

	Material* copy = copyMaterial(m);
	assert(strcmp(copy->name, m->name) == 0);
	assert(strcmp(copy->supplier, m->supplier) == 0);
	assert(copy->quantity, m->quantity);
	assert(copy->expiration_date->day == m->expiration_date->day);
	assert(copy->expiration_date->month == m->expiration_date->month);
	assert(copy->expiration_date->year == m->expiration_date->year);

	destroyMaterial(m);
	destroyMaterial(copy);
}

void test_filterExpiredByStringInName() {
	Repository* r = createRepo();
	Controller* c = createController(r);

	Date* d = createDate(11, 11, 2011);
	Material* m = createMaterial("abc", "def", 5, d);
	add(c->repo, m);

	Date* d1 = createDate(11, 11, 2099);
	Material* m1 = createMaterial("xyz", "qwe", 8, d1);
	add(c->repo, m1);

	assert(getLength(c->repo) == 2);
	Repository* filtered = filterExpiredByStringInName(c, "");
	assert(getLength(filtered) == 1);
	assert(strcmp(getElement(filtered, 0)->name, "abc") == 0);

	destroyRepo(filtered);
	destroyController(c);
}

void test_sortAscendingByQuantity() {
	Repository* repo = createRepo();
	assignRandomMaterials(repo);
	sortAscendingByQuantity(repo);
	for (int i = 0; i < repo->materials->length - 1; i++) {
		assert(getQuantity(repo->materials->elems[i]) <= getQuantity(repo->materials->elems[i + 1]));
	}
	destroyRepo(repo);
}

void test_areInOrderAscending() {
	int a = 1, b = 2;
	assert(areInOrderAscending(a, b) == 1);
	a = 2, b = 1;
	assert(areInOrderAscending(a, b) == 0);
	a = b = 1;
	assert(areInOrderAscending(a, b) == 1);
}

void test_areInOrderDescending() {
	int a = 1, b = 2;
	assert(areInOrderDescending(a, b) == 0);
	a = 2, b = 1;
	assert(areInOrderDescending(a, b) == 1);
	a = b = 1;
	assert(areInOrderDescending(a, b) == 1);
}

void test_sortByQuantityGeneric() {
	Repository* repo = createRepo();
	assignRandomMaterials(repo);

	sortByQuantityGeneric(repo, areInOrderAscending);
	for (int i = 0; i < repo->materials->length - 1; i++) {
		assert(getElement(repo, i)->quantity <= getElement(repo, i + 1)->quantity);
	}

	sortByQuantityGeneric(repo, areInOrderDescending);
	for (int i = 0; i < repo->materials->length - 1; i++) {
		assert(getElement(repo, i)->quantity >= getElement(repo, i + 1)->quantity);
	}

	destroyRepo(repo);
}

void test_filterInShortSupplyGeneric() {
	Repository* repo = createRepo();
	Controller* cont = createController(repo);
	assignRandomMaterials(repo);

	Repository* filtered = filterInShortSupplyGeneric(cont, getElement(repo, 0)->supplier, 
		1, areInOrderAscending);
	for (int i = 0; i < filtered->materials->length; i++) {
		assert(getElement(filtered, i)->quantity <= 1);
	}

	Repository* filtered2 = filterInShortSupplyGeneric(cont, getElement(repo, 0)->supplier,
		100, areInOrderDescending);
	for (int i = 0; i < filtered2->materials->length; i++) {
		assert(getElement(filtered2, i)->quantity <= 100);
	}

	destroyController(cont);
	destroyRepo(filtered);
	destroyRepo(filtered2);
}

void test_filterInShortSupply() {
	Repository* repo = createRepo();
	Controller* cont = createController(repo);

	assignRandomMaterials(cont->repo);
	double value = 1;
	Repository* filtered = filterInShortSupply(cont, getSupplier(cont->repo->materials->elems[0]), value);

	for (int i = 0; i < filtered->materials->length - 1; i++) {
		if (strcmp(getSupplier(filtered->materials->elems[i]),
			getSupplier(cont->repo->materials->elems[0])) == 0) {
			assert(getQuantity(filtered->materials->elems[i]) <= value);
		}
	}

	destroyController(cont);
	destroyRepo(filtered);
}

void test_hasShortName() {
	Repository* repo = createRepo();
	assignRandomMaterials(repo);
	for (int i = 0; i < repo->materials->length; i++) {
		if (strlen(getElement(repo, i)->name) <= 5) {
			assert(hasShortName(getElement(repo, i)) == 1);
		}
		else {
			assert(hasShortName(getElement(repo, i)) == 0);
		}
	}
	destroyRepo(repo);
}

void test_genericFilter() {
	Repository* repo1 = createRepo();
	Controller* cont = createController(repo1);
	assignRandomMaterials(cont->repo);

	Repository* repo = genericFilter(cont, hasShortName);
	for (int i = 0; i < repo->materials->length; i++) {
		if (strlen(getElement(repo, i)->name) <= 5) {
			assert(hasShortName(getElement(repo, i)) == 1);
		}
		else {
			assert(hasShortName(getElement(repo, i)) == 0);
		}
	}

	destroyController(cont);
	destroyRepo(repo);
}

void test_assignRandomMaterials() {
	Repository* r = createRepo();
	assignRandomMaterials(r);
	assert(r->materials->length == 10);
	for (int i = 0; i < r->materials->length; i++) {
		for (int j = i + 1; j < r->materials->length; j++) {
			assert(strcmp(getElement(r, i)->name, getElement(r, j)->name) != 0);
		}
	}
	destroyRepo(r);
}

// undo/redo tests below:

void test_copyRepository() {
	Repository* r1 = createRepo();
	assignRandomMaterials(r1);
	Repository* r2 = copyRepository(r1);
	for (int i = 0; i < getLength(r1); i++) {
		assert(getQuantity(r1->materials->elems[i]) == getQuantity(r1->materials->elems[i]));
		assert(strcmp(getName(r1->materials->elems[i]), getName(r1->materials->elems[i])) == 0);
		assert(strcmp(getSupplier(r1->materials->elems[i]), getSupplier(r1->materials->elems[i])) == 0);
	}
	assert(r1->materials->capacity == r2->materials->capacity);
	assert(r1->materials->length == r2->materials->length);
	destroyRepo(r1);
	destroyRepo(r2);
}

void test_addToUndo() {
	Repository* repo = createRepo();
	Controller* cont = createController(repo);

	assert(cont->undo_stack->length == 0);
	addToUndo(cont);
	assert(cont->undo_stack->length == 1);
	addToUndo(cont);
	assert(cont->undo_stack->length == 2);

	destroyController(cont);
}

void test_undo() {
	Repository* repo = createRepo();
	Controller* cont = createController(repo);

	assert(cont->undo_stack->length == 0);
	addToUndo(cont);
	assert(cont->undo_stack->length == 1);
	addToUndo(cont);
	assert(cont->undo_stack->length == 2);

	undo(cont);
	assert(cont->undo_stack->length == 1);
	undo(cont);
	assert(cont->undo_stack->length == 0);
	undo(cont);
	assert(cont->undo_stack->length == 0);

	destroyController(cont);
}

void test_clearRedo() {
	Repository* repo = createRepo();
	Controller* cont = createController(repo);

	assert(cont->redo_stack->length == 0);
	addToRedo(cont);
	assert(cont->redo_stack->length == 1);
	addToRedo(cont);
	assert(cont->redo_stack->length == 2);

	clearRedo(cont);
	assert(cont->redo_stack->length == 0);

	destroyController(cont);
}

void test_addToRedo() {
	Repository* repo = createRepo();
	Controller* cont = createController(repo);

	assert(cont->redo_stack->length == 0);
	addToRedo(cont);
	assert(cont->redo_stack->length == 1);
	addToRedo(cont);
	assert(cont->redo_stack->length == 2);

	destroyController(cont);
}

void test_redo() {
	Repository* repo = createRepo();
	Controller* cont = createController(repo);

	assert(cont->redo_stack->length == 0);
	addToRedo(cont);
	assert(cont->redo_stack->length == 1);
	addToRedo(cont);
	assert(cont->redo_stack->length == 2);

	redo(cont);
	assert(cont->redo_stack->length == 1);
	redo(cont);
	assert(cont->redo_stack->length == 0);
	redo(cont);
	assert(cont->redo_stack->length == 0);

	destroyController(cont);
}

void test_controller() {
	test_createController();
	test_addMaterialByName();
	test_deleteMaterialByName();
	test_updateMaterialByName();
	test_getCurrentDate();
	test_isExpired();
	test_copyDate();
	test_copyMaterial();
	test_filterExpiredByStringInName();
	test_sortAscendingByQuantity();
	test_areInOrderAscending();
	test_areInOrderDescending();
	test_sortByQuantityGeneric();
	test_filterInShortSupplyGeneric();
	test_filterInShortSupply();
	test_hasShortName();
	test_genericFilter();
	test_assignRandomMaterials();

	// undo/redo tests below:

	test_copyRepository();
	test_addToUndo();
	test_undo();
	test_clearRedo();
	test_addToRedo();
	test_redo();
}