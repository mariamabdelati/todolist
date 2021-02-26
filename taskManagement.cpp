#include "taskManage.h"
#include "filehandler.h"
#include "filehandler.cpp"

void Task::Add_Task(vector<string> list) {

	cout << "--- Add Task --- \n";
	cout << "Enter the task you would like to add: " << endl;

	string item;
	cin >> item;

	list.push_back(item);

	cout << "Task has been successfully added!" << endl;
	cin.clear();

}

void Task::Remove_Task(vector<string> list) {

	cout << "--- Remove Task --- \n";
	cout << "Enter the number of the task you would like to remove: " << endl;

    if (list.size()) {
        for (int i = 0; i < (int)list.size(); i++) {
            cout << i << ": " << list[i] << "\n";
        }
        int choiceNum;
        cin >> choiceNum;
        list.erase(list.begin() + choiceNum);
    }
    else {
        cout << "No items to delete.\n";
    }

}
