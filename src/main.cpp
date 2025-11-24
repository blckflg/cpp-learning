#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>

size_t utf8_length(const std::string& str) {
    size_t size = 0;
    for (unsigned char c : str) {
        if ((c & 0b11000000) != 0b10000000) {
            ++size;
        }
    }
    return size;
}

int main() {

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);     //UTF-8 в консоли Windows
    system("chcp 65001 > nul");
#endif

    std::vector<std::string> names;
    std::vector<std::string> namesmaxlength;

    //Собираем имена от пользователя
    std::cout << "=== Программа сбора имён ===\n";
    std::cout << "Вводите имена (пустая строка - завершение):\n";
    std::string name;
    while (std::getline(std::cin, name)) {
        if (name.empty()) break;
        names.emplace_back(std::move(name)); // чуть быстрее
    }

    if (names.empty()) {
        std::cout << "\nВы не ввели ни одного имени.\n";
        std::cin.get();
        return 0;
    }

    //Сортируем и выводим
    std::ranges::sort(names); //C++20

   std::cout << "\nОтсортированный список (" << names.size() << " чел.):\n";
    for (const auto& n : names) {
        std::cout << "- " << n << '\n';
    }

    // Правильный поиск самых длинных имён — отдельно!
    size_t max_len = 0;
    std::vector<std::string> longest;

    for (const auto& n : names) {
        size_t len = utf8_length(n);
        if (len > max_len) {
            max_len = len;
            longest = {n};
        } else if (len == max_len) {
            longest.push_back(n);
        }
    }

    std::cout << "\n";
    if (longest.size() == 1) {
        std::cout << "Самое длинное имя (" << max_len << " символов):\n";
    } else {
        std::cout << "Самые длинные имена (" << max_len << " символов):\n";
    }
    for (const auto& n : longest) {
        std::cout << "- " << n << '\n';
    }

    std::cout << "\nНажмите Enter для выхода...\n";
    std::cin.get();
    return 0;
}