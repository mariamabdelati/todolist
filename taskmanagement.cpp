#include "taskmanagement.h"

TaskManagement::TaskManagement():FileManagement(){}
//the taskmanagement constructor calls the inherited class constructor to create a file

TaskManagement::~TaskManagement()
{
    // do nothing
}

TaskManagement::TaskManagement(const char *filename) : FileManagement(filename) {

}

void TaskManagement::organize()
{
    const int width = 40; //read-only cannot be modified by program
    //iomanip library is used for a nice looking table
    cout << setfill('-') << setw(width*2.5) << "-" << endl;
    cout << setfill(' ') << fixed;
    cout << "   " << setw(width) << left << "TASK" << setw(width) << "DONE" << setw(width) << "PRIORITY" << endl;
    cout << setfill('-') << setw(width*2.5) << "-" << endl;
    cout << setfill(' ') << fixed;
}

void TaskManagement::display() {
    cout << endl;
    cout << "                                     " << "YOUR TO DO LIST" << "    " << endl;

    const int width = 40; //read-only cannot be modified by program
    organize();
    int x = 0;
    //for loop iterates over the list and prints each line
    for (auto &i : list)
    {
    cout << x + 1 << ") " << setw(width) << left << i.text() << setw(width) << (i.is_done() ? "Done" : "")
         << setw(width) << (i.getpriority()) << endl;
    //? is a conditional operator that returns X if condition true or Y if condition false [? X:Y]
    //list[i].text returns the text from that line as defined in the item class
    x++;
    }
    cout << setfill('-') << setw(width*2.5) << "-" << endl;
    cout << setfill(' ') << fixed;
}

void TaskManagement::create() //this creates a new list
{
    bool is_finished = false; // this is defined to check if user is done entering tasks
    int count = 1;
    string task;

    list.clear();

    while (!is_finished) //while user gives in an input
    {
        cout << count << ": ";

        getline(cin, task);
        if (task.empty()) is_finished = true; //loop breaks if user presses enter

        Item item(task); //cast task as an item
        list.push_back(item); //add item to list vector
        count++; //add to the counter
    }
}

int TaskManagement::get_count() //this function returns the size of the list vector, to check if file has items
{
    return list.size();
}

void TaskManagement::add()
{
    int index = list.size();
    while (true)
    {
        cout << ++index << ": "; //checks current list size and adds to it to keep count of items

        string task;
        getline(cin, task);
        if (task.empty()) break; //this breaks loop if user presses enter

        Item item(task);
        list.push_back(item);
    }

    FileManagement::write(); //write the list into the file
}

void TaskManagement::del()
{
    while (true)
    {
        cout << "Enter the number of the task you would like to remove: ";
        try {
            string choice;
            getline(cin, choice);

            if (choice.empty()) break;
            for (char c : choice) {
                if (isalpha(c) || isspace(c)) {
                    throw 0;
                }
            }
            int index = stoi(choice) - 1; //converts the string to integer and subtracts 1 because our index starts at 0
            if (index > list.size() || index < 0) //breaks if invalid number
                throw 0;

            auto it = list.begin();
            advance(it,index);
            list.erase(it);
            //takes the index at which list begins and adds to it the index of specified task to erase it
            FileManagement::write();
            display();
        } catch (int exception) {
            cout << "Invalid Choice." << endl;
        }

        //if (index > list.size()) return; //breaks if invalid number


    }
}

void TaskManagement::edit()
{
    while (true)
    {
        cout << "Enter the number of the task you would like to edit: ";

        try {
            string choice;
            getline(cin, choice);

            if (choice.empty()) break; //this breaks loop if user presses enter
            for (char c : choice) {
                if (isalpha(c) || isspace(c)) {
                    throw 0;
                }
            }

            int index = stoi(choice) - 1; //converts the string to integer and subtracts 1 because our index starts at 0
            if (index > list.size() || index < 0) //breaks if invalid number
                throw 0;

            while (true)
            {
                string changetask;
                cout << "Enter what you would like to change the task to: " << endl;
                getline(cin, changetask);
                if (!changetask.empty())
                {
                    Item item(changetask);
                    //list[index] = changetask;
                    int x = 0;
                    for (auto &i : list) {
                        if (index == x) {
                            i = changetask;
                            break;
                        }
                        else
                        {
                            x++;
                        }
                    }

                    FileManagement::write(); //saves the list
                    display();
                    break;
                }
            }
        } catch (int exception) {
            cout << "Invalid Choice." << endl;
        }
    }

    //FileManagement::write();
}

