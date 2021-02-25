#include<iostream>
#include "filehandler.h"
using namespace std;
//include header file with class definition here

int main(int argc, char const *argv[]) 
/*
int argc is used to count the arguments that the user has inputed
int argv stores the values in an array which can let us print it if we want to
*/
{
    //this opens the file in order to read it
    FileHandler tasklist("list.txt");
    
    while (true)
    {
        //this reads the items in the file
        tasklist.read_file();

        //this makes sure there are tasks to display in the txt
        if (task.get_count() > 0)
        {
            task.display();
            cout << endl;
            cout << "Below are the features currently supported by the program: \n 1)  Add Task \n 2) Remove Task \n 3) Mark Off Task \n 4) View Tasks \n Please input what you would like to do: ";
            string choice;
            getline(cin, choice);

            if (choice == "1" || choice == "1) Add Task" || choice == "Add Task" || choice == "1)")
			{
				//function from class runs to add the task
                task.add();
			} else if (choice == "2" || choice == "2) Remove Task" || choice == "Remove Task" || choice == "2)") {
				//function from class runs to remove the task chosen
                task.remove();
            } else if (choice == "3" || choice == "3) Mark Off Task" || choice == "Mark Off Task" || choice == "4)") {
				//function from class runs to view completed tasks and/or tasks to complete
                task.markoff();
			} else if (choice == "4" || choice == "4) View Tasks" || choice == "View Tasks" || choice == "4)") {
				//function from class runs to view completed tasks and/or tasks to complete
                task.view();
			} else {
				break;
            }

        }else {
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