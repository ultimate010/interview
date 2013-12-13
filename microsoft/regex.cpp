#include <iostream>
using namespace std;

bool matchChZeroOrMore(const char * str,const char * regex,const char ch);
bool subMatch(const char * str,const char * regex);
bool match(const char * str,const char * regex);

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

int main(){
  const char * regex = "ab*";
  const char * regex1 = "^ab+";
  const char * regex2 = "ab+";
  const char * regex3 = "bc$";

  const char * testStr = "babc";
  const char * testStr1 = "bac";
  const char * testStr2 = "abbc";
  const char * testStr3 = "aabc";
  const char * testStr4 = "aabcc";
  const char * testStr5 = "aacc";

  if(match(testStr,regex)){
    cout <<"Match " << regex <<" The str is " <<testStr <<endl;
  }else{
    cout <<"Not match " << regex <<" The str is " <<testStr <<endl;
  }

  if(match(testStr5,regex)){
    cout <<"Match " << regex <<" The str is " <<testStr5 <<endl;
  }else{
    cout <<"Not match " << regex <<" The str is " <<testStr5 <<endl;
  }

  if(match(testStr1,regex)){
    cout <<"Match " << regex <<" The str is " <<testStr1 <<endl;
  }else{
    cout <<"Not match " << regex <<" The str is " <<testStr1 <<endl;
  }

  if(match(testStr2,regex1)){
    cout <<"Match " << regex1 <<" The str is " <<testStr2 <<endl;
  }else{
    cout <<"Not match " << regex1 <<" The str is " <<testStr2 <<endl;
  }

  if(match(testStr3,regex1)){
    cout <<"Match " << regex1 <<" The str is " <<testStr3 <<endl;
  }else{
    cout <<"Not match " << regex1 <<" The str is " <<testStr3 <<endl;
  }

  if(match(testStr2,regex2)){
    cout <<"Match " << regex2 <<" The str is " <<testStr2 <<endl;
  }else{
    cout <<"Not match " << regex2 <<" The str is " <<testStr2 <<endl;
  }
  if(match(testStr1,regex2)){
    cout <<"Match " << regex2 <<" The str is " <<testStr1 <<endl;
  }else{
    cout <<"Not match " << regex2 <<" The str is " <<testStr1 <<endl;
  }
  if(match(testStr3,regex3)){
    cout <<"Match " << regex3 <<" The str is " <<testStr3 <<endl;
  }else{
    cout <<"Not match " << regex3 <<" The str is " <<testStr3 <<endl;
  }
  if(match(testStr4,regex3)){
    cout <<"Match " << regex3 <<" The str is " <<testStr4 <<endl;
  }else{
    cout <<"Not match " << regex3 <<" The str is " <<testStr4 <<endl;
  }
  return 0;
}


