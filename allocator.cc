#ifndef AYU_ALLOCATOR_CC
#define AYU_ALLOCATOR_CC
#include "allocator.h"
namespace ayu
{
    template <typename T, size_t BlockSize>
    inline typename Allocator<T, BlockSize>::size_type
    Allocator<T, BlockSize>::padPointer(data_pointer_ p, size_type align)
    const throw()
    {
        std::size_t result = reinterpret_cast<std::size_t>(p);
        return ((align - result) % align);
    }
    
    
    
    template <typename T, size_t BlockSize>
    Allocator<T, BlockSize>::Allocator()
    throw()
    {
        currentBlock_ = 0;
        currentSlot_ = 0;
        lastSlot_ = 0;
        freeSlots_ = 0;
    }
    
    
    
    template <typename T, size_t BlockSize>
    Allocator<T, BlockSize>::Allocator(const Allocator& Allocator)
    throw()
    {
        Allocator();
    }
    
    
    
    template <typename T, size_t BlockSize>
    template<class U>
    Allocator<T, BlockSize>::Allocator(const Allocator<U>& Allocator)
    throw()
    {
        Allocator();
    }
    
    
    
    template <typename T, size_t BlockSize>
    Allocator<T, BlockSize>::~Allocator()
    throw()
    {
        slot_pointer_ curr = currentBlock_;
        while (curr != 0) {
            slot_pointer_ prev = curr->next;
            operator delete(reinterpret_cast<void*>(curr));
            curr = prev;
        }
    }
    
    
    
    template <typename T, size_t BlockSize>
    inline typename Allocator<T, BlockSize>::pointer
    Allocator<T, BlockSize>::address(reference x)
    const throw()
    {
        return &x;
    }
    
    
    
    template <typename T, size_t BlockSize>
    inline typename Allocator<T, BlockSize>::const_pointer
    Allocator<T, BlockSize>::address(const_reference x)
    const throw()
    {
        return &x;
    }
    
    
    
    template <typename T, size_t BlockSize>
    void
    Allocator<T, BlockSize>::allocateBlock()
    {
        // Allocate space for the new block and store a pointer to the previous one
        data_pointer_ newBlock = reinterpret_cast<data_pointer_>
        (operator new(BlockSize));
        reinterpret_cast<slot_pointer_>(newBlock)->next = currentBlock_;
        currentBlock_ = reinterpret_cast<slot_pointer_>(newBlock);
        // Pad block body to staisfy the alignment requirements for elements
        data_pointer_ body = newBlock + sizeof(slot_pointer_);
        size_type bodyPadding = padPointer(body, sizeof(slot_type_));
        currentSlot_ = reinterpret_cast<slot_pointer_>(body + bodyPadding);
        lastSlot_ = reinterpret_cast<slot_pointer_>
        (newBlock + BlockSize - sizeof(slot_type_) + 1);
    }
    
    
    
    template <typename T, size_t BlockSize>
    inline typename Allocator<T, BlockSize>::pointer
    Allocator<T, BlockSize>::allocate(size_type, const_pointer)
    {
        if (freeSlots_ != 0) {
            pointer result = reinterpret_cast<pointer>(freeSlots_);
            freeSlots_ = freeSlots_->next;
            return result;
        }
        else {
            if (currentSlot_ >= lastSlot_)
                allocateBlock();
            return reinterpret_cast<pointer>(currentSlot_++);
        }
    }
    
    
    
    template <typename T, size_t BlockSize>
    inline void
    Allocator<T, BlockSize>::deallocate(pointer p, size_type)
    {
        if (p != 0) {
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
    
    
    
    template <typename T, size_t BlockSize>
    inline void
    Allocator<T, BlockSize>::construct(pointer p, const_reference val)
    {
        new (p) value_type (val);
    }
    
    
    
    template <typename T, size_t BlockSize>
    inline void
    Allocator<T, BlockSize>::destroy(pointer p)
    {
        p->~value_type();
    }
    
    
    
    template <typename T, size_t BlockSize>
    inline typename Allocator<T, BlockSize>::pointer
    Allocator<T, BlockSize>::newElement(const_reference val)
    {
        pointer result = allocate();
        construct(result, val);
        return result;
    }
    
    
    
    template <typename T, size_t BlockSize>
    inline void
    Allocator<T, BlockSize>::deleteElement(pointer p)
    {
        if (p != 0) {
            p->~value_type();
            deallocate(p);
        }
    }
}
#endif
