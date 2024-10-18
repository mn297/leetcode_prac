#include <stdio.h>
#include <string.h>

void reverse_segment(char *str, int start, int len)
{
    int end = start + len - 1;
    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void reverse_every_5th(char *str)
{
    int i = 0;
    int length = strlen(str);

    while (i < length)
    {
        // Skip the next 5 characters
        if (i + 5 <= length)
        {
            i += 5;
        }
        else
        {
            break;
        }

        // Reverse the next 3 characters if they exist
        if (i + 3 <= length)
        {
            reverse_segment(str, i, 3);
        }
        else
        {
            reverse_segment(str, i, length - i); // Reverse remaining characters if less than 3
        }

        i += 3; // Move the pointer after reversing 3 characters
    }
}

int main()
{
    char input_str[] = "abcdefghijklmnopqrst";

    reverse_every_5th(input_str);
    printf("Output: %s\n", input_str);

    return 0;
}
