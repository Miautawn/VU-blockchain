#ifndef HASHPOINTER_HPP
#define HASHPOINTER_HPP

#include "main_imports.hpp"

template <class T>
class HashPointer {

    private:
        T* data_ptr;
        string hash;

    public:
        HashPointer(string hash, T* data_ptr = nullptr) : hash{hash}, data_ptr{data_ptr} {}
        
        string getHash() {
            return hash;
        }

        T* getPointer() {
            return data_ptr;
        }

        ~HashPointer() {
            delete data_ptr;
        }


};


#endif