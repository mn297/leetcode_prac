#include <stack>
#include <iostream>
#include <climits>

using namespace std;
// Leetcode https://leetcode.com/problems/min-stack
// What's a min stack? A min stack is a stack (first in, last out) that also tracks the minimum value at any given point of time.
// push, pop, top and min element need to be constant time.

class StackNode
{
public:
    int val;
    int minval;

    StackNode(int x, int min) : val(x), minval(min) {};
};

class MinStack
{
public:
    /** initialize your data structure here. */

    stack<StackNode> customstack;
    int minval;

    MinStack()
    {
        minval = INT_MAX;
    }

    void push(int x)
    {
        StackNode node(x, minval);
        customstack.push(node);
        if (x < minval)
            minval = x;
    }

    void pop()
    {
        StackNode tops = customstack.top();
        if (tops.val == minval)
            minval = tops.minval;

        customstack.pop();
    }

    int top()
    {
        StackNode tops = customstack.top();
        return tops.val;
    }

    int getMin()
    {
        return minval;
    }
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
