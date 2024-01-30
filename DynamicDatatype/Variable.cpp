#include "Variable.h"
#include <stdexcept>
#include <iostream>
#include "ListValue.h"
#include "DictionaryValue.h"
#include "StackValue.h"
#include "QueueValue.h"
#include "PointerValue.h"

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
	else if (src.m_datatype == Datatypes::Stack)
	{
		m_datatype = Datatypes::Stack;
		m_value = new StackValue();
		((StackValue*)m_value)->m_valueStack = ((StackValue*)src.m_value)->m_valueStack;
	}
	else if (src.m_datatype == Datatypes::Queue)
	{
		m_datatype = Datatypes::Queue;
		m_value = new StackValue();
		((QueueValue*)m_value)->m_valueQueue = ((QueueValue*)src.m_value)->m_valueQueue;
	}
	else if (src.m_datatype == Datatypes::Pointer)
	{
		m_datatype = Datatypes::Pointer;
		m_value = new PointerValue(&((PointerValue*)src.m_value)->dereference());
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

Variable::Variable(Variable* reference)
{
	m_value = new PointerValue(reference);
	m_datatype = Datatypes::Pointer;
	m_elementDatatype = Datatypes::None;
	m_elementTypeLocked = false;
	m_lockMode = 0;
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

bool Variable::isError() const
{
	return m_datatype==Datatypes::Error;
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

void Variable::makeError()
{
	// Guards against using changeing datatype of variable if it is type locked
	if (m_lockMode > 0 && m_datatype != Datatypes::Error)
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
	m_datatype = Datatypes::Error;
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

void Variable::makeStack()
{
	// Guards against using changeing datatype of variable if it is type locked
	if (m_lockMode > 0 && m_datatype != Datatypes::Stack)
	{
		throw std::logic_error("Variable is type locked to a non Stack datatype.");
	}
	// Guards against using changeing value of variable if it is value locked
	if (m_lockMode == 2)
	{
		throw std::logic_error("Variable is constant and can not be changed while value locked.");
	}
	delete m_value;
	m_value = new StackValue();
	m_datatype = Datatypes::Stack;
	m_elementDatatype = Datatypes::None;
	m_elementTypeLocked = false;
}

void Variable::makeStack(Datatypes dt)
{
	// Guards against using changeing datatype of variable if it is type locked
	if (m_lockMode > 0 && m_datatype != Datatypes::Stack)
	{
		throw std::logic_error("Variable is type locked to a non Stack datatype.");
	}
	// Guards against using changeing value of variable if it is value locked
	if (m_lockMode == 2)
	{
		throw std::logic_error("Variable is constant and can not be changed while value locked.");
	}
	delete m_value;
	m_value = new StackValue();
	m_datatype = Datatypes::Stack;
	m_elementDatatype = dt;
	m_elementTypeLocked = true;
}

void Variable::makeQueue()
{
	// Guards against using changeing datatype of variable if it is type locked
	if (m_lockMode > 0 && m_datatype != Datatypes::Queue)
	{
		throw std::logic_error("Variable is type locked to a non Queue datatype.");
	}
	// Guards against using changeing value of variable if it is value locked
	if (m_lockMode == 2)
	{
		throw std::logic_error("Variable is constant and can not be changed while value locked.");
	}
	delete m_value;
	m_value = new QueueValue();
	m_datatype = Datatypes::Queue;
	m_elementDatatype = Datatypes::None;
	m_elementTypeLocked = false;
}

void Variable::makeQueue(Datatypes dt)
{
	// Guards against using changeing datatype of variable if it is type locked
	if (m_lockMode > 0 && m_datatype != Datatypes::Queue)
	{
		throw std::logic_error("Variable is type locked to a non Queue datatype.");
	}
	// Guards against using changeing value of variable if it is value locked
	if (m_lockMode == 2)
	{
		throw std::logic_error("Variable is constant and can not be changed while value locked.");
	}
	delete m_value;
	m_value = new QueueValue();
	m_datatype = Datatypes::Queue;
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
		throw std::logic_error("Dictionary elements are type locked to " + datatypeName(m_elementDatatype) + " datatype.");
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

bool Variable::isStackEmpty()
{
	// Guards against using Stack method on non-stack variable
	if (m_datatype != Datatypes::Stack)
	{
		throw std::logic_error("Variable is not of type Stack");
	}
	return ((StackValue*)m_value)->isEmpty();
}

unsigned int Variable::stackSize()
{
	// Guards against using Stack method on non-stack variable
	if (m_datatype != Datatypes::Stack)
	{
		throw std::logic_error("Variable is not of type Stack");
	}
	return ((StackValue*)m_value)->size();
}

void Variable::stackPush(Variable value)
{
	// Guards against using Stack method on non-stack variable
	if (m_datatype != Datatypes::Stack)
	{
		throw std::logic_error("Variable is not of type Stack");
	}
	// Guards against pushing value that does not match element type when elements are type locked
	if (m_elementTypeLocked == true && value.getDatatype() != m_elementDatatype)
	{
		throw std::logic_error("Stack elements are type locked to " + datatypeName(m_elementDatatype) + " datatype.");
	}
	((StackValue*)m_value)->push(value);
}

Variable Variable::stackPop()
{
	// Guards against using Stack method on non-stack variable
	if (m_datatype != Datatypes::Stack)
	{
		throw std::logic_error("Variable is not of type Stack");
	}
	return ((StackValue*)m_value)->pop();
}

Variable& Variable::stackTop()
{
	// Guards against using Stack method on non-stack variable
	if (m_datatype != Datatypes::Stack)
	{
		throw std::logic_error("Variable is not of type Stack");
	}
	return ((StackValue*)m_value)->top();
}

bool Variable::QueueEmpty()
{
	// Guards against using Queue method on non-stack variable
	if (m_datatype != Datatypes::Queue)
	{
		throw std::logic_error("Variable is not of type Queue");
	}
	return ((QueueValue*)m_value)->isEmpty();
}

unsigned int Variable::QueueSize()
{
	// Guards against using Queue method on non-stack variable
	if (m_datatype != Datatypes::Queue)
	{
		throw std::logic_error("Variable is not of type Queue");
	}
	return ((QueueValue*)m_value)->size();
}

void Variable::QueuePush(Variable value)
{
	// Guards against using Queue method on non-stack variable
	if (m_datatype != Datatypes::Queue)
	{
		throw std::logic_error("Variable is not of type Queue");
	}
	// Guards against pushing value that does not match element type when elements are type locked
	if (m_elementTypeLocked == true && value.getDatatype() != m_elementDatatype)
	{
		throw std::logic_error("Queue elements are type locked to " + datatypeName(m_elementDatatype) + " datatype.");
	}
	return ((QueueValue*)m_value)->push(value);
}

Variable& Variable::QueueFront()
{
	// Guards against using Queue method on non-stack variable
	if (m_datatype != Datatypes::Queue)
	{
		throw std::logic_error("Variable is not of type Queue");
	}
	return ((QueueValue*)m_value)->front();
}

Variable Variable::QueuePop()
{
	// Guards against using Queue method on non-stack variable
	if (m_datatype != Datatypes::Queue)
	{
		throw std::logic_error("Variable is not of type Queue");
	}
	return ((QueueValue*)m_value)->pop();
}

Variable& Variable::pointerDereference()
{
	// Guards against using Pointer method on non-pointer variable
	if (m_datatype != Datatypes::Pointer)
	{
		throw std::logic_error("Variable is not of type Pointer");
	}
	return ((PointerValue*)m_value)->dereference();
}

Datatypes Variable::getDatatype() const
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

Variable Variable::castInterger(Variable value)
{
	
	if (value.getDatatype() == Datatypes::Integer)
	{
		return value;
	}
	else if (value.getDatatype() == Datatypes::Float)
	{
		return Variable((int)value.getFloat());
	}
	else if (value.getDatatype() == Datatypes::String)
	{
		return Variable(std::stoi(value.getString()));
	}
	else if (value.getDatatype() == Datatypes::Boolean)
	{
		return Variable(value.getBoolean()?1:0);
	}
	else
	{
		Variable ans;
		ans.makeError();
		return ans;
	}
}

Variable Variable::castFloat(Variable value)
{
	if (value.getDatatype() == Datatypes::Integer)
	{
		return Variable((float)value.getInteger());
	}
	else if (value.getDatatype() == Datatypes::Float)
	{
		return value;
	}
	else if (value.getDatatype() == Datatypes::String)
	{
		return Variable(std::stof(value.getString()));
	}
	else if (value.getDatatype() == Datatypes::Boolean)
	{
		return Variable(value.getBoolean() ? 1.0 : 0.0);
	}
	else
	{
		Variable ans;
		ans.makeError();
		return ans;
	}
}

Variable Variable::castString(Variable value)
{
	if (value.getDatatype() == Datatypes::Integer)
	{
		return Variable(std::to_string(value.getInteger()));
	}
	else if (value.getDatatype() == Datatypes::Float)
	{
		return Variable(std::to_string(value.getFloat()));
	}
	else if (value.getDatatype() == Datatypes::String)
	{
		return value;
	}
	else if (value.getDatatype() == Datatypes::Boolean)
	{
		return Variable(value.getBoolean() ? "true" : "false");
	}
	else
	{
		Variable ans;
		ans.makeError();
		return ans;
	}
}

Variable Variable::castBoolean(Variable value)
{
	if (value.getDatatype() == Datatypes::Integer)
	{
		return Variable(value.getInteger()>0?true:false);
	}
	else if (value.getDatatype() == Datatypes::Float)
	{
		return Variable(value.getFloat() > 0 ? true : false);
	}
	else if (value.getDatatype() == Datatypes::String)
	{
		if (value.getString() == "true" || value.getString() == "True")
		{
			return Variable(true);
		}
		else if (value.getString() == "false" || value.getString() == "False")
		{
			return Variable(false);
		}
		else
		{
			Variable ans;
			ans.makeError();
			return ans;
		}
	}
	else if (value.getDatatype() == Datatypes::Boolean)
	{
		return value;
	}
	else
	{
		Variable ans;
		ans.makeError();
		return ans;
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
	else if (dt == Datatypes::Stack)
	{
		return "Stack";
	}
	else if (dt == Datatypes::Error)
	{
		return "Error";
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

Variable Variable::createStack()
{
	Variable a;
	a.makeStack();
	return a;
}

Variable Variable::createStack(Datatypes dt, bool locked)
{
	Variable a;
	a.makeStack(dt);
	if (locked)
	{
		a.setLockMode(1);
	}
	return a;
}

Variable Variable::createQueue()
{
	Variable a;
	a.makeQueue();
	return a;
}

Variable Variable::createQueue(Datatypes dt, bool locked)
{
	Variable a;
	a.makeQueue(dt);
	if (locked)
	{
		a.setLockMode(1);
	}
	return a;
}

void Variable::operator=(const Variable& other)
{
	if (m_lockMode > 0 && m_datatype != other.getDatatype())
	{
		throw std::logic_error("Can not assign value of differnt type to type locked variable.");
	}
	if (m_lockMode == 2)
	{
		throw std::logic_error("Can not assign value to a value locked variable.");
	}
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
	else if (other.m_datatype == Datatypes::Stack)
	{
		m_datatype = Datatypes::Stack;
		m_value = new StackValue();
		((StackValue*)m_value)->m_valueStack = ((StackValue*)other.m_value)->m_valueStack;
	}
	else if (other.m_datatype == Datatypes::Queue)
	{
		m_datatype = Datatypes::Queue;
		m_value = new StackValue();
		((QueueValue*)m_value)->m_valueQueue = ((QueueValue*)other.m_value)->m_valueQueue;
	}
	else if (other.m_datatype == Datatypes::Pointer)
	{
		m_datatype = Datatypes::Pointer;
		m_value = new PointerValue(&((PointerValue*)other.m_value)->dereference());
	}
	else
	{
		m_value = nullptr;
		m_datatype = Datatypes::None;
	}

	m_elementDatatype = other.m_elementDatatype;
	m_elementTypeLocked = other.m_elementTypeLocked;
}

Variable operator+(const Variable& lhs, const Variable& rhs)
{
	if (lhs.m_datatype == rhs.m_datatype)
	{
		Variable ans;
		if (lhs.m_datatype == Datatypes::Integer)
		{
			ans.setInteger(lhs.getInteger() + rhs.getInteger());
		}
		else if (lhs.m_datatype == Datatypes::Float)
		{
			ans.setFloat(lhs.getFloat() + rhs.getFloat());
		}
		else if (lhs.m_datatype == Datatypes::String)
		{
			ans.setString(lhs.getString() + rhs.getString());
		}
		else
		{
			ans.makeError();
		}
		return ans;
	}
	else
	{
		Variable ans;
		if (lhs.m_datatype == Datatypes::Integer || rhs.m_datatype == Datatypes::Integer 
			&& lhs.m_datatype == Datatypes::Float || rhs.m_datatype == Datatypes::Float)
		{
			ans.setFloat((Variable::castFloat(lhs)+ Variable::castFloat(rhs)).getFloat());
		}
		else
		{
			ans.makeError();
		}
		return ans;
	}
}

Variable operator-(const Variable& lhs, const Variable& rhs)
{
	if (lhs.m_datatype == rhs.m_datatype)
	{
		Variable ans;
		if (lhs.m_datatype == Datatypes::Integer)
		{
			ans.setInteger(lhs.getInteger() - rhs.getInteger());
		}
		else if (lhs.m_datatype == Datatypes::Float)
		{
			ans.setFloat(lhs.getFloat() - rhs.getFloat());
		}
		else
		{
			ans.makeError();
		}
		return ans;
	}
	else
	{
		Variable ans;
		if (lhs.m_datatype == Datatypes::Integer || rhs.m_datatype == Datatypes::Integer
			&& lhs.m_datatype == Datatypes::Float || rhs.m_datatype == Datatypes::Float)
		{
			ans.setFloat((Variable::castFloat(lhs) - Variable::castFloat(rhs)).getFloat());
		}
		else
		{
			ans.makeError();
		}
	}
}
