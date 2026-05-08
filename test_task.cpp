// test_Task.cpp
#include "Task.h"
#include <cassert>
#include <iostream>

void test_newTask_shouldHaveDefaultStatus()
{
    Task t;
    assert(t.isCompleted == false);
    std::cout << "PASS: test_newTask_shouldHaveDefaultStatus" << std::endl;
}

int main()
{
    test_newTask_shouldHaveDefaultStatus();
    std::cout << "All tests passed." << std::endl;
    return 0;
}

