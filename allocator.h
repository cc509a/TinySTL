#ifndef AYU_ALLOCATOR_H
#define AYU_ALLOCATOR_H

#include <climits>
#include <cstddef>
namespace ayu
{
template <typename T, size_t BlockSize = 4096>

class alloctaor
{
  public:
    typedef T   value_type;
    typedef T*  pointer;
    typedef T&  reference;
    typedef const T* const_pointer;
    typedef const T& const_reference;
    typedef size_t  size_type;
    typedef ptrdiff_t   difference_type;
    typedef std::false_type_on_conta
}
}//end ayu

