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
                if (isalpha(c))
                {
                    throw invalid_argument("Invalid Choice, Choice cannot contain an Alphabet Character.");
                } else if (isspace(c))
                {
                    throw invalid_argument("Invalid Choice, Choice cannot contain Spaces.");
                } else if (ispunct(c))
                {
                    throw invalid_argument("Invalid Choice, Choice cannot contain Punctuation.");
                }
            }
            int index = stoi(choice) - 1; //converts the string to integer and subtracts 1 because our index starts at 0
            if (index >= list.size() || index < 0) //breaks if invalid number
                throw invalid_argument("Invalid Choice, Choice out of Range.");

            auto it = list.begin();
            advance(it,index);
            list.erase(it);
            //takes the index at which list begins and adds to it the index of specified task to erase it
            FileManagement::write();
            display();
        } catch (invalid_argument& e) {
            cerr << e.what() << "\nPlease Enter the Number Corresponding to your Choice\n" << endl;
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
                if (isalpha(c))
                {
                    throw invalid_argument("Invalid Choice, Choice cannot contain an Alphabet Character.");
                } else if (isspace(c))
                {
                    throw invalid_argument("Invalid Choice, Choice cannot contain Spaces.");
                } else if (ispunct(c))
                {
                    throw invalid_argument("Invalid Choice, Choice cannot contain Punctuation.");
                }
            }

            int index = stoi(choice) - 1; //converts the string to integer and subtracts 1 because our index starts at 0
            if (index >= list.size() || index < 0) //breaks if invalid number
                throw invalid_argument("Invalid Choice, Choice out of Range.");

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
        } catch (invalid_argument& e) {
            cerr << e.what() << "\nPlease Enter the Number Corresponding to your Choice\n" << endl;
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
                if (isalpha(c))
                {
                    throw invalid_argument("Invalid Choice, Choice cannot contain an Alphabet Character.");
                } else if (isspace(c))
                {
                    throw invalid_argument("Invalid Choice, Choice cannot contain Spaces.");
                } else if (ispunct(c))
                {
                    throw invalid_argument("Invalid Choice, Choice cannot contain Punctuation.");
                }
            }
            int index = stoi(choice) - 1; //converts the string to integer and subtracts 1 because our index starts at 0
            if (index >= list.size() || index < 0) //breaks if invalid number

            // list[index].done(); //takes the index and marks it as done
                throw invalid_argument("Invalid Choice, Choice out of Range.");

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
        } catch (invalid_argument& e) {
            cerr << e.what() << "\nPlease Enter the Number Corresponding to your Choice\n" << endl;
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
                if (isalpha(c))
                {
                    throw invalid_argument("Invalid Choice, Choice cannot contain an Alphabet Character.");
                } else if (isspace(c))
                {
                    throw invalid_argument("Invalid Choice, Choice cannot contain Spaces.");
                } else if (ispunct(c))
                {
                    throw invalid_argument("Invalid Choice, Choice cannot contain Punctuation.");
                }
            }
            int index = stoi(choice) - 1; //converts the string to integer and subtracts 1 because our index starts at 0
            if (index >= list.size() || index < 0) //breaks if invalid number
                //list[index].notdone(); //takes the index and marks it as not done
                throw invalid_argument("Invalid Choice, Choice out of Range.");

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
        } catch (invalid_argument& e) {
            cerr << e.what() << "\nPlease Enter the Number Corresponding to your Choice\n" << endl;
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
                if (isalpha(c))
                {
                    throw invalid_argument("Invalid Choice, Choice cannot contain an Alphabet Character.");
                } else if (isspace(c))
                {
                    throw invalid_argument("Invalid Choice, Choice cannot contain Spaces.");
                } else if (ispunct(c))
                {
                    throw invalid_argument("Invalid Choice, Choice cannot contain Punctuation.");
                }
            }
            int index = stoi(choice) - 1; //converts the string to integer and subtracts 1 because our index starts at 0
            if (index >= list.size() || index < 0) //breaks if invalid number
                //list[index].notdone(); //takes the index and marks it as not done
                throw invalid_argument("Invalid Choice, Choice out of Range.");

            while (true)
            {
                cout << "Enter priority (low, medium, high, none): ";
                try {
                    string priority;
                    getline(cin, priority);
                    priority = Item::str_tolower(priority);
                    if (!priority.empty())
                    {
                        if (priority == "low" || priority == "medium" || priority == "high" || priority == "none") {}
                        else throw invalid_argument("Invalid Priority.");

                        for (char p : priority) {
                            if (isdigit(p))
                            {
                                throw invalid_argument("Invalid Choice, Choice cannot contain a Number.");
                            } else if (isspace(p))
                            {
                                throw invalid_argument("Invalid Choice, Choice cannot contain Spaces.");
                            } else if (ispunct(p))
                            {
                                throw invalid_argument("Invalid Choice, Choice cannot contain Punctuation.");
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
                } catch (invalid_argument& e) {
                    cerr << e.what() << "\nPlease Enter low, medium, high, none for the Priority\n" << endl;
                }
            }
        } catch (invalid_argument& e) {
            cerr << e.what() << "\nPlease Enter the Number Corresponding to your Choice\n" << endl;
        }
    }
}


