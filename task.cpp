#include "Task.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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
            std::cout << "Статус задачи " << id << " изменён" << std::endl;  // НОВОЕ СООБЩЕНИЕ
            return true;
        }
    }
    std::cout << "Ошибка: задача с ID " << id << " не найдена" << std::endl;  // НОВОЕ СООБЩЕНИЕ
    return false;
}

bool saveToFile(const std::vector<Task>& tasks, const std::string& filename)
{
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка сохранения данных" << std::endl;
        return false;
    }

    for (const auto& task : tasks) {
        file << task.id << ";"
            << task.description << ";"
            << (task.isCompleted ? 1 : 0) << std::endl;

        // Проверяем ошибку записи
        if (file.fail()) {
            std::cout << "Ошибка сохранения данных" << std::endl;
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}

bool loadFromFile(std::vector<Task>& tasks, const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        tasks.clear();
        return true;
    }

    tasks.clear();
    std::string line;
    int loadedCount = 0;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string idStr, description, statusStr;

        if (!std::getline(ss, idStr, ';') ||
            !std::getline(ss, description, ';') ||
            !std::getline(ss, statusStr, ';')) {
            std::cout << "Ошибка загрузки: файл повреждён, начат новый список задач" << std::endl;
            tasks.clear();
            return false;
        }

        try {
            Task t;
            t.id = std::stoi(idStr);
            t.description = description;
            int status = std::stoi(statusStr);

            // ДОПОЛНИТЕЛЬНАЯ ПРОВЕРКА: статус должен быть 0 или 1
            if (status != 0 && status != 1) {
                std::cout << "Ошибка загрузки: файл повреждён, начат новый список задач" << std::endl;
                tasks.clear();
                return false;
            }

            t.isCompleted = (status == 1);
            tasks.push_back(t);
            loadedCount++;
        }
        catch (...) {
            std::cout << "Ошибка загрузки: файл повреждён, начат новый список задач" << std::endl;
            tasks.clear();
            return false;
        }
    }

    file.close();
    std::cout << "Загружено задач: " << loadedCount << std::endl;
    return true;
}