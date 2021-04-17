#include "taskmanagement.h"

/*TaskManagement::TaskManagement():DatabaseManagement(){}
//the taskmanagement constructor calls the inherited class constructor to create a file*/

TaskManagement::~TaskManagement()
{
    // do nothing
}

TaskManagement::TaskManagement(const char *filename) : DatabaseManagement(filename) {

}

void TaskManagement::organize()
{
    const int width = 40; //read-only cannot be modified by program
    //iomanip library is used for a nice looking table
    cout << setfill('-') << setw(width*5) << "-" << endl;
    cout << setfill(' ') << fixed;
    cout << "   " << setw(width) << left << "TASK" << setw(width) << "DONE" << setw(width) << "PRIORITY" << setw(width) << "CATEGORY" << setw(width) << "DATE" << endl;
    cout << setfill('-') << setw(width*5) << "-" << endl;
    cout << setfill(' ') << fixed;
}

void TaskManagement::display() {
    cout << endl;
    cout << "                                     " << "YOUR TO DO LIST" << "    " << endl;

    const int width = 40; //read-only cannot be modified by program
    organize();
    int x = 0;
    //for loop iterates over the list and prints each line
    //for (auto &i : FileManagement::list)
    for (auto &i : list)
    {
    cout << x + 1 << ") " << setw(width) << left << i.text() << setw(width) << (i.is_done() ? "Done" : "") << setw(width) << (i.getpriority()) << setw(width) << (i.getcategory()) << setw(width) << (i.date()) << endl;
    //? is a conditional operator that returns X if condition true or Y if condition false [? X:Y]
    //list[i].text returns the text from that line as defined in the item class
    x++;
    }
    cout << setfill('-') << setw(width*5) << "-" << endl;
    cout << setfill(' ') << fixed;
}

void TaskManagement::create() //this creates a new list
{
    bool is_finished = false; // this is defined to check if user is done entering tasks
    int count = 1;
    string task;

    list.clear();
    //FileManagement::list.clear();

    while (!is_finished) //while user gives in an input
    {
        cout << count << ": ";

        getline(cin, task);
        if (task.empty()) is_finished = true; //loop breaks if user presses enter
        else
        {
            Item item(task); //cast task as an item
            list.push_back(item);
            count++; //add to the counter
        }
        //FileManagement::list.push_back(item); //add item to list vector
    }
}


int TaskManagement::get_count() //this function returns the size of the list vector, to check if file has items
{
    return int(list.size());
    //return FileManagement::list.size();
}

void TaskManagement::add()
{
    int index = int(list.size()); //FileManagement::list.size();
    while (true)
    {
        int ind = ++index;
        cout << ind << ": "; //checks current list size and adds to it to keep count of items

        string task;
        getline(cin, task);
        if (task.empty()) break; //this breaks loop if user presses enter
        else
        {
            Item item(task);
            list.push_back(item);
            //DatabaseManagement::inserData(task, ind);
        }


        //FileManagement::list.push_back(item);
    }
    //DatabaseManagement::deleteData();
    DatabaseManagement::insertData();


    //FileManagement::write(); //write the list into the file
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
                if (!isdigit(c)) {
                    throw invalid_argument(
                            "Invalid Choice, Choice cannot contain an Alphabet Character, Spaces, Symbols or Punctuation");
                }
            }
            int index = stoi(choice) - 1; //converts the string to integer and subtracts 1 because our index starts at 0
            if (index >= list.size() || index < 0) //breaks if invalid number
                throw invalid_argument("Invalid Choice, Choice out of Range.");

            auto it = list.begin();
            advance(it,index);
            list.erase(it);
            //takes the index at which list begins and adds to it the index of specified task to erase it
            //DatabaseManagement::deleteData();
            DatabaseManagement::insertData();
            display();
        } catch (invalid_argument& e) {
            cerr << e.what() << "\nPlease Enter the Number Corresponding to your Choice\n" << endl;
        }

        //if (index > list.size()) return; //breaks if invalid number


    }
}

