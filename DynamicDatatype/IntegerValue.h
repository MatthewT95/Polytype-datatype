#pragma once
#include "VariableValue.h"

class IntegerValue : public VariableValue
{
public:
	IntegerValue();
	IntegerValue(int value);
	IntegerValue(const IntegerValue& src);
	~IntegerValue();

	long long getValue();
	void setValue(long long value);
private:
	long long m_value;
};

