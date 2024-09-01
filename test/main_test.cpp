#include <stdexcept>
#include <gtest/gtest.h>
#include "../src/safe_ptr.hpp"

/***************************  
 TESTS FOR THE SafePtr CLASS
****************************/
// test the basic functions of the SafePtr class
TEST(SafePtrTests, BasicTests){
    SafePtr<int> ptr;
    ptr.set(10);
    EXPECT_EQ(ptr.get(), 10);
    *ptr = 15;
    EXPECT_EQ(*ptr, 15);
}

// test the copying functionality of the SafePtr class
TEST(SafePtrTests, CopyTests){
    SafePtr<int> ptr;
    SafePtr<int> ptr2 = ptr.copy();
    *ptr = 42;
    EXPECT_EQ(*ptr2, 42);
    *ptr2 = 666;
    EXPECT_EQ(*ptr, 666);
}

// test the move functionality
TEST(SafePtrTests, MoveTests){
    // ensure the value is moved properly
    SafePtr<int> ptr;
    *ptr = 123;
    SafePtr<int> ptr2 = ptr.move();
    EXPECT_EQ(*ptr2, 123);
    // ensure that ptr was emptied correctly 
    bool is_nullptr = true;
    if (ptr.get_raw())
        is_nullptr = false;
    EXPECT_TRUE(is_nullptr);
}

// test that exceptions are thrown when an unitialized pointer is accessed
TEST(SafePtrTests, ExceptionTests){
    SafePtr<int> ptr;
    try{
        int n = ptr.get();
    }
    catch (std::runtime_error e){
        EXPECT_FALSE(strcmp(e.what(), "Attempting to access an uninitialized pointer is forbidden"));
    }
}

/***************************  
 TESTS FOR THE SafeArr CLASS
*****************************/
// TODO: Create tests for the SafeArr class

int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}