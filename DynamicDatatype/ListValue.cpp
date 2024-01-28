#include "ListValue.h"

ListValue::ListValue()
{
	m_values = std::vector<Variable>();
}

ListValue::ListValue(const ListValue& src)
{
	m_values = src.m_values;
}

ListValue::~ListValue()
{

}

Variable& ListValue::getElement(unsigned int index)
{
	return m_values[index];
}

void ListValue::setElement(unsigned int index,Variable value)
{
	m_values[index] = value;
}

void ListValue::append(const Variable &value)
{
	m_values.push_back(value);
}

void ListValue::appendNewList()
{
	Variable value;
	value.makeList();
	m_values.push_back(value);
}

void ListValue::remove(unsigned int index)
{
	m_values.erase(m_values.begin()+index);
}

void ListValue::empty()
{
	m_values.clear();
}

void ListValue::makeElementList(unsigned int index)
{
	m_values[index].makeList();
}

unsigned int ListValue::size()
{
	return m_values.size();
}
