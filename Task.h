#pragma once
#include <string>

struct Task {
    int id;
    std::string description;
    bool isCompleted = false;
};

bool addTask(std::vector<Task>& tasks, const std::string& description);