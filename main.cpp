/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 四  1/28 16:31:13 2016
 ************************************************************************/

#include<iostream>
#include"vector.h"
int main()
{
  ayu::vector<int> v;
  for(int i = 0; i<10; ++i)
  {
    v.push_back(i);
  }
  for(int i = 0; i<10; ++i)
  {
    std::cout<<v[i];
  }

}
