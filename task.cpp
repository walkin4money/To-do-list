#include "Task.h"
#include <iostream> 

bool addTask(std::vector<Task>& tasks, const std::string& description)
{
    if (description.length() < 1 || description.length() > 200) {
        return false;
    }
    Task t;
    t.id = tasks.size() + 1;
    t.description = description;
    tasks.push_back(t);
    return true;
}

void showTasks(const std::vector<Task>& tasks)
{
    if (tasks.empty()) {
        std::cout << "Список задач пуст" << std::endl;
        return;
    }

    std::cout << "\n=== Список задач ===" << std::endl;
    for (const auto& task : tasks) {
        std::string status = task.isCompleted ? "Выполнена" : "Не выполнена";
        std::cout << "ID: " << task.id
            << " | " << task.description
            << " | " << status << std::endl;
    }
}

bool deleteTask(std::vector<Task>& tasks, int id)
{
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->id == id) {
            tasks.erase(it);
            std::cout << "Задача удалена" << std::endl;
            return true;
        }
    }
    std::cout << "Ошибка: задача с ID " << id << " не найдена" << std::endl;  
    return false;
}

bool toggleTaskStatus(std::vector<Task>& tasks, int id)
{
    for (auto& task : tasks) {
        if (task.id == id) {
            task.isCompleted = !task.isCompleted;
            return true;
        }
    }
    return false;
}