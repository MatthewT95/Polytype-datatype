#include "QueueValue.h"

QueueValue::QueueValue()
{
	m_valueQueue = std::queue<Variable>();
}

QueueValue::QueueValue(const QueueValue& src)
{
	m_valueQueue = src.m_valueQueue;
}

QueueValue::~QueueValue()
{

}

Variable& QueueValue::front()
{
	return m_valueQueue.front();
}

void QueueValue::push(Variable value)
{
	m_valueQueue.push(value);
}

Variable QueueValue::pop()
{
	Variable front = m_valueQueue.front();
	m_valueQueue.pop();
	return front;
}

unsigned int QueueValue::isEmpty()
{
	return m_valueQueue.empty();
}

unsigned int QueueValue::size()
{
	return m_valueQueue.size();
}
