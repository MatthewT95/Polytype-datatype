#include "Variable.h"
#include <stdexcept>
#include <iostream>

Variable::Variable()
{
	m_value = nullptr;
	m_datatype = Datatypes::None;
	m_lockMode = 0;
	m_elementDatatype = Datatypes::None;
	m_elementTypeLocked = false;
}

Variable::Variable(const Variable& src)
{
	if (src.m_datatype == Datatypes::Integer)
	{
		m_datatype = Datatypes::Integer;
		m_value = new IntegerValue(src.getInteger());
	}
	else if (src.m_datatype == Datatypes::Float)
	{
		m_datatype = Datatypes::Float;
		m_value = new FloatValue(src.getFloat());
	}
	else if (src.m_datatype == Datatypes::String)
	{
		m_datatype = Datatypes::String;
		m_value = new StringValue(src.getString());
	}
	else if (src.m_datatype == Datatypes::Boolean)
	{
		m_datatype = Datatypes::Boolean;
		m_value = new BooleanValue(src.getBoolean());
	}
	else if (src.m_datatype == Datatypes::List)
	{
		m_datatype = Datatypes::List;
		m_value = new ListValue();
		for (int i = 0; i < ((ListValue*)src.m_value)->size(); i++)
		{
			((ListValue*)m_value)->append(src.getListElementCopy(i));
		}
	}
	else if (src.m_datatype == Datatypes::Dictionary)
	{
		m_datatype = Datatypes::Dictionary;
		m_value = new DictionaryValue();

		for (std::string key : ((DictionaryValue*)src.m_value)->getKeys())
		{
			this->setDictionarlyElement(key,((DictionaryValue*)src.m_value)->getValue(key));
		}
	}
	else
	{
		m_value = nullptr;
		m_datatype = Datatypes::None;
	}

	m_lockMode = src.m_lockMode;
	m_elementDatatype = src.m_elementDatatype;
	m_elementTypeLocked = src.m_elementTypeLocked;
}

Variable::~Variable()
{
	if (m_value != nullptr)
	{
		delete m_value;
	}
}

Variable::Variable(int value,int lockMode)
{
	m_value = new IntegerValue(value);
	m_datatype = Datatypes::Integer;
	m_elementDatatype = Datatypes::None;
	m_elementTypeLocked = false;
	m_lockMode = lockMode;
}

Variable::Variable(double value, int lockMode)
{
	m_value = new FloatValue(value);
	m_datatype = Datatypes::Float;
	m_elementDatatype = Datatypes::None;
	m_elementTypeLocked = false;
	m_lockMode = lockMode;
}

Variable::Variable(std::string value, int lockMode)
{
	m_value = new StringValue(value);
	m_datatype = Datatypes::String;
	m_elementDatatype = Datatypes::None;
	m_elementTypeLocked = false;
	m_lockMode = lockMode;
}

Variable::Variable(const char* value, int lockMode)
{
	m_value = new StringValue(std::string(value));
	m_datatype = Datatypes::String;
	m_elementDatatype = Datatypes::None;
	m_elementTypeLocked = false;
	m_lockMode = lockMode;
}

Variable::Variable(bool value, int lockMode)
{
	m_value = new BooleanValue(value);
	m_datatype = Datatypes::Boolean;
	m_elementDatatype = Datatypes::None;
	m_elementTypeLocked = false;
	m_lockMode = lockMode;
}

long long Variable::getInteger() const
{
	if (m_datatype != Datatypes::Integer)
	{
		throw std::logic_error("Variable is not of type Integer.");
	}
	return ((IntegerValue*)m_value)->getValue();

}

double Variable::getFloat() const
{
	if (m_datatype != Datatypes::Float)
	{
		throw std::logic_error("Variable is not of type Float.");
	}
	return ((FloatValue*)m_value)->getValue();
}

std::string Variable::getString() const
{
	if (m_datatype != Datatypes::String)
	{
		throw std::logic_error("Variable is not of type String.");
	}
	return ((StringValue*)m_value)->getValue();
}

bool Variable::getBoolean() const
{
	if (m_datatype != Datatypes::Boolean)
	{
		throw std::logic_error("Variable is not of type Boolean.");
	}
	return ((BooleanValue*)m_value)->getValue();
}

