#include<iostream>
#include<string> //for getline and tolower function and comparing strings
#include<algorithm> //includes transform function
#include "filehandler.h"
#include "taskManage.h"
using namespace std;
//include header file with class definition here

int main(int argc, char const* argv[])
/*
int argc is used to count the arguments that the user has inputed
int argv stores the values in an array which can let us print it if we want to
*/
{
    //this creates and object of type FileHandler
    FileHandler tasklist;
    Task task;

    while (true)
    {
        //this reads the items in the file
        tasklist.read_file();

        //this makes sure there are tasks to display in the txt
        if (task.get_count() > 0)
        {
            task.display();
            cout << endl;
            cout << "Below are the features currently supported by the program: \n 1)  Add Task \n 2) Remove Task \n 3) Mark Off Task \n 4) Unmark Task \n 5) View Tasks \n Please input what you would like to do: ";
            string choice;
            getline(cin, choice);

            //this changes the input to lowercase so it is easier to deal with
            transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

            if (choice == "1" || choice == "1) add task" || choice == "add task" || choice == "1)")
            {
                //function from class runs to add the task
                task.add();
            }
            else if (choice == "2" || choice == "2) remove task" || choice == "remove task" || choice == "2)") {
                //function from class runs to remove the task chosen
                task.remove();
            }
            else if (choice == "3" || choice == "3) mark off task" || choice == "mark off task" || choice == "3)") {
                //function from class runs to mark off completed tasks
                task.markoff();
            }
            else if (choice == "4" || choice == "4) unmark task" || choice == "unmark task" || choice == "4)") {
                //function from class runs to mark off completed tasks
                task.unmark();
            }
            else if (choice == "5" || choice == "5) view tasks" || choice == "view tasks" || choice == "5)") {
                //user is given choice of view completed tasks and/or tasks to complete
                cout << "The Following Views are available \n 1) To Complete \n 2) Completed \n";
                string view;
                getline(cin, view);

                transform(view.begin(), view.end(), view.begin(), ::tolower);
                if (choice == "1" || choice == "1) to complete" || choice == "to complete" || choice == "1)")
                {
                    //function from class runs to view the tasks that are not done yet
                    task.view_tocomplete();
                }
                else if (choice == "2" || choice == "2) completed" || choice == "completed" || choice == "2)") {
                    //function from class runs to view the tasks that are done
                    task.view_completed();
                }
                else {
                    cout << "this view is not supported \n";
                }

            }
            else {
                break;
            }

        }
        else {
            //program automatically creates new list
            cout << "creating new list... \n";
            //function called to create new list
            list.create();
            cout << endl;
            //new tasks displayed
            task.display();


        }
    }
    return 0;
}