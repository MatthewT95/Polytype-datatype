#include "PointerValue.h"

PointerValue::PointerValue()
{
	m_reference = nullptr;
}

PointerValue::PointerValue(Variable* reference)
{
	m_reference = reference;
}

PointerValue::PointerValue(const PointerValue& src)
{
	m_reference = src.m_reference;
}

Variable& PointerValue::dereference()
{
	return *m_reference;
}
