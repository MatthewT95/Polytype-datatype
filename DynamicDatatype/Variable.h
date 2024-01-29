#pragma once
#include "Datatypes.h"
#include "IntegerValue.h"
#include "FloatValue.h"
#include "StringValue.h"
#include "BooleanValue.h"
#include "ListValue.h"
#include "DictionaryValue.h"
#include "StackValue.h"
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

	long long getInteger() const;
	double getFloat() const;
	std::string getString() const;
	bool getBoolean() const;
	bool isNone() const;

	void setInteger(long long value);
	void setFloat(double value);
	void setString(std::string value);
	void setBoolean(bool value);
	void makeList();
	void makeList(Datatypes dt);
	void makeDictionarly();
	void makeDictionarly(Datatypes dt);
	void makeStack();
	void makeStack(Datatypes dt);
	void makeNone();
	void makeError();

	// List
	void appendListElement(Variable value);
	Variable& getListElement(unsigned int index);
	Variable getListElementCopy(unsigned int index) const;
	void setListElement(unsigned int index, Variable value);
	void removeListElement(unsigned int index);
	unsigned int getListElementsCount();
	void clearListElements();
	void fillList(unsigned int targetSize, Variable fillValue);
	void pruneList(unsigned int targetSize);

	// Dictionarly
	bool keyExists(std::string key);
	Variable& getDictionarlyElement(std::string key);
	void setDictionarlyElement(std::string key, Variable value);
	void removeDictionarlyKey(std::string key);
	void clearDictionarlyKeys();

	// Stack
	bool isStackEmpty();
	unsigned int stackSize();
	void stackPush(Variable value);
	Variable stackPop();


	Datatypes getDatatype();
	void setLockMode(unsigned int mode);

	static std::string datatypeName(Datatypes dt);

	static Variable createList();
	static Variable createList(Datatypes dt, bool locked = false);
	static Variable createDictionarly();
	static Variable createDictionarly(Datatypes dt, bool locked = false);
	static Variable createStack();
	static Variable createStack(Datatypes dt, bool locked = false);

	void operator=(const Variable& other);

	// Arithmetic Operators
	friend Variable operator+(const Variable& lhs, const Variable& rhs);
	friend Variable operator-(const Variable& lhs, const Variable& rhs);

private:
	VariableValue* m_value; // Pointer to the value stored in the variable
	Datatypes m_datatype; // Datatype of value store in the variable
	Datatypes m_elementDatatype; // The datatype the collection elements are locked to if locked
	unsigned char m_lockMode; // 0: unlocked 1: type locked 2: value locked
	bool m_elementTypeLocked; // If true the elements of the collection are locked to m_elementDatatype
};

