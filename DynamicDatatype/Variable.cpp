#include "Variable.h"
#include <stdexcept>
#include <iostream>

Variable::Variable()
{
	m_value = nullptr;
	m_datatype = Datatypes::None;
	m_typeLocked = false;
	m_elementDatatype = Datatypes::None;
	m_elementTypeLocked = false;
}

Variable::Variable(const Variable& src)
{
	m_datatype = Datatypes::None;
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
			//((ListValue*)m_value)->append(src.getElement(i));
		}
	}

	m_typeLocked = src.m_typeLocked;
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

Variable::Variable(int value,bool locked)
{
	m_value = new IntegerValue(value);
	m_typeLocked = locked;
	m_datatype = Datatypes::Integer;
	m_elementDatatype = Datatypes::None;
	m_elementTypeLocked = false;
}

Variable::Variable(double value, bool locked)
{
	m_value = new FloatValue(value);
	m_typeLocked = locked;
	m_datatype = Datatypes::Float;
	m_elementDatatype = Datatypes::None;
	m_elementTypeLocked = false;
}

Variable::Variable(std::string value, bool locked)
{
	m_value = new StringValue(value);
	m_typeLocked = locked;
	m_datatype = Datatypes::String;
	m_elementDatatype = Datatypes::None;
	m_elementTypeLocked = false;
}

Variable::Variable(const char* value, bool locked)
{
	m_value = new StringValue(std::string(value));
	m_typeLocked = locked;
	m_datatype = Datatypes::String;
	m_elementDatatype = Datatypes::None;
	m_elementTypeLocked = false;
}

Variable::Variable(bool value, bool locked)
{
	m_value = new BooleanValue(value);
	m_typeLocked = locked;
	m_datatype = Datatypes::Boolean;
	m_elementDatatype = Datatypes::None;
	m_elementTypeLocked = false;
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
	if (m_typeLocked == false || m_datatype == Datatypes::Integer)
	{
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
	if (m_typeLocked == false || m_datatype == Datatypes::Float)
	{
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
	if (m_typeLocked == false || m_datatype == Datatypes::String)
	{
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
	if (m_typeLocked == false || m_datatype == Datatypes::Boolean)
	{
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
	if (m_typeLocked == false || m_datatype == Datatypes::List)
	{
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
	if (m_typeLocked == false || m_datatype == Datatypes::List)
	{
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

void Variable::appendElement(Variable value)
{
	if (m_datatype == Datatypes::List)
	{
		if (m_elementTypeLocked == false || value.getDatatype() == m_elementDatatype)
		{
			value.lock();
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

void Variable::appendNewList()
{
	if (m_datatype == Datatypes::List)
	{
		if (m_elementTypeLocked == false || Datatypes::List == m_elementDatatype)
		{
			((ListValue*)m_value)->appendNewList();
			if (m_elementTypeLocked)
			{
				((ListValue*)m_value)->getElement(((ListValue*)m_value)->size() - 1).lock();
			}
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

Variable& Variable::getElement(unsigned int index)
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

void Variable::setElement(unsigned int index, Variable value)
{
	if (m_datatype == Datatypes::List)
	{
		if (m_elementTypeLocked == false || value.getDatatype() == m_elementDatatype)
		{
			value.lock();
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

void Variable::removeElement(unsigned int index)
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

unsigned int Variable::getElementsCount()
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

void Variable::clearElements()
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

void Variable::makeElementList(unsigned int index)
{
	if (m_datatype == Datatypes::List)
	{
		((ListValue*)m_value)->makeElementList(index);
	}
	else
	{
		throw std::logic_error("Variable is not of type List");
	}
}

Datatypes Variable::getDatatype()
{
	return m_datatype;
}

void Variable::lock()
{
	m_typeLocked = true;
}

void Variable::unlock()
{
	m_typeLocked = false;
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
	else if (dt == Datatypes::Dictionarly)
	{
		return "Dictionarly";
	}
	else if (dt == Datatypes::None)
	{
		return "None";
	}

	return "";
}
