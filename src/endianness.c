/*
 * stack_heap_endianness_demo.c
 *
 * This program demonstrates:
 * 1. Stack allocation and recursion.
 * 2. Heap allocation using malloc, calloc, realloc, and free.
 * 3. Implementation of a simple custom memory allocator.
 * 4. Endianness detection and byte order reversal.
 * 5. Memory alignment techniques.
 * 6. Bit manipulation tricks.
 *
 * Compile with: gcc -o demo stack_heap_endianness_demo.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h> // For sbrk()
#include <stddef.h> // For size_t

/* ============================= */
/*          STACK EXAMPLES       */
/* ============================= */

/*
 * Function: stack_allocation_example
 * --------------------
 * Demonstrates allocation of local variables on the stack.
 */
void stack_allocation_example()
{
    int local_var = 42;
    double local_array[10];

    printf("=== Stack Allocation Example ===\n");
    printf("Address of local_var: %p\n", (void *)&local_var);
    printf("Address of local_array: %p\n\n", (void *)local_array);
}

/*
 * Function: factorial
 * --------------------
 * Recursive function to calculate factorial, demonstrating stack usage.
 *
 *  n: integer for which factorial is calculated.
 *
 *  returns: factorial of n.
 */
int factorial(int n)
{
    if (n <= 1)
        return 1;
    else
        return n * factorial(n - 1);
}

/* ============================= */
/*           HEAP EXAMPLES       */
/* ============================= */

/*
 * Function: heap_allocation_example
 * --------------------
 * Demonstrates dynamic memory allocation on the heap using malloc, calloc, realloc, and free.
 */
void heap_allocation_example()
{
    printf("=== Heap Allocation Example ===\n");

    // Allocate memory for an integer using malloc
    int *heap_int = (int *)malloc(sizeof(int));
    if (!heap_int)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    *heap_int = 100;
    printf("Allocated int at %p with value %d\n", (void *)heap_int, *heap_int);

    // Allocate memory for an array of 10 doubles using calloc
    double *heap_array = (double *)calloc(10, sizeof(double));
    if (!heap_array)
    {
        perror("calloc");
        free(heap_int);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 10; i++)
    {
        heap_array[i] = (double)i * 1.1;
    }
    printf("Allocated double array at %p with first element %.2f\n", (void *)heap_array, heap_array[0]);

    // Reallocate memory for the double array to hold 20 elements
    double *realloc_array = (double *)realloc(heap_array, 20 * sizeof(double));
    if (!realloc_array)
    {
        perror("realloc");
        free(heap_int);
        free(heap_array);
        exit(EXIT_FAILURE);
    }
    // Initialize new elements
    for (int i = 10; i < 20; i++)
    {
        realloc_array[i] = (double)i * 1.1;
    }
    printf("Reallocated double array to %p with 20 elements. Last element: %.2f\n",
           (void *)realloc_array, realloc_array[19]);

    // Free allocated memory
    free(heap_int);
    free(realloc_array);

    printf("Freed heap_int and realloc_array.\n\n");
}

/* ============================= */
/*     CUSTOM MEMORY ALLOCATOR   */
/* ============================= */

/*
 * Structure: mem_block_t
 * --------------------
 * Represents a memory block in the custom allocator's free list.
 */
typedef struct mem_block
{
    size_t size;            // Size of the block
    int free;               // Free flag: 1 if free, 0 if allocated
    struct mem_block *next; // Pointer to the next block
} mem_block_t;

#define BLOCK_SIZE sizeof(mem_block_t)

mem_block_t *free_list = NULL; // Head of the free list

/*
 * Function: my_malloc
 * --------------------
 * Custom implementation of malloc using a free list.
 *
 *  size: number of bytes to allocate.
 *
 *  returns: pointer to allocated memory, or NULL on failure.
 */
void *my_malloc(size_t size)
{
    mem_block_t *current, *prev;
    void *result;
    size_t total_size;

    // Align size to 8 bytes
    size = (size + 7) & ~7;

    // Traverse the free list to find a suitable block (First-Fit)
    current = free_list;
    prev = NULL;
    while (current && !(current->free && current->size >= size))
    {
        prev = current;
        current = current->next;
    }

    if (current)
    {
        // Found a free block
        current->free = 0;
        result = (void *)(current + 1);
    }
    else
    {
        // No suitable block found, request more memory using sbrk
        total_size = size + BLOCK_SIZE;
        current = (mem_block_t *)sbrk(total_size); // Cast the return value of sbrk to mem_block_t*
        if (current == (void *)-1)
        {
            // sbrk failed
            return NULL;
        }

        current->size = size;
        current->free = 0;
        current->next = NULL;

        if (prev)
        {
            prev->next = current;
        }
        else
        {
            free_list = current;
        }

        result = (void *)(current + 1);
    }

    return result;
}

/*
 * Function: my_free
 * --------------------
 * Custom implementation of free, marking blocks as free and coalescing adjacent free blocks.
 *
 *  ptr: pointer to the memory block to free.
 */
