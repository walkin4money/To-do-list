#pragma once
#include <string>
#include <vector>


struct Task {
    int id;
    std::string description;
    bool isCompleted = false;
};

bool addTask(std::vector<Task>& tasks, const std::string& description);
void showTasks(const std::vector<Task>& tasks); 
bool deleteTask(std::vector<Task>& tasks, int id);
bool toggleTaskStatus(std::vector<Task>& tasks, int id);
bool saveToFile(const std::vector<Task>& tasks, const std::string& filename);
bool loadFromFile(std::vector<Task>& tasks, const std::string& filename);