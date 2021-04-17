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
    const int width = 35; //read-only cannot be modified by program
    //iomanip library is used for a nice looking table
    cout << setfill('-') << setw(width*4.5) << "-" << endl;
    cout << setfill(' ') << fixed;
    cout << "   " << setw(width) << left << "TASK" << setw(width) << "DONE" << setw(width) << "PRIORITY" << setw(width) << "DUE DATE" << setw(width) << "CATEGORY" << endl;
    cout << setfill('-') << setw(width*4.5) << "-" << endl;
    cout << setfill(' ') << fixed;
}

void TaskManagement::display()
{
    const int width = 40; //read-only cannot be modified by program
    cout << endl;
    cout << setw(width*2.125) << "YOUR TO DO LIST" << endl;

    organize();
   
    //for loop iterates over the list and prints each line
    for (int i = 0; i < list.size(); ++i)
        cout << i + 1 << ") " << setw(width) << left << list[i].text() << setw(width) << (list[i].is_done() ? "Done" : "") << setw(width) << (list[i].getpriority()) << endl;
        //? is a conditional operator that returns X if condition true or Y if condition false [? X:Y]
        //list[i].text returns the text from that line as defined in the item class
    cout << setfill('-') << setw(width*3.93) << "-" << endl;
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
        if (task == "") break; //this breaks loop if user presses enter

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

        string choice;
        getline(cin, choice);
        if (choice == "") break;

        int index = stoi(choice) - 1; //converts the string to integer and subtracts 1 because our index starts at 0
        if (index > list.size()) return; //breaks if invalid number
        list.erase(list.begin() + index);
        //takes the index at which list begins and adds to it the index of specified task to erase it
        FileManagement::write();
        display();
    }
}

void TaskManagement::edit()
{
    while (true)
    {
        cout << "Enter the number of the task you would like to edit: ";

        string choice;
        getline(cin, choice);
        if (choice == "") break; //this breaks loop if user presses enter

        int index = stoi(choice) - 1; //converts the string to integer and subtracts 1 because our index starts at 0
        if (index > list.size()) return; //breaks if invalid number

        string changetask;
        cout << "Enter what you would like to change the task to: " << endl;
        getline(cin, changetask);
        if (changetask == "") break;

        Item item(changetask);
        list[index] = changetask;

        FileManagement::write(); //saves the list
        display();
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
    for (int i = 0; i < list.size(); ++i)
        if (!list[i].is_done())
        {
            cout << n + 1 << ") " << setw(width) << left << list[i].text() << setw(width) << (list[i].is_done() ? "Done" : "") << setw(width) << (list[i].getpriority()) << endl;
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
    for (int i = 0; i < list.size(); ++i)
        if (list[i].is_done())
        {
            cout << n + 1 << ") " << setw(width) << left << list[i].text() << setw(width) << (list[i].is_done() ? "Done" : "") << setw(width) << (list[i].getpriority()) << endl;
            ++n;
        }
    cout << setfill('-') << setw(width*2.5) << "-" << endl;
    cout << setfill(' ') << fixed;

}

void TaskManagement::check()
{
    while (true) {
        cout << "Enter number of task to mark off: ";

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

        FileManagement::write();
        display();
    }
}

void TaskManagement::uncheck() {
    while (true) {
        cout << "Enter number of task to unmark: ";

        string choice;
        getline(cin, choice);

        if (choice.empty()) return;
        for (char c : choice) if (isalpha(c)) return;

        int index = stoi(choice) - 1;
        if (index > list.size()) return;
        list[index].notdone(); //takes the index and marks it as not done

        FileManagement::write();
        display();

    }
}

void TaskManagement::set_priority()
{
    while (true)
    {
        cout << "Enter the number of the task you would like to set the priority for: ";

        string choice;
        getline(cin, choice);

        if (choice == "") break;
        for (char c : choice) if (isalpha(c)) return;


        int index = stoi(choice) - 1; //converts the string to integer and subtracts 1 because our index starts at 0
        if (index > list.size()) return;

        cout << "Enter priority (low, medium, high, none): ";
        string priority;
        getline(cin, priority);
        if (priority == "low") {
            list[index].lowpriority();
        } else if (priority == "medium") {
            list[index].mediumpriority();
        } else if (priority == "high") {
            list[index].highpriority();

        } else if (priority == "none") {
            list[index].nopriority();
        } else {
            return;
        }
        FileManagement::write();
        display();
    }
}

void TaskManagement::set_date()
{
    while (true)
    {
        cout << "Enter the number of the task you would like to set a due date for: ";

        try {
            string choice;
            getline(cin, choice);

            if (choice.empty()) break;
            for (char c : choice) {
                if (isalpha(c) || ispunct(c) || isspace(c))
                {
                    throw invalid_argument("Invalid input");
                }
            }
            int index = stoi(choice) - 1; //converts the string to integer and subtracts 1 because our index starts at 0
            if (index >= list.size() || index < 0) //breaks if invalid number
                throw invalid_argument("Invalid Choice, Choice out of Range.");

            string day, month, year;
            cout << "Format: dd/mm/yyyy" << endl;

            cout << "Enter day: ";
            getline(cin, day);
            for (char c : day) {
                if (isalpha(c) || ispunct(c) || isspace(c))
                {
                    throw invalid_argument("Invalid input");
                }
            }
            if (stoi(day) < 1 || stoi(day) > 31) {
                throw invalid_argument("Invalid day. Enter a day from 1 to 31\n");
            };
            list[index].setDay(day);

            cout << "Enter month: ";
            getline(cin, month);
            for (char c : month) {
                if (isalpha(c) || ispunct(c) || isspace(c))
                {
                    throw invalid_argument("Invalid input");
                }
            }
            if (stoi(month) < 1 || stoi(month) > 12) {
                throw invalid_argument("Invalid month. Enter a month from 1 to 12\n");
            };
            list[index].setMonth(month);

            cout << "Enter year: ";
            getline(cin, year);
            for (char c : year)  {
                if (isalpha(c) || ispunct(c) || isspace(c))
                {
                    throw invalid_argument("Invalid input");
                }
            }
            if (stoi(year) < 2021 || stoi(year) > 9999 ) {
                throw invalid_argument("Invalid year. Enter a year from 2021 to 9999\n");
            };
            list[index].setYear(year);

            FileManagement::write();
            display();
        }
        catch (invalid_argument& e) {
            cerr << e.what() << "" << endl;
        }
    }
}

void TaskManagement::set_category()
{
    while (true)
    {
        cout << "Enter the number of the task you would like to add to a category: ";


        string choice;
        getline(cin, choice);

        if (choice == "") break;
        for (char c : choice) if (isalpha(c)) return;


        int index = stoi(choice) - 1; //converts the string to integer and subtracts 1 because our index starts at 0
        if (index > list.size()) return;

        cout << "Enter category (none, other, home, work, entertainment): ";
        string priority;
        getline(cin, priority);
        if (priority == "none") {
            list[index].catnone();
        }
        else if (priority == "other") {
            list[index].catother();
        }
        else if (priority == "home") {
            list[index].cathome();
        }
        else if (priority == "work") {
            list[index].catwork();
        }
        else if (priority == "entertainent") {
            list[index].catentertainment();
        }
        else {
            return;
        }
        FileManagement::write();
        display();
    }
}