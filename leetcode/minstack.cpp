#include <iostream>
#include <stack>
#include <limits>
#include <chrono>
#include <random>
#include <vector>

#include <stack>
#include <limits>

class MinStack
{
private:
    std::stack<int> mainStack;
    std::stack<int> minStack;

public:
    MinStack() {}

    void push(int val)
    {
        mainStack.push(val);

        if (minStack.empty() || val <= minStack.top())
        {
            minStack.push(val);
        }
    }

    void pop()
    {
        if (!mainStack.empty())
        {
            if (mainStack.top() == minStack.top())
            {
                minStack.pop();
            }
            mainStack.pop();
        }
    }

    int top()
    {
        if (!mainStack.empty())
        {
            return mainStack.top();
        }
        return std::numeric_limits<int>::min(); // Or throw an exception
    }

    int getMin()
    {
        if (!minStack.empty())
        {
            return minStack.top();
        }
        return std::numeric_limits<int>::min(); // Or throw an exception
    }
};
void testMinStack(int N)
{
    MinStack stack;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-1000, 1000);

    auto start = std::chrono::high_resolution_clock::now();

    // Push N random elements
    for (int i = 0; i < N; ++i)
    {
        int value = dis(gen);
        stack.push(value);
    }

    // Perform N getMin operations
    int minValue;
    for (int i = 0; i < N; ++i)
    {
        minValue = stack.getMin();
    }

    // Pop N/2 elements
    for (int i = 0; i < N / 2; ++i)
    {
        stack.pop();
    }

    // Push N/2 new elements
    for (int i = 0; i < N / 2; ++i)
    {
        int value = dis(gen);
        stack.push(value);
    }

    // Perform N more getMin operations
    for (int i = 0; i < N; ++i)
    {
        minValue = stack.getMin();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "Test with N = " << N << " completed in " << duration.count() << " ms" << std::endl;
}

int main()
{
    std::vector<int> testSizes = {1000, 10000, 100000, 1000000};

    for (int N : testSizes)
    {
        testMinStack(N);
    }

    return 0;
}