#pragma once
#include "repository.h"

typedef int (*FilterFunctionType)(void*);

typedef int (*CompareFunctionType)(double, double);

typedef struct {
	Repository* repo;
	DynamicArray* undo_stack;
	DynamicArray* redo_stack;
} Controller;

/// <summary>
/// Creates an element of type Controller by allocating memory and returning a pointer to it.
/// </summary>
/// <returns>A pointer to the created object of type Controller</returns>
Controller* createController(Repository* repo);

/// <summary>
/// Destroys a given object of type Controller by deallocating memory.
/// </summary>
/// <param name="cont">Pointer to an object of type Controller</param>
void destroyController(Controller* cont);

/// <summary>
/// Takes the fields of an element of type Material, creates the element and adds to
/// the repository.
/// </summary>
/// <param name="cont">pointer to object of type Controller</param>
/// <param name="name">pointer to char array</param>
/// <param name="supplier">pointer to char array</param>
/// <param name="quantity">real number of type double</param>
/// <param name="day">positive integer denoting a day</param>
/// <param name="month">positive integer denoting a month</param>
/// <param name="year">positive integer denoting a year</param>
/// <returns>1, if the element was added successfully, 0 otherwise</returns>
int addMaterialByName(Controller* cont, char* name, char* supplier, double quantity,
	int day, int month, int year);

/// <summary>
/// Takes the name of an element of type Material and deletes it, if it exists
/// in the repository.
/// </summary>
/// <param name="cont">pointer to object of type Controller</param>
/// <param name="name">pointer to char array</param>
/// <returns>1, if the element was deleted successfully, 0 otherwise</returns>
int deleteMaterialByName(Controller* cont, char* name);

/// <summary>
/// Takes the fields of an element of type Material, searches for the element
/// with the given name in the repository and updates it's fields, if it exists.
/// </summary>
/// <param name="cont">pointer to object of type Controller</param>
/// <param name="name">pointer to char array</param>
/// <param name="supplier">pointer to char array</param>
/// <param name="quantity">real number of type double</param>
/// <param name="day">positive integer denoting a day</param>
/// <param name="month">positive integer denoting a month</param>
/// <param name="year">positive integer denoting a year</param>
/// <returns>1, if the element was updated successfully, 0 otherwise</returns>
int updateMaterialByName(Controller* cont, char* name, char* supplier, double quantity,
	int day, int month, int year);

/// <summary>
/// Returns the repository linked to a given object of type Controller
/// </summary>
/// <param name="cont">pointer to object of type Controller</param>
/// <returns>A pointer to an object of type Repository.</returns>
Repository* getRepo(Controller* cont);

/// <summary>
/// Returns a pointer to an object of type Date representing the current date.
/// </summary>
/// <returns>Pointer to an object of type Date</returns>
Date* getCurrentDate();

/// <summary>
/// Checks if the expiration date is "before" the current date.
/// Returns 1 if true, 0 otherwise.
/// </summary>
/// <param name="expiration_date">pointer to object of type Date</param>
/// <param name="current_date">pointer to object of type Date</param>
/// <returns>1 if expired, 0 otherwise.</returns>
int isExpired(Date* expiration_date, Date* current_date);

/// <summary>
/// Makes a deep copy of a given object of type Date and returns a pointer to it.
/// </summary>
/// <param name="d">pointer to object of type Date</param>
/// <returns>pointer to object of type Date</returns>
Date* copyDate(Date* d);

/// <summary>
/// Makes a deep copy of a given object of type Material and returns a pointer to it.
/// </summary>
/// <param name="m">pointer to object of type Material</param>
/// <returns>pointer to object of type Material</returns>
Material* copyMaterial(Material* m);

/// <summary>
/// Returns a pointer to an object of type Repository containing the
/// objects from the repository of the given object of type Controller,
/// that are past their expiration date and have names that contain a
/// given substring "str"
/// </summary>
/// <param name="cont">pointer to an object of type Controller</param>
/// <param name="str">pointer to char array</param>
/// <returns>pointer to an object of type Repository</returns>
Repository* filterExpiredByStringInName(Controller* cont, char* str);

/// <summary>
/// Sorts the elements of type Material found in a given repo ascending by quantity.
/// </summary>
/// <param name="repo">pointer to an object of type Repository</param>
void sortAscendingByQuantity(Repository* repo);

