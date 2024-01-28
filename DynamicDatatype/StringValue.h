#pragma once
#include "VariableValue.h"
#include <string>

class StringValue : public VariableValue
{
public:
	StringValue();
	StringValue(std::string value);
	StringValue(const StringValue& src);

	std::string getValue();
	void setValue(std::string value);
private:
	std::string m_value;
};

