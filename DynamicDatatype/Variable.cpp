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
	// Guards against using Interger method on non-integer variable
	if (m_datatype != Datatypes::Integer)
	{
		throw std::logic_error("Variable is not of type Integer.");
	}
	return ((IntegerValue*)m_value)->getValue();

}

double Variable::getFloat() const
{
	// Guards against using Float method on non-float variable
	if (m_datatype != Datatypes::Float)
	{
		throw std::logic_error("Variable is not of type Float.");
	}
	return ((FloatValue*)m_value)->getValue();
}

std::string Variable::getString() const
{
	// Guards against using String method on non-string variable
	if (m_datatype != Datatypes::String)
	{
		throw std::logic_error("Variable is not of type String.");
	}
	return ((StringValue*)m_value)->getValue();
}

bool Variable::getBoolean() const
{
	// Guards against using Boolean method on non-boolean variable
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
	// Guards against using changing datatype of variable if it is locked
	if (m_lockMode > 0 && m_datatype != Datatypes::Integer)
	{
		throw std::logic_error("Variable is type locked to a non Integer datatype.");
	}
	// Guards against using changing value of variable if it is locked
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
	// Guards against using changing datatype of variable if it is type locked
	if (m_lockMode > 0 && m_datatype != Datatypes::Float)
	{
		throw std::logic_error("Variable is type locked to a non Float datatype.");
	}
	// Guards against using changing value of variable if it is value locked
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
	// Guards against using changeing datatype of variable if it is type locked
	if (m_lockMode > 0 && m_datatype != Datatypes::String)
	{
		throw std::logic_error("Variable is type locked to a non String datatype.");
	}
	// Guards against using changeing value of variable if it is value locked
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
	// Guards against using changeing datatype of variable if it is type locked
	if (m_lockMode > 0 && m_datatype != Datatypes::Boolean)
	{
		throw std::logic_error("Variable is type locked to a non Boolean datatype.");
	}
	// Guards against using changeing value of variable if it is value locked
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
	// Guards against using changeing datatype of variable if it is type locked
	if (m_lockMode > 0 && m_datatype != Datatypes::List)
	{
		throw std::logic_error("Variable is type locked to a non List datatype.");
	}
	// Guards against using changeing value of variable if it is value locked
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
	// Guards against using changeing datatype of variable if it is type locked
	if (m_lockMode > 0 && m_datatype != Datatypes::List)
	{
		throw std::logic_error("Variable is type locked to a non List datatype.");
	}
	// Guards against using changeing value of variable if it is value locked
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
	// Guards against using changeing datatype of variable if it is type locked
	if (m_lockMode > 0 && m_datatype != Datatypes::None)
	{
		throw std::logic_error("Variable is type locked to a non None datatype.");
	}
	// Guards against using changeing value of variable if it is value locked
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
	// Guards against using changeing datatype of variable if it is type locked
	if (m_lockMode > 0 && m_datatype != Datatypes::Dictionary)
	{
		throw std::logic_error("Variable is type locked to a non Dictionary datatype.");
	}
	// Guards against using changeing value of variable if it is value locked
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
	// Guards against using changeing datatype of variable if it is type locked
	if (m_lockMode > 0 && m_datatype != Datatypes::Dictionary)
	{
		throw std::logic_error("Variable is type locked to a non Dictionary datatype.");
	}
	// Guards against using changeing value of variable if it is value locked
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
	// Guards against using changeing datatype of variable if it is type locked
	if (m_datatype != Datatypes::List)
	{
		throw std::logic_error("Variable is not of type List");
	}
	// Guards against using changeing datatype of variable if it is value locked
	if (m_elementTypeLocked != 0 && value.getDatatype() != m_elementDatatype)
	{
		throw std::logic_error("List elements are type locked to " + datatypeName(m_elementDatatype) + " datatype.");
	}
	// Locks the element if collection elements are suppost to type locked
	if (m_elementTypeLocked)
	{
		value.setLockMode(1);
	}
	((ListValue*)m_value)->append(value);
}

Variable& Variable::getListElement(unsigned int index)
{
	// Guards against using List method on non-list variable
	if (m_datatype != Datatypes::List)
	{
		throw std::logic_error("Variable is not of type List");
	}
	return ((ListValue*)m_value)->getElement(index);
}

Variable Variable::getListElementCopy(unsigned int index) const
{
	// Guards against using List method on non-list variable
	if (m_datatype != Datatypes::List)
	{
		throw std::logic_error("Variable is not of type List");
	}
	return ((ListValue*)m_value)->getElement(index);
}

