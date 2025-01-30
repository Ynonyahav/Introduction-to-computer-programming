
#include <iostream>
#include <cassert>
#include "SortedList.h"

using namespace mtm;

// Helper functions for filter and apply
bool isEven(const T& data) {
    return data % 2 == 0;
}

T increment(const T& data) {
    return data + 1;
}

int main() {
    int test = 0;
    // Test 1: Constructor and length
    SortedList<T> list1;
    assert(list1.length() == 0);
    std::cout << "Test: " << ++test << " Passed" << std::endl;

    // Test 2: Insertion and length
    list1.insert(5);
    list1.insert(3);
    list1.insert(8);
    list1.insert(1);
    assert(list1.length() == 4);
    std::cout << "Test: " << ++test << " Passed" << std::endl;

    // Test 3: Order of elements
    SortedList<T>::ConstIterator it = list1.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 3);
    ++it;
    assert(*it == 5);
    ++it;
    assert(*it == 8);
    std::cout << "Test: " << ++test << " Passed" << std::endl;

    // Test 4: Copy constructor
    SortedList<T> list2(list1);
    assert(list2.length() == 4);
    it = list2.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 3);
    ++it;
    assert(*it == 5);
    ++it;
    assert(*it == 8);
    std::cout << "Test: " << ++test << " Passed" << std::endl;

    // Test 5: Assignment operator
    SortedList<T> list3;
    list3 = list1;
    assert(list3.length() == 4);
    it = list3.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 3);
    ++it;
    assert(*it == 5);
    ++it;
    assert(*it == 8);
    std::cout << "Test: " << ++test << " Passed" << std::endl;

    // Test 6: Remove element
    SortedList<T>::ConstIterator it_remove = list1.begin();
    ++it_remove; // Point to 3
    list1.remove(it_remove);
    assert(list1.length() == 3);
    it = list1.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 5);
    ++it;
    assert(*it == 8);
    std::cout << "Test: " << ++test << " Passed" << std::endl;

    // Test 7: Filter
    SortedList<T> evenList = list1.filter(isEven);
    assert(evenList.length() == 1);
    it = evenList.begin();
    assert(*it == 8);
    std::cout << "Test: " << ++test << " Passed" << std::endl;

    // Test 8: Apply
    SortedList<T> incrementedList = list1.apply(increment);
    assert(incrementedList.length() == 3);
    it = incrementedList.begin();
    assert(*it == 2);
    ++it;
    assert(*it == 6);
    ++it;
    assert(*it == 9);
    std::cout << "Test: " << ++test << " Passed" << std::endl;

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
