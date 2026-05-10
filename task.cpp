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