/// <summary>
/// Returns 1 if first <= second, 0 otherwise
/// </summary>
/// <param name="first">double</param>
/// <param name="second">double</param>
/// <returns>integer 1, if params are in the desired order, 0 otherwise</returns>
int areInOrderAscending(double first, double second);

/// <summary>
/// Returns 1 if first >= second, 0 otherwise
/// </summary>
/// <param name="first">double</param>
/// <param name="second">double</param>
/// <returns>integer 1, if params are in the desired order, 0 otherwise</returns>
int areInOrderDescending(double first, double second);

/// <summary>
/// Function that takes a pointer to an element of type Repository and calls the
/// generic function areInOrder (which points to a comparison function) in order
/// to sort the elements found in the repository.
/// </summary>
/// <param name="repo">pointer to an object of type Repository</param>
/// <param name="areInOrder">generic function of type CompareFunctionType</param>
void sortByQuantityGeneric(Repository* repo, CompareFunctionType areInOrder);

/// <summary>
/// Returns a pointer to an object of type Repository containing the
/// objects from the repository of the given object of type Controller,
/// that are in short supply (their quantity is less that a given value),
/// and their supplier matches with the given one. The generic function
/// areInOrder is used when calling a generic sorting function, in order
/// to sort the elements in the built repository.
/// </summary>
/// <param name="cont">pointer to an object of type Controller</param>
/// <param name="supplier">pointer to char array</param>
/// <param name="value">real number of type double</param>
/// <returns>pointer to an object of type Repository</returns>
Repository* filterInShortSupplyGeneric(Controller* cont, char* supplier, double value,
	CompareFunctionType areInOrder);

/// <summary>
/// Returns a pointer to an object of type Repository containing the
/// objects from the repository of the given object of type Controller,
/// that are in short supply (their quantity is less that a given value),
/// and their supplier matches with the given one
/// </summary>
/// <param name="cont">pointer to an object of type Controller</param>
/// <param name="supplier">pointer to char array</param>
/// <param name="value">real number of type double</param>
/// <returns>pointer to an object of type Repository</returns>
Repository* filterInShortSupply(Controller* cont, char* supplier, double value);

/// <summary>
/// Checks if a given material has a short name, up to 5 characters long.
/// </summary>
/// <param name="m">pointer to an object of type Material</param>
/// <returns>1 if the name of the material is short, 0 otherwise</returns>
int hasShortName(Material* m);

/// <summary>
/// Filters the elements found in a given Controller's Repository.
/// Uses a generic filtering function establishing the criteria
/// by which materials are filtered.
/// </summary>
/// <param name="cont">pointer to an object of type Controller</param>
/// <param name="toFilter">generic fuction of type FilterFunctionType</param>
/// <returns>a pointer to an object of type Repository</returns>
Repository* genericFilter(Controller* cont, FilterFunctionType toFilter);

/// <summary>
/// Assigns 10 random items of type Material to a given object of type Repository.
/// </summary>
/// <param name="repo">pointer to an object of type Repository</param>
void assignRandomMaterials(Repository* repo);

/// <summary>
/// Creates a deep copy of a given repository and returns it.
/// </summary>
/// <param name="repo">pointer to an object of type Repository</param>
/// <returns>pointer to an object of type Repository</returns>
Repository* copyRepository(Repository* repo);

/// <summary>
/// Adds an element of type Repository from the controller to the undo_stack in the controller
/// </summary>
/// <param name="cont">pointer to an object of type Controller</param>
void addToUndo(Controller* cont);

/// <summary>
/// performs an undo operation on a given Controller
/// </summary>
/// <param name="cont">pointer to an object of type Controller</param>
/// <returns>1 if the undo operation was successful, -1 otherwise</returns>
int undo(Controller* cont);

/// <summary>
/// clears the redo_stack of a given object of type Controller
/// </summary>
/// <param name="cont">pointer to an object of type Controller</param>
void clearRedo(Controller* cont);

/// <summary>
/// Adds an element of type Repository from the controller to the redo_stack in the controller
/// </summary>
/// <param name="cont">pointer to an object of type Controller</param>
void addToRedo(Controller* cont);

/// <summary>
/// performs a redo operation on a given Controller
/// </summary>
/// <param name="cont">pointer to an object of type Controller</param>
/// <returns>1 if the redo operation was successful, -1 otherwise</returns>
int redo(Controller* cont);