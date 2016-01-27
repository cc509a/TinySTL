#ifndef AYU_HEAD_H
#define AYU_HEAD_H
#include <iostream>
#include <assert.h>
namespace ayu
{
typedef unsigned int size_t;

template<typename T>
inline void swap(T& a,T& b)
{
  T temp = a;
  a = b;
  b = temp;
}

size_t strlen(const char* str)
{
 assert(str != nullptr);
 size_t len = 0;
 while((*str++) != '\0')
 {
   ++len;
 }
 return len;
}

char* strcpy(char* des,const  char* source)
{
  assert((des != nullptr) && (source != nullptr));
  char *ret = des;
  while((*des++ = *source++) != '\0');
  return ret;
}

}//end ayu
#endif
