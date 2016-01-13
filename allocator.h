#ifndef AYU_ALLOCATOR_H
#define AYU_ALLOCATOR_H

#include <climits>
#include <cstddef>
namespace ayu
{
template <typename T, size_t BlockSize = 4096>

class Allocator
{
  public:
    typedef T                   value_type;
    typedef T*                  pointer;
    typedef T&                  reference;
    typedef const T*            const_pointer;
    typedef const T&            const_reference;
    typedef size_t              size_type;
    typedef ptrdiff_t           difference_type;
    typedef std::false_type     on_container_copy_assignment;
    typedef std::true_type      on_container_move_assignment;

    template <typename U> struct rebind
    {
        typedef Allocator<U> other;
    };

    Alloctor() noexcept;
    Allocator(const Allocator& allocator) noexcept;
    Allocator(Allocator&& allocator) noexcept;
    template<class U> Allocator(const Allocator<U>& allocator)noexcept;

    ~Allocator() noexcept;

    Allocator& operator=(const Allocator& allocator) = delete;
    Allocator& operator=(Allocator&& allocator) noexcept;
    //元素取址
    pointer address(refrence x) const noexcept;
    const_pointer address(const_reference x) const noexcept;

    //allocae one object at a time
    pointer allocate(size_type n = 1,const_pointer hint = 0);
    void deallocate(pointer p, size_type n = 1);

    size_type max_size() const noexcept;
    //基于内存池的释放和构造
    tenplate<class U, class... Args> void construct(U* p, Args&&... args);
    template<class U> void destory(U* p);
    //自带内存申请和释放
    template<class,,, Args> pointer newElement(Args&&... args);
    void deketeEkenent(pointer p);

  private:
    //用于存放元素或next指针
    union Slot_
    {
        value_type element;
        Slot_* next;
    }
    //内存首地址
    typedef char* data_pointer_;
    typedef Slot_ slot_type_;
    typedef Slot_* slot_poniter_;

    slot_pointer_ currentBlock_;//内存块链表头指针
    slot_pointer_ currentSlot_;//元素链表头指针
    slot_pointer_ lastSlot_;//可存放元素的最后指针
    slot_pointer_ freeSlots_;//元素构造后释放的内存链表头指针

    size_type padPointer(data_pointer_p, size_type align) const noexcept;//计算对齐空间
    void allocateBlock();//申请内存放进内存池

    static_assert(BlockSize >= 2 * sizeof(slot_type_), "BlockSize too smll.");

};
}//end ayu

