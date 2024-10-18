#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int solution_choice = 1;

void print_sequence(string &seq)
{
    for (char c : seq)
    {
        cout << c;
    }
    cout << endl;
}

// Recursive function to generate the count-and-say sequence at the nth position
string countAndSay_recursive(int n)
{
    // Base case for the first sequence
    if (n == 1)
        return "1";

    // Recursively generate the previous sequence
    string prev_sequence = countAndSay_recursive(n - 1);

    // Process the previous sequence to generate the nth sequence
    string result;
    // (Logic will go here to generate the nth sequence from prev_sequence)

    return result;
}

// string convert_to_rle(string &sequence)
// {
//     string result;
//     int count = 1;
//     char prev_char = sequence[0];

//     for (int i = 1; i <= sequence.size(); i++)
//     {
//         char current_char = sequence[i];
//         if (i < sequence.size() && current_char == prev_char)
//         {
//             count++;
//         }
//         else
//         {
//             result +=  to_string(count) + prev_char;
//             prev_char = current_char;
//             count = 1;
//         }
//     }

//     return result;
// }

// solution
string convert_to_rle(string &sequence)
{
    string result;
    int count = 1;
    char prev_char = sequence[0];

    for (int i = 1; i <= sequence.size(); i++)
    {
        if (i < sequence.size() && sequence[i] == prev_char)
        {
            count++;
        }
        // last index or different character
        else
        {
            result += to_string(count) + prev_char;
            if (i < sequence.size())
            {
                prev_char = sequence[i];
                count = 1;
            }
        }
    }

    return result;
}

// Iterative function to generate the count-and-say sequence at the nth position
string countAndSay_iterative(int n)
{
    // Start with the first sequence
    string sequence = "1";

    // Iterate to generate the nth sequence
    for (int i = 2; i <= n; i++)
    {
        sequence = convert_to_rle(sequence);
    }

    return sequence;
}

// Function to select between recursive or iterative solutions
string countAndSay(int n)
{
    if (solution_choice == 0)
    {
        return countAndSay_recursive(n);
    }
    else if (solution_choice == 1)
    {
        return countAndSay_iterative(n);
    }
    else
    {
        return ""; // Handle invalid solution_choice
    }
}

// Driver program to test the countAndSay function
int main()
{
    // string str1 = "1";
    // string str2 = "22333";
    // cout << str1 + str2 << endl;
    // cout << str2[3] << endl;
    // // Define test cases for different values of n
    // vector<int> testCases = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // // Loop over each test case
    // for (int n : testCases)
    // {
    //     cout << "Count and Say for n = " << n << " is: ";
    //     string result = countAndSay(n);

    //     print_sequence(result);
    // }
    int n = 5;
    cout << "Count and Say for n = 2 is: " << countAndSay(5) << endl;
    printf("RLE of %d is %s\n", n, countAndSay(n).c_str());
    return 0;
}