void TaskManagement::view_incomplete()
{
    cout << endl;
    cout << "                                     " << "TASKS TO COMPLETE" << "    " << endl;

    const int width = 40;
    organize();

    int n = 0;
    for (auto &i : list)
        if (!i.is_done())
        {
            cout << n + 1 << ") " << setw(width) << left << i.text() << setw(width) << (i.is_done() ? "Done" : "") << setw(width) << (i.getpriority()) << endl;
            ++n;
        }
    cout << setfill('-') << setw(width*2.5) << "-" << endl;
    cout << setfill(' ') << fixed;
}

void TaskManagement::view_complete()
{
    cout << endl;
    cout << "                                     " << "COMPLETED TASKS" << "    " << endl;

    const int width = 40;
    organize();

    int n = 0;
    for (auto &i : list)
        if (i.is_done())
        {
            cout << n + 1 << ") " << setw(width) << left << i.text() << setw(width) << (i.is_done() ? "Done" : "") << setw(width) << (i.getpriority()) << endl;
            ++n;
        }
    cout << setfill('-') << setw(width*2.5) << "-" << endl;
    cout << setfill(' ') << fixed;

}

void TaskManagement::check()
{
    while (true) {
        cout << "Enter number of task to mark off: ";

        try {
            string choice;
            getline(cin, choice); //takes input from user

            if (choice.empty()) break;
            for (char c : choice) {
                /*
                colon syntax just iterates over the characters in choice and checks if they are alphabet, if they are it stops
                */
                if (isalpha(c) || isspace(c)) {
                    throw 0;
                }
            }
            int index = stoi(choice) - 1; //converts the string to integer and subtracts 1 because our index starts at 0
            if (index > list.size() || index < 0) //breaks if invalid number

            // list[index].done(); //takes the index and marks it as done
                throw 0;

            int x = 0;
            for (auto &i : list) {
                if (index == x) {
                    i.done();
                    break;
                }
                else
                {
                    x++;
                }
            }
            FileManagement::write();
            display();
        } catch (int exception) {
            cout << "Invalid Choice." << endl;
        }
    }
}

void TaskManagement::uncheck() {
    while (true) {
        cout << "Enter number of task to unmark: ";

        try {
            string choice;
            getline(cin, choice); //takes input from user

            if (choice.empty()) break;
            for (char c : choice) {
                /*
                colon syntax just iterates over the characters in choice and checks if they are alphabet, if they are it stops
                */
                if (isalpha(c) || isspace(c)) {
                    throw 0;
                }
            }
            int index = stoi(choice) - 1; //converts the string to integer and subtracts 1 because our index starts at 0
            if (index > list.size() || index < 0) //breaks if invalid number
                //list[index].notdone(); //takes the index and marks it as not done
                throw 0;

            int x = 0;
            for (auto &i : list) {
                if (index == x) {
                    i.notdone();
                    break;
                }
                else
                {
                    x++;
                }
            }
            FileManagement::write();
            display();
        } catch (int exception) {
            cout << "Invalid Choice." << endl;
        }
    }
}

void TaskManagement::set_priority()
{
    while (true)
    {
        cout << "Enter the number of the task you would like to set the priority for: ";

        try {
            string choice;
            getline(cin, choice); //takes input from user

            if (choice.empty()) break;
            for (char c : choice) {
                /*
                colon syntax just iterates over the characters in choice and checks if they are alphabet, if they are it stops
                */
                if (isalpha(c) || isspace(c)) {
                    throw 0;
                }
            }
            int index = stoi(choice) - 1; //converts the string to integer and subtracts 1 because our index starts at 0
            if (index > list.size() || index < 0) //breaks if invalid number
                //list[index].notdone(); //takes the index and marks it as not done
                throw 0;

            while (true)
            {
                cout << "Enter priority (low, medium, high, none): ";
                try {
                    string priority;
                    getline(cin, priority);
                    if (!priority.empty())
                    {
                        if (priority != "low" && priority != "medium" && priority != "high" && priority != "none")
                            throw 0;

                        for (char p : priority) {
                            if (isdigit(p) || isspace(p)) {
                                throw 0;
                            }
                        }

                        int x = 0;
                        for (auto &i : list)
                        {
                            if (priority == "low" && index == x) {
                                i.lowpriority();
                                break;
                            } else if (priority == "medium" && index == x) {
                                i.mediumpriority();
                                break;
                            } else if (priority == "high" && index == x) {
                                i.highpriority();
                                break;
                            } else if (priority == "none" && index == x) {
                                i.nopriority();
                                break;
                            } else if (index != x || index > x)
                            {
                                x++;
                            }
                        }
                        FileManagement::write();
                        display();
                        break;
                    }
                }catch (int exception) {
                    cout << "Invalid Priority." << endl;
                }
            }
        } catch (int exception) {
            cout << "Invalid Choice." << endl;
        }
    }
}

