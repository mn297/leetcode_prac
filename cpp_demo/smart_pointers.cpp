#include <iostream>
#include <memory>

using namespace std;

class Demo
{
public:
    Demo(int val) : value(val)
    {
        cout << "Constructor called for value: " << value << endl;
    }

    ~Demo()
    {
        cout << "Destructor called for value: " << value << endl;
    }

    void display() const
    {
        cout << "Value: " << value << endl;
    }

private:
    int value;
};

int main()
{
    // Demonstration of unique_ptr
    cout << "\n=== unique_ptr Demonstration ===" << endl;
    unique_ptr<Demo> uniquePtr1 = make_unique<Demo>(10);
    uniquePtr1->display();

    // Transfer ownership to another unique_ptr
    unique_ptr<Demo> uniquePtr2 = move(uniquePtr1);
    if (!uniquePtr1)
    {
        cout << "uniquePtr1 is now nullptr after move." << endl;
    }
    uniquePtr2->display();

    // Demonstration of shared_ptr
    cout << "\n=== shared_ptr Demonstration ===" << endl;
    shared_ptr<Demo> sharedPtr1 = make_shared<Demo>(20);
    shared_ptr<Demo> sharedPtr2 = sharedPtr1; // shared ownership

    cout << "sharedPtr1 use count: " << sharedPtr1.use_count() << endl;
    cout << "sharedPtr2 use count: " << sharedPtr2.use_count() << endl;

    sharedPtr1->display();
    sharedPtr2->display();

    // Reset sharedPtr1, sharedPtr2 still holds ownership
    sharedPtr1.reset();
    cout << "\nAfter resetting sharedPtr1:" << endl;
    cout << "sharedPtr1 use count: " << sharedPtr1.use_count() << endl;
    cout << "sharedPtr2 use count: " << sharedPtr2.use_count() << endl;
    sharedPtr2->display();

    return 0;
}
