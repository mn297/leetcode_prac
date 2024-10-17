#include <iostream>
#include <vector>
#include <algorithm> // for std::reverse
#include <string>

using namespace std;

vector<int> spiralOrder(vector<vector<int>> &matrix)
{
    vector<int> result;
    if (matrix.empty())
    {
        return result;
    }

    int rowBegin = 0;
    int rowEnd = matrix.size() - 1;
    int colBegin = 0;
    int colEnd = matrix[0].size() - 1;

    while (rowBegin <= rowEnd && colBegin <= colEnd)
    {
        // Traverse Right
        for (int j = colBegin; j <= colEnd; j++)
        {
            result.push_back(matrix[rowBegin][j]);
        }
        // exclude curren first row
        rowBegin++;

        // Traverse Down
        for (int j = rowBegin; j <= rowEnd; j++)
        {
            result.push_back(matrix[j][colEnd]);
        }
        // exclude current last column
        colEnd--;

        if (rowBegin <= rowEnd)
        {
            // Traverse Left
            for (int j = colEnd; j >= colBegin; j--)
            {
                result.push_back(matrix[rowEnd][j]);
            }
        }
        // exclude current last row, after traversing left we are done with last row
        rowEnd--;

        if (colBegin <= colEnd)
        {
            // Traver Up
            for (int j = rowEnd; j >= rowBegin; j--)
            {
                result.push_back(matrix[j][colBegin]);
            }
        }
        // exclude current first column, after traversing up we are done with first column
        colBegin++;
    }

    return result;
}

int main()
{
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    vector<int> result = spiralOrder(matrix);

    cout << "Spiral Order: ";
    for (int val : result)
    {
        cout << val << " ";
    }

    return 0;
}
