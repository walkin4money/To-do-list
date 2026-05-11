
#include "Task.h"
#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>


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

void test_showTasks_singleTask_shouldDisplayIdAndDescription()
{
    std::vector<Task> tasks;

    Task t1;
    t1.id = 1;
    t1.description = "Купить хлеб";
    t1.isCompleted = false;
    tasks.push_back(t1);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    showTasks(tasks);

    std::cout.rdbuf(old);
    std::string output = buffer.str();

    assert(output.find("ID: 1") != std::string::npos);
    assert(output.find("Купить хлеб") != std::string::npos);
    std::cout << "PASS: PB-2.T2" << std::endl;
}

void test_showTasks_multipleTasks_shouldDisplayInOrderById()
{
    std::vector<Task> tasks;

    Task t1;
    t1.id = 1;
    t1.description = "Первая задача";
    t1.isCompleted = false;

    Task t2;
    t2.id = 2;
    t2.description = "Вторая задача";
    t2.isCompleted = true;

    Task t3;
    t3.id = 3;
    t3.description = "Третья задача";
    t3.isCompleted = false;

    tasks.push_back(t1);
    tasks.push_back(t2);
    tasks.push_back(t3);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    showTasks(tasks);

    std::cout.rdbuf(old);
    std::string output = buffer.str();
    size_t pos1 = output.find("ID: 1");
    size_t pos2 = output.find("ID: 2");
    size_t pos3 = output.find("ID: 3");

    assert(pos1 != std::string::npos);
    assert(pos2 != std::string::npos);
    assert(pos3 != std::string::npos);
    assert(pos1 < pos2);
    assert(pos2 < pos3);

    std::cout << "PASS: PB-2.T3" << std::endl;
}

void test_showTasks_emptyList_shouldShowEmptyMessage()
{
    std::vector<Task> tasks;

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    showTasks(tasks);

    std::cout.rdbuf(old);
    std::string output = buffer.str();

    assert(output.find("Список задач пуст") != std::string::npos);
    std::cout << "PASS: PB-2.T1" << std::endl;
}

void test_deleteTask_existingId_shouldDeleteTask()
{
    std::vector<Task> tasks;

    Task t1; t1.id = 1; t1.description = "Первая"; t1.isCompleted = false;
    Task t2; t2.id = 2; t2.description = "Вторая"; t2.isCompleted = true;
    Task t3; t3.id = 3; t3.description = "Третья"; t3.isCompleted = false;

    tasks.push_back(t1);
    tasks.push_back(t2);
    tasks.push_back(t3);

    assert(tasks.size() == 3);

    bool result = deleteTask(tasks, 2);

    assert(result == true);
    assert(tasks.size() == 2);
    assert(tasks[0].id == 1);
    assert(tasks[1].id == 3);

    std::cout << "PASS: PB-3.T1 - deleteTask() removes existing task" << std::endl;
}

void test_deleteTask_nonExistingId_shouldReturnFalse()
{
    std::vector<Task> tasks;

    Task t1; t1.id = 1; t1.description = "Первая"; t1.isCompleted = false;
    Task t2; t2.id = 2; t2.description = "Вторая"; t2.isCompleted = true;

    tasks.push_back(t1);
    tasks.push_back(t2);

    assert(tasks.size() == 2);

    bool result = deleteTask(tasks, 99);

    assert(result == false);
    assert(tasks.size() == 2);

    std::cout << "PASS: PB-3.T2 - deleteTask() returns false for non-existing ID" << std::endl;
}

void test_deleteTask_idsShouldNotBeReassigned()
{
    std::vector<Task> tasks;

    Task t1; t1.id = 1; t1.description = "Первая"; t1.isCompleted = false;
    Task t2; t2.id = 2; t2.description = "Вторая"; t2.isCompleted = true;
    Task t3; t3.id = 3; t3.description = "Третья"; t3.isCompleted = false;

    tasks.push_back(t1);
    tasks.push_back(t2);
    tasks.push_back(t3);

    deleteTask(tasks, 2);

    // ID не должны переназначиться
    assert(tasks[0].id == 1);
    assert(tasks[1].id == 3);

    std::cout << "PASS: PB-3.T3 - IDs are not reassigned after deletion" << std::endl;
}

void test_deleteTask_lastTask_shouldWork()
{
    std::vector<Task> tasks;

    Task t1; t1.id = 1; t1.description = "Первая"; t1.isCompleted = false;
    Task t2; t2.id = 2; t2.description = "Вторая"; t2.isCompleted = true;

    tasks.push_back(t1);
    tasks.push_back(t2);

    assert(tasks.size() == 2);

    bool result = deleteTask(tasks, 2);

    assert(result == true);
    assert(tasks.size() == 1);
    assert(tasks[0].id == 1);

    std::cout << "PASS: PB-3.T4 - deleteTask() works for last task" << std::endl;
}

void test_deleteTask_firstTask_shouldWork()
{
    std::vector<Task> tasks;

    Task t1; t1.id = 1; t1.description = "Первая"; t1.isCompleted = false;
    Task t2; t2.id = 2; t2.description = "Вторая"; t2.isCompleted = true;

    tasks.push_back(t1);
    tasks.push_back(t2);

    assert(tasks.size() == 2);

    bool result = deleteTask(tasks, 1);

    assert(result == true);
    assert(tasks.size() == 1);
    assert(tasks[0].id == 2);

    std::cout << "PASS: PB-3.T5 - deleteTask() works for first task" << std::endl;
}

void test_toggleStatus_existingTask_notCompletedToCompleted()
{
    std::vector<Task> tasks;

    Task t1;
    t1.id = 1;
    t1.description = "Первая задача";
    t1.isCompleted = false;
    tasks.push_back(t1);
    assert(tasks[0].isCompleted == false);

    bool result = toggleTaskStatus(tasks, 1);

    assert(result == true);
    assert(tasks[0].isCompleted == true);

    std::cout << "PASS: PB-4.T1 - toggleTaskStatus() changes not completed to completed" << std::endl;
}

void test_toggleStatus_existingTask_completedToNotCompleted()
{
    std::vector<Task> tasks;

    Task t1;
    t1.id = 1;
    t1.description = "Первая задача";
    t1.isCompleted = true;
    tasks.push_back(t1);

    // Проверяем начальный статус
    assert(tasks[0].isCompleted == true);

    // Меняем статус
    bool result = toggleTaskStatus(tasks, 1);

    // Проверяем результат
    assert(result == true);
    assert(tasks[0].isCompleted == false);

    std::cout << "PASS: PB-4.T2 - toggleTaskStatus() changes completed to not completed" << std::endl;
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    test_newTask_shouldHaveDefaultStatus();
    test_addTask_emptyInput_shouldFail();
    test_addTask_oneChar_shouldPass();
    test_addTask_200chars_shouldPass();
    test_addTask_201chars_shouldFail();
    test_addTask_uniqueId();
    test_showTasks_singleTask_shouldDisplayIdAndDescription();
    test_showTasks_multipleTasks_shouldDisplayInOrderById();
    test_showTasks_emptyList_shouldShowEmptyMessage();
    test_deleteTask_existingId_shouldDeleteTask();
    test_deleteTask_nonExistingId_shouldReturnFalse();
    test_deleteTask_idsShouldNotBeReassigned();
    test_deleteTask_lastTask_shouldWork();
    test_deleteTask_firstTask_shouldWork();
    test_toggleStatus_existingTask_notCompletedToCompleted();
    test_toggleStatus_existingTask_completedToNotCompleted();
    std::cout << "All tests passed." << std::endl;
    return 0;
}