bool Variable::isNone() const
{
	return m_datatype==Datatypes::None;
}

void Variable::setInteger(long long value)
{
	if (m_lockMode > 0 && m_datatype != Datatypes::Integer)
	{
		throw std::logic_error("Variable is type locked to a non Integer datatype.");
	}
	if (m_lockMode == 2)
	{
		throw std::logic_error("Variable is constant and can not be changed while value locked.");
	}
	delete m_value;
	m_value = new IntegerValue(value);
	m_datatype = Datatypes::Integer;
}

void Variable::setFloat(double value)
{
	if (m_lockMode > 0 && m_datatype != Datatypes::Float)
	{
		throw std::logic_error("Variable is type locked to a non Float datatype.");
	}

	if (m_lockMode == 2)
	{
		throw std::logic_error("Variable is constant and can not be changed while value locked.");
	}
	delete m_value;
	m_value = new FloatValue(value);
	m_datatype = Datatypes::Float;
}

void Variable::setString(std::string value)
{
	if (m_lockMode > 0 && m_datatype != Datatypes::String)
	{
		throw std::logic_error("Variable is type locked to a non String datatype.");
	}
	if (m_lockMode == 2)
	{
		throw std::logic_error("Variable is constant and can not be changed while value locked.");
	}
	delete m_value;
	m_value = new StringValue(value);
	m_datatype = Datatypes::String;
}

void Variable::setBoolean(bool value)
{
	if (m_lockMode > 0 && m_datatype != Datatypes::Boolean)
	{
		throw std::logic_error("Variable is type locked to a non Boolean datatype.");
	}

	if (m_lockMode == 2)
	{
		throw std::logic_error("Variable is constant and can not be changed while value locked.");
	}
	delete m_value;
	m_value = new BooleanValue(value);
	m_datatype = Datatypes::Boolean;
}

void Variable::makeList()
{
	if (m_lockMode > 0 && m_datatype != Datatypes::List)
	{
		throw std::logic_error("Variable is type locked to a non List datatype.");
	}
	if (m_lockMode == 2)
	{
		throw std::logic_error("Variable is constant and can not be changed while value locked.");
	}
	//delete m_value;
	m_value = new ListValue();
	m_datatype = Datatypes::List;
	m_elementDatatype = Datatypes::None;
	m_elementTypeLocked = false;
}

void Variable::makeList(Datatypes dt)
{
	if (m_lockMode > 0 && m_datatype != Datatypes::List)
	{
		throw std::logic_error("Variable is type locked to a non List datatype.");
	}
	if (m_lockMode == 2)
	{
		throw std::logic_error("Variable is constant and can not be changed while value locked.");
	}
	delete m_value;
	m_value = new ListValue();
	m_datatype = Datatypes::List;
	m_elementDatatype = dt;
	m_elementTypeLocked = true;
}

void Variable::makeNone()
{
	if (m_lockMode > 0 && m_datatype != Datatypes::None)
	{
		throw std::logic_error("Variable is type locked to a non None datatype.");
	}
	if (m_lockMode == 2)
	{
		throw std::logic_error("Variable is constant and can not be changed while value locked.");
	}
	delete m_value;
	m_value = nullptr;
	m_datatype = Datatypes::None;
	m_elementDatatype = Datatypes::None;
	m_elementTypeLocked = false;
}

void Variable::makeDictionarly()
{
	if (m_lockMode > 0 && m_datatype != Datatypes::Dictionary)
	{
		throw std::logic_error("Variable is type locked to a non Dictionary datatype.");
	}

	if (m_lockMode == 2)
	{
		throw std::logic_error("Variable is constant and can not be changed while value locked.");
	}
	delete m_value;
	m_value = new DictionaryValue();
	m_datatype = Datatypes::Dictionary;
	m_elementDatatype = Datatypes::None;
	m_elementTypeLocked = false;
}

void Variable::makeDictionarly(Datatypes dt)
{
	if (m_lockMode > 0 && m_datatype != Datatypes::Dictionary)
	{
		throw std::logic_error("Variable is type locked to a non Dictionary datatype.");
	}
	if (m_lockMode == 2)
	{
		throw std::logic_error("Variable is constant and can not be changed while value locked.");
	}
	delete m_value;
	m_value = new DictionaryValue();
	m_datatype = Datatypes::Dictionary;
	m_elementDatatype = dt;
	m_elementTypeLocked = true;
}

