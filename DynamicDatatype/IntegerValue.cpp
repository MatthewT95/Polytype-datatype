#include "IntegerValue.h"

IntegerValue::IntegerValue()
{
	m_value = 0;
}

IntegerValue::IntegerValue(int value)
{
	m_value = value;
}

IntegerValue::IntegerValue(const IntegerValue& src)
{
	m_value = src.m_value;
}

IntegerValue::~IntegerValue()
{

}

long long IntegerValue::getValue()
{
	return m_value;
}

void IntegerValue::setValue(long long value)
{
	m_value = value;
}
