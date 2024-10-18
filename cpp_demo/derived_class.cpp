#include <iostream>

class Base
{
public:
    // Virtual destructor, to make sure that the derived class destructor is called even when the base class pointer is used to delete the object
    virtual ~Base()
    {
        std::cout << "Base destructor called" << std::endl;
    }
};

class Derived : public Base
{
public:
    ~Derived()
    {
        std::cout << "Derived destructor called" << std::endl;
    }
};

int main()
{
    Base *b = new Derived();
    delete b; // Both Derived and Base destructors are called correctly
    return 0;
}
