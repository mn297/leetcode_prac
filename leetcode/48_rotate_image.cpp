#include <iostream>
#include <vector>
#include <algorithm> // for std::reverse
#include <string>

using namespace std;

void rotate(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    // Step 1: Transpose the matrix
    for (int i = 0; i < n; ++i)
    {
        for (int j = i; j < n; ++j)
        {
            // Swap elements at (i, j) and (j, i)
            swap(matrix[i][j], matrix[j][i]);
        }
    }

    // Step 2: Reverse each row to achieve the final rotated state
    for (int i = 0; i < n; ++i)
    {
        reverse(matrix[i].begin(), matrix[i].end());
    }
}

int main()
{
    // Example input matrix
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    // Call the rotate function
    rotate(matrix);

    // Print the rotated matrix
    for (const auto &row : matrix)
    {
        for (int val : row)
        {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
