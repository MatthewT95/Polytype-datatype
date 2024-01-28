#pragma once
#include "Datatypes.h"
#include "IntegerValue.h"
#include "FloatValue.h"
#include "StringValue.h"
#include "BooleanValue.h"
#include "ListValue.h"
#include <vector>

class Variable
{
public:
	Variable();
	Variable(const Variable& src);
	~Variable();
	Variable(int value,bool locked = false);
	Variable(double value, bool locked = false);
	Variable(std::string value, bool locked = false);
	Variable(const char* value, bool locked = false);
	Variable(bool value, bool locked = false);

	long long getInteger() const;
	double getFloat() const;
	std::string getString() const;
	bool getBoolean() const;
	std::vector<Variable>& getList() const;
	bool isNone() const;

	void setInteger(long long value);
	void setFloat(double value);
	void setString(std::string value);
	void setBoolean(bool value);
	void makeList();
	void makeList(Datatypes dt);
	void makeNone();

	// List
	void appendElement(Variable value);
	void appendNewList();
	Variable& getElement(unsigned int index);
	void setElement(unsigned int index, Variable value);
	void removeElement(unsigned int index);
	unsigned int getElementsCount();
	void clearElements();
	void makeElementList(unsigned int index);

	Datatypes getDatatype();
	void lock();
	void unlock();

	static std::string datatypeName(Datatypes dt);
private:
	VariableValue* m_value;
	Datatypes m_datatype;
	Datatypes m_elementDatatype;
	bool m_typeLocked;
	bool m_elementTypeLocked;
};

