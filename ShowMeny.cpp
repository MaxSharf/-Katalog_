
#include "DirMeny.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

void ColorMeny() {
    HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hwnd, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    std::system("color F0");
}

void Meny()
{

    string path;
    string namedir;
    char switch_on;
    cout << "Enter path: ";
    getline(cin, path);
    do
    {
        std::system("cls");
        PrintDir(path);       
        cout << "1 - Create dir" << endl;
        cout << "2 - Remove dir" << endl;
        cout << "3 - Rename dir" << endl;
        cout << "4 - Open dir" << endl;
        cout << "5 - Back" << endl;
        cout << "6 - Exit" << endl;
        cout << "Enter: ";
        cin >> switch_on;
        switch (switch_on)
        {
        case '1':
        {
            cin.ignore();
            cout << "Enter name of new dir: ";
            getline(cin, namedir);
            CreateDir(path, namedir);
        }break;
        case '2':
        {
            cin.ignore();
            cout << "Enter name dir for remove: ";
            getline(cin, namedir);
            RemoveDir(path, namedir);
        }break;
        case '3':
        {
            cin.ignore();
            RenameDir(path);
        }break;
        case '4':
        {
            cin.ignore();
            cout << "Enter name of dir: ";
            getline(cin, namedir);
            filesystem::current_path(path + '/' + namedir);
            path = filesystem::current_path().string();
        }break;
        case '5':
        {
            filesystem::path p = filesystem::current_path();
            path = p.parent_path().string();
            filesystem::current_path(path);
        }break;
        case '6':
        {
            cout << "Exit for program" << endl;
              exit(EXIT_FAILURE);

        }break;

        }
    } while (true);

}

