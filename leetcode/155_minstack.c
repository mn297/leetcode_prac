#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX_SIZE 1000000

typedef struct
{
    int *stack;
    int *minStack;
    int top;
    int minTop;
} MinStack;

MinStack *minStackCreate()
{
    MinStack *obj = (MinStack *)malloc(sizeof(MinStack));
    obj->stack = (int *)malloc(MAX_SIZE * sizeof(int));
    obj->minStack = (int *)malloc(MAX_SIZE * sizeof(int));
    obj->top = -1;
    obj->minTop = -1;
    return obj;
}

void minStackPush(MinStack *obj, int val)
{
    if (obj->top < MAX_SIZE - 1)
    {
        obj->stack[++(obj->top)] = val;
        if (obj->minTop == -1 || val <= obj->minStack[obj->minTop])
        {
            obj->minStack[++(obj->minTop)] = val;
        }
    }
}

void minStackPop(MinStack *obj)
{
    if (obj->top > -1)
    {
        if (obj->stack[obj->top] == obj->minStack[obj->minTop])
        {
            obj->minTop--;
        }
        obj->top--;
    }
}

int minStackTop(MinStack *obj)
{
    if (obj->top > -1)
    {
        return obj->stack[obj->top];
    }
    return INT_MIN; // Or handle error
}

int minStackGetMin(MinStack *obj)
{
    if (obj->minTop > -1)
    {
        return obj->minStack[obj->minTop];
    }
    return INT_MIN; // Or handle error
}

void minStackFree(MinStack *obj)
{
    free(obj->stack);
    free(obj->minStack);
    free(obj);
}

double testMinStack(int N)
{
    MinStack *obj = minStackCreate();
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    // Push N random elements
    for (int i = 0; i < N; ++i)
    {
        int value = rand() % 2001 - 1000; // Random value between -1000 and 1000
        minStackPush(obj, value);
    }

    // Perform N getMin operations
    for (int i = 0; i < N; ++i)
    {
        minStackGetMin(obj);
    }

    // Pop N/2 elements
    for (int i = 0; i < N / 2; ++i)
    {
        minStackPop(obj);
    }

    // Push N/2 new elements
    for (int i = 0; i < N / 2; ++i)
    {
        int value = rand() % 2001 - 1000;
        minStackPush(obj, value);
    }

    // Perform N more getMin operations
    for (int i = 0; i < N; ++i)
    {
        minStackGetMin(obj);
    }

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0; // Convert to milliseconds

    minStackFree(obj);
    return cpu_time_used;
}

int main()
{
    int testSizes[] = {1000, 10000, 100000, 1000000};
    int numTests = sizeof(testSizes) / sizeof(testSizes[0]);

    srand(time(NULL)); // Initialize random seed

    printf("%10s %15s\n", "N", "Time (ms)");
    printf("-------------------------\n");

    for (int i = 0; i < numTests; ++i)
    {
        int N = testSizes[i];
        double duration = testMinStack(N);
        printf("%10d %15.2f\n", N, duration);
    }

    return 0;
}