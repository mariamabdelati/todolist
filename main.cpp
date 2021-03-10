#include <iostream>
#include "todo_list.h"

using namespace std;

int main(int argc, char const *argv[])
{
    TodoList tasks("list.txt");

    while(true)
    {
        tasks.read();

        if (tasks.get_count() > 0)
        {
            tasks.display();
            cout << endl;

            cout << "1) Add" << endl;
            cout << "2) Clear" << endl;
            cout << "3) Check" << endl;
            cout << "4) Uncheck" << endl;
            cout << "5) View Incomplete" << endl;
            cout << "6) View Completed" << endl;
            cout << "Choice: ";

            string choice;
            getline(cin, choice);

            if (choice == "1")
            {
                tasks.add();
            } else if (choice == "2") {
                tasks.clear();
            } else if (choice == "3") {
                tasks.check();
            } else if (choice == "4") {
                tasks.uncheck();
            } else if (choice == "5") {
                tasks.display_incomplete();
            } else if (choice == "6") {
                tasks.display_complete();
            } else {
                break;
            }

        } else {
            cout << "Created a new list .." << endl;
            tasks.create();

            cout << endl;
            tasks.display();

            tasks.save();
        }
    }

    return 0;
}
