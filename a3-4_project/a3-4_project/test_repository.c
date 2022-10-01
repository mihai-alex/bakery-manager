#include "repository.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void test_createRepo() {
	Repository* r = createRepo();
	assert(r != NULL);
	assert(getLength(r) == 0);
	destroyRepo(r);
}

void test_find() {
	Repository* r = createRepo();

	Date* d = createDate(11, 11, 2011);
	Material* m = createMaterial("abc", "def", 5, d);
	add(r, m);
	Material* found = find(r, "abc");
	assert(found == m);

	Date* d1 = createDate(3, 7, 2000);
	Material* m1 = createMaterial("xyz", "klm", 25.5, d1);
	add(r, m1);
	Material* found1 = find(r, "xyz");
	assert(found1 == m1);

	Material* found2 = find(r, "ijk");
	assert(found2 == NULL);

	destroyRepo(r);
}

void test_findPosition() {
	Repository* r = createRepo();

	Date* d = createDate(11, 11, 2011);
	Material* m = createMaterial("abc", "def", 5, d);
	add(r, m);
	int pos = findPosition(r, "abc");
	assert(pos == 0);

	Date* d1 = createDate(3, 7, 2000);
	Material* m1 = createMaterial("xyz", "klm", 25.5, d1);
	add(r, m1);
	int pos1 = findPosition(r, "xyz");
	assert(pos1 == 1);

	int pos2 = findPosition(r, "ijk");
	assert(pos2 == -1);

	destroyRepo(r);
}

void test_add() {
	Repository* r = createRepo();

	Date* d = createDate(11, 11, 2011);
	Material* m = createMaterial("abc", "def", 5, d);
	int add_result = add(r, m);
	assert(add_result == 1);
	assert(getLength(r) == 1);
	Material* temp = find(r, "abc");
	assert(strcmp(getName(temp), "abc") == 0);
	assert(strcmp(getSupplier(temp), "def") == 0);
	assert(getQuantity(temp) == 5);
	assert(getExpirationDate(temp) == d);

	Date* d1 = createDate(3, 7, 2000);
	Material* m1 = createMaterial("xyz", "klm", 25.5, d1);
	int add_result2 = add(r, m1);
	assert(add_result2 == 1);
	assert(getLength(r) == 2);
	Material* temp1 = find(r, "xyz");
	assert(strcmp(getName(temp1), "xyz") == 0);
	assert(strcmp(getSupplier(temp1), "klm") == 0);
	assert(getQuantity(temp1) == 25.5);
	assert(getExpirationDate(temp1) == d1);

	destroyRepo(r);
}

void test_repository() {
	test_createRepo();
	test_find();
	test_findPosition();
	test_add();
}