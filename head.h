#ifndef AYU_HEAD_H
#define AYU_HEAD_H
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
}//end ayu
#endif
