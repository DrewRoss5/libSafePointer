#pragma once
  
#include <stdexcept>

template <typename T>

class SafePtr{
    private:
        T*   ptr_ {nullptr};
        int  size_ {0}; 
        bool is_initialized_ {false};
        void free_mem();
    public:
        SafePtr();
        ~SafePtr();
        // operators
        bool operator==(const T val);
        bool operator==(const SafePtr<T>& val);
        T& operator*();
        // getters (defined here for conciseness)
        T* get_raw() {return this->ptr_;}
        T get() const ;
        int size() const {return this->size_;}
        // setter prototytpes
        void set(const T tmp);
        // other functions
        void reset();
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
    this->free_mem();
}

// equality opperator for the raw type 
template <typename T> 
bool SafePtr<T>::operator==(const T val){
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
void SafePtr<T>::set(T val){
    this->is_initialized = true;
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

// a class to automatically handle memory for array style pointers
template <typename T>
class SafeArr{
    private:
        T* ptr_ {nullptr};
        int size_ {0};
        int length_ {0};
        bool is_initialized_{false};
        void free_mem();
    public:
        SafeArr(const int n);
        ~SafeArr();
        // getters
        T get(const int index);
        int size() const {return this->size_;}
        int length() const {return this->length_;}
        bool is_initialized() const {return this->is_initialized_;}
        // operator
        T operator[](const int index);
        // other functions
        void set(const int index, T val);
        void reset(const int n);
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
    free_mem();
}

// sets the value of a single element in the array, and marks the array as initialized
template <typename T>
void SafeArr<T>::set(const int index, T val){
    if (index < 0 || index > this->length_)
        throw std::out_of_range("Invalid index");
    this->is_initialized_ = true;
    this->ptr_[index] = val;
}

// returns the value at the given index, throwing an exception if the index is out of bounds, or if the array is unitialized
template <typename T>
T SafeArr<T>::get(const int index){
    if (!this->is_initialized_)
        throw std::runtime_error("Cannot retrieve value from an unitialized array");
    if (index < 0 || index > this->length_)
        throw std::out_of_range("Invalid index");
    return this->ptr_[index];
}

// operator for the get method
template <typename T>
T SafeArr<T>::operator[](const int index){
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
void SafeArr<T>::reset(const int n){
    free_mem();
    if (n < 0)
        throw std::invalid_argument("Invalid array size");
    this->ptr_ = new T[n];
    this->size_ = sizeof(T) * n;
    this->length_ = n;
}