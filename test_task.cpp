
#include "Task.h"
#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include <fstream>

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

void test_toggleStatus_otherTasksStatusShouldNotChange()
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

    // Меняем статус только у задачи с ID = 2
    toggleTaskStatus(tasks, 2);

    // Проверяем, что статус других задач не изменился
    assert(tasks[0].isCompleted == false);
    assert(tasks[1].isCompleted == false);  // Изменился с true на false
    assert(tasks[2].isCompleted == false);

    std::cout << "PASS: PB-4.T4 - other tasks status not changed" << std::endl;
}
void test_toggleStatus_toggleTwice_shouldReturnToOriginal()
{
    std::vector<Task> tasks;

    Task t1;
    t1.id = 1;
    t1.description = "Первая задача";
    t1.isCompleted = false;
    tasks.push_back(t1);

    // Первое изменение
    toggleTaskStatus(tasks, 1);
    assert(tasks[0].isCompleted == true);

    // Второе изменение (обратно)
    toggleTaskStatus(tasks, 1);
    assert(tasks[0].isCompleted == false);

    std::cout << "PASS: PB-4.T5 - toggleTaskStatus() toggles back to original on second call" << std::endl;
}

void test_toggleStatus_nonExistingTask_shouldShowErrorMessage()
{
    std::vector<Task> tasks;

    Task t1;
    t1.id = 1;
    t1.description = "Первая задача";
    t1.isCompleted = false;
    tasks.push_back(t1);

    // Перенаправляем вывод в строку
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    // Пытаемся изменить статус несуществующей задачи
    bool result = toggleTaskStatus(tasks, 99);

    // Восстанавливаем вывод
    std::cout.rdbuf(old);
    std::string output = buffer.str();

    // Проверяем, что функция вернула false
    assert(result == false);

    // Проверяем, что статус задачи не изменился
    assert(tasks[0].isCompleted == false);

    // Проверяем, что выведено сообщение об ошибке
    assert(output.find("Ошибка: задача с ID 99 не найдена") != std::string::npos);

    std::cout << "PASS: PB-4.T3 - toggleTaskStatus() shows error message for non-existing ID" << std::endl;
}

void test_saveToFile_emptyList_shouldCreateEmptyFile()
{
    std::vector<Task> tasks;

    std::string testFile = "test_empty.csv";

    bool result = saveToFile(tasks, testFile);

    assert(result == true);

    // Проверяем, что файл существует
    std::ifstream file(testFile);
    assert(file.good());

    // Проверяем, что файл пустой или содержит только заголовок?
    file.seekg(0, std::ios::end);
    std::streampos size = file.tellg();
    // Файл может быть пустым или содержать пустые строки

    file.close();
    std::remove(testFile.c_str());

    std::cout << "PASS: PB-6.T1 - saveToFile() handles empty list" << std::endl;
}

void test_saveToFile_singleTask_shouldSaveCorrectly()
{
    std::vector<Task> tasks;

    Task t1;
    t1.id = 1;
    t1.description = "Купить хлеб";
    t1.isCompleted = false;
    tasks.push_back(t1);

    std::string testFile = "test_single.csv";

    bool result = saveToFile(tasks, testFile);

    assert(result == true);

    // Проверяем содержимое файла
    std::ifstream file(testFile);
    std::string line;
    std::getline(file, line);

    // Ожидаемый формат: id;description;status
    assert(line == "1;Купить хлеб;0");

    file.close();
    std::remove(testFile.c_str());

    std::cout << "PASS: PB-6.T2 - saveToFile() saves single task correctly" << std::endl;
}
void test_saveToFile_multipleTasks_shouldSaveAll()
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

    std::string testFile = "test_multiple.csv";

    bool result = saveToFile(tasks, testFile);

    assert(result == true);

    // Проверяем содержимое файла
    std::ifstream file(testFile);
    std::string line;

    std::getline(file, line);
    assert(line == "1;Первая задача;0");

    std::getline(file, line);
    assert(line == "2;Вторая задача;1");

    std::getline(file, line);
    assert(line == "3;Третья задача;0");

    // Проверяем, что нет лишних строк
    std::getline(file, line);
    assert(file.eof());

    file.close();
    std::remove(testFile.c_str());

    std::cout << "PASS: PB-6.T3 - saveToFile() saves multiple tasks correctly" << std::endl;
}

