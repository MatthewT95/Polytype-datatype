#include "StringValue.h"

StringValue::StringValue()
{
	m_value = "";
}

StringValue::StringValue(std::string value)
{
	m_value = value;
}

StringValue::StringValue(const StringValue& src)
{
	m_value = src.m_value;
}

std::string StringValue::getValue()
{
	return m_value;
}

void StringValue::setValue(std::string value)
{
	m_value = value;
}