void my_free(void *ptr)
{
    if (!ptr)
        return;

    mem_block_t *block_ptr = (mem_block_t *)ptr - 1;
    block_ptr->free = 1;

    // Coalesce adjacent free blocks
    mem_block_t *current = free_list;
    while (current && current->next)
    {
        if (current->free && current->next->free)
        {
            current->size += BLOCK_SIZE + current->next->size;
            current->next = current->next->next;
        }
        else
        {
            current = current->next;
        }
    }
}

/*
 * Function: print_free_list
 * --------------------
 * Prints the current state of the free list for debugging purposes.
 */
void print_free_list()
{
    mem_block_t *current = free_list;
    printf("Free List:\n");
    while (current)
    {
        printf("Block at %p: size = %zu, free = %d, next = %p\n",
               (void *)current, current->size, current->free, (void *)current->next);
        current = current->next;
    }
    printf("\n");
}

/*
 * Function: custom_allocator_example
 * --------------------
 * Demonstrates usage of the custom memory allocator.
 */
void custom_allocator_example()
{
    printf("=== Custom Memory Allocator Example ===\n");

    // Allocate memory for an integer
    int *custom_int = (int *)my_malloc(sizeof(int));
    if (!custom_int)
    {
        perror("my_malloc");
        exit(EXIT_FAILURE);
    }
    *custom_int = 555;
    printf("Allocated custom_int at %p with value %d\n", (void *)custom_int, *custom_int);

    // Allocate memory for a double array
    double *custom_array = (double *)my_malloc(5 * sizeof(double));
    if (!custom_array)
    {
        perror("my_malloc");
        my_free(custom_int);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 5; i++)
    {
        custom_array[i] = (double)i * 2.2;
    }
    printf("Allocated custom_array at %p with values: ", (void *)custom_array);
    for (int i = 0; i < 5; i++)
    {
        printf("%.1f ", custom_array[i]);
    }
    printf("\n");

    // Print free list before freeing
    print_free_list();

    // Free the allocated memory
    my_free(custom_int);
    my_free(custom_array);
    printf("Freed custom_int and custom_array.\n");

    // Print free list after freeing
    print_free_list();
}

/* ============================= */
/*        ENDIANNESS HANDLING     */
/* ============================= */

/*
 * Function: is_little_endian
 * --------------------
 * Detects the system's endianness.
 *
 *  returns: 1 if little-endian, 0 if big-endian.
 */
int is_little_endian()
{
    uint16_t num = 0x1;
    uint8_t *ptr = (uint8_t *)&num;
    return (*ptr == 0x1);
}

/*
 * Function: reverse_endianness32
 * --------------------
 * Reverses the byte order of a 32-bit unsigned integer.
 *
 *  num: 32-bit unsigned integer to reverse.
 *
 *  returns: 32-bit unsigned integer with reversed byte order.
 */
uint32_t reverse_endianness32(uint32_t num)
{
    return ((num >> 24) & 0x000000FF) |
           ((num >> 8) & 0x0000FF00) |
           ((num << 8) & 0x00FF0000) |
           ((num << 24) & 0xFF000000);
}

/*
 * Function: serialize_uint32
 * --------------------
 * Serializes a 32-bit unsigned integer into a byte array in big-endian order.
 *
 *  num: 32-bit unsigned integer to serialize.
 *  buffer: array of at least 4 bytes to store the serialized data.
 */
void serialize_uint32(uint32_t num, uint8_t *buffer)
{
    buffer[0] = (num >> 24) & 0xFF;
    buffer[1] = (num >> 16) & 0xFF;
    buffer[2] = (num >> 8) & 0xFF;
    buffer[3] = num & 0xFF;
}

/*
 * Function: deserialize_uint32
 * --------------------
 * Deserializes a big-endian byte array into a 32-bit unsigned integer.
 *
 *  buffer: array of at least 4 bytes containing the serialized data.
 *
 *  returns: 32-bit unsigned integer.
 */
uint32_t deserialize_uint32(uint8_t *buffer)
{
    return ((uint32_t)buffer[0] << 24) |
           ((uint32_t)buffer[1] << 16) |
           ((uint32_t)buffer[2] << 8) |
           ((uint32_t)buffer[3]);
}

/*
 * Function: endianness_example
 * --------------------
 * Demonstrates endianness detection and byte order reversal.
 */
void endianness_example()
{
    printf("=== Endianness Handling Example ===\n");

    // Detect system endianness
    if (is_little_endian())
    {
        printf("System Endianness: Little-Endian\n");
    }
    else
    {
        printf("System Endianness: Big-Endian\n");
    }

    // Original number
    uint32_t original = 0x12345678;
    printf("Original Number: 0x%08X\n", original);

    // Reverse endianness
    uint32_t reversed = reverse_endianness32(original);
    printf("Reversed Endianness: 0x%08X\n", reversed);

    // Serialize to big-endian byte array
    uint8_t buffer[4];
    serialize_uint32(original, buffer);
    printf("Serialized Buffer: ");
    for (int i = 0; i < 4; i++)
    {
        printf("0x%02X ", buffer[i]);
    }
    printf("\n");

    // Deserialize back to integer
    uint32_t deserialized = deserialize_uint32(buffer);
    printf("Deserialized Number: 0x%08X\n", deserialized);

    // Verify if serialization and deserialization are consistent
    if (original == deserialized)
    {
        printf("Serialization and Deserialization Successful.\n");
    }
    else
    {
        printf("Mismatch in Serialization and Deserialization.\n");
    }

    printf("\n");
}

