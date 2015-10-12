//计算最短编辑距离
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int LevenshteinDistanceIterative(string s, int len_s, string t, int len_t)
{
    char * row_before = new char[len_s + 1];
    char * row_current = new char[len_s + 1];
    for (int i = 0;i <= len_s;i++) 
    {
        row_before[i] = i;
    }
    for (int i = 1;i <= len_t;i++) 
    {
        row_current[0] = i;
        for (int j = 1;j <= len_s;j++)
        {
            int deleteCost = row_before[j] + 1;
            int insertCost = row_current[j - 1] + 1;
            int replaceCost = 0;
            if (t.c_str()[i] != s.c_str()[j - 1]) 
            {
                replaceCost = row_before[j - 1] + 1;
            } else {
                replaceCost = row_before[j - 1];
            }
            row_current[j] = std::min(replaceCost, std::min(deleteCost, insertCost) );
        }
        std::swap(row_before, row_current);
    }
    delete [] row_before;
    delete [] row_current;
    return row_current[len_s];
}

int LevenshteinDistanceRecursive(string s, int len_s, string t, int len_t)
{
    int cost;

    /* base case: empty strings */
    if (len_s == 0) return len_t;
    if (len_t == 0) return len_s;

    /* test if last characters of the strings match */
    if (s[len_s-1] == t[len_t-1])
        cost = 0;
    else
        cost = 1;

    /* return minimum of delete char from s, delete char from t, and delete char from both */
    return std::min(LevenshteinDistanceRecursive(s, len_s - 1, t, len_t    ) + 1,
            std::min(LevenshteinDistanceRecursive(s, len_s    , t, len_t - 1) + 1,
            LevenshteinDistanceRecursive(s, len_s - 1, t, len_t - 1) + cost) );
}

int main(){

    string  str0 = "study";
    string str1 = "spread";

    cout <<"Input two word:" <<endl;
    cin >> str0;
    cin >> str1;
    cout <<"Edit distance Recursive is " << LevenshteinDistanceRecursive(str0, str0.size(), str1, str1.size()) << endl;
    cout <<"Edit distance Iterative is " << LevenshteinDistanceIterative(str0, str0.size(), str1, str1.size()) << endl;
    return 0;
}
