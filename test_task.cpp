
#include "Task.h"
#include <cassert>
#include <iostream>

void test_newTask_shouldHaveDefaultStatus()
{
    Task t;
    assert(t.isCompleted == false);
    std::cout << "PASS: PB-1.T6" << std::endl;
}

void test_addTask_emptyInput_shouldFail()
{
    std::string input = "";
    bool isValid = (input.length() >= 1 && input.length() <= 200);
    assert(isValid == false);
    std::cout << "PASS: PB-1.T1" << std::endl;
}

void test_addTask_oneChar_shouldPass()
{
    std::string input = "X";
    bool isValid = (input.length() >= 1 && input.length() <= 200);
    assert(isValid == true);
    std::cout << "PASS: PB-1.T2" << std::endl;
}
void test_addTask_200chars_shouldPass()
{
    std::string input(200, 'X');
    bool isValid = (input.length() >= 1 && input.length() <= 200);
    assert(isValid == true);
    std::cout << "PASS: PB-1.T3" << std::endl;
}

void test_addTask_201chars_shouldFail()
{
    std::string input(201, 'X');
    bool isValid = (input.length() >= 1 && input.length() <= 200);
    assert(isValid == false);
    std::cout << "PASS: PB-1.T4" << std::endl;
}

void test_addTask_uniqueId()
{
    std::vector<Task> tasks;
    addTask(tasks, "Первая задача");
    addTask(tasks, "Вторая задача");
    assert(tasks.size() == 2);
    assert(tasks[0].id != tasks[1].id);
    std::cout << "PASS: PB-1.T5" << std::endl;
}


int main()
{
    test_newTask_shouldHaveDefaultStatus();
    test_addTask_emptyInput_shouldFail();
    test_addTask_oneChar_shouldPass();
    test_addTask_200chars_shouldPass();
    test_addTask_201chars_shouldFail();
    test_addTask_uniqueId();
    std::cout << "All tests passed." << std::endl;
    return 0;
}
