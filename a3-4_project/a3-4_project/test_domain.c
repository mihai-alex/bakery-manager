#include "domain.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void test_createDate() {
	Date* d = createDate(10, 12, 2011);
	assert(getDay(d) == 10);
	assert(getMonth(d) == 12);
	assert(getYear(d) == 2011);
	destroyDate(d);
}

void test_dateToString() {
	Date* d = createDate(10, 12, 2011);
	char str[20] = { 0 };
	dateToString(d, str);
	assert(strcmp(str, "10/12/2011") == 0);
	destroyDate(d);
	d = createDate(1, 2, 1999);
	dateToString(d, str);
	assert(strcmp(str, "1/2/1999") == 0);
	destroyDate(d);
}

void test_createMaterial() {
	Date* d = createDate(10, 12, 2011);
	Material* m = createMaterial("abc", "def", 5, d);
	assert(strcmp(getName(m), "abc") == 0);
	assert(strcmp(getSupplier(m), "def") == 0);
	assert(getQuantity(m) == 5);
	assert(getDay(getExpirationDate(m)) == 10);
	assert(getMonth(getExpirationDate(m)) == 12);
	assert(getYear(getExpirationDate(m)) == 2011);
	destroyMaterial(m);
}

void test_materialToString() {
	Date* d = createDate(10, 12, 2011);
	Material* m = createMaterial("abc", "def", 5, d);
	char str[1000] = { 0 };
	materialToString(m, str);
	assert(strcmp(str, "Material properties:"
		"\n\t- name: abc\n\t- supplier: def\n\t- quantity: 5.00\n\t- expiration date: 10/12/2011") == 0);
	destroyMaterial(m);
}

void test_domain() {
	test_createDate();
	test_dateToString();

	test_createMaterial();
	test_materialToString();
}