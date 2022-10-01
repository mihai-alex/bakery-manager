#include "dynamic_array.h"
#include "domain.h"
#include <assert.h>
#include <stdlib.h>

void test_createDynamicArray() {
	DynamicArray* da = createDynamicArray(10, &destroyMaterial);
	assert(da->length == 0);
	assert(da->capacity == 10);
	destroyDynamicArray(da);
}

void test_resizeDynamicArray() {
	DynamicArray* da = createDynamicArray(10, &destroyMaterial);
	assert(da->length == 0);
	assert(da->capacity == 10);
	resizeDynamicArray(da);
	assert(da->length == 0);
	assert(da->capacity == 20);
	resizeDynamicArray(da);
	assert(da->length == 0);
	assert(da->capacity == 40);
	destroyDynamicArray(da);
}

void test_addToDynamicArray() {
	DynamicArray* da = createDynamicArray(10, &destroyMaterial);
	char str[2] = { 0 };
	str[0] = 'a';
	for (int i = 0; i < 21; i++) {
		Date* d = createDate(i+1, 11, 2011);
		Material* m = createMaterial(str, "def", 5, d);
		addToDynamicArray(da, m);
		str[0] += i;
	}
	assert(da->length == 21);
	assert(da->capacity == 40);
	destroyDynamicArray(da);
}

void test_deleteFromDynamicArray() {
	DynamicArray* da = createDynamicArray(10, &destroyMaterial);
	Date* d = createDate(1, 11, 2011);
	Material* m = createMaterial("abc", "def", 5, d);

	deleteFromDynamicArray(da, 15);
	deleteFromDynamicArray(da, -1);

	addToDynamicArray(da, m);
	assert(da->length == 1);
	deleteFromDynamicArray(da, 0);
	assert(da->length == 0);

	destroyDynamicArray(da);
}

void test_getLengthDynamicArray() {
	DynamicArray* da = createDynamicArray(10, &destroyMaterial);

	Date* d = createDate(1, 11, 2011);
	Material* m = createMaterial("abc", "def", 5, d);

	Date* d1 = createDate(1, 1, 2010);
	Material* m1 = createMaterial("fgh", "dty", 4, d1);

	assert(getLengthDynamicArray(da) == 0);
	addToDynamicArray(da, m);
	assert(getLengthDynamicArray(da) == 1);
	addToDynamicArray(da, m1);
	assert(getLengthDynamicArray(da) == 2);
	deleteFromDynamicArray(da, 0);
	assert(getLengthDynamicArray(da) == 1);
	deleteFromDynamicArray(da, 0);
	assert(getLengthDynamicArray(da) == 0);

	destroyDynamicArray(da);
}

void test_getCapacityDynamicArray() {
	DynamicArray* da = createDynamicArray(10, &destroyMaterial);
	assert(getCapacityDynamicArray(da) == 10);
	char str[2] = { 0 };
	str[0] = 'a';
	for (int i = 0; i < 21; i++) {
		Date* d = createDate(i + 1, 11, 2011);
		Material* m = createMaterial(str, "def", 5, d);
		addToDynamicArray(da, m);
		str[0] += i;
	}
	assert(getCapacityDynamicArray(da) == 40);
	destroyDynamicArray(da);
}

void test_getElementDynamicArray() {
	DynamicArray* da = createDynamicArray(10, &destroyMaterial);

	Date* d = createDate(1, 11, 2011);
	Material* m = createMaterial("abc", "def", 5, d);

	Date* d1 = createDate(1, 1, 2010);
	Material* m1 = createMaterial("fgh", "dty", 4, d1);

	addToDynamicArray(da, m);
	addToDynamicArray(da, m1);

	assert(getElementDynamicArray(da, 0) == m);
	assert(getElementDynamicArray(da, 1) == m1);
	assert(getElementDynamicArray(da, -1) == NULL);

	destroyDynamicArray(da);
}

void test_dynamic_array() {
	test_createDynamicArray();
	test_resizeDynamicArray();
	test_addToDynamicArray();
	test_deleteFromDynamicArray();
	test_getLengthDynamicArray();
	test_getCapacityDynamicArray();
	test_getElementDynamicArray();
}