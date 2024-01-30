#pragma once
#include "Variable.h"
#include <queue>

class Variable;

class QueueValue : public VariableValue
{
public:
	QueueValue();
	QueueValue(const QueueValue& src);
	~QueueValue();

	Variable& front();
	void push(Variable value);
	Variable pop();
	unsigned int isEmpty();

	unsigned int size();
	friend class Variable;
private:
	std::queue<Variable> m_valueQueue;
};