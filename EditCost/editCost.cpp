//计算最短编辑距离
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
int main(){
  const char * str0 = "study";
  //const char * str0 = "execution";
  const char * str1 = "spread";
  //const char * str1 = "intention";
  cout <<"Word0:\t" <<str0 <<endl;
  cout <<"Word1:\t" <<str1 <<endl;
  int len0 = strlen(str0);
  int len1 = strlen(str1);
  int lenght = (len0 + 1) * (len1 + 1);
  int * arr = new int[lenght];
  memset(arr,0,lenght);
  int i,j;
  for(i = 0;i <= len0;i++){
    arr[i] = i;
  }
  for(j = 0;j <= len1;j++){
    arr[j * (len0 + 1)] = j;
  }
  for(j = 0;j <= len1;j++){
    for(i = 0;i <= len0;i++){
      cout <<*(arr + j * (len0 +1) + i) <<"\t";
    }
    cout << endl;
  }
  int tmp0,tmp1,tmp2;
  int min;
  for(j = 1;j <= len1;j++){
    for(i = 1;i <= len0;i++){
      tmp1 = *(arr + (j - 1) * (len0 + 1) + i - 1); //left up
      if(str0[i - 1] != str1[j -1]){
	tmp1 += 2;
      }
      min = tmp1;
      tmp0 = *(arr + j * (len0 + 1) + i - 1); //left
      tmp0 += 1;
      tmp2 = *(arr + (j - 1) * (len0 + 1) + i); //right up
      tmp2 += 1;
      if(min > tmp0){ min = tmp0;}
      if(min > tmp2){ min = tmp2;}
      *(arr + j * (len0 + 1) + i) = min;
    }
  }
  cout <<"New \n";
  for(j = 0;j <= len1;j++){
    for(i = 0;i <= len0;i++){
      cout <<*(arr + j * (len0 +1) + i) <<"\t";
    }
    cout << endl;
  }

  delete arr;
  return 0;
}
