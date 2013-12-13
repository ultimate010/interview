#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

int getLCS(const char* str1,const char* str2,char * result);
void buildRegex(const char * lcs,const char * str,char * result);
bool matchChZeroOrMore(const char * str,const char * regex,const char ch);
bool subMatch(const char * str,const char * regex);
bool match(const char * str,const char * regex);
void subBuild(const char * str,char * result,int pos);

void buildRegex(const char * lcs,const char * str,char * result){
  int len = strlen(lcs);
  for(int i = 0;i < len;i++){
    subBuild(lcs,result,i);
    if(!match(str,result)){
      return ;
    }
  }
  *result = '\0';
  return ;
}

void subBuild(const char * str,char * result,int pos){
  for(int i = 0;i <= pos && *(str + i) != '\0';i++){
    *result++ = *(str + i);
  }
  *result++ = '+';
  for(int i = pos + 1;*(str + i) != '\0';i++){
    *result++ = *(str + i);
  }
  *result++ = '\0';
}

bool match(const char * str,const char * regex){
  if(*str == '\0' || *regex == '\0'){
    return false;
  }
  if(regex[0] == '^'){
    return subMatch(str,++regex); //从头匹配
  }
  while(*str != '\0'){
    if(subMatch(str++,regex)){
      return true;
    }
  }
  return false;
}


bool subMatch(const char * str,const char * regex){
  if(*(regex + 1) == '*'){
    return matchChZeroOrMore(str,regex + 2,*regex); //匹配零或多个
  }
  if(*(regex + 1) == '+'){
    if(*regex == *str){
      return matchChZeroOrMore(str + 1,regex + 2,*regex); //匹配零或多个
    }
  }
  if(*regex == '$' && *(regex + 1) == '\0'){
    return *str == '\0';
  }
  if(*regex == '\0'){
    return true; //匹配完了
  }
  if(*str != '\0' && (*regex == '.' || *regex == *str)){
    return subMatch(++str,++regex);
  }
  return false;
}

bool matchChZeroOrMore(const char * str,const char * regex,const char ch){
  do{
    if(subMatch(str,regex)){
      return true;
    }
  }while(*str != '\0' && (*str++ == ch || ch == '.')); //匹配任意或相等
  return false;
}
int getLCS(const char* str1,const char* str2,char * result){
  //求得两个字符串的最大公共子串
  int length1 = strlen(str1);
  int length2 = strlen(str2);
  //开辟空间
  int **c = new int*[length1+1];
  for(int i = 0; i < length1+1; i++){
    c[i] = new int[length2+1];
  }

  for(int i = 0; i < length1+1; i++){
    c[i][0]=0;        //第0列都初始化为0
  }
  for(int j = 0; j < length2+1; j++){
    c[0][j]=0;        //第0行都初始化为0
  }


  for(int i = 1; i < length1+1; i++){
    for(int j = 1; j < length2+1; j++){
      if(str1[i-1]==str2[j-1]){
	c[i][j]=c[i-1][j-1]+1;
      }else if(c[i-1][j]>c[i][j-1]){
	c[i][j]=c[i-1][j];
      }else{
	c[i][j]=c[i][j-1];
      }
    }
  }

  int len,k;
  len = k = c[length1][length2];
  result[k--]='\0';
  int i = length1;
  int j = length2;
  while(i > 0 && j > 0){
    if(str1[i - 1] == str2[j - 1]){
      result[k--] = str1[i - 1];
      i--;
      j--;
    }else if(c[i-1][j]<c[i][j-1]){
      j--;
    }else{
      i--;
    }
  }

  for(i = 0; i < length1+1; i++){    //释放空间
    delete[] c[i];
  }
  delete[] c;
  return len;
}

int main(){
  const char * str = "acdef";
  const char * str1 = "ccef";
  const char * str2 = "fgh";
  char result[256];
  char resultRegex[256];

  getLCS(str,str1,result); //获得最大公共子串
  buildRegex(result,str2,resultRegex);

  cout <<"The str0 is " <<str <<"\tThe str1 is " <<str1 <<"\tThe str2 is " <<str2 <<endl;
  cout <<"The regex is " <<resultRegex <<endl;

  return 0;
}
