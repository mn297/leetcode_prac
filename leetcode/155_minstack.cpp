#include <stack>
#include <iostream>

using namespace std;

class MinStack
{
public:
    MinStack()
    {
    }

    void push(int val)
    {
        main_stack.push(val);
        if (min_stack.empty() || val <= min_stack.top())
        {
            min_stack.push(val);
        }
    }

    void pop()
    {
        if (main_stack.top() == min_stack.top())
        {
            min_stack.pop();
        }
        main_stack.pop();
    }

    int top()
    {
        return main_stack.top();
    }

    int getMin()
    {
        return min_stack.top();
    }

private:
    stack<int> main_stack; // Main stack to store all elements
    stack<int> min_stack;  // Auxiliary stack to keep track of minimum values
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

int main()
{
    // Example usage
    MinStack *minStack = new MinStack();
    minStack->push(-2);
    minStack->push(0);
    minStack->push(-3);
    cout << "Min: " << minStack->getMin() << endl; // Returns -3
    minStack->pop();
    cout << "Top: " << minStack->top() << endl;    // Returns 0
    cout << "Min: " << minStack->getMin() << endl; // Returns -2

    // Bigger test
    minStack->push(5);
    minStack->push(1);
    minStack->push(3);
    minStack->push(-1);
    cout << "Min: " << minStack->getMin() << endl; // Returns -1
    minStack->pop();
    cout << "Min: " << minStack->getMin() << endl; // Returns 1
    minStack->pop();
    cout << "Top: " << minStack->top() << endl;    // Returns 1
    cout << "Min: " << minStack->getMin() << endl; // Returns 1
    minStack->pop();
    cout << "Top: " << minStack->top() << endl;    // Returns 5
    cout << "Min: " << minStack->getMin() << endl; // Returns -2

    // Even bigger test with more operations
    minStack->push(10);
    minStack->push(20);
    minStack->push(-5);
    minStack->push(15);
    minStack->push(-10);
    cout << "Min: " << minStack->getMin() << endl; // Returns -10
    minStack->pop();
    cout << "Min: " << minStack->getMin() << endl; // Returns -5
    minStack->pop();
    cout << "Top: " << minStack->top() << endl;    // Returns -5
    cout << "Min: " << minStack->getMin() << endl; // Returns -5
    minStack->pop();
    cout << "Top: " << minStack->top() << endl;    // Returns 20
    cout << "Min: " << minStack->getMin() << endl; // Returns -2
    minStack->push(-15);
    cout << "Min: " << minStack->getMin() << endl; // Returns -15
    minStack->pop();
    minStack->pop();
    cout << "Min: " << minStack->getMin() << endl; // Returns -2
    minStack->pop();
    cout << "Top: " << minStack->top() << endl;    // Returns 5
    cout << "Min: " << minStack->getMin() << endl; // Returns -2

    delete minStack;
    return 0;
}