bool TaskManagement::priority_check() {
    try {
        int count = 0;
        for (auto &i : list)
            if (i.priority() == "0" || i.priority().empty()) {
                count++;
            }
        if (count == list.size())
            throw invalid_argument("No Priorities Set");
        return true;
    }catch (invalid_argument& e) {
        cerr << e.what() << "\nPlease Set Priorities to be able to use this Feature\n" << endl;
        return false;
    }
}

void TaskManagement::priority_sort_by_high() {
    cout << endl;
    cout << "                             " << "SORT BY PRIORITY FROM HIGH TO LOW" << "    " << endl;

    const int width = 40;
    organize();
    int n = 0;
    for (auto& i : list)
        if (i.priority() == "3")
        {
            cout << n + 1 << ") " << setw(width) << left << i.text() << setw(width) << (i.is_done() ? "Done" : "") << setw(width) << (i.getpriority()) << endl;
            ++n;
        }

    for (auto& i : list)
        if (i.priority() == "2")
        {
            cout << n + 1 << ") " << setw(width) << left << i.text() << setw(width) << (i.is_done() ? "Done" : "") << setw(width) << (i.getpriority()) << endl;
            ++n;
        }

    for (auto& i : list)
        if (i.priority() == "1")
        {
            cout << n + 1 << ") " << setw(width) << left << i.text() << setw(width) << (i.is_done() ? "Done" : "") << setw(width) << (i.getpriority()) << endl;
            ++n;
        }

    for (auto& i : list)
        if (i.priority() == "0" || i.priority().empty())
        {
            cout << n + 1 << ") " << setw(width) << left << i.text() << setw(width) << (i.is_done() ? "Done" : "") << setw(width) << (i.getpriority()) << endl;
            ++n;
        }

    cout << setfill('-') << setw(width * 2.5) << "-" << endl;
    cout << setfill(' ') << fixed;
}

void TaskManagement::priority_sort_by_low() {
    cout << endl;
    cout << "                             " << "SORT BY PRIORITY FROM LOW TO HIGH" << "    " << endl;

    const int width = 40;
    organize();

    int n = 0;
    for (auto &i : list)
        if (i.priority() == "0" || i.priority().empty()) {
            cout << n + 1 << ") " << setw(width) << left << i.text() << setw(width) << (i.is_done() ? "Done" : "")
            << setw(width) << (i.getpriority()) << endl;
            ++n;
        }

    for (auto &i : list)
        if (i.priority() == "1") {
            cout << n + 1 << ") " << setw(width) << left << i.text() << setw(width) << (i.is_done() ? "Done" : "")
            << setw(width) << (i.getpriority()) << endl;
            ++n;
        }

    for (auto &i : list)
        if (i.priority() == "2") {
            cout << n + 1 << ") " << setw(width) << left << i.text() << setw(width) << (i.is_done() ? "Done" : "")
            << setw(width) << (i.getpriority()) << endl;
            ++n;
        }

    for (auto &i : list)
        if (i.priority() == "3") {
            cout << n + 1 << ") " << setw(width) << left << i.text() << setw(width) << (i.is_done() ? "Done" : "")
            << setw(width) << (i.getpriority()) << endl;
            ++n;
        }

    cout << setfill('-') << setw(width * 2.5) << "-" << endl;
    cout << setfill(' ') << fixed;
}
