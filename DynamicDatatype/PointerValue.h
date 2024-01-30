#pragma once
#include "VariableValue.h"
#include "Variable.h"

class PointerValue : public VariableValue
{
public:
	PointerValue();
	PointerValue(Variable* reference);
	PointerValue(const PointerValue& src);

	Variable& dereference();
private:
	Variable* m_reference;
};

