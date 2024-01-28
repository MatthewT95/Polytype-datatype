#include "BooleanValue.h"

BooleanValue::BooleanValue()
{
	m_value = false;
}

BooleanValue::BooleanValue(bool value)
{
	m_value = value;
}

BooleanValue::BooleanValue(const BooleanValue& src)
{
	m_value = src.m_value;
}

bool BooleanValue::getValue()
{
	return m_value;
}

void BooleanValue::setValue(bool value)
{
	m_value = value;
}