#pragma once
#include "Datatypes.h"
#include "IntegerValue.h"
#include "FloatValue.h"
#include "StringValue.h"
#include "BooleanValue.h"
#include <vector>

class Variable
{
public:
	Variable();
	Variable(const Variable& src);
	~Variable();
	Variable(int value, int lockMode = 0);
	Variable(double value, int lockMode = 0);
	Variable(std::string value, int lockMode = 0);
	Variable(const char* value, int lockMode = 0);
	Variable(bool value, int lockMode = 0);
	Variable(Variable* reference);

	long long getInteger() const;
	double getFloat() const;
	std::string getString() const;
	bool getBoolean() const;
	bool isNone() const;
	bool isError() const;

	void setInteger(long long value);
	void setFloat(double value);
	void setString(std::string value);
	void setBoolean(bool value);
	
	void makeNone();
	void makeError();

	// List
	// Makes target variable a empty list
	void makeList();
	// Makes target variable a empty list locked to specific datatype
	void makeList(Datatypes dt);
	// Returns an empty list.
	// Use when appending a element to list or dictionarly that has its elements
	//   locked to list type
	static Variable createList();
	// Returns an empty list locked to a specific datatype
	// Use when appending a element to list or dictionarly that has its elements
	//   locked to list type
	static Variable createList(Datatypes dt, bool locked = false);
	// Appends a Variable to the list
	// We throw exception if list is type locked to a type different then the value
	void appendListElement(Variable value);
	// Returns a Variable reference to a list element
	Variable& getListElement(unsigned int index);
	// Returns a Variable value of list element
	Variable getListElementCopy(unsigned int index) const;
	// Updates the value of an element at given index
	// We throw exception if list is type locked to a type different then the value
	void setListElement(unsigned int index, Variable value);
	// Removes an element at given index in list
	void removeListElement(unsigned int index);
	// Returns the total number of elements in the list
	unsigned int getListElementsCount();
	// Removes all elements from list
	void clearListElements();
	// Adds elements of fillValue untill list reaches target size
	void fillList(unsigned int targetSize, Variable fillValue);
	// Repeatly removes last element until list reaches target size
	void pruneList(unsigned int targetSize);

	// Dictionarly
	// Makes a variable a unlocked empty dictionary
	void makeDictionarly();
	// Makes a variable a empty dictionary with elements lock to a given type
	void makeDictionarly(Datatypes dt);
	// Creates an empty dictionary that is unlocked
	static Variable createDictionarly();
	// Creates an empty dictionary that lock to a given type.
	//	also allows you have the variable type locked to dictionary
	static Variable createDictionarly(Datatypes dt, bool locked = false);
	// Checks if a given key exists in the dictionary
	bool keyExists(std::string key);
	// Returns a reference to a dictionary value
	Variable& getDictionarlyElement(std::string key);
	// Sets the value of a dictionary element with given key
	void setDictionarlyElement(std::string key, Variable value);
	// Deletes a key value pair
	void removeDictionarlyKey(std::string key);
	// Deletes all key value pairs
	void clearDictionarlyKeys();

	// Stack
	void makeStack();
	void makeStack(Datatypes dt);
	static Variable createStack();
	static Variable createStack(Datatypes dt, bool locked = false);
	bool isStackEmpty();
	unsigned int stackSize();
	void stackPush(Variable value);
	Variable stackPop();
	Variable& stackTop();

	// Queue
	void makeQueue();
	void makeQueue(Datatypes dt);
	static Variable createQueue();
	static Variable createQueue(Datatypes dt, bool locked = false);
	bool QueueEmpty();
	unsigned int QueueSize();
	void QueuePush(Variable value);
	Variable& QueueFront();
	Variable QueuePop();

	// Pointer
	Variable& pointerDereference();


	Datatypes getDatatype() const;
	void setLockMode(unsigned int mode);

	static Variable castInterger(Variable value);
	static Variable castFloat(Variable value);
	static Variable castString(Variable value);
	static Variable castBoolean(Variable value);

	static std::string datatypeName(Datatypes dt);

	Variable& operator[](unsigned int index);
	Variable& operator[](std::string key);


	void operator=(const Variable& other);

	// Arithmetic Operators
	friend Variable operator+(const Variable& lhs, const Variable& rhs);
	friend Variable operator-(const Variable& lhs, const Variable& rhs);
	friend Variable operator*(const Variable& lhs, const Variable& rhs);
	friend Variable operator/(const Variable& lhs, const Variable& rhs);

private:
	VariableValue* m_value; // Pointer to the value stored in the variable
	Datatypes m_datatype; // Datatype of value store in the variable
	Datatypes m_elementDatatype; // The datatype the collection elements are locked to if locked
	unsigned char m_lockMode; // 0: unlocked 1: type locked 2: value locked
	bool m_elementTypeLocked; // If true the elements of the collection are locked to m_elementDatatype
};

