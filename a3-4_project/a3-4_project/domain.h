#pragma once

typedef struct {
	int day;
	int month;
	int year;
} Date;

typedef struct {
	char* name;
	char* supplier;
	double quantity;
	Date* expiration_date;
} Material;

/// <summary>
/// Creates an element of type Date by allocating memory and returning a pointer to it.
/// </summary>
/// <param name="day">Integer representing a day</param>
/// <param name="month">Integer representing a month</param>
/// <param name="year">Integer representing a year</param>
/// <returns>A pointer to the created object of type Date</returns>
Date* createDate(int day, int month, int year);

/// <summary>
/// Destroys a given object of type Date by deallocating memory.
/// </summary>
/// <param name="d">Pointer to an object of type Date</param>
void destroyDate(Date* d);

/// <summary>
/// Returns the day of a given object of type Date.
/// </summary>
/// <param name="d">Pointer to an object of type Date</param>
/// <returns>Integer denoting a day</returns>
int getDay(Date* d);

/// <summary>
/// Returns the month of a given object of type Date.
/// </summary>
/// <param name="d">Pointer to an object of type Date</param>
/// <returns>Integer denoting a month</returns>
int getMonth(Date* d);

/// <summary>
/// Returns the year of a given object of type Date.
/// </summary>
/// <param name="d">Pointer to an object of type Date</param>
/// <returns>Integer denoting a year</returns>
int getYear(Date* d);

/// <summary>
/// Takes an object of type Date and populates a given char array "str" 
/// with the object's string representation.
/// </summary>
/// <param name="d">Pointer to an object of type Date</param>
/// <param name="str">char array</param>
void dateToString(Date* d, char str[]);

/// <summary>
/// Creates an element of type Material by allocating memory and returning a pointer to it.
/// </summary>
/// <param name="name">pointer to char array</param>
/// <param name="supplier">pointer to char array</param>
/// <param name="quantity">element of type double</param>
/// <param name="expiration_date">element of type Date</param>
/// <returns>A pointer to the created material</returns>
Material* createMaterial(char* name, char* supplier, double quantity, Date* expiration_date);

/// <summary>
/// Destroys a given object of type Material by deallocating memory.
/// </summary>
/// <param name="m">Pointer to an object of type Material</param>
void destroyMaterial(Material* m);

/// <summary>
/// Returns a pointer to a char array denoting the name of the given material
/// </summary>
/// <param name="m">Pointer to an object of type Material</param>
/// <returns>Pointer to char array denoting the name of the given material</returns>
char* getName(Material* m);

/// <summary>
/// Returns a pointer to a char array denoting the supplier of the given material
/// </summary>
/// <param name="m">Pointer to an object of type Material</param>
/// <returns>Pointer to char array denoting the supplier of the given material</returns>
char* getSupplier(Material* m);

/// <summary>
/// Returns a real number of type double denoting he quantity of the given material.
/// </summary>
/// <param name="m">Pointer to an object of type Material</param>
/// <returns>object of type double denoting the quantity of the given material</returns>
double getQuantity(Material* m);

/// <summary>
/// Returns a pointer of type Date to the expiration date of the given material.
/// </summary>
/// <param name="m">Pointer to an object of type Material</param>
/// <returns>Pointer to an object of type Date - the expiration date of the material</returns>
Date* getExpirationDate(Material* m);

/// <summary>
/// Takes an object of type Material and populates a given char array "str" 
/// with the object's string representation.
/// </summary>
/// <param name="m">Pointer to an object of type Material</param>
/// <param name="str">char array</param>
void materialToString(Material* m, char str[]);