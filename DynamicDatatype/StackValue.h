#pragma once
#include "Variable.h"
#include <stack>

class Variable;

class StackValue:public VariableValue
{
public:
	StackValue();
	StackValue(const StackValue& src);
	~StackValue();

	void push(Variable value);
	Variable pop();
	unsigned int size();
	bool isEmpty();

private:
	std::stack<Variable> m_valueStack;
};

