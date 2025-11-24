#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
using namespace std;

size_t utf8_length(const std::string& str) {
    size_t count = 0;
    for (unsigned char c : str) {
        if ((c & 0b11000000) != 0b10000000) {
            ++count;
        }
    }
    return count;
}

int main() {

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);     //UTF-8 в консоли Windows
    system("chcp 65001 > nul");
#endif

    vector<string> names;
    vector<string> namesmaxlength;

    //Собираем имена от пользователя
    cout << "=== Программа сбора имён ===\n";
    cout << "Вводите имена (пустая строка - завершение):\n";
    string name;
    while (getline(cin, name))
    {
        if (name.empty()) break;
        names.push_back(name);
    }

    //Сортируем и выводим
    ranges::sort(names); //C++20

    cout << "\nОтсортированный список(" << names.size() << " чел.):\n";
    for (const auto& n : names)
    {
        //Заполняем дополнительный вектор для самых длинных имен
        if (namesmaxlength.empty() ) {
            namesmaxlength.push_back(n);
        }
        else if (utf8_length(n) >= utf8_length(namesmaxlength[0])) {
            if (utf8_length(n) > utf8_length(namesmaxlength[0])) { namesmaxlength.clear(); }
            namesmaxlength.push_back(n);
        }

        cout << "- " << n << '\n';
    }

    if (namesmaxlength.size()>1) {
        cout << "Самое длинное имя (" << utf8_length(namesmaxlength[0]) << " символов):\n";
        cout << "- " << namesmaxlength[0]<<'\n';
    }
    else {
        cout << "Самые длинные имена (" << utf8_length(namesmaxlength[0]) << " символов):\n";
        for (const auto& n : namesmaxlength) {
            cout << "- " << n << '\n';
        }
    }


    system("pause");
    return 0;
}