/* ============================= */
/*        MEMORY ALIGNMENT        */
/* ============================= */

/*
 * Function: align_address
 * --------------------
 * Aligns a given memory address to the nearest multiple of align (power of two).
 *
 *  ptr: original memory address.
 *  align: alignment boundary (must be power of two).
 *
 *  returns: aligned memory address.
 */
uintptr_t align_address(uintptr_t ptr, size_t align)
{
    if ((align & (align - 1)) != 0)
    {
        fprintf(stderr, "Alignment must be a power of two.\n");
        return ptr;
    }
    return (ptr + align - 1) & ~(align - 1);
}

/*
 * Function: memory_alignment_example
 * --------------------
 * Demonstrates memory alignment techniques.
 */
void memory_alignment_example()
{
    printf("=== Memory Alignment Example ===\n");

    // Example buffer
    char buffer[20];
    uintptr_t original_addr = (uintptr_t)buffer;
    size_t align = 8; // Align to 8-byte boundary

    uintptr_t aligned_addr = align_address(original_addr, align);

    printf("Original Address: %p\n", (void *)original_addr);
    printf("Aligned Address:  %p\n", (void *)aligned_addr);

    // Check if alignment was successful
    if (aligned_addr % align == 0)
    {
        printf("Address is aligned to %zu bytes.\n", align);
    }
    else
    {
        printf("Address is NOT aligned to %zu bytes.\n", align);
    }

    printf("\n");
}

/* ============================= */
/*       BIT MANIPULATION TRICKS  */
/* ============================= */

/*
 * Function: set_bit
 * --------------------
 * Sets the nth bit of a number.
 *
 *  num: pointer to the number.
 *  n: bit position to set (0-based).
 */
void set_bit(uint32_t *num, int n)
{
    *num |= (1U << n);
}

/*
 * Function: clear_bit
 * --------------------
 * Clears the nth bit of a number.
 *
 *  num: pointer to the number.
 *  n: bit position to clear (0-based).
 */
void clear_bit(uint32_t *num, int n)
{
    *num &= ~(1U << n);
}

/*
 * Function: toggle_bit
 * --------------------
 * Toggles the nth bit of a number.
 *
 *  num: pointer to the number.
 *  n: bit position to toggle (0-based).
 */
void toggle_bit(uint32_t *num, int n)
{
    *num ^= (1U << n);
}

/*
 * Function: is_bit_set
 * --------------------
 * Checks if the nth bit of a number is set.
 *
 *  num: number to check.
 *  n: bit position to check (0-based).
 *
 *  returns: 1 if set, 0 otherwise.
 */
int is_bit_set(uint32_t num, int n)
{
    return (num & (1U << n)) != 0;
}

/*
 * Function: bit_manipulation_example
 * --------------------
 * Demonstrates bit manipulation tricks: set, clear, toggle, and check bits.
 */
void bit_manipulation_example()
{
    printf("=== Bit Manipulation Tricks Example ===\n");

    uint32_t number = 0x0F0F; // 0000 1111 0000 1111
    printf("Initial Number: 0x%04X\n", number);

    // Set the 4th bit
    set_bit(&number, 4);
    printf("After setting 4th bit: 0x%04X\n", number);

    // Clear the 8th bit
    clear_bit(&number, 8);
    printf("After clearing 8th bit: 0x%04X\n", number);

    // Toggle the 12th bit
    toggle_bit(&number, 12);
    printf("After toggling 12th bit: 0x%04X\n", number);

    // Check if 4th bit is set
    printf("Is 4th bit set? %s\n", is_bit_set(number, 4) ? "Yes" : "No");

    // Check if 8th bit is set
    printf("Is 8th bit set? %s\n", is_bit_set(number, 8) ? "Yes" : "No");

    // Check if 12th bit is set
    printf("Is 12th bit set? %s\n", is_bit_set(number, 12) ? "Yes" : "No");

    printf("\n");
}

/* ============================= */
/*              MAIN             */
/* ============================= */

/*
 * Function: main
 * --------------------
 * Acts as a tester to demonstrate stack, heap, custom memory allocator, endianness, memory alignment, and bit manipulation.
 */
int main()
{
    printf("=== Compiler Role Preparation Demo ===\n\n");

    // Stack Allocation
    stack_allocation_example();

    // Heap Allocation
    heap_allocation_example();

    // Custom Memory Allocator
    custom_allocator_example();

    // Endianness Handling
    endianness_example();

    // Memory Alignment
    memory_alignment_example();

    // Bit Manipulation Tricks
    bit_manipulation_example();

    // Stack Usage with Recursion
    printf("=== Stack Usage with Recursion ===\n");
    int num = 5;
    int fact = factorial(num);
    printf("Factorial of %d is %d\n\n", num, fact);

    printf("=== End of Demo ===\n");
    return 0;
}
