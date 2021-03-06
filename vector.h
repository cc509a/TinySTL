#ifndef AYU_VECTOR_H
#define AYU_VECTOR_H

#include "head.h"

namespace ayu
{
    const size_t DEFAULT_CAP = 3;
    template<typename T>
    class vector
    {
    public:
        typedef T* iterator;
        vector()
        :capacity_(DEFAULT_CAP),
        size_(0),
        data_(new T[capacity_]),
        last_(NULL)
        {
        }
        
        virtual ~vector()
        {
            delete []data_;
        }
        
        vector(vector& v)
        :capacity_(v.cap()),
        size_(v.size())
        {
            data_ = v.data_;
            v.data_ = NULL;
        }
        
        vector& operator= (const vector& v)
        {
            sw(*this,v);
            return *this;
        }
        
        T& operator[](size_t i) const
        {
            return data_[i];
        }
        
        size_t size() const
        {
            return size_;
        }
        
        size_t cap() const
        {
            return capacity_;
        }
        
        bool checkCap() const
        {
            if(size_ == capacity_)
            {
                return true;
            }
            return false;
        }
        
        void expand()
        {
            T* temp = data_;
            capacity_ <<=1;
            data_ = new T[capacity_];
            for(size_t i = 0; i < size_; ++i)
            {
                data_[i] = temp[i];
            }
            delete []temp;
        }
        
        void sw (vector& v)
        {
            swap(size_, v.size_);
            swap(data_, v.data_);
            swap(capacity_, v.capacity_);
        }
        
        void push_back(const T& temp)
        {
            if(checkCap())
            {
                expand();
            }
            data_[size_++] = temp;
        }
        
        iterator begin() const
        {
            return data_;
        }
        
        iterator end() const
        {
            return data_+size_;
        }
        
    protected:
        
        
    private:
        size_t capacity_;
        size_t size_;
        T* data_;
        iterator last_;
        
    };
}
#endif
