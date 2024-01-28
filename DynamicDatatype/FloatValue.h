#pragma once
#include "VariableValue.h"
class FloatValue : public VariableValue
{
public:
	FloatValue();
	FloatValue(double value);
	FloatValue(const FloatValue& src);

	double getValue();
	void setValue(double value);
private:
	double m_value;
};

