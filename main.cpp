#include <iostream>
#include "todolist.h"

using namespace std;

int main(int argc, char const* argv[])
{
    TodoList tasks("list.txt");

    while (true)
    {
        tasks.read();

        if (tasks.get_count() > 0)
        {
            tasks.display();
            cout << endl;

            cout << "---- MENU ----" << endl << endl;
            cout << "1) Add" << endl;
            cout << "2) Remove" << endl;
            cout << "3) View complete" << endl;
            cout << "4) View incomplete" << endl;
            cout << "5) Clear" << endl;
            cout << "6) Check" << endl;
            cout << "7) Uncheck" << endl;
            cout << "Choice: ";

            string choice;
            getline(cin, choice);

            if (choice == "1")
            {
                tasks.add();
            }
            else if (choice == "2") {
                tasks.del();
            }
            else if (choice == "3") {
                tasks.display_complete();
            }
            else if (choice == "4") {
                tasks.display_incomplete();
            }
            else if (choice == "5") {
                tasks.clear();
            }
            else if (choice == "6") {
                tasks.check();
            }
            else if (choice == "7") {
                tasks.uncheck();
            }
            else {
                break;
            }

        }
        else {
            cout << "Created a new list .." << endl;
            cout << "Press enter to finish adding tasks." << endl;
            tasks.create();

            cout << endl;
            tasks.display();

            tasks.save();
        }
    }

    return 0;
}