void TaskManagement::edit(int option)
{
    while (true)
    {
        cout << "Enter the number of the task you would like to edit: ";

        try {
            string choice;
            getline(cin, choice);

            if (choice.empty()) break; //this breaks loop if user presses enter
            for (char c : choice) {
                if (!isdigit(c)) {
                    throw invalid_argument(
                            "Invalid Choice, Choice cannot contain an Alphabet Character, Spaces, Symbols or Punctuation");
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
                            if (option == 1)
                            {
                                i = changetask;
                                break;
                            }
                            else if (option == 2)
                            {
                                i.set_text(changetask);
                                break;
                            }
                        }
                        else
                        {
                            x++;
                        }
                    }
                    //DatabaseManagement::deleteData();
                    DatabaseManagement::insertData(); //saves the list
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
            cout << n + 1 << ") " << setw(width) << left << i.text() << setw(width) << (i.is_done() ? "Done" : "") << setw(width) << (i.getpriority()) << setw(width) << (i.getcategory()) << setw(width) << (i.date()) << endl;
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
            cout << n + 1 << ") " << setw(width) << left << i.text() << setw(width) << (i.is_done() ? "Done" : "") << setw(width) << (i.getpriority()) << setw(width) << (i.getcategory()) << setw(width) << (i.date()) << endl;
            ++n;
        }
    cout << setfill('-') << setw(width*2.5) << "-" << endl;
    cout << setfill(' ') << fixed;

}

void TaskManagement::status(int option)
{
    while (true) {
        if (option == 1)
        {
            cout << "Enter number of task to mark off: ";
        }
        else if (option == 2)
        {
            cout << "Enter number of task to unmark: ";
        }

        try {
            string choice;
            getline(cin, choice); //takes input from user

            if (choice.empty()) break;
            for (char c : choice) {
                /*
                colon syntax just iterates over the characters in choice and checks if they are alphabet, if they are it stops
                */
                if (!isdigit(c)) {
                    throw invalid_argument(
                            "Invalid Choice, Choice cannot contain an Alphabet Character, Spaces, Symbols or Punctuation");
                }
            }
            int index = stoi(choice) - 1; //converts the string to integer and subtracts 1 because our index starts at 0
            if (index >= list.size() || index < 0) //breaks if invalid number

            // list[index].done(); //takes the index and marks it as done
                throw invalid_argument("Invalid Choice, Choice out of Range.");

            int x = 0;
            for (auto &i : list) {
                if (index == x) {
                    if (option == 1)
                    {
                        i.done();
                        //DatabaseManagement::updateData(i, 3, stoi(choice));
                        break;
                    }
                    else if (option == 2)
                    {
                        i.notdone();
                        //DatabaseManagement::updateData(i, 3, stoi(choice));
                        break;
                    }
                }
                else
                {
                    x++;
                }
            }
            //DatabaseManagement::deleteData();
            DatabaseManagement::insertData();

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
                if (!isdigit(c)) {
                    throw invalid_argument(
                            "Invalid Choice, Choice cannot contain an Alphabet Character, Spaces, Symbols or Punctuation");
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
                        for (char p : priority) {
                            if (!isalpha(p)) {
                                throw invalid_argument(
                                        "Invalid Choice, Choice cannot contain an Number, Spaces, Symbols or Punctuation");
                            }
                        }

                        /*if (priority == "low" || priority == "medium" || priority == "high" || priority == "none") {}
                        else throw invalid_argument("Invalid Priority.");*/

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
                        //DatabaseManagement::deleteData();
                        DatabaseManagement::insertData();
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
    if (list1.empty())
    {
        for (const auto& item : list){
            list1.push_back(item);
        }
    }
    list.clear();

    for (auto i : list1)
        if (i.priority() == "3") {
            list.push_back(i);
        }
    for (auto i : list1)
        if (i.priority() == "2") {
            list.push_back(i);
        }
    for (auto i : list1)
        if (i.priority() == "1") {
            list.push_back(i);
        }
    for (auto i : list1)
        if (i.priority() == "0" || i.priority().empty()) {
            list.push_back(i);
        }
    DatabaseManagement::insertData();
    //list.clear();
    //DatabaseManagement::selectPriority(1);
    //display();
}

void TaskManagement::priority_sort_by_low() {
    if (list1.empty())
    {
        for (const auto& item : list){
            list1.push_back(item);
        }
    }

    list.clear();

    for (auto i : list1)
        if (i.priority() == "0" || i.priority().empty()) {
            list.push_back(i);
        }
    for (auto i : list1)
        if (i.priority() == "1") {
            list.push_back(i);
        }
    for (auto i : list1)
        if (i.priority() == "2") {
            list.push_back(i);
        }
    for (auto i : list1)
        if (i.priority() == "3") {
            list.push_back(i);
        }
    DatabaseManagement::insertData();

    //DatabaseManagement::selectPriority(2);
    //display();
}

bool TaskManagement::restore_list()
{
    if (list1.empty())
        return false;
    else
    {
        list.clear();
        for (const auto& item : list1){
            list.push_back(item);
        }
        DatabaseManagement::insertData();
        return true;
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
                if (!isdigit(c))
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
                if (!isdigit(c))
                {
                    throw invalid_argument("Invalid input");
                }
            }

            if (stoi(day) < 1 || stoi(day) > 31) {
                throw invalid_argument("Invalid day. Enter a day from 1 to 31\n");
            }

            int x = 0;
            for (auto &i : list) {
                if (index == x) {
                    i.setDay(day);
                    //DatabaseManagement::updateData(i, 3, stoi(choice));
                    break;
                } else {
                    x++;
                }
            }

            cout << "Enter month: ";
            getline(cin, month);
            for (char c : month) {
                if (!isdigit(c))
                {
                    throw invalid_argument("Invalid input");
                }
            }

            if (stoi(month) < 1 || stoi(month) > 12) {
                throw invalid_argument("Invalid month. Enter a month from 1 to 12\n");
            }

            int y = 0;
            for (auto &i : list) {
                if (index == y) {
                    i.setMonth(month);
                    //DatabaseManagement::updateData(i, 3, stoi(choice));
                    break;
                } else {
                    y++;
                }
            }

            cout << "Enter year: ";
            getline(cin, year);
            for (char c : year) {
                if (!isdigit(c))
                {
                    throw invalid_argument("Invalid input");
                }
            }

            if (stoi(year) < 2021 || stoi(year) > 9999 ) {
                throw invalid_argument("Invalid year. Enter a year from 2021 to 9999\n");
            }

            int z = 0;
            for (auto &i : list) {
                if (index == z) {
                    i.setYear(year);
                    //DatabaseManagement::updateData(i, 3, stoi(choice));
                    break;
                } else {
                    z++;
                }
            }

            DatabaseManagement::insertData();
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

        if (choice.empty()) break;
        for (char c : choice) if (isalpha(c)) return;


        int index = stoi(choice) - 1; //converts the string to integer and subtracts 1 because our index starts at 0
        if (index > list.size()) return;


        while (true)
        {
            cout << "Enter category (none, other, home, work, entertainment): ";
            try {
                string category;
                getline(cin, category);
                category = Item::str_tolower(category);
                if (!category.empty())
                {
                    for (char c : category) {
                        if (!isalpha(c)) {
                            throw invalid_argument(
                                    "Invalid Choice, Choice cannot contain an Number, Spaces, Symbols or Punctuation");
                        }
                    }

                    int x = 0;
                    for (auto &i : list)
                    {
                        if (category == "work" && index == x) {
                            i.catwork();
                            break;
                        } else if (category == "home" && index == x) {
                            i.cathome();
                            break;
                        } else if (category == "entertainment" && index == x) {
                            i.catentertainment();
                            break;
                        } else if (category == "other" && index == x) {
                            i.catother();
                            break;
                        } else if (category == "none" && index == x) {
                            i.catnone();
                            break;
                        } else if (index != x || index > x)
                        {
                            x++;
                        }
                    }
                    //DatabaseManagement::deleteData();
                    DatabaseManagement::insertData();
                    display();
                    break;
                }
            } catch (invalid_argument& e) {
                cerr << e.what() << "\nPlease Enter low, medium, high, none for the Priority\n" << endl;
            }
        }
    }
}
