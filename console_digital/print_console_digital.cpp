#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool GetBit(char c, int i){
    return c & (1 << i);
}

/*
 *          0
 *         -------   
 *      |           |
 *      |           |
 *      | 5         | 1
 *      |           |
 *          6
 *         -------   
 *      |           |
 *      | 4         | 2
 *      |           |
 *      |           |
 *         -------   
 *          3
 * 
 */

char GBits[] = {
    0b0111111, 0b0000110, 0b1011011, 0b1001111, 0b1100110, 0b1101101, 0b1111101, 0b0000111, 0b1111111, 0b1101111
};

void PrintDigital(vector<int> digitals, int width, int hight) 
{
    for (int i = 0;i < 5;i++) 
    {
        if (i == 0 || i == 2 || i == 4)
        {
            // Horizontal
            for (int z = 0;z < digitals.size();z++){
                int num = digitals[z];
                int bitpos = 0;
                if (i == 0) 
                {
                    bitpos = 0;
                } else if (i == 2) {
                    bitpos = 6;
                } else if (i == 4) {
                    bitpos = 3;
                }
                cout << " ";
                if (GetBit(GBits[num], bitpos)) 
                {
                    for (int t = 0; t < width;t++) 
                    {
                        cout << "-";
                    }
                } else {
                    for (int t = 0; t < width;t++) 
                    {
                        cout << " ";
                    }
                }
                cout << " ";
            }
            cout <<endl;
        } else {
            // Vertical  
            for (int j = 0;j < hight;j++)
            {
                for (int z = 0;z < digitals.size();z++){
                    int num = digitals[z];
                    int bitpos = 0;
                    if (i == 1) 
                    {
                        bitpos = 5;
                    } else if (i == 3) {
                        bitpos = 4;
                    }
                    // Print the left | 
                    if (GetBit(GBits[num], bitpos))
                    {
                        cout <<"|";
                    } else {
                        cout <<" ";
                    }
                    // Print middle space 
                    for (int k = 0;k < width;k++)
                    {
                        cout <<" ";
                    }
                    if (i == 1) 
                    {
                        bitpos = 1;
                    } else if (i == 3) {
                        bitpos = 2;
                    }
                    // Print the right | 
                    if (GetBit(GBits[num], bitpos))
                    {
                        cout <<"|";
                    } else {
                        cout <<" ";
                    }
                }
                cout <<endl;
            }
        }
    }
}

int main(){
    vector<int> digitals;
    for (int i = 0;i < 10;i++) {
        digitals.push_back(i);
    }
    PrintDigital(digitals, 4, 3);
    return 0;
}
