#include <iostream>
#include <vector>
#include <windows.h>
#include "Task.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::vector<Task> tasks;
    int choice;

    do {
        std::cout << "\n===== TODO List =====" << std::endl;
        std::cout << "1. Добавить задачу" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "Выбор: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Ошибка: введите число" << std::endl;
            choice = -1;
        }
        else {
            std::cin.ignore();
        }

        if (choice == 1) {
            std::string desc;
            std::cout << "Описание: ";
            std::getline(std::cin, desc);

            if (addTask(tasks, desc)) {
                std::cout << "Задача добавлена (ID: " << tasks.back().id << ")" << std::endl;
            }
            else {
                std::cout << "Ошибка: описание не может быть пустым" << std::endl;
            }
        }
    } while (choice != 0);

    return 0;
}