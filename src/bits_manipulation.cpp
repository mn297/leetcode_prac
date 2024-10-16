#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <bitset>
#include <cstdint> // For uintptr_t
#include <iomanip> // For std::hex, std::setw, etc.

using namespace std;

// Helper function to print binary representation of a number
template <typename T>
void print_binary(T num, int bits = sizeof(T) * 8)
{
    cout << bitset<64>(num).to_string().substr(64 - bits, bits);
}

// 1. Aligning Memory Addresses
// Adding extra first then trim down
uintptr_t align_address(uintptr_t ptr, size_t align)
{
    // Ensure align is a power of two
    if ((align & (align - 1)) != 0)
    {
        cerr << "Alignment must be a power of two." << endl;
        return ptr;
    }
    uintptr_t aligned_ptr = (ptr + align - 1) & ~(align - 1);
    return aligned_ptr;
}

// 2. Checking if an Address is Aligned
bool is_aligned(uintptr_t ptr, size_t align)
{
    return (ptr & (align - 1)) == 0;
}

// 3. Bit Packing and Unpacking
// Example: Packing two 4-bit numbers into one 8-bit number
uint8_t pack_two_nibbles(uint8_t high, uint8_t low)
{
    return (high << 4) | (low & 0x0F);
}

pair<uint8_t, uint8_t> unpack_two_nibbles(uint8_t packed)
{
    uint8_t high = (packed >> 4) & 0x0F;
    uint8_t low = packed & 0x0F;
    return {high, low};
}

// 4. Swapping Two Values Without a Temporary Variable (Using XOR)
void swap_without_temp(int &a, int &b)
{
    if (&a == &b)
        return; // Handle same memory address
    a ^= b;
    b ^= a;
    a ^= b;
}

// 5. Setting, Clearing, Toggling, and Checking Specific Bits
// Set the nth bit
void set_bit(uint32_t &x, int n)
{
    x |= (1U << n);
}

// Clear the nth bit
void clear_bit(uint32_t &x, int n)
{
    x &= ~(1U << n);
}

// Toggle the nth bit
void toggle_bit(uint32_t &x, int n)
{
    x ^= (1U << n);
}

// Check if the nth bit is set
bool is_bit_set(uint32_t x, int n)
{
    return (x & (1U << n)) != 0;
}

// 6. Fast Multiplying/Dividing by Powers of Two Using Bit Shifts
int multiply_by_power_of_two(int x, int power)
{
    return x << power; // Equivalent to x * 2^power
}

int divide_by_power_of_two(int x, int power)
{
    return x >> power; // Equivalent to x / 2^power
}

// 7. Endianness Conversion (Byte-Swapping)
uint32_t swap_endianness(uint32_t x)
{
    return ((x >> 24) & 0x000000FF) |
           ((x >> 8) & 0x0000FF00) |
           ((x << 8) & 0x00FF0000) |
           ((x << 24) & 0xFF000000);
}

// 8. Rounding Up to the Nearest Power of Two
uintptr_t round_up_to_power_of_two(uintptr_t value, size_t align)
{
    // Ensure align is a power of two
    if ((align & (align - 1)) != 0)
    {
        cerr << "Alignment must be a power of two." << endl;
        return value;
    }
    return (value + align - 1) & ~(align - 1);
}

