#ifndef AYU_ALLOCATOR_CC
#define AYU_ALLOCATOR_CC
#include "allocator.h"

template <typename T, size_t BLockSize>
inline typename Alloctator<T, BLockSize>::size_type
Allocator<T, BLockSize>::padPointer(data_pointer_p, size_type align) const noexcept
{
  uintptr_t result = reinterpret_cast<uintptr_t>(p);
  return ((align - result) % align);
}

template <typename T, size_t BLockSize>
Allocator<T, BLockSize>::Allocator() noexcept
{
  currentBlock_ = nullptr;//内存快头指针
  currentSlot_ = nullptr;//元素链表头指针
  lastSlot_ = nullptr;  //可存放元素的最后指针
  freeSlot = nullptr;  //元素构造后是放掉的内存链表头指针
}

template <typename T, size_t BlockSize>
Allocator<T, BlockSize>::Allocator(const Allocator& memoryPool) noexcept 
:Allocator()
{}

template <typename T, size_t BlockSize>
Allocator<T, BlockSize>::Allocator(Allocator&& memoryPool) noexcept
{
  currentBlock_ = memoryPool.currentBlock_;
  memoryPool.currentBlock_ = nullptr;
  currentSlot_ = memoryPool.currentSlot_;
  lastSlot_ = memoryPool.lastSlot_;
  freeSlots_ = memoryPool.freeSlots;
}


template <typename T, size_t BlockSize>
template<class U>
Allocator<T, BlockSize>::Allocator(const Allocator<U>& memoryPool) noexcept 
:Allocator()
{}

template <typename T, size_t BlockSize>
Allocator<T, BlockSize>&
Allocator<T, BlockSize>::operator=(Allocator&& memoryPool)  noexcept
{
  if (this != &memoryPool)
  {
    std::swap(currentBlock_, memoryPool.currentBlock_);
    currentSlot_ = memoryPool.currentSlot_;
    lastSlot_ = memoryPool.lastSlot_;
    freeSlots_ = memoryPool.freeSlots;
  }
  return *this;
}


template <typename T, size_t BlockSize>
Allocator<T, BlockSize>::~Allocator() noexcept
{
  slot_pointer_ curr = currentBlock_;
  while (curr != nullptr)
  {
    slot_pointer_ prev = curr->next;
    operator delete(reinterpret_cast<void*>(curr));
    curr = prev;
  }
}

template <typename T, size_t BlockSize>
inline typename Allocator<T, BlockSize>::pointer
Allocator<T, BlockSize>::address(reference x) const noexcept
{
  return &x
}

template <typename T, size_t BlockSize>
inline typename Allocator<T, BlockSize>::const_pointer
Allocator<T, BlockSize>::address(const_reference x) const noexcept
{
    return &x;
}

template <typename T, size_t BlockSize>
void Allocator<T, size_t>::allocateBlock()
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
  lastSlot_ reinterpret_cast<slot_pointer_>(newBlock + BlockSize - sizeof(slot_type_) + 1);
}



template <typename T, size_t BlockSize>
inline typename Allocator<T, BlockSize>::pointer
Allocator<T, BlockSize>::allocate(size_type n, const_pointer hint)
{
  if (freeSlots_ != nullptr)
  {
    pointer result = reinterpret_cast<pointer>(freeSlots_);
    freeSlots_ = freeSlots_->next;
    return result;
  }
  else 
  {
    if (currentSlot_ >= lastSlot_)
    allocateBlock();
    return reinterpret_cast<pointer>(currentSlot_++);
  }
}


template <typename T, size_t BlockSize>
inline void
Allocator<T, BlockSize>::deallocate(pointer p, size_type n)
{
  if (p != nullptr) 
  {
    reinterpret_cast<slot_pointer_>(p)->next = freeSlots_;
    freeSlots_ = reinterpret_cast<slot_pointer_>(p);
  }
}

template <typename T, size_t BlockSize>
inline typename Allocator<T, BlockSize>::size_type
Allocator<T, BlockSize>::max_size()
const noexcept
{
  size_type maxBlocks = -1 / BlockSize;
  return (BlockSize - sizeof(data_pointer_)) / sizeof(slot_type_) * maxBlocks;
}



template <typename T, size_t BlockSize>
template <class U, class... Args>
inline void
Allocator<T, BlockSize>::construct(U* p, Args&&... args)
{
  new (p) U (std::forward<Args>(args)...);
}



template <typename T, size_t BlockSize>
template <class U>
inline void
Allocator<T, BlockSize>::destroy(U* p)
{
  p->~U();
}



template <typename T, size_t BlockSize>
template <class... Args>
inline typename Allocator<T, BlockSize>::pointer
Allocator<T, BlockSize>::newElement(Args&&... args)
{
  pointer result = allocate();
  construct<value_type>(result, std::forward<Args>(args)...);
  return result;
}



template <typename T, size_t BlockSize>
inline void
Allocator<T, BlockSize>::deleteElement(pointer p)
{
  if (p != nullptr) 
  {
    p->~value_type();
    deallocate(p);
  }
}


#endif
