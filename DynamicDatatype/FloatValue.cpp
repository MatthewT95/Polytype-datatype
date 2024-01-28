#include "FloatValue.h"

FloatValue::FloatValue()
{
	m_value = 0;
}

FloatValue::FloatValue(double value)
{
	m_value = value;
}

FloatValue::FloatValue(const FloatValue& src)
{
	m_value = src.m_value;
}

double FloatValue::getValue()
{
	return m_value;
}

void FloatValue::setValue(double value)
{
	m_value = value;
}
