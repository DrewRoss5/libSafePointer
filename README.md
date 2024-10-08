# libSafePointer
A library for safe pointers, similar to smart pointers. Created for educationalpurposes

# API:
## The `SafePtr` Class:
A dynamically allocated pointer of a user-specified type. Manages its own memory and automatically frees it once needed.
### Public Methods:
#### SafePtr<T>():
- Parameters:
  - None
- Return type: `SafePtr<T>`
- Notes: The default constructor for this class.
#### get_raw():
- Parameters:
     - None
- Return type: `T*`
- Returns: The raw pointer for this object
#### get():
- Parameters:
   - None
- Return type: `T`
- Returns: The value this object points to
- Notes:
  - A mutable reference to this value be accessed with the `*` operator.
  - Throws a `std::runtime_error` if the pointer is uninitialized
#### size():
- Parameters:
   - None
- Return type: `int`
- Returns: The size of this pointer in bytes.
#### set(const T& val):
- Parameters
  - `const T& value`: The value to set this pointer to.
- Returns: `void`
- Description: Sets the value of the pointer to the provide value.
#### reset():
- Parameters:
     - None
- Returns: `void`
- Description: Sets this pointer to null, and resets all member variables
#### copy():
- Parameters:
  - None
- Return Type: `SafePtr<T>`
- Returns: The copy of this object.
- Description: Creates a shallow copy of this pointer, and does not modify this object.
- Notes:
  - Intended use case is using this method to pass the pointer to a function
  - A copy of a SafePtr does not automatically free it's memory once it goes out of scope. If you desire to free the memory from a copy, you must explicitly call `reset` on the copied object. Though, doing so is generally inadvisable, as it may cause undefined behavior when the original smart pointer is deconstructed.
#### move():
- Parameters:
  - None
- Return Type: `SafePtr<T>`
- Returns: A clone of this object.
- Description: Creates a shallow copy of this pointer, and sets the pointer on this object to `null`
- Notes:
  - Unlike the `copy` method, the returned object will free its own memory once it goes out of scope.
  - The above does not apply if the caller is, itself, a copy.
#### transfer(SafePtr<T>& new_ptr)
- Parameters:
  - `SafePtr<T>& new_ptr`: The pointer to transfer this object's memory to.
- Returns: `void`
- Description: Copies the pointer of this object to `new_ptr`, and overwrites this object's pointer. In essence, this replaces this object with `new_ptr` 
### Example:
#### Code:
```
#include <iostream>
#include "safe_ptr.hpp"

void double_val(SafePtr<int> ptr){
    *ptr *= 2;
}

int main(){
    SafePtr<int> ptr;
    ptr.set(32);
    double_val(ptr.copy());
    std::cout << "Value: " << ptr.get() << std::endl;
}
```
#### stdout:
`Value: 64`

## The `SafeArr` Class:
A dynamically allocated array of a user specified type and size. As with the `SafePtr` class, this manages its own memory.
### Public Methods:
#### SafeArr<T>(unsigned int n):
- Parameters:
   - `unsigned int n`: The size (in elements) of the array to be allocated
- Return Type: `SafeArr<T>`
#### get(unsigned int index):
- Parameters: 
  - `unsigned int index`: the index in the array to get
- Return type: `T`
- Returns: The element at `index` if present.
- Notes:
  - Throws an exception if the array hasn't been initialized, or if the index is out of range
  - Can also be accessed using bracket opperators (ex: `myarr[0]`)
#### size():
- Parameters:
  - None
- Return type: `int`
- Returns: The size of the array in bytes
#### length():
- Parameters:
  - None
- Return type: `int`
- Returns: The number of elements in the array
#### is_initalized():
- Parameters:
  - None
- Return type: `bool`
- Returns: `true` if the array is initialized, otherwise returns `false`
#### set(unsigned int index, T val):
- Parameters:
  - `unsigned int index`: the index in the array to set the value of
  - `T val`: the value to be set
- Returns: `void`
- Description: Sets the value at `index` to `T`. Throws an exception if the array hasn't been initialized, or if the index is out of range.
#### reset(unsigned int n):
- Parameters:
  - `unsigned int n`: The size to reallocate the array to
- Returns: `void`
- Description: Frees the memory associated with the array and reallocates the array for a size of `n` elements.
#### copy():
  See `copy` method of the `SafePtr` class
#### move():
  See `move` method of the `SafePtr` class
#### transfer():
  See `transfer` method of the `SafePtr` class
### Example:
#### Code:
```
#include <iostream>
#include "safe_ptr.hpp"
using std::string;

int main(){
    SafeArr<string> arr(4);
    arr.set(0, "Foo");
    arr.set(1, "Bar");
    arr.set(2, "Hello");
    arr.set(3, "World");
    for (int i = 0; i < arr.length(); i++){
        std::cout << arr[i] << std::endl;
    }
}
```
#### stdout:
```
Foo
Bar
Hello
World
```
### Notes:
Same caveats as the copy method for the `SafePtr` class apply
