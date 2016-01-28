/*************************************************************************
	> File Name: pair.h
	> Author: 
	> Mail: 
	> Created Time: 四  1/28 12:00:55 2016
 ************************************************************************/

#ifndef AYU_PAIR_H
#define AYU_PAIR_H
namespace ayu 
{
template<typename T1, typename T2>
  struct pair
  {
    typedef T1 fist_type;
    typedef T2 second_type;

    T1 first;
    T2 second;

    pair():first(T1()),second(T2()) {}

    pair(const T1& a, const T2& b):first(a),second(b){}
  };
  //template<typename T1, typename T2>
  
}//endayu

#endif
