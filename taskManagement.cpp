#include "taskManage.h"
#include "filehandler.h"
#include "filehandler.cpp"
// The other header files and source files are included to allow easier use and implementation of variables

void Task::Add_Task(vector<string> list) {

// This function takes the list vector as a parameter to allow us to be able to add items 

	cout << "--- Add Task --- \n";
	cout << "Enter the task you would like to add: " << endl;

	string item;
	cin >> item;

	list.push_back(item);

// The push_back command is from the vector library and allows us to add items to the list

	cout << "Task has been successfully added!" << endl;

}

void Task::Remove_Task(vector<string> list) {

	cout << "--- Remove Task --- \n";
	cout << "Enter the number of the task you would like to remove: " << endl;

    if (list.size()) {
        for (int i = 0; i < (int)list.size(); i++) {
            cout << i << ": " << list[i] << "\n";
        }

    // This outputs the length of the list so the user could know the range of the items they can choose to delete

        int choiceNum;
        cin >> choiceNum;
        list.erase(list.begin() + choiceNum);

    // This takes the input of the user and is used as an index so the item can be deleted

    }
    else {
        cout << "No items to delete.\n";
    }

}