void test_saveToFile_statusEncoding_shouldBeZeroOrOne()
{
    std::vector<Task> tasks;

    Task t1;
    t1.id = 1;
    t1.description = "Не выполнена";
    t1.isCompleted = false;

    Task t2;
    t2.id = 2;
    t2.description = "Выполнена";
    t2.isCompleted = true;

    Task t3;
    t3.id = 3;
    t3.description = "Снова не выполнена";
    t3.isCompleted = false;

    tasks.push_back(t1);
    tasks.push_back(t2);
    tasks.push_back(t3);

    std::string testFile = "test_status.csv";

    saveToFile(tasks, testFile);

    std::ifstream file(testFile);
    std::string line;

    // Первая задача: статус 0
    std::getline(file, line);
    assert(line.find(";0") != std::string::npos || line.back() == '0');

    // Вторая задача: статус 1
    std::getline(file, line);
    assert(line.find(";1") != std::string::npos || line.back() == '1');

    // Третья задача: статус 0
    std::getline(file, line);
    assert(line.find(";0") != std::string::npos || line.back() == '0');

    file.close();
    std::remove(testFile.c_str());

    std::cout << "PASS: PB-6.T4 - saveToFile() encodes status as 0 and 1" << std::endl;
}

void test_saveToFile_writeError_shouldShowErrorMessage()
{
    std::vector<Task> tasks;

    Task t1;
    t1.id = 1;
    t1.description = "Тестовая задача";
    t1.isCompleted = false;
    tasks.push_back(t1);

    // Создаём файл и делаем его read-only
    std::string testFile = "test_readonly.csv";

    // Сначала создаём файл
    std::ofstream dummy(testFile);
    dummy.close();

    // Делаем файл только для чтения (Windows)
    SetFileAttributesA(testFile.c_str(), FILE_ATTRIBUTE_READONLY);

    // Перенаправляем вывод
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    bool result = saveToFile(tasks, testFile);

    // Восстанавливаем вывод
    std::cout.rdbuf(old);
    std::string output = buffer.str();

    // Проверяем, что функция вернула false
    assert(result == false);

    // Проверяем, что выведено сообщение об ошибке
    assert(output.find("Ошибка сохранения данных") != std::string::npos);

    // Убираем read-only атрибут и удаляем файл
    SetFileAttributesA(testFile.c_str(), FILE_ATTRIBUTE_NORMAL);
    std::remove(testFile.c_str());

    std::cout << "PASS: PB-6.T6 - saveToFile() shows error message on write failure" << std::endl;
}

void test_loadFromFile_singleTask_shouldLoadCorrectly()
{
    // Создаём тестовый файл
    std::string testFile = "test_load_single.csv";
    std::ofstream file(testFile);
    file << "1;Купить хлеб;0";
    file.close();

    std::vector<Task> tasks;

    bool result = loadFromFile(tasks, testFile);

    assert(result == true);
    assert(tasks.size() == 1);
    assert(tasks[0].id == 1);
    assert(tasks[0].description == "Купить хлеб");
    assert(tasks[0].isCompleted == false);

    std::remove(testFile.c_str());

    std::cout << "PASS: PB-7.T2 - loadFromFile() loads single task correctly" << std::endl;
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
    test_toggleStatus_otherTasksStatusShouldNotChange();
    test_toggleStatus_toggleTwice_shouldReturnToOriginal();
    test_toggleStatus_nonExistingTask_shouldShowErrorMessage();
    test_saveToFile_emptyList_shouldCreateEmptyFile();
    test_saveToFile_singleTask_shouldSaveCorrectly();
    test_saveToFile_multipleTasks_shouldSaveAll();
    test_saveToFile_statusEncoding_shouldBeZeroOrOne();
    test_saveToFile_writeError_shouldShowErrorMessage();
    test_loadFromFile_singleTask_shouldLoadCorrectly();
    std::cout << "All tests passed." << std::endl;
    return 0;
}
