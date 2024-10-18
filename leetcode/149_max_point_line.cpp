// https://leetcode.com/problems/max-points-on-a-line/description/

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution
{
public:
    int maxPoints(vector<vector<int>> &points)
    {
        if (points.size() <= 2)
            return points.size();
        int max_count = 0;

        for (int i = 0; i < points.size(); ++i)
        {
            unordered_map<string, int> slope_count;
            int duplicate = 1;
            int local_max = 0;

            for (int j = i + 1; j < points.size(); ++j)
            {
                int dx = points[j][0] - points[i][0];
                int dy = points[j][1] - points[i][1];

                if (dx == 0 && dy == 0)
                {
                    ++duplicate;
                }
                else
                {
                    int gcd_val = gcd(dx, dy);
                    dx /= gcd_val;
                    dy /= gcd_val;
                    string slope = to_string(dx) + "/" + to_string(dy);
                    ++slope_count[slope];
                    local_max = max(local_max, slope_count[slope]);
                }
            }
            max_count = max(max_count, local_max + duplicate);
        }

        return max_count;
    }

private:
    int gcd(int a, int b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }
};

int main()
{
    Solution solution;
    vector<vector<int>> points = {{1, 1}, {2, 2}, {3, 3}};
    int result = solution.maxPoints(points);
    cout << "Max Points on a Line: " << result << endl;

    vector<vector<int>> points_2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}, {3, 4}, {5, 6}, {7, 8}, {9, 10}, {11, 12}, {13, 14}, {15, 16}, {17, 18}, {19, 20}, {1, 2}, {2, 4}, {3, 6}, {4, 8}, {5, 10}, {6, 12}, {7, 14}, {8, 16}, {9, 18}, {10, 20}};
    result = solution.maxPoints(points_2);
    cout << "points_2 size() " << points_2.size() << endl;
    cout << "Max Points on a Line: " << result << endl;
    return 0;
}
