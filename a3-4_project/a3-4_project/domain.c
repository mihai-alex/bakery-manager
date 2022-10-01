#include "domain.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Date* createDate(int day, int month, int year) {
	Date* d = malloc(sizeof(Date));
	if (d == NULL) {
		return NULL;
	}
	d->day = day;
	d->month = month;
	d->year = year;
	return d;
}

void destroyDate(Date* d) {
	if (d == NULL) {
		return;
	}
	free(d);
}

int getDay(Date* d) {
	if (d == NULL) {
		return -1;
	}
	return d->day;
}

int getMonth(Date* d) {
	if (d == NULL) {
		return -1;
	}
	return d->month;
}

int getYear(Date* d) {
	if (d == NULL) {
		return -1;
	}
	return d->year;
}

void dateToString(Date* d, char str[]) {
	if (d == NULL) {
		return;
	}
	sprintf(str, "%d/%d/%d", d->day, d->month, d->year);
}

Material* createMaterial(char* name, char* supplier, double quantity, Date* expiration_date) {
	Material* m = malloc(sizeof(Material));
	if (m == NULL) {
		return NULL;
	}
	m->name = malloc(sizeof(char) * (strlen(name) + 1));
	if (m->name != NULL) {
		strcpy(m->name, name);
	}
	m->supplier = malloc(sizeof(char) * (strlen(supplier) + 1));
	if (m->supplier != NULL) {
		strcpy(m->supplier, supplier);
	}
	m->quantity = quantity;
	if (m->expiration_date != NULL) {
		m->expiration_date = expiration_date;
	}
	return m;
}

void destroyMaterial(Material* m) {
	if (m == NULL) {
		return;
	}
	free(m->name);
	free(m->supplier);
	destroyDate(m->expiration_date);
	free(m);
}

char* getName(Material* m) {
	if (m == NULL) {
		return NULL;
	}
	return m->name;
}

char* getSupplier(Material* m) {
	if (m == NULL) {
		return NULL;
	}
	return m->supplier;
}

double getQuantity(Material* m) {
	if (m == NULL) {
		return -1;
	}
	return m->quantity;
}

Date* getExpirationDate(Material* m) {
	if (m == NULL) {
		return NULL;
	}
	return m->expiration_date;
}

void materialToString(Material* m, char str[]) {
	// A date string has the form: "dd/mm/yyyy\0"
	char material_expiration_date_string[20] = { 0 };
	dateToString(m->expiration_date, material_expiration_date_string);
	sprintf(str, "Material properties:"
		"\n\t- name: %s\n\t- supplier: %s\n\t- quantity: %.2lf\n\t- expiration date: %s",
		m->name, m->supplier, m->quantity, material_expiration_date_string);
}