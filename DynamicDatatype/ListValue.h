#pragma once
#include "Variable.h"
#include <vector>

class Variable;

class ListValue :  public VariableValue
{
public:
	ListValue();
	ListValue(const ListValue& src);
	~ListValue();

	Variable& getElement(unsigned int index);
	void setElement(unsigned int index,Variable value);
	void append(const Variable &value);
	void appendNewList();
	void remove(unsigned int index);
	void empty();
	void makeElementList(unsigned int index);

	unsigned int size();
	//friend class Variable;
private:
	std::vector<Variable> m_values;
};

