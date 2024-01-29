#include "DictionaryValue.h"

DictionaryValue::DictionaryValue()
{
	m_keyValuePairs = std::map<std::string, Variable>();
}

DictionaryValue::DictionaryValue(const DictionaryValue& src)
{
	m_keyValuePairs = src.m_keyValuePairs;
}

DictionaryValue::~DictionaryValue()
{

}

bool DictionaryValue::keyExists(std::string key)
{
	return (m_keyValuePairs.find(key) == m_keyValuePairs.end())? false : true;
}

Variable& DictionaryValue::getValue(std::string key)
{
	return m_keyValuePairs[key];
}

void DictionaryValue::setValue(std::string key, Variable value)
{
	m_keyValuePairs[key] = value;
}

void DictionaryValue::removeKey(std::string key)
{
	m_keyValuePairs.erase(key);
}

void DictionaryValue::empty()
{
	m_keyValuePairs.clear();
}

std::vector<std::string> DictionaryValue::getKeys()
{
	std::vector<std::string> keys;
	for (const auto& kv : m_keyValuePairs) {
		keys.push_back(kv.first);
	}
	return keys;
}

unsigned int DictionaryValue::size()
{
	return m_keyValuePairs.size();
}
