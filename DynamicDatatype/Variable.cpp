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

	m_lockMode = m_lockMode > 0 ? 1 : 0;
	m_elementDatatype = src.m_elementDatatype;
	m_elementTypeLocked = src.m_elementTypeLocked;
}

Variable::~Variable()
{
	if (m_value != nullptr)
	{
		//delete m_value;
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
	if (m_datatype == Datatypes::Integer)
	{
		return ((IntegerValue*)m_value)->getValue();
	}
	else
	{
		throw std::logic_error("Variable is not of type Integer.");
	}
}

double Variable::getFloat() const
{
	if (m_datatype == Datatypes::Float)
	{
		return ((FloatValue*)m_value)->getValue();
	}
	else
	{
		throw std::logic_error("Variable is not of type Float.");
	}
}

std::string Variable::getString() const
{
	if (m_datatype == Datatypes::String)
	{
		return ((StringValue*)m_value)->getValue();
	}
	else
	{
		throw std::logic_error("Variable is not of type String.");
	}
}

bool Variable::getBoolean() const
{
	if (m_datatype == Datatypes::Boolean) 
	{
		return ((BooleanValue*)m_value)->getValue();
	}
	else
	{
		throw std::logic_error("Variable is not of type Boolean.");
	}
}

std::vector<Variable>& Variable::getList() const
{
	if (m_datatype == Datatypes::List)
	{
		//return ((ListValue*)m_value)->m_values;
	}
	else
	{
		throw std::logic_error("Variable is not of type List.");
	}
}

bool Variable::isNone() const
{
	return m_datatype==Datatypes::None;
}

void Variable::setInteger(long long value)
{
	if (m_lockMode == 0 || m_datatype == Datatypes::Integer)
	{
		if (m_lockMode == 2)
		{
			throw std::logic_error("Variable is constant and can not be changed while value locked.");
		}
		delete m_value;
		m_value = new IntegerValue(value);
		m_datatype = Datatypes::Integer;
	}
	else
	{
		throw std::logic_error("Variable is type locked to a non Integer datatype.");
	}
}

void Variable::setFloat(double value)
{
	if (m_lockMode == 0 || m_datatype == Datatypes::Float)
	{
		if (m_lockMode == 2)
		{
			throw std::logic_error("Variable is constant and can not be changed while value locked.");
		}
		delete m_value;
		m_value = new FloatValue(value);
		m_datatype = Datatypes::Float;
	}
	else
	{
		throw std::logic_error("Variable is type locked to a non Float datatype.");
	}
}

void Variable::setString(std::string value)
{
	if (m_lockMode == 0 || m_datatype == Datatypes::String)
	{
		if (m_lockMode == 2)
		{
			throw std::logic_error("Variable is constant and can not be changed while value locked.");
		}
		delete m_value;
		m_value = new StringValue(value);
		m_datatype = Datatypes::String;
	}
	else
	{
		throw std::logic_error("Variable is type locked to a non String datatype.");
	}
}

void Variable::setBoolean(bool value)
{
	if (m_lockMode == 0 || m_datatype == Datatypes::Boolean)
	{
		if (m_lockMode == 2)
		{
			throw std::logic_error("Variable is constant and can not be changed while value locked.");
		}
		delete m_value;
		m_value = new BooleanValue(value);
		m_datatype = Datatypes::Boolean;
	}
	else
	{
		throw std::logic_error("Variable is type locked to a non Boolean datatype.");
	}
}

void Variable::makeList()
{
	if (m_lockMode == 0 || m_datatype == Datatypes::List)
	{
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
	else
	{
		throw std::logic_error("Variable is type locked to a non List datatype.");
	}
}

void Variable::makeList(Datatypes dt)
{
	if (m_lockMode == 0 || m_datatype == Datatypes::List)
	{
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
	else
	{
		throw std::logic_error("Variable is type locked to a non List datatype.");
	}
}

void Variable::makeNone()
{
	delete m_value;
	m_value = nullptr;
	m_datatype = Datatypes::None;
	m_elementDatatype = Datatypes::None;
	m_elementTypeLocked = false;
}

void Variable::makeDictionarly()
{
	if (m_lockMode == 0 || m_datatype == Datatypes::Dictionary)
	{
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
	else
	{
		throw std::logic_error("Variable is type locked to a non List datatype.2");
	}
}

void Variable::makeDictionarly(Datatypes dt)
{
	if (m_lockMode == 0 || m_datatype == Datatypes::Dictionary)
	{
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
	else
	{
		throw std::logic_error("Variable is type locked to a non List datatype.");
	}
}

void Variable::appendListElement(Variable value)
{
	if (m_datatype == Datatypes::List)
	{
		if (m_lockMode == 0 || value.getDatatype() == m_elementDatatype)
		{
			if (m_elementTypeLocked)
			{
				value.setLockMode(1);
			}
			((ListValue*)m_value)->append(value);
		}
		else
		{
			throw std::logic_error("List elements are type locked to " + datatypeName(m_elementDatatype) + " datatype.");
		}
	}
	else
	{
		throw std::logic_error("Variable is not of type List");
	}
}

Variable& Variable::getListElement(unsigned int index)
{
	if (m_datatype == Datatypes::List)
	{
		return ((ListValue*)m_value)->getElement(index);
	}
	else
	{
		throw std::logic_error("Variable is not of type List");
	}
}

Variable Variable::getListElementCopy(unsigned int index) const
{
	if (m_datatype == Datatypes::List)
	{
		return ((ListValue*)m_value)->getElement(index);
	}
	else
	{
		throw std::logic_error("Variable is not of type List");
	}
}

void Variable::setListElement(unsigned int index, Variable value)
{
	if (m_datatype == Datatypes::List)
	{
		if (m_lockMode == 0 || value.getDatatype() == m_elementDatatype)
		{
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
		else
		{
			throw std::logic_error("List elements are type locked to " + datatypeName(m_elementDatatype) + " datatype.");
		}
	}
	else
	{
		throw std::logic_error("Variable is not of type List");
	}
}

void Variable::removeListElement(unsigned int index)
{
	if (m_datatype == Datatypes::List)
	{
		return ((ListValue*)m_value)->remove(index);
	}
	else
	{
		throw std::logic_error("Variable is not of type List");
	}
}

unsigned int Variable::getListElementsCount()
{
	if (m_datatype == Datatypes::List)
	{
		return ((ListValue*)m_value)->size();
	}
	else
	{
		throw std::logic_error("Variable is not of type List");
	}
}

void Variable::clearListElements()
{
	if (m_datatype == Datatypes::List)
	{
		return ((ListValue*)m_value)->empty();
	}
	else
	{
		throw std::logic_error("Variable is not of type List");
	}
}

void Variable::fillList(unsigned int targetSize, Variable fillValue)
{
	if (m_datatype == Datatypes::List)
	{
		while (((ListValue*)m_value)->size() < targetSize)
		{
			((ListValue*)m_value)->append(fillValue);
		}
	}
	else
	{
		throw std::logic_error("Variable is not of type List");
	}
}

void Variable::pruneList(unsigned int targetSize)
{
	if (m_datatype == Datatypes::List)
	{
		while (((ListValue*)m_value)->size() > targetSize)
		{
			((ListValue*)m_value)->remove(((ListValue*)m_value)->size()-1);
		}
	}
	else
	{
		throw std::logic_error("Variable is not of type List");
	}
}

bool Variable::keyExists(std::string key)
{
	if (m_datatype == Datatypes::Dictionary)
	{
		return ((DictionaryValue*)m_value)->keyExists(key);
	}
	else
	{
		throw std::logic_error("Variable is not of type Dictionarly");
	}
}

Variable& Variable::getDictionarlyElement(std::string key)
{
	if (m_datatype == Datatypes::Dictionary)
	{
		return ((DictionaryValue*)m_value)->getValue(key);
	}
	else
	{
		throw std::logic_error("Variable is not of type Dictionarly");
	}
}

void Variable::setDictionarlyElement(std::string key, Variable value)
{
	if (m_datatype == Datatypes::Dictionary)
	{
		if (m_lockMode == 0 || value.getDatatype() == m_elementDatatype)
		{
			if (getDictionarlyElement(key).m_lockMode == 2)
			{
				throw std::logic_error("Variable is constant and can not be changed while value locked.");
			}
			value.setLockMode(1);
			((DictionaryValue*)m_value)->setValue(key, value);
		}
		else
		{
			throw std::logic_error("List elements are type locked to " + datatypeName(m_elementDatatype) + " datatype.");
		}
	}
	else
	{
		throw std::logic_error("Variable is not of type Dictionarly");
	}
}

void Variable::removeDictionarlyKey(std::string key)
{
	if (m_datatype == Datatypes::Dictionary)
	{
		((DictionaryValue*)m_value)->removeKey(key);
	}
	else
	{
		throw std::logic_error("Variable is not of type Dictionarly");
	}
}

void Variable::clearDictionarlyKeys()
{
	if (m_datatype == Datatypes::Dictionary)
	{
		((DictionaryValue*)m_value)->empty();
	}
	else
	{
		throw std::logic_error("Variable is not of type Dictionarly");
	}
}

Datatypes Variable::getDatatype()
{
	return m_datatype;
}

void Variable::setLockMode(unsigned int mode)
{
	if (mode >= 0 && mode <= 2)
	{
		m_lockMode = mode;
	}
	else
	{
		throw std::invalid_argument("Not a vaild lock mode.");
	}
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
