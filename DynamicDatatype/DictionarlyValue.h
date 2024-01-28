#pragma once
#include "Variable.h"
#include <map>
#include <vector>

class Variable;

class DictionarlyValue : public VariableValue
{
public:
	DictionarlyValue();
	DictionarlyValue(const DictionarlyValue& src);
	~DictionarlyValue();

	bool keyExists(std::string key);
	Variable& getValue(std::string key);
	void setValue(std::string key, Variable value);
	void removeKey(std::string key);
	void empty();
	std::vector<std::string> getKeys();

	unsigned int size();

private:
	std::map<std::string,Variable> m_keyValuePairs;
};

