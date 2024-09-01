# libSafePointer
A library for safe pointers, similar to smart pointers. Created for educationalpurposes

# Roadmap/ToDO
- Finish documentation
- Create a proper test suite (using GTest)
- Implement a move command for the `SafePtr` class
- Implement functionality simmilar to shared pointers
- Replace the use of  `new` and `delete` with a custom allocater.

# API:
## The `SafePtr` Class:
A dynamically allocated pointer of a user-specified type. Manages its own memory and automatically frees it once needed.
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
### Notes:
Copied safe pointers are shallow copies.<br>
Copied safe pointers do not automatically delete their allocated memory, if you desire to free the memory from a copy, you must explicitly call the `reset` method on the copy.
## The `SafeArr` Class:
A dynamically allocated array of a user specified type. As with the `SafePtr` class, this manages its own memory.
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
