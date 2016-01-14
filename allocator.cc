#ifndef AYU_ALLOCATOR_CC
#define AYU_ALLOCATOR_CC
#include "allocator.h"

template <typename T, size_t BLockSize>
inline typename Alloctator<T, BLockSize>::size_type
Alloctator<T, BLockSize>::padPointer(data_pointer_p, size_type align)
const noexcept
{
  uintptr_t result = reinterpret_cast<uintptr_t>(p);
  return ((align - result) % align);
}


#endif
