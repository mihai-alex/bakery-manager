#include "dynamic_array.h"
#include <stdlib.h>

DynamicArray* createDynamicArray(int capacity, DestroyElementFunctionType destroyElemFunc) {
	DynamicArray* da = (DynamicArray*)malloc(sizeof(DynamicArray)); // type casting
	if (da == NULL) {
		return NULL;
	}
	da->capacity = capacity;
	da->length = 0;
	da->elems = (TElement*)malloc(capacity * sizeof(TElement)); // type casting
	if (da->elems == NULL) {
		return NULL;
	}
	da->destroyElemFunc = destroyElemFunc;
	return da;
}

void destroyDynamicArray(DynamicArray* arr) {
	if (arr == NULL) {
		return;
	}
	for (int i = 0; i < getLengthDynamicArray(arr); i++) {
		arr->destroyElemFunc(arr->elems[i]);
	}
	free(arr->elems);
	arr->elems = NULL;
	free(arr);
	arr = NULL;
}

int resizeDynamicArray(DynamicArray* arr) {
	if (arr == NULL) {
		return -1;
	}
	arr->capacity = arr->capacity * 2;
	TElement* temp = (TElement*)malloc(sizeof(TElement) * arr->capacity);
	if (temp == NULL) {
		return -1;
	}
	for (int i = 0; i < getLengthDynamicArray(arr); i++) {
		temp[i] = getElementDynamicArray(arr, i);
	}
	free(arr->elems);
	arr->elems = temp;
	return 0;
}

void addToDynamicArray(DynamicArray* arr, TElement elem) {
	if (arr == NULL) {
		return;
	}
	if (arr->elems == NULL) {
		return;
	}
	if (getLengthDynamicArray(arr) == getCapacityDynamicArray(arr)) {
		resizeDynamicArray(arr);
	}
	arr->elems[arr->length] = elem;
	arr->length = arr->length + 1;
}

void deleteFromDynamicArray(DynamicArray* arr, int pos) {
	if (arr == NULL || pos < 0 || pos >= getLengthDynamicArray(arr)) {
		return;
	}
	arr->destroyElemFunc(getElementDynamicArray(arr, pos));

	// this is ONLY done when the deleted element is NOT the last (pos != length - 1)
	if (pos != getLengthDynamicArray(arr) - 1) {
		arr->elems[pos] = getElementDynamicArray(arr, getLengthDynamicArray(arr) - 1);
	}

	arr->length = arr->length - 1;
}

int getLengthDynamicArray(DynamicArray* arr) {
	if (arr == NULL) {
		return -1;
	}
	return arr->length;
}

int getCapacityDynamicArray(DynamicArray* arr) {
	if (arr == NULL) {
		return -1;
	}
	return arr->capacity;
}

TElement getElementDynamicArray(DynamicArray* arr, int pos) {
	if (arr == NULL || pos < 0) {
		return NULL;
	}
	return arr->elems[pos];
}