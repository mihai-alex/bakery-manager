#include "repository.h"
#include "dynamic_array.h"
#include <stdlib.h>
#include <string.h>

Repository* createRepo() {
	Repository* r = (Repository*)malloc(sizeof(Repository));
	if (r == NULL) {
		return NULL;
	}
	r->materials = createDynamicArray(CAPACITY, &destroyMaterial);
	return r;
}

void destroyRepo(Repository* r) {
	if (r == NULL) {
		return;
	}
	destroyDynamicArray(r->materials);
	free(r);
}

Material* find(Repository* r, char* name) {
	for (int i = 0; i < getLength(r); i++) {
		if (strcmp(getElement(r, i)->name, name) == 0) {
			return getElement(r, i);
		}
	}
	return NULL;
}

int findPosition(Repository* r, char* name) {
	for (int i = 0; i < getLength(r); i++) {
		if (strcmp(getElement(r, i)->name, name) == 0) {
			return i;
		}
	}
	return -1;
}

int add(Repository* r, Material* m) {
	Material* found = find(r, m->name);
	int resize_successful = 0;
	if (found == NULL) {
		if (getCapacityDynamicArray(r->materials) == getLengthDynamicArray(r->materials)) {
			resize_successful = resizeDynamicArray(r->materials);
			if (resize_successful == -1) {
				return -1;
			}
		}
		r->materials->elems[getLength(r)] = m;
		r->materials->length = r->materials->length + 1;
		return 1; // planet was not found, so it was added!
	}
	else {
		found->quantity = found->quantity + m->quantity;
		return 0;
	}
}

int getLength(Repository* r) {
	return getLengthDynamicArray(r->materials);
}

Material* getElement(Repository* r, int pos) {
	return getElementDynamicArray(r->materials, pos);
}