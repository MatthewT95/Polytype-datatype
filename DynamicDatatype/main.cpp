#include "Variable.h"
#include <iostream>

int main()
{
    Variable a;
    a.makeList();
   

    try
    {
       a.appendElement(Variable(true));
       a.appendNewList();
       a.getElement(1).appendElement(Variable("jj"));
       std::cout << a.getElement(1).getElement(0).getString() << "\n";
    }
    catch(std::exception ex)
    {
        std::cout << ex.what();
    }
    
}
