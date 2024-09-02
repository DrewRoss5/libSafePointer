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

// ensure basic functions work
TEST(SafeArrTests, BasicTest){
    SafeArr<int> arr(3);
    arr.set(0, 1);
    arr.set(1, 2);
    arr.set(2, 3);
    // validate that all data was set correctly
    int len = arr.length();
    for (int i = 0; i < len; i++)
        EXPECT_EQ(arr[i], i + 1);
}

// ensure copying works
TEST(SafeArrTests, CopyTests){
    SafeArr<int> arr(2);
    SafeArr<int> copy = arr.copy();
    arr.set(0, 42);
    copy.set(1, 24);
    // validate that the data was succesfully updated by both
    EXPECT_EQ(copy[0], 42);
    EXPECT_EQ(arr[1], 24);
}

// ensure moving works
TEST(SafeArrTests, MoveTests){
    SafeArr<int> arr(5);
    for (int i = 0; i < 5; i++)
        arr.set(i, 5 - i);
    SafeArr<int> moved = arr.move();
    // ensure the data was transfered successfully
    for (int i = 0; i < 5; i++)
        EXPECT_EQ(moved[i], 5 - i);
    // ensure the pointer was nulles successfully
    bool is_nullptr = true;
    if (arr.get_raw())
        is_nullptr = false;
    EXPECT_TRUE(is_nullptr);
}

// ensure exceptions are raised as appropriate
TEST(SafeArrTests, ExceptionTests){
    SafeArr<int> arr(2);
    try{
        int tmp = arr[0];
    }
    catch (std::runtime_error e){
        EXPECT_FALSE(strcmp(e.what(), "Cannot retrieve value from an unitialized array"));
    }
    arr.set(0, 123);
    try{
        int tmp = arr[3];
    }
    catch (std::out_of_range e){
        EXPECT_FALSE(strcmp(e.what(), "Invalid index"));
    }
    try{
        int tmp = arr[-1];
    }
    catch (std::out_of_range e){
        EXPECT_FALSE(strcmp(e.what(), "Invalid index"));
    }
}

int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
