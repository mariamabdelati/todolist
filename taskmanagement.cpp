#include "taskmanagement.h"

TaskManagement::TaskManagement()
{
    filename = nullptr; //file is null
}

TaskManagement::TaskManagement(const char* filename) //const char makes sure that file won't be changed
{
    this->filename = filename;
    /*
    this is a pointer, arrow is used to dereference, helps assign the variable of same name to itself
    */
}

TaskManagement::~TaskManagement()
{
    // do nothing
}

void TaskManagement::read()
{
    //creates an instance of a file and opens it for reading
    fstream fs(filename, fstream::in);
    string line;

    //this ensures the vector is empty
    list.clear();

    while (getline(fs, line)) //while can read the lines in file
    {
        if (line == "") continue; //if it encounters an empty line skip iteration
        Item item(line); //makes line an instance of class item (similar to type casting)
        list.push_back(item); //adds to list vector
    }

    fs.close();
}

void TaskManagement::display()
{
    cout << endl;
    cout << "                                     " << "YOUR TO DO LIST" << "    " << endl;

    const int width = 40; //read-only cannot be modified by program
    //iomanip library is used for a nice looking table
    cout << setfill('-') << setw(width*2.5) << "-" << endl;
    cout << setfill(' ') << fixed;
    cout << "   " << setw(width) << left << "TASK" << setw(width) << "DONE" << setw(width) << "PRIORITY" << endl;
    cout << setfill('-') << setw(width*2.5) << "-" << endl;
    cout << setfill(' ') << fixed;

    //for loop iterates over the list and prints each line
    for (int i = 0; i < list.size(); ++i)
        cout << i + 1 << ") " << setw(width) << left << list[i].text() << (list[i].is_done() ? "Done" : "") << setw(width) << (list[i].getpriority()) << endl;
        //? is a conditional operator that returns X if condition true or Y if condition false [? X:Y]
        //list[i].text returns the text from that line as defined in the item class
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
        if (task == "") is_finished = true; //loop breaks if user presses enter

        Item item(task); //cast task as an item
        list.push_back(item); //add item to list vector
        count++; //add to the counter
    }
}

void TaskManagement::write() //this function writes the list into the file
{
    //file is open for writing
    fstream fs(filename, fstream::out);

    //for loop iterates over the items in list
    for (Item item : list)
    {
        if (item.text().empty()) continue; //if empty line skip iteration

        fs << item.text() << " " << (item.is_done() ? "true" : "false") << " " << (item.priority()) << endl;
        //otherwise it will add the item text to the file
        //then it will check if the item is done and save a true or false value in file
        //then it will save the item priority into file
    }

    fs.close();
}

int TaskManagement::get_count() //this function returns the size of the list vector, to check if file has items
{
    return list.size();
};

void TaskManagement::add()
{
    int index = list.size();
    while (true)
    {
        cout << ++index << ": "; //checks current list size and adds to it to keep count of items

        string task;
        getline(cin, task);
        if (task == "") break; //this breaks loop if user presses enter

        Item item(task);
        list.push_back(item);
    }

    write(); //write the list into the file
};

void TaskManagement::del()
{
    while (true)
    {
        cout << "Enter the number of the task you would like to remove: " << endl;

        string choice;
        getline(cin, choice);
        if (choice == "") break;

        Item item(choice);
        int index = stoi(choice) - 1; //converts the string to integer and subtracts 1 because our index starts at 0
        if (index > list.size()) return; //breaks if invalid number
        list.erase(list.begin() + index);
        //takes the index at which list begins and adds to it the index of specified task to erase it
    }

    write();
}

void TaskManagement::view_incomplete()
{
    cout << endl;
    cout << "                                     " << "TASKS TO COMPLETE" << "    " << endl;

    const int width = 40;
    cout << setfill('-') << setw(width*2.5) << "-" << endl;
    cout << setfill(' ') << fixed;
    cout << "   " << setw(width) << left << "TASK" << setw(width) << "DONE" << setw(width) << "PRIORITY" << endl;
    cout << setfill('-') << setw(width*2.5) << "-" << endl;
    cout << setfill(' ') << fixed;

    int n = 0;
    for (int i = 0; i < list.size(); ++i)
        if (!list[i].is_done())
        {
            cout << n + 1 << ") " << setw(width) << left << list[i].text() << (list[i].is_done() ? "Done" : "") << endl;
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
    cout << setfill('-') << setw(width*2.5) << "-" << endl;
    cout << setfill(' ') << fixed;
    cout << "   " << setw(width) << left << "TASK" << setw(width) << "DONE" << setw(width) << "PRIORITY" << endl;
    cout << setfill('-') << setw(width*2.5) << "-" << endl;
    cout << setfill(' ') << fixed;

    int n = 0;
    for (int i = 0; i < list.size(); ++i)
        if (list[i].is_done())
        {
            cout << n + 1 << ") " << setw(width) << left << list[i].text() << (list[i].is_done() ? "Done" : "") << endl;
            ++n;
        }
        cout << setfill('-') << setw(width*2.5) << "-" << endl;
        cout << setfill(' ') << fixed;

}

void TaskManagement::reset()
{
    list.clear(); //clears list
    remove(filename); //deletes file
}

void TaskManagement::check()
{
    cout << "Enter number of task: ";

    string choice;
    getline(cin, choice); //takes input from user

    if (choice.empty()) return;
    for (char c : choice) if (isalpha(c)) return;
    /*
    colon syntax just iterates over the characters in choice and checks if they are alphabet, if they are it stops
    */

    int index = stoi(choice) - 1; //converts the string to integer and subtracts 1 because our index starts at 0
    if (index > list.size()) return; //breaks if invalid number
    list[index].done(); //takes the index and marks it as done

    write();
};

void TaskManagement::uncheck()
{
    cout << "Enter number of task: ";

    string choice;
    getline(cin, choice);

    if (choice.empty()) return;
    for (char c : choice) if (isalpha(c)) return;

    int index = stoi(choice) - 1;
    if (index > list.size()) return;
    list[index].notdone(); //takes the index and marks it as not done

    write();
};

void TaskManagement::set_priority() {
    cout << "Enter number of task: ";

    string choice;
    getline(cin, choice);

    if (choice.empty()) return;
    for (char c : choice) if (isalpha(c)) return;


    int index = stoi(choice) - 1; //converts the string to integer and subtracts 1 because our index starts at 0
    if (index > list.size()) return;

    cout << "Enter priority (low, medium, high, none): ";
    string priority;
    getline(cin, priority);
    if (priority == "low") {
        list[index].lowpriority();
    }
    else if (priority == "medium") {
        list[index].mediumpriority();
    }
    else if (priority == "high") {
        list[index].highpriority();

    }
    else if (priority == "none")
    {
        list[index].nopriority();
    }
    else
    {
        return;
    }


    write();

};