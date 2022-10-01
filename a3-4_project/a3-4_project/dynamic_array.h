#pragma once
#define CAPACITY 10

typedef void* TElement;
typedef void (*DestroyElementFunctionType)(void*);

typedef struct {
	TElement* elems;
	int length;
	int capacity;
	DestroyElementFunctionType destroyElemFunc;
} DynamicArray;

/// <summary>
/// Creates a dynamic array of generic elements, with a given capacity.
/// </summary>
/// <param name="capacity">Integer, maximum capacity for the dynamic array.</param>
/// <param name="destroyElemFunc">Function pointer of type DestroyElementFunctionType. 
///				The function that deals with deallocating the elements of the array.</param>
/// <returns>A pointer to the created dynamic array.</returns>
DynamicArray* createDynamicArray(int capacity, DestroyElementFunctionType destroyElemFunc);

/// <summary>
/// Destroys a given dynamic array by freeing it's allocated memory.
/// </summary>
/// <param name="arr">Pointer to a dynamic array</param>
void destroyDynamicArray(DynamicArray* arr);

/// <summary>
/// Resizes the capacity of the given dynamic array by allocating double the 
/// memory that was already allocated. The capacity is doubled.
/// </summary>
/// <param name="arr">Pointer to a dynamic array</param>
/// <returns>0 if the resize was successful, -1 otherwise</returns>
int resizeDynamicArray(DynamicArray* arr);

/// <summary>
/// Adds and element of type TElement to the given dynamic array and
/// resizes the array (if there is no more space available) by allocating more memory.
/// </summary>
/// <param name="arr">Pointer to a dynamic array</param>
/// <param name="elem">generic element of type TElement</param>
void addToDynamicArray(DynamicArray* arr, TElement elem);

/// <summary>
/// Deletes an element from position "pos" from the given dynamic array,
/// if the given position (index) is valid.
/// </summary>
/// <param name="arr"Pointer to a dynamic array></param>
/// <param name="pos">Integer denoting the position of the element to be deleted</param>
void deleteFromDynamicArray(DynamicArray* arr, int pos);

/// <summary>
/// Returns the length of the given dynamic array
/// </summary>
/// <param name="arr">Pointer to a dynamic array</param>
/// <returns>Integer, length of the dynamic array</returns>
int getLengthDynamicArray(DynamicArray* arr);

/// <summary>
/// Returns the capacity of the given dynamic array
/// </summary>
/// <param name="arr">Pointer to a dynamic array</param>
/// <returns>Integer, capacity of the dynamic array</returns>
int getCapacityDynamicArray(DynamicArray* arr);

/// <summary>
/// Returns a generic element of type TElement from the given dynamic array,
/// at position "pos", if the position (index) is valid.
/// </summary>
/// <param name="arr">Pointer to a dynamic array</param>
/// <param name="pos">Integer denoting the position of the element to be returned</param>
/// <returns>Element of type TElement from the dynamic array</returns>
TElement getElementDynamicArray(DynamicArray* arr, int pos);