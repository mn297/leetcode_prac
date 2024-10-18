#include <iostream>
#include <cstdio>
#include <string>

#include <bits/stdc++.h>

using namespace std;

const int solution_choice = 1;

void print_array(vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << ", ";
    }
    cout << endl;
}

int lisEndAtI_recursive(vector<int> &arr, int i)
{
    if (i == 0)
        return 1;

    int res = 1;
    for (int prev = 0; prev < i; prev++)
    {
        if (arr[prev] < arr[i])
            res = max(res, lisEndAtI_recursive(arr, prev) + 1);
    }

    return res;
}

int lisEndAtI_memo(vector<int> &arr, int i, vector<int> &dp)
{
    if (i == 0)
        return 1;

    if (dp[i] != -1)
        return dp[i];

    int res = 1;
    for (int prev = 0; prev < i; prev++)
    {
        if (arr[prev] < arr[i])
        {
            int temp = lisEndAtI_memo(arr, prev, dp) + 1;
            res = max(res, temp);
        }
    }

    return dp[i] = res;
}

int lis_dp(vector<int> &arr)
{
    int n = arr.size();
    vector<int> lis(n, 1);

    // Compute optimized LIS values in
    // bottom-up manner
    for (int i = 1; i < n; i++)
    {
        for (int prev = 0; prev < i; prev++)
        {
            if (arr[i] > arr[prev] && lis[i] < lis[prev] + 1)
            {
                lis[i] = lis[prev] + 1;
            }
        }
    }

    print_array(lis);

    // Return maximum value in lis
    return *max_element(lis.begin(), lis.end());
}

int lis_recursive(vector<int> &arr, bool memoization = false)
{
    int n = arr.size();
    if (n == 0)
        return 0;

    if (memoization)
    {
        vector<int> dp(n, -1);
        int res = 1;
        for (int i = 0; i < n; i++)
        {
            res = max(res, lisEndAtI_memo(arr, i, dp));
        }
        return res;
    }
    else
    {
        int res = 1;
        for (int i = 0; i < n; i++)
        {
            res = max(res, lisEndAtI_recursive(arr, i));
        }
        return res;
    }
}

int lis(vector<int> &arr)
{
    if (solution_choice == 0)
    {
        return lis_recursive(arr);
    }
    else if (solution_choice == 1)
    {
        return lis_dp(arr);
    }
    else if (solution_choice == 2)
    {
        return lis_recursive(arr, true);
    }
    else
    {
        return -1;
    }
}

// Driver program to test above function
int main()
{
    // Define multiple test cases
    vector<vector<int>> testCases = {
        {10, 22, 9, 33, 21, 50, 41, 60},
        {5},
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1},
        {3, 10, 2, 1, 20},
        {1, 3, 5, 4, 7},
        {0, 8, 4, 12, 2},
        {7, 7, 7, 7, 7},
        {10, 22, 9, 33, 21, 50, 41, 60},
        {1, 2},
        {3, 10, 2, 1, 20, 4, 6, 7},
        {1, 3, 5, 4, 7},
        {}, // Empty array
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 3, 2, 4, 3, 5, 4, 6, 7}};

    // Corresponding indices to test lisEndAtI
    vector<int> testIndices = {4, 0, 4, 4, 4, 4, 4, 4, 7, 1, 7, 4, 0, 9, 7};

    vector<int> arr = {10, 22, 9, 33, 21, 50, 41, 60};

    // cout << "Length of lis is " << lis(arr) << endl;

    print_array(arr);
    lis_dp(arr);
    return 0;
}
