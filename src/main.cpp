#ifdef _WIN32
    #include <windows.h>
#endif


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(){
    
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);     //UTF-8 в консоли Windows
    system("chcp 65001 > nul");
    #endif

    vector<string> names;

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
    
    cout << "\nОтсортированный список("<< names.size()<<" чел.):\n";
    for (const auto& n: names)
    {
        cout<<"- "<<n<<'\n';
    }

    system ("pause"); 
    return 0;
}