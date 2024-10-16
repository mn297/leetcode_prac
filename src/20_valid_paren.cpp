#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Solution
{
public:
    bool isValid(string s)
    {
        stack<char> st;
        for (char c : s)
        {
            if (c == '(' || c == '[' || c == '{')
            {
                st.push(c);
            }
            else
            {
                if (st.empty())
                {
                    return false;
                }
                char top = st.top();
                st.pop();
                if ((c == ')' && top != '(') || (c == ']' && top != '[') || (c == '}' && top != '{'))
                {
                    return false;
                }
            }
        }
        return st.empty();
    }
};

int main()
{
    Solution s;
    cout << s.isValid("()") << endl;     // Output: 1
    cout << s.isValid("()[]{}") << endl; // Output: 1
    cout << s.isValid("(]") << endl;     // Output: 0
    return 0;
}