// Driver function to test all bit manipulation and memory alignment tricks
int main()
{
    cout << "===== Bit Manipulation and Memory Alignment Tricks =====" << endl
         << endl;

    // 1. Aligning Memory Addresses
    cout << "1. Aligning Memory Addresses" << endl;
    uintptr_t address = 123; // Example address
    size_t alignment = 8;    // Align to 8 bytes
    uintptr_t aligned_address = align_address(address, alignment);
    cout << "Original Address: " << address << endl;
    cout << "Aligned Address (to " << alignment << " bytes): " << aligned_address << endl;
    cout << "Binary Original: ";
    print_binary(address, 16);
    cout << endl;
    cout << "Binary Aligned:  ";
    print_binary(aligned_address, 16);
    cout << endl
         << endl;

    // 2. Checking if an Address is Aligned
    cout << "2. Checking Memory Alignment" << endl;
    cout << "Is address " << address << " aligned to " << alignment << " bytes? ";
    cout << (is_aligned(address, alignment) ? "Yes" : "No") << endl;
    cout << "Is address " << aligned_address << " aligned to " << alignment << " bytes? ";
    cout << (is_aligned(aligned_address, alignment) ? "Yes" : "No") << endl
         << endl;

    // 3. Bit Packing and Unpacking
    cout << "3. Bit Packing and Unpacking" << endl;
    uint8_t high_nibble = 9; // 1001
    uint8_t low_nibble = 6;  // 0110
    uint8_t packed = pack_two_nibbles(high_nibble, low_nibble);
    auto unpacked = unpack_two_nibbles(packed);
    cout << "High Nibble: " << (int)high_nibble << " (";
    print_binary(high_nibble, 4);
    cout << ")" << endl;
    cout << "Low Nibble:  " << (int)low_nibble << " (";
    print_binary(low_nibble, 4);
    cout << ")" << endl;
    cout << "Packed Byte: " << (int)packed << " (";
    print_binary(packed, 8);
    cout << ")" << endl;
    cout << "Unpacked High: " << (int)unpacked.first << " (";
    print_binary(unpacked.first, 4);
    cout << ")" << endl;
    cout << "Unpacked Low:  " << (int)unpacked.second << " (";
    print_binary(unpacked.second, 4);
    cout << ")" << endl
         << endl;

    // 4. Swapping Two Values Without a Temporary Variable
    cout << "4. Swapping Two Values Without a Temporary Variable" << endl;
    int a = 5, b = 10;
    cout << "Before Swap: a = " << a << ", b = " << b << endl;
    swap_without_temp(a, b);
    cout << "After Swap:  a = " << a << ", b = " << b << endl
         << endl;

    // 5. Setting, Clearing, Toggling, and Checking Specific Bits
    cout << "5. Setting, Clearing, Toggling, and Checking Specific Bits" << endl;
    uint32_t x = 0b00001100; // 12 in binary
    cout << "Initial x: " << bitset<8>(x) << " (" << x << ")" << endl;

    // Set the 0th bit
    set_bit(x, 0);
    cout << "After setting 0th bit: " << bitset<8>(x) << " (" << x << ")" << endl;

    // Clear the 3rd bit
    clear_bit(x, 3);
    cout << "After clearing 3rd bit: " << bitset<8>(x) << " (" << x << ")" << endl;

    // Toggle the 2nd bit
    toggle_bit(x, 2);
    cout << "After toggling 2nd bit: " << bitset<8>(x) << " (" << x << ")" << endl;

    // Check if the 2nd bit is set
    cout << "Is 2nd bit set? " << (is_bit_set(x, 2) ? "Yes" : "No") << endl
         << endl;

    // 6. Fast Multiplying/Dividing by Powers of Two Using Bit Shifts
    cout << "6. Fast Multiplying/Dividing by Powers of Two Using Bit Shifts" << endl;
    int num = 5;
    int power = 3; // Multiply and divide by 2^3 = 8
    int multiplied = multiply_by_power_of_two(num, power);
    int divided = divide_by_power_of_two(num, power);
    cout << num << " * 2^" << power << " = " << multiplied << endl;
    cout << num << " / 2^" << power << " = " << divided << endl
         << endl;

    // 7. Endianness Conversion (Byte-Swapping)
    cout << "7. Endianness Conversion (Byte-Swapping)" << endl;
    uint32_t original = 0x12345678;
    uint32_t swapped = swap_endianness(original);
    cout << "Original (hex): " << hex << original << endl;
    cout << "Swapped  (hex): " << swapped << endl;
    cout << "Original (binary): ";
    print_binary(original, 32);
    cout << endl;
    cout << "Swapped  (binary): ";
    print_binary(swapped, 32);
    cout << endl
         << endl;

    // 8. Rounding Up to the Nearest Power of Two
    cout << "8. Rounding Up to the Nearest Power of Two" << endl;
    uintptr_t value = 123;   // Example value
    size_t round_align = 16; // Round up to nearest 16 bytes
    uintptr_t rounded_up = round_up_to_power_of_two(value, round_align);
    cout << "Original Value: " << value << endl;
    cout << "Rounded Up (to " << round_align << " bytes): " << rounded_up << endl;
    cout << "Binary Original: ";
    print_binary(value, 16);
    cout << endl;
    cout << "Binary Rounded Up:  ";
    print_binary(rounded_up, 16);
    cout << endl
         << endl;

    cout << "===== End of Bit Manipulation and Memory Alignment Tricks =====" << endl;
    return 0;
}
