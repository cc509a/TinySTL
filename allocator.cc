#ifndef AYU_ALLOCATOR_CC
#define AYU_ALLOCATOR_CC
#include "allocator.h"
namespace ayu
{

template <typename T, size_t BLockSize>
inline typename Allocator<T, BLockSize>::size_type
Allocator<T, BLockSize>::padPointer(data_pointer_ p, size_type align) const throw()
{
  //uintptr_t result = reinterpret_cast<uintptr_t>(p);
  size_t result = reinterpret_cast<size_t>(p);
  return ((align - result) % align);
}

template <typename T, size_t BLockSize>
Allocator<T, BLockSize>::Allocator() throw()
{
  currentBlock_ = NULL;//内存快头指针
  currentSlot_ = NULL;//元素链表头指针
  lastSlot_ = NULL;  //可存放元素的最后指针
  freeSlots_  = NULL;  //元素构造后是放掉的内存链表头指针
}

template <typename T, size_t BlockSize>
Allocator<T, BlockSize>::Allocator(const Allocator& Allocator) throw() 
{
  Allocator();
}


template <typename T, size_t BlockSize>
template<class U>
Allocator<T, BlockSize>::Allocator(const Allocator<U>& memoryPool) throw() 
{
  Allocator();
}

template <typename T, size_t BlockSize>
Allocator<T, BlockSize>::~Allocator() throw()
{
  slot_pointer_ curr = currentBlock_;
  while (curr != NULL)
  {
    slot_pointer_ prev = curr->next;
    operator delete(reinterpret_cast<void*>(curr));
    curr = prev;
  }
}
/* return address */
template <typename T, size_t BlockSize>
inline typename Allocator<T, BlockSize>::pointer
Allocator<T, BlockSize>::address(reference x) const throw()
{
  return &x;
}

template <typename T, size_t BlockSize>
inline typename Allocator<T, BlockSize>::const_pointer
Allocator<T, BlockSize>::address(const_reference x) const throw()
{
    return &x;
}

template <typename T, size_t BlockSize>
void Allocator<T, BlockSize>::allocateBlock()
{
  //allocate space for new block and store a poniter to the previous one
  data_pointer_ newBlock = reinterpret_cast<data_pointer_>(operator new(BlockSize));
  //old block head linked new block
  reinterpret_cast<slot_pointer_>(newBlock)->next = currentBlock_;
  // new currentBlock
  currentBlock_ = reinterpret_cast<slot_pointer_>(newBlock);
  //pad block body to staisf the alignment requriments for elements 
  data_pointer_ body = newBlock + sizeof(slot_pointer_);
  //in order to calculate how much position alignment should be vacated
  size_type bodyPadding = padPointer(body, sizeof(slot_type_));
  //for this new block add some char* type space
  currentSlot_ = reinterpret_cast<slot_pointer_>(body + bodyPadding);
  //calculate the last slot_type postion
  lastSlot_ = reinterpret_cast<slot_pointer_>(newBlock + BlockSize - sizeof(slot_type_) + 1);
}



template <typename T, size_t BlockSize>
inline typename Allocator<T, BlockSize>::pointer
Allocator<T, BlockSize>::allocate(size_type n, const_pointer hint)
{
  //如果 eslot_非空 就在eSLots_中取
  if (freeSlots_ != NULL)
  {
    pointer result = reinterpret_cast<pointer>(freeSlots_);
    freeSlots_ = freeSlots_->next;//更新freeSlots
    return result;
  }
  else 
  {//分配新的
    if (currentSlot_ >= lastSlot_)
    allocateBlock();
    //从分配的block中划出去
    return reinterpret_cast<pointer>(currentSlot_++);
  }
}


template <typename T, size_t BlockSize>
inline void
Allocator<T, BlockSize>::deallocate(pointer p, size_type n)
{
  if (p != NULL) 
  {
    reinterpret_cast<slot_pointer_>(p)->next = freeSlots_;
    freeSlots_ = reinterpret_cast<slot_pointer_>(p);
  }
}

template <typename T, size_t BlockSize>
inline typename Allocator<T, BlockSize>::size_type
Allocator<T, BlockSize>::max_size()
const throw()
{
  size_type maxBlocks = -1 / BlockSize;
  return (BlockSize - sizeof(data_pointer_)) / sizeof(slot_type_) * maxBlocks;
}

// 在已分配内存上构造对象
template <typename T, size_t BlockSize>
inline void
Allocator<T, BlockSize>::construct(pointer p, const_reference val)
{
    // placement new 用法，在已有内存上构造对象，调用 T 的复制构造函数，
    new (p) value_type (val);
}

// 销毁对象
template <typename T, size_t BlockSize>
inline void
Allocator<T, BlockSize>::destroy(pointer p)
{
    // placement new 中需要手动调用元素 T 的析构函数
    p->~value_type();
}

// 创建新元素
template <typename T, size_t BlockSize>
inline typename Allocator<T, BlockSize>::pointer
Allocator<T, BlockSize>::newElement(const_reference val)
{
    // 申请内存
    pointer result = allocate();
      // 在内存上构造对象
      construct(result, val);
        return result;
}




template <typename T, size_t BlockSize>
inline void
Allocator<T, BlockSize>::deleteElement(pointer p)
{
  if (p != NULL) 
  {
    p->~value_type();
    deallocate(p);
  }
}

}//end ayu
#endif