void Variable::appendListElement(Variable value)
{
	if (m_datatype != Datatypes::List)
	{
		throw std::logic_error("Variable is not of type List");
	}
	if (m_elementTypeLocked != 0 && value.getDatatype() != m_elementDatatype)
	{
		throw std::logic_error("List elements are type locked to " + datatypeName(m_elementDatatype) + " datatype.");
	}
	if (m_elementTypeLocked)
	{
		value.setLockMode(1);
	}
	((ListValue*)m_value)->append(value);
}

Variable& Variable::getListElement(unsigned int index)
{
	if (m_datatype != Datatypes::List)
	{
		throw std::logic_error("Variable is not of type List");
	}
	return ((ListValue*)m_value)->getElement(index);
}

Variable Variable::getListElementCopy(unsigned int index) const
{
	if (m_datatype != Datatypes::List)
	{
		throw std::logic_error("Variable is not of type List");
	}
	return ((ListValue*)m_value)->getElement(index);
}

void Variable::setListElement(unsigned int index, Variable value)
{
	if (m_datatype != Datatypes::List)
	{
		throw std::logic_error("Variable is not of type List");
	}
	if (m_lockMode != 0 && value.getDatatype() != m_elementDatatype)
	{
		throw std::logic_error("List elements are type locked to " + datatypeName(m_elementDatatype) + " datatype.");
	}
	if (getListElement(index).m_lockMode == 1)
	{
		throw std::logic_error("Variable in list at index " + std::to_string(index) + " is type locked to " +
			datatypeName(getListElement(index).getDatatype()));
	}
	if (getListElement(index).m_lockMode == 2)
	{
		throw std::logic_error("Variable is constant and can not be changed while value locked.");
	}
	if (m_elementTypeLocked)
	{
		value.setLockMode(1);
	}
	((ListValue*)m_value)->setElement(index, value);
}

void Variable::removeListElement(unsigned int index)
{
	if (m_datatype != Datatypes::List)
	{
		throw std::logic_error("Variable is not of type List");
	}
	return ((ListValue*)m_value)->remove(index);
}

unsigned int Variable::getListElementsCount()
{
	if (m_datatype != Datatypes::List)
	{
		throw std::logic_error("Variable is not of type List");
	}
	return ((ListValue*)m_value)->size();
}

void Variable::clearListElements()
{
	if (m_datatype != Datatypes::List)
	{
		throw std::logic_error("Variable is not of type List");
	}
	return ((ListValue*)m_value)->empty();
}

void Variable::fillList(unsigned int targetSize, Variable fillValue)
{
	if (m_datatype != Datatypes::List)
	{
		throw std::logic_error("Variable is not of type List");
	}
	if (m_lockMode != 0 && m_elementDatatype != fillValue.getDatatype())
	{
		throw std::logic_error("List elements are type locked to " + datatypeName(m_elementDatatype) + " datatype.");
	}
	while (((ListValue*)m_value)->size() < targetSize)
	{
		((ListValue*)m_value)->append(fillValue);
	}
}

void Variable::pruneList(unsigned int targetSize)
{
	if (m_datatype != Datatypes::List)
	{
		throw std::logic_error("Variable is not of type List");
	}
	while (((ListValue*)m_value)->size() > targetSize)
	{
		((ListValue*)m_value)->remove(((ListValue*)m_value)->size()-1);
	}
}

bool Variable::keyExists(std::string key)
{
	if (m_datatype != Datatypes::Dictionary)
	{
		throw std::logic_error("Variable is not of type Dictionarly");
	}
	return ((DictionaryValue*)m_value)->keyExists(key);
}

Variable& Variable::getDictionarlyElement(std::string key)
{
	if (m_datatype != Datatypes::Dictionary)
	{
		throw std::logic_error("Variable is not of type Dictionarly");
	}
	return ((DictionaryValue*)m_value)->getValue(key);
}

