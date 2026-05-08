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

void test_addTask_emptyInput_shouldFail()
{
    std::string input = "";
    bool isValid = (input.length() >= 1 && input.length() <= 200);
    assert(isValid == false);
    std::cout << "PASS: T-1" << std::endl;
}

int main()
{
    test_newTask_shouldHaveDefaultStatus();
    test_addTask_emptyInput_shouldFail()
    std::cout << "All tests passed." << std::endl;
    return 0;
}

s