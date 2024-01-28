#include "DictionarlyValue.h"

DictionarlyValue::DictionarlyValue()
{
	m_keyValuePairs = std::map<std::string, Variable>();
}

DictionarlyValue::DictionarlyValue(const DictionarlyValue& src)
{
	m_keyValuePairs = src.m_keyValuePairs;
}

DictionarlyValue::~DictionarlyValue()
{

}

bool DictionarlyValue::keyExists(std::string key)
{
	return (m_keyValuePairs.find(key) == m_keyValuePairs.end())? false : true;
}

Variable& DictionarlyValue::getValue(std::string key)
{
	return m_keyValuePairs[key];
}

void DictionarlyValue::setValue(std::string key, Variable value)
{
	m_keyValuePairs[key] = value;
}

void DictionarlyValue::removeKey(std::string key)
{
	m_keyValuePairs.erase(key);
}

void DictionarlyValue::empty()
{
	m_keyValuePairs.clear();
}

std::vector<std::string> DictionarlyValue::getKeys()
{
	std::vector<std::string> keys;
	for (const auto& kv : m_keyValuePairs) {
		keys.push_back(kv.first);
	}
	return keys;
}

unsigned int DictionarlyValue::size()
{
	return m_keyValuePairs.size();
}
