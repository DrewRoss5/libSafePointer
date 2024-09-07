#pragma once
  
#include <stdexcept>

template <typename T>

class SafePtr{
    private:
        T*   ptr_ {nullptr};
        int  size_ {0}; 
        bool is_initialized_ {false};
        bool is_copy_ {false};
        void free_mem();
    public:
        SafePtr();
        ~SafePtr();
        // operators
        bool operator==(const T& val);
        bool operator==(const SafePtr<T>& val);
        T& operator*();
        // getters (defined here for conciseness)
        T* get_raw() {return this->ptr_;}
        T get() const ;
        int size() const {return this->size_;}
        // setter prototytpes
        void set(const T& tmp);
        // other functions
        void reset();
        SafePtr<T> copy();
        SafePtr<T> move();
        void transfer(SafePtr<T>& new_arr);
};

// simple constructor
template <typename T>
SafePtr<T>::SafePtr(){
    this->size_ = sizeof(T);
    this->ptr_ = new T;
}

// simple destructor
template <typename T>
SafePtr<T>::~SafePtr(){
    if (!this->is_copy_)
        delete this->ptr_;
}

// equality opperator for the raw type 
template <typename T> 
bool SafePtr<T>::operator==(const T& val){
    return *(this->ptr_) == val;
}

// equality operator for SafePtr comparisons
template <typename T>
bool SafePtr<T>::operator==(const SafePtr<T>& val){
    return *(this->ptr_) == val.get();
}

// an operator to return the dereferenced pointer
template <typename T>
T& SafePtr<T>::operator*(){
    this->is_initialized_ = true;
    return *(this->ptr_);
} 

// returns the value pointed to, throws an exception if the value is uninitialized
template <typename T>
T SafePtr<T>::get() const{
    if (!this->is_initialized_)
        throw std::runtime_error("Attempting to access an uninitialized pointer is forbidden");
    return *(this->ptr_);
}

// sets the value of the pointer
template <typename T>
void SafePtr<T>::set(const T& val){
    this->is_initialized_ = true;
    *(this->ptr_) = val;
}

// frees the memory currently associated with the pointer and sets the pointer to null
template <typename T>
void SafePtr<T>::reset(){
    this->free_mem();
    this->size_ = 0;
}

// frees all memory allocated to the pointer, respective of if it's an array or not
template <typename T>
void SafePtr<T>::free_mem(){
    delete this->ptr_;
    this->is_initialized_ = false;
    this->ptr_ = nullptr;
}

// returns a copy of this pointer, pointing to the same memory address 
template <typename T>
SafePtr<T> SafePtr<T>::copy(){
    SafePtr<T> new_ptr;
    new_ptr.ptr_ = this->ptr_;
    new_ptr.is_initialized_ = this->is_initialized_;
    new_ptr.is_copy_ = true;
    return new_ptr;
}

// creates a non-copy clone of this pointer, and sets this pointer to null
template <typename T>
SafePtr<T> SafePtr<T>::move(){
    SafePtr<T> new_ptr;
    this->transfer(new_ptr);
    return new_ptr;
}

// transfers the ownership of this pointer to another a pointer
template <typename T>
void SafePtr<T>::transfer(SafePtr<T>& new_ptr){
    // delete the exisiting memory of new_ptr, if it owns the memory, and transfer the pointer
    if (new_ptr.is_initialized_ && !new_ptr.is_copy_)
        new_ptr.reset();
    new_ptr.is_copy_ = this->is_copy_;
    new_ptr.is_initialized_ = this->is_initialized_;
    new_ptr.ptr_ = this->ptr_;
    // clean up this object
    this->ptr_ = nullptr;
    this->is_initialized_ = false;
    this->is_copy_ = false;
}

// a class to automatically handle memory for array style pointers
template <typename T>
class SafeArr{
    private:
        T* ptr_ {nullptr};
        int size_ {0};
        int length_ {0};
        bool is_initialized_ {false};
        bool is_copy_ {false};
        void free_mem();
    public:
        SafeArr(const int n);
        ~SafeArr();
        // getters
        T get(const unsigned int index);
        T* get_raw() {return this->ptr_;};
        int size() const {return this->size_;}
        int length() const {return this->length_;}
        bool is_initialized() const {return this->is_initialized_;}
        // operators
        T operator[](const unsigned int index);
        // other functions
        void set(const unsigned int index, T& val);
        void reset(const unsigned int n);
        SafeArr<T> copy();
        SafeArr<T> move();
        void transfer(SafeArr<T>& new_arr);
};  

// simple constructor, creates an array with room for n elements
template <typename T>
SafeArr<T>::SafeArr(const int n){
    if (n < 0)
        throw std::invalid_argument("Invalid array size");
    this->ptr_ = new T[n];
    this->size_ = sizeof(T) * n;
    this->length_ = n;
}

// simple destructor
template <typename T>
SafeArr<T>::~SafeArr(){
    if (!this->is_copy_)
        delete[] this->ptr_;
}

// sets the value of a single element in the array, and marks the array as initialized
template <typename T>
void SafeArr<T>::set(const unsigned int index, T& val){
    if (index < 0 || index > this->length_)
        throw std::out_of_range("Invalid index");
    this->is_initialized_ = true;
    this->ptr_[index] = val;
}

// returns the value at the given index, throwing an exception if the index is out of bounds, or if the array is unitialized
template <typename T>
T SafeArr<T>::get(const unsigned  int index){
    if (!this->is_initialized_)
        throw std::runtime_error("Cannot retrieve value from an unitialized array");
    if (index < 0 || index > this->length_)
        throw std::out_of_range("Invalid index");
    return this->ptr_[index];
}

// operator for the get method
template <typename T>
T SafeArr<T>::operator[](const unsigned int index){
    return get(index);
}

// deletes the memory associated with the array
template <typename T>
void SafeArr<T>::free_mem(){
    delete[] this->ptr_;
    this->size_ = 0;
    this->length_ = 0;
    this->is_initialized_ = false;
    this->ptr_ = nullptr;
}

// resets the array, and reallocates it with a new size
template <typename T>
void SafeArr<T>::reset(const unsigned int n){
    free_mem();
    if (n < 0)
        throw std::invalid_argument("Invalid array size");
    this->ptr_ = nullptr;
    this->size_ = sizeof(T) * n;
    this->length_ = n;
    this->is_copy_ = false;
}

// returns a copy of this pointer, pointing to the same memory address 
template <typename T>
SafeArr<T> SafeArr<T>::copy(){
    SafeArr<T> new_arr(this->length_);
    new_arr.is_initialized_ = this->is_initialized_;
    new_arr.ptr_ = this->ptr_;
    new_arr.is_copy_ = true;
    return new_arr;
}

// creates a non-copy clone of this pointer, and sets this pointer to null
template <typename T>
SafeArr<T> SafeArr<T>::move(){
    SafeArr<T> new_arr(this->length_);
    this->transfer(new_arr);
    return new_arr;
}

// transfers the memory of this SafeArr to another
template <typename T>
void SafeArr<T>::transfer(SafeArr<T>& new_arr){
    // transfer the memory
    if (new_arr.is_initialized_ && !new_arr.is_copy_)
        new_arr.reset(this->length_);
    new_arr.is_copy_ = this->is_copy_;
    new_arr.is_initialized_ = this->is_initialized_;
    new_arr.ptr_ = this->ptr_;
    // clean up this object
    this->ptr_ = nullptr;
    this->is_copy_ = false;
    this->is_initialized_ = false;
    this->size_ = 0;
}
