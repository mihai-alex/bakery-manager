#pragma once
#include "domain.h"
#include "dynamic_array.h"

/*
// Static array implementation
typedef struct {
	Material* materials[100];
	int length;
} Repository;
*/

typedef struct {
	DynamicArray* materials;
} Repository;

/// <summary>
/// Creates an element of type Repository by allocating memory and returning a pointer to it.
/// </summary>
/// <returns>A pointer to the created object of type Repository</returns>
Repository* createRepo();

/// <summary>
/// Destroys a given object of type Repository by deallocating memory.
/// </summary>
/// <param name="r">Pointer to an object of type Repository</param>
void destroyRepo(Repository* r);

/// <summary>
/// Searches for a Material with a given name in the list of materials from the repository
/// and returns a pointer to it, or NULL if the material is not found.
/// </summary>
/// <param name="r">Pointer to an object of type Repository</param>
/// <param name="name">pointer to char array</param>
/// <returns>Pointer to object of type Material, or NULL if material is not found</returns>
Material* find(Repository* r, char* name);

/// <summary>
/// Searches for a Material with a given name in the list of materials from the repository
/// and returns it's position, or -1 if the material is not found.
/// </summary>
/// <param name="r">Pointer to an object of type Repository</param>
/// <param name="name">pointer to char array</param>
/// <returns>Integer denoting the position of the material,
///			 or -1 if the material is not found.</returns>
int findPosition(Repository* r, char* name);

/// <summary>
/// Adds a Material to the dynamic array found in a given object of type Repository.
/// In the case that the material already exists (found by it's unique name), the 
/// object is not added again. In this case the new quantity is added to the original quantity.
/// In the case that the dynamic array does not have enough memory allocated,
/// the resize function is called. 
/// If the resize is not successful, the function returns -1.
/// If the material is already in the dynamic array, the function returns 0.
/// If the material was not found, the function returns 1.
/// </summary>
/// <param name="r">Pointer to an object of type Repository</param>
/// <param name="m">Pointer to an object of type Material</param>
/// <returns>If the resize is not successful, the function returns -1.
///		     If the material is already in the dynamic array, the function returns 0.
///          If the material was not found, the function returns 1.</returns>
int add(Repository* r, Material* m);

/// <summary>
/// Gets the length of a dynamic array, field of the given object of type repository.
/// </summary>
/// <param name="r">Pointer to an object of type Repository</param>
/// <returns>Integer, length of a dynamic array, field of the object of type Repository</returns>
int getLength(Repository* r);

/// <summary>
/// Returns a pointer to an element of type Material found at a given position "pos" 
/// in the dynamic array field of a given object of type Repository.
/// </summary>
/// <param name="r">Pointer to an object of type Repository</param>
/// <param name="pos">Integer denoting the position of the searched element</param>
/// <returns>Pointer to an object of type Material</returns>
Material* getElement(Repository* r, int pos);