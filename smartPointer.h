//
// Created by zy on 2021/4/16.
//

#ifndef AUTO_PTR_SMARTPOINTER_H
#define AUTO_PTR_SMARTPOINTER_H
#include <iostream>
#include <memory>

template<typename T>
class smartPointer{
private:
    T* my_ptr;
    size_t * count;
public:
    smartPointer(T* ptr = nullptr): my_ptr(ptr){
        if(my_ptr){
            count = new size_t(1);
        }
        else{
            count = new size_t(0);
        }
    }
    smartPointer(const smartPointer& ptr){
        if(this != &ptr){
            this->my_ptr = ptr.my_ptr;
            this->count = ptr.count;
            (*this->count)++;
        }
    }

    smartPointer& operator=(const smartPointer& ptr){
        if(this->my_ptr == ptr.my_ptr){
            return *this;
        }
        if(this->my_ptr){
            (*this->count)--;
            if(*this->count == 0){
                delete this->my_ptr;
                delete this->count;
            }
        }
        this->my_ptr = ptr.my_ptr;
        this->count = ptr.count;
        (*this->count)++;
        return *this;
    }

    T& operator*(){
        assert(this->my_ptr == nullptr);
        return *(this->my_ptr);
    }

    T& operator->(){
        assert(this->my_ptr == nullptr);
        return this->my_ptr;
    }

    ~smartPointer(){
        (*this->count)--;
        if(*this->count == 0){
            delete this->my_ptr;
            delete this->count;
        }
    }

    size_t use_count(){
        return *this->count;
    }
};

#endif //AUTO_PTR_SMARTPOINTER_H
