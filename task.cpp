#include "Task.h"

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
    std::cout << "\n=== Список задач ===" << std::endl;
    for (const auto& task : tasks) {
        std::string status = task.isCompleted ? "Выполнена" : "Не выполнена";
        std::cout << "ID: " << task.id
            << " | " << task.description
            << " | " << status << std::endl;
    }
}