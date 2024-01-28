#pragma once
#include "VariableValue.h"
class BooleanValue :  public VariableValue
{
public:
	BooleanValue();
	BooleanValue(bool value);
	BooleanValue(const BooleanValue& src);

	bool getValue();
	void setValue(bool value);
private:
	bool m_value;
};