void Variable::setListElement(unsigned int index, Variable value)
{
	// Guards against using List method on non-list variable
	if (m_datatype != Datatypes::List)
	{
		throw std::logic_error("Variable is not of type List");
	}
	// Guards against setting collection element to wrong type if element type locked
	if (m_lockMode != 0 && value.getDatatype() != m_elementDatatype)
	{
		throw std::logic_error("List elements are type locked to " + datatypeName(m_elementDatatype) + " datatype.");
	}
	// Guards against changing variable type if type locked
	if (getListElement(index).m_lockMode == 1)
	{
		throw std::logic_error("Variable in list at index " + std::to_string(index) + " is type locked to " +
			datatypeName(getListElement(index).getDatatype()));
	}
	// Guards against changing value of variable that is value locked
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
	// Guards against using List method on non-list variable
	if (m_datatype != Datatypes::List)
	{
		throw std::logic_error("Variable is not of type List");
	}
	return ((ListValue*)m_value)->remove(index);
}

unsigned int Variable::getListElementsCount()
{
	// Guards against using List method on non-list variable
	if (m_datatype != Datatypes::List)
	{
		throw std::logic_error("Variable is not of type List");
	}
	return ((ListValue*)m_value)->size();
}

void Variable::clearListElements()
{
	// Guards against using List method on non-list variable
	if (m_datatype != Datatypes::List)
	{
		throw std::logic_error("Variable is not of type List");
	}
	return ((ListValue*)m_value)->empty();
}

void Variable::fillList(unsigned int targetSize, Variable fillValue)
{
	// Guards against using List method on non-list variable
	if (m_datatype != Datatypes::List)
	{
		throw std::logic_error("Variable is not of type List");
	}
	// Guards against filling collection with elements of the wrong type if element type locked
	if (m_lockMode != 0 && m_elementDatatype != fillValue.getDatatype())
	{
		throw std::logic_error("List elements are type locked to " + datatypeName(m_elementDatatype) + " datatype.");
	}
	// Fills list with elements untill desired size is met
	while (((ListValue*)m_value)->size() < targetSize)
	{
		if (m_elementTypeLocked)
		{
			fillValue.setLockMode(1);
		}
		((ListValue*)m_value)->append(fillValue);
	}
}

void Variable::pruneList(unsigned int targetSize)
{
	// Guards against using List method on non-list variable
	if (m_datatype != Datatypes::List)
	{
		throw std::logic_error("Variable is not of type List");
	}
	// Removes elements until desired size is met
	while (((ListValue*)m_value)->size() > targetSize)
	{
		((ListValue*)m_value)->remove(((ListValue*)m_value)->size()-1);
	}
}

bool Variable::keyExists(std::string key)
{
	// Guards against using Dictionary method on non-dictionary variable
	if (m_datatype != Datatypes::Dictionary)
	{
		throw std::logic_error("Variable is not of type Dictionarly");
	}
	return ((DictionaryValue*)m_value)->keyExists(key);
}

Variable& Variable::getDictionarlyElement(std::string key)
{
	// Guards against using Dictionary method on non-dictionary variable
	if (m_datatype != Datatypes::Dictionary)
	{
		throw std::logic_error("Variable is not of type Dictionarly");
	}
	return ((DictionaryValue*)m_value)->getValue(key);
}

void Variable::setDictionarlyElement(std::string key, Variable value)
{
	// Guards against using Dictionary method on non-dictionary variable
	if (m_datatype != Datatypes::Dictionary)
	{
		throw std::logic_error("Variable is not of type Dictionarly");
	}
	// Guards against setting collection element to wrong type if element type locked
	if (m_lockMode != 0 && value.getDatatype() != m_elementDatatype)
	{
		throw std::logic_error("List elements are type locked to " + datatypeName(m_elementDatatype) + " datatype.");
	}
	// Guards against changing element value if element is value locked
	if (getDictionarlyElement(key).m_lockMode == 2)
	{
		throw std::logic_error("Variable is constant and can not be changed while value locked.");
	}
	if (m_elementTypeLocked)
	{
		value.setLockMode(1);
	}
	((DictionaryValue*)m_value)->setValue(key, value);
}

void Variable::removeDictionarlyKey(std::string key)
{
	// Guards against using Dictionary method on non-dictionary variable
	if (m_datatype != Datatypes::Dictionary)
	{
		throw std::logic_error("Variable is not of type Dictionarly");
	}
	((DictionaryValue*)m_value)->removeKey(key);
}

void Variable::clearDictionarlyKeys()
{
	// Guards against using Dictionary method on non-dictionary variable
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
	// Guards against mode setting being invaild
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