void Variable::setDictionarlyElement(std::string key, Variable value)
{
	if (m_datatype != Datatypes::Dictionary)
	{
		throw std::logic_error("Variable is not of type Dictionarly");
	}
	if (m_lockMode != 0 && value.getDatatype() != m_elementDatatype)
	{
		throw std::logic_error("List elements are type locked to " + datatypeName(m_elementDatatype) + " datatype.");
	}
	if (getDictionarlyElement(key).m_lockMode == 2)
	{
		throw std::logic_error("Variable is constant and can not be changed while value locked.");
	}
	value.setLockMode(1);
	((DictionaryValue*)m_value)->setValue(key, value);
}

void Variable::removeDictionarlyKey(std::string key)
{
	if (m_datatype != Datatypes::Dictionary)
	{
		throw std::logic_error("Variable is not of type Dictionarly");
	}
	((DictionaryValue*)m_value)->removeKey(key);
}

void Variable::clearDictionarlyKeys()
{
	if (m_datatype != Datatypes::Dictionary)
	{
		throw std::logic_error("Variable is not of type Dictionarly");
	}
	((DictionaryValue*)m_value)->empty();
}

Datatypes Variable::getDatatype()
{
	return m_datatype;
}

void Variable::setLockMode(unsigned int mode)
{
	if (mode < 0 || mode > 2)
	{
		throw std::invalid_argument("Not a vaild lock mode.");
	}
	m_lockMode = mode;
}

std::string Variable::datatypeName(Datatypes dt)
{
	if (dt == Datatypes::Integer)
	{
		return "Integer";
	}
	else if (dt == Datatypes::Float)
	{
		return "Float";
	}
	else if (dt == Datatypes::String)
	{
		return "String";
	}
	else if (dt == Datatypes::Boolean)
	{
		return "Boolean";
	}
	else if (dt == Datatypes::List)
	{
		return "List";
	}
	else if (dt == Datatypes::Dictionary)
	{
		return "Dictionary";
	}
	else if (dt == Datatypes::None)
	{
		return "None";
	}
	else if (dt == Datatypes::Any)
	{
		return "Any";
	}

	return "";
}

Variable Variable::createList()
{
	Variable a;
	a.makeList();
	return a;
}

Variable Variable::createList(Datatypes dt, bool locked)
{
	Variable a;
	a.makeList(dt);
	if (locked)
	{
		a.setLockMode(1);
	}
	return a;
}

Variable Variable::createDictionarly()
{
	Variable a;
	a.makeDictionarly();
	return a;
}

Variable Variable::createDictionarly(Datatypes dt, bool locked)
{
	Variable a;
	a.makeDictionarly(dt);
	if (locked)
	{
		a.setLockMode(1);
	}
	return a;
}

void Variable::operator=(const Variable& other)
{
	if (other.m_datatype == Datatypes::Integer)
	{
		m_datatype = Datatypes::Integer;
		m_value = new IntegerValue(other.getInteger());
	}
	else if (other.m_datatype == Datatypes::Float)
	{
		m_datatype = Datatypes::Float;
		m_value = new FloatValue(other.getFloat());
	}
	else if (other.m_datatype == Datatypes::String)
	{
		m_datatype = Datatypes::String;
		m_value = new StringValue(other.getString());
	}
	else if (other.m_datatype == Datatypes::Boolean)
	{
		m_datatype = Datatypes::Boolean;
		m_value = new BooleanValue(other.getBoolean());
	}
	else if (other.m_datatype == Datatypes::List)
	{
		m_datatype = Datatypes::List;
		m_value = new ListValue();
		for (int i = 0; i < ((ListValue*)other.m_value)->size(); i++)
		{
			((ListValue*)m_value)->append(other.getListElementCopy(i));
		}
	}
	else if (other.m_datatype == Datatypes::Dictionary)
	{
		m_datatype = Datatypes::Dictionary;
		m_value = new DictionaryValue();

		for (std::string key : ((DictionaryValue*)other.m_value)->getKeys())
		{
			this->setDictionarlyElement(key, ((DictionaryValue*)other.m_value)->getValue(key));
		}
	}
	else
	{
		m_value = nullptr;
		m_datatype = Datatypes::None;
	}

	m_lockMode = 0;
	m_elementDatatype = other.m_elementDatatype;
	m_elementTypeLocked = other.m_elementTypeLocked;
}
