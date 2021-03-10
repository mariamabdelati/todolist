#include <iostream>
#include "taskmanagement.h"

using namespace std;

int main(int argc, char const* argv[])
/*
int argc is used to count the arguments that the user has inputed
int argv stores the values in an array which can let us print it if we want to
*/
{
    //this creates and object of type FileHandler
    TaskManagement tasks("todolist.txt");

    while (true) {
        //this reads the items in the file
        tasks.read();

        //this makes sure there are tasks to display in the txt
        if (tasks.get_count() > 0) {
            tasks.display();
            cout << endl <<endl;

            cout << "---- MENU ----" << endl << endl;
            cout << "1) Add Task" << endl;
            cout << "2) Remove Task" << endl;
            cout << "3) Mark Off Task" << endl;
            cout << "4) Unmark Task" << endl;
            cout << "5) Reset Current List" << endl;
            cout << "6) View Tasks" << endl << endl;
            cout << "--------------" << endl;
            cout << "Choice: ";

            string choice;
            getline(cin, choice);

            if (choice == "1") {
                tasks.add();
            } else if (choice == "2") {
                tasks.del();
            } else if (choice == "3") {
                tasks.check();
            } else if (choice == "4") {
                tasks.uncheck();
            } else if (choice == "5") {
                tasks.reset();
            } else if (choice == "6") {
                cout << "--------------" << endl << endl;
                cout << "The Following Views are available \n";
                cout << "--------------" << endl;
                cout << "1) To Complete \n2) Completed \n" ;
                cout << "--------------" << endl;
                cout << "Choice: ";
                string view;
                getline(cin, view);

                if (view == "1")
                {
                    tasks.view_incomplete();
                } else if (view == "2") {
                    //function from class runs to view the tasks that are done
                    tasks.view_complete();
                }else{
                    cout << "this view is not supported \n";
                }
            } else {
                break;
            }

        } else {
            //program automatically creates new list when first started or reset
            cout << "A New List Has Been Created ..." << endl;
            cout << "Press Enter to finish adding tasks." << endl;
            tasks.create();

            cout << endl;
            //new tasks displayed
            tasks.display();

            //tasks entered are saved into the file
            tasks.write();
        }
    }

    return 0;
}