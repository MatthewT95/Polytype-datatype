# Datatypes

[Integer](#integer)
[Float](#float)
[String](#string)
[Boolean](#boolean)
[List](#list)

## Single value types

### Integer
The integer datatype stores a single whole number which can be negative,positive or zero.

Header:
```cpp
// Creates a new Integer Variable with given value and lockmode
Variable(int value, int lockMode = 0);
// Assigns integer value to Variable.
// If type locked to a none integer type exception will be throw
// If value locked error will be thrown
void setInteger(long long value);
// Returns an integer if Variable is of type integer
// If not of type integer exception will be throw
long long getInteger() const;
// casts a variable to type integer
static Variable castInterger(Variable value);
```
Examples:
```cpp
Variable(20); // Creates a integer variable with value of 20
Variable(32,1); // Creates a integer Variable that is locked to the integer type with a value of 32
Variable(40,2); // Creates a constant with value of 40

Variable a(20);
a.setInteger(20) // Sets value to Integer 20
a.getInterger(); // returns int with value 20
```

### Float

The float datatype stores a single real number which can be negative,positive or zero.

Header:
```cpp
// Creates a new float Variable with given value and lockmode
Variable(double value, int lockMode = 0);
// Assigns float value to Variable.
// If type locked to a none float type exception will be throw
// If value locked error will be thrown
void setFloat(double value);
// Returns an double if Variable is of type float
// If not of type float exception will be throw
double getFloat() const;
// casts a variable to type float
static Variable castFloat(Variable value);
```
Examples:
```cpp
Variable(22.5); // Creates a float variable with value of 20.5
Variable(32.6,1); // Creates a float Variable that is locked to the float type with a value of 32.6
Variable(40.5,2); // Creates a constant with value of 40.5.

Variable a(20.67);
a.setFloat(30.34) // Sets value to Float 30.34
a.getFloat(); // returns double with value 30.34
```

### String

The string datatype stores a string of text.

Header:
```cpp
// Creates a new string Variable with given value and lockmode
Variable(std::string value, int lockMode = 0);
// Assigns string value to Variable.
// If type locked to a none string type exception will be throw
// If value locked error will be thrown
void setString(std::string value);
// Returns an string if Variable is of type string
// If not of type string exception will be throw
std::string getString() const;
// casts a variable to type string
static Variable castString(Variable value);
```
Examples:
```cpp
Variable("apple"); // Creates a float variable with value of "apple"
Variable("pizza",1); // Creates a string Variable that is locked to the string type with a value of "pizza"
Variable("fruit",2); // Creates a constant with value of "fruit".

Variable a("orange");
a.setString("pie") // Sets value to string "pie"
a.getString() // returns std::string with value "pie"
```

### Boolean

The boolean datatype stores a true or false value.

Header:
```cpp
// Creates a new boolean Variable with given value and lockmode
Variable(bool value, int lockMode = 0);
// Assigns boolean value to Variable.
// If type locked to a none boolean type exception will be throw
// If value locked error will be thrown
void setBoolean(bool value);
// Returns an bool if Variable is of type boolean
// If not of type boolean exception will be throw
bool getBoolean() const;
// casts a variable to type boolean
static Variable castBoolean(Variable value);
```
Examples:
```cpp
Variable(true); // Creates a boolean variable with value of true
Variable(false,1); // Creates a boolean Variable that is locked to the string type with a value of false
Variable(true,2); // Creates a constant with value of true.

Variable a(true);
a.setString(false) // Sets value to boolean false
a.getString() // returns bool with value false
```

## Collection datatypes

### List
The list type can store a collection of Variables in indexable list. A list can be locked to store only store elements of a specific datatype.

Header:
```cpp
// Makes target variable a empty list
void makeList();
// Makes target variable a empty list locked to specific datatype
void makeList(Datatypes dt);
// Returns an empty list.
// Use when appending a element to list or dictionarly that has its elements
//   locked to list type
static Variable createList();
// Returns an empty list locked to a specific datatype
// Use when appending a element to list or dictionarly that has its elements
//   locked to list type
static Variable createList(Datatypes dt, bool locked = false);
// Appends a Variable to the list
// We throw exception if list is type locked to a type different then the value
void appendListElement(Variable value);
// Returns a Variable reference to a list element
Variable& getListElement(unsigned int index);
// Returns a Variable value of list element
Variable getListElementCopy(unsigned int index) const;
// Updates the value of an element at given index
// We throw exception if list is type locked to a type different then the value
void setListElement(unsigned int index, Variable value);
// Removes an element at given index in list
void removeListElement(unsigned int index);
// Returns the total number of elements in the list
unsigned int getListElementsCount();
// Removes all elements from list
void clearListElements();
// Adds elements of fillValue untill list reaches target size
void fillList(unsigned int targetSize, Variable fillValue);
// Repeatly removes last element until list reaches target size
void pruneList(unsigned int targetSize);
// If variable is of type list, this will return a reference to element at given index
Variable& operator[](unsigned int index);
```

**Creating a new list**
```cpp
Variable a;
Variable b;
// Makes a empty list
a.makeList();
// Makes b an empty list locked to integers
b.makeList(Datatypes::Integer);

// Declares c to be an empty list
Variable c = Variable::createList();
// Declares d to be an empty list locked to booleans
Variable d = Variable::createList(Datatypes::boolean);
```

**Appending, setting and accessing list elements**
```cpp
// Creates a new list
Variable list=Variable::createList();
// Appends string value to list
list.appendListElement(Variable("Apple"));
// Appends empty list to list
list.appendListElement(Variable::createList());
// Appends integer 12 to nested list
list[1].appendElement(Variable(12));

// Accesses list using getListElement
std::cout << list.getListElement(0).getString() << "\n";
// Access list using []
std::cout << list[1][0].getInteger() << "\n";
```
output
```
Apple
12
```
### Dictionary

### Stack

### Queue

## Reference datatypes

### Pointer

## Special datatypes

### None

### Any

### Error
