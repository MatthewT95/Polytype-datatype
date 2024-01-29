#include "StackValue.h"

StackValue::StackValue()
{
	m_valueStack = std::stack<Variable>();
}

StackValue::StackValue(const StackValue& src)
{
	m_valueStack = src.m_valueStack;
}

StackValue::~StackValue()
{

}

void StackValue::push(Variable value)
{
	m_valueStack.push(value);
}

Variable StackValue::pop()
{
	Variable top = m_valueStack.top();
	m_valueStack.pop();
	return top;
}

unsigned int StackValue::size()
{
	return m_valueStack.size();
}

bool StackValue::isEmpty()
{
	return m_valueStack.empty();
}
