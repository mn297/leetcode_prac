#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Structure to demonstrate stack allocation
typedef struct
{
    int id;
    char name[50];
} Employee;

// Structure to demonstrate heap allocation
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// Function prototypes
void demonstrateStackAllocation();
void demonstrateHeapAllocation();
void demonstrateStackOverflow(int depth);
void demonstrateMemoryLeak();
void demonstrateUseAfterFree();
void demonstrateBufferOverflow();
Node *createLinkedList(int size);
void freeLinkedList(Node *head);

// Global variable (stored in data segment)
int globalVar = 10;

int main()
{
    printf("==== Stack and Heap Memory Demo ====\n\n");

    // Demonstrate stack allocation
    printf("1. Demonstrating Stack Allocation\n");
    demonstrateStackAllocation();
    printf("\n");

    // Demonstrate heap allocation
    printf("2. Demonstrating Heap Allocation\n");
    demonstrateHeapAllocation();
    printf("\n");

    // Demonstrate stack overflow (commented out for safety)
    printf("3. Stack Overflow Demonstration (commented out)\n");
    // Uncomment the next line to see stack overflow
    // demonstrateStackOverflow(0);
    printf("\n");

    // Demonstrate memory leak
    printf("4. Memory Leak Demonstration\n");
    demonstrateMemoryLeak();
    printf("\n");

    // Demonstrate use after free
    printf("5. Use After Free Demonstration\n");
    demonstrateUseAfterFree();
    printf("\n");

    // Demonstrate buffer overflow
    printf("6. Buffer Overflow Demonstration\n");
    demonstrateBufferOverflow();
    printf("\n");

    printf("==== Demo Complete ====\n");
    return 0;
}

void demonstrateStackAllocation()
{
    // Stack-allocated struct
    Employee emp = {1, "John Doe"};
    printf("Employee ID: %d, Name: %s\n", emp.id, emp.name);

    // Stack-allocated array
    int numbers[5] = {1, 2, 3, 4, 5};
    printf("Third number: %d\n", numbers[2]);

    // Accessing global variable
    printf("Global variable: %d\n", globalVar);
}

void demonstrateHeapAllocation()
{
    // Heap-allocated integer
    int *dynamicInt = (int *)malloc(sizeof(int));
    *dynamicInt = 42;
    printf("Heap-allocated int: %d\n", *dynamicInt);
    free(dynamicInt);

    // Heap-allocated array
    int *dynamicArray = (int *)calloc(5, sizeof(int));
    for (int i = 0; i < 5; i++)
    {
        dynamicArray[i] = i * 10;
    }
    printf("Third element of dynamic array: %d\n", dynamicArray[2]);
    free(dynamicArray);

    // Linked list on heap
    Node *list = createLinkedList(3);
    printf("Second node data: %d\n", list->next->data);
    freeLinkedList(list);
}

void demonstrateStackOverflow(int depth)
{
    char largeArray[1000000]; // Large array to consume stack space
    printf("Recursion depth: %d\n", depth);
    demonstrateStackOverflow(depth + 1);
}

void demonstrateMemoryLeak()
{
    int *leakedMemory = (int *)malloc(sizeof(int));
    *leakedMemory = 100;
    printf("This memory will be leaked: %d\n", *leakedMemory);
    // Intentionally not freeing the memory to demonstrate a leak
}

void demonstrateUseAfterFree()
{
    int *dangling = (int *)malloc(sizeof(int));
    *dangling = 50;
    printf("Before free: %d\n", *dangling);
    free(dangling);
    // The next line is a bug (use after free)
    // printf("After free: %d\n", *dangling);
    printf("Uncommenting the above line would demonstrate use after free\n");
}

void demonstrateBufferOverflow()
{
    char buffer[5];
    strcpy(buffer, "Hello"); // This will overflow the buffer
    printf("Buffer content (overflowed): %s\n", buffer);
}

Node *createLinkedList(int size)
{
    Node *head = NULL;
    Node *current = NULL;

    for (int i = 0; i < size; i++)
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = i;
        newNode->next = NULL;

        if (head == NULL)
        {
            head = newNode;
            current = newNode;
        }
        else
        {
            current->next = newNode;
            current = newNode;
        }
    }

    return head;
}

void freeLinkedList(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        Node *next = current->next;
        free(current);
        current = next;
    }
}