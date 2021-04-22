#include "taskmanagement.h"

/*TaskManagement::TaskManagement():DatabaseManagement(){}
*/

TaskManagement::~TaskManagement()
{
    // do nothing
}
//the taskmanagement constructor calls the inherited class constructor to create a file
TaskManagement::TaskManagement(const char *filename) : DatabaseManagement(filename) {

}

void TaskManagement::organize()
{
    const int width = 35; //read-only cannot be modified by program
    //iomanip library is used for a nice looking table
    cout << setfill('-') << setw(width*5) << "-" << endl;
    cout << setfill(' ') << fixed;
    cout << "   " << setw(width) << left << "TASK" << setw(width) << "DONE" << setw(width) << "PRIORITY" << setw(width) << "DATE" << setw(width) << "CATEGORY" << endl;
    cout << setfill('-') << setw(width*5) << "-" << endl;
    cout << setfill(' ') << fixed;
}

// this function checks to see if the user has pressed enter to continue displaying the tasks
void TaskManagement::enter()
{
    while (true) {
        cout << "Press Enter to continue ";
        try {
            string enter;
            getline(cin, enter);
            if (!enter.empty()) {
                throw invalid_argument("Invalid.");
            } else break;
        } catch (invalid_argument &e) {
            cerr << e.what() << "\nPlease Press Enter\n" << endl;
        }

    }
}

void TaskManagement::display() {
    cout << endl;
    cout << "                                                                      " << "YOUR TO DO LIST" << "    " << endl;

    const int width = 35; //read-only cannot be modified by program
    organize();
    int x = 0;
    /*
     * auto just specifies the type automatically
     * for loop iterates over the list and prints each line
     * colon syntax just iterates over the characters in choice and checks if they are alphabet, if they are it stops
     */
    for (auto &i : list)
    {
    cout << x + 1 << ") " << setw(width) << left << i.text() << setw(width) << (i.is_done() ? "Done" : "") << setw(width) << (i.getpriority()) << setw(width) << (i.date()) << setw(width) << (i.category())<< endl;
    /*
     * ? is a conditional operator that returns X if condition true or Y if condition false [? X:Y]
     * i.text returns the text from that line as defined in the item class
     * i.getpriority gets the priority of the task
     * i.category displays the category of the task
     */
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

    while (!is_finished) //while user gives in an input
    {
        cout << count << ": ";

        getline(cin, task);
        if (task.empty()) is_finished = true; //loop breaks if user presses enter
        else
        {
            Item item(task); //cast task as an item
            list.push_back(item);  //add item to list
            count++; //add to the counter
        }
    }
}


int TaskManagement::get_count() //this function returns the size of the list, to check if db has items
{
    return int(list.size());
}

void TaskManagement::add()
{
    int index = int(list.size());
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
            DatabaseManagement::appendData(task, ind);
        }
    }
    //DatabaseManagement::insertData(); //write the list into the file
}

void TaskManagement::del()
{
    while (true)
    {
        cout << endl;
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
            advance(it,index); //this moves the iterator to the index that the user has specified
            list.erase(it);
            DatabaseManagement::insertData();
            display();
        } catch (invalid_argument& e) {
            cerr << e.what() << "\nPlease Enter the Number Corresponding to your Choice\n" << endl;
        }
    }
}

void TaskManagement::edit()
{
    while (true)
    {
        cout << endl;
        cout << "--------------" << endl << endl;
        cout << "The Following Edits are available \n";
        cout << "--------------" << endl;
        cout << "1) Edit Line (removes done status, priority, date, and category) \n2) Edit Task ONLY \n" ;
        cout << "--------------" << endl;
        cout << "Choice: ";

        try{
            string edit;
            getline(cin, edit);

            if (edit.empty())
            {
                break;
            }
            for (char c : edit) {
                if (!isdigit(c)) {
                    throw invalid_argument(
                            "Invalid Choice, Choice cannot contain an Alphabet Character, Spaces, Symbols or Punctuation");
                }
            }

            if (stoi(edit) > 2 || stoi(edit) < 1)
                throw invalid_argument("Invalid Choice, Choice out of Range.");

            while (true) {
                cout << "Enter the number of the task you would like to edit: ";


                string choice;
                getline(cin, choice);

                if (choice.empty()) break;
                for (char c : choice) {
                    if (!isdigit(c)) {
                        throw invalid_argument(
                                "Invalid Choice, Choice cannot contain an Alphabet Character, Spaces, Symbols or Punctuation");
                    }
                }

                int index = stoi(choice) - 1;
                if (index >= list.size() || index < 0)
                    throw invalid_argument("Invalid Choice, Choice out of Range.");

                string changetask;
                cout << "Enter what you would like to change the task to: " << endl;
                getline(cin, changetask);
                if (!changetask.empty())
                {
                    Item item(changetask);
                    int x = 0;
                    for (auto &i : list) { //iterates over list and checks if it has reached the specified index then edits task according to what the user chose
                        if (index == x) {
                            if (stoi(edit) == 1)
                            {
                                i = changetask;
                                break;
                            }
                            else if (stoi(edit) == 2)
                            {
                                i.set_text(changetask);
                                break;
                            }
                        }
                        else
                        {
                            x++; //adds when task hasn't been reached
                        }
                    }
                    DatabaseManagement::insertData(); //saves the list
                    display();
                    break;
                }
            }
        } catch (invalid_argument& e) {
            cerr << e.what() << "\nPlease Enter the Number Corresponding to your Choice\n" << endl;
        }
    }
}

void TaskManagement::view_incomplete()
{
    cout << endl;
    cout << "                                                                    " << "TASKS TO COMPLETE" << "    " << endl;

    const int width = 35;
    organize();

    int n = 0;
    for (auto &i : list)
        if (!i.is_done())
        {
            cout << n + 1 << ") " << setw(width) << left << i.text() << setw(width) << (i.is_done() ? "Done" : "") << setw(width) << (i.getpriority()) << setw(width) << (i.date()) << setw(width) << (i.category()) << endl;
            ++n;
        }
    cout << setfill('-') << setw(width*5) << "-" << endl;
    cout << setfill(' ') << fixed;

    enter();
}

void TaskManagement::view_complete()
{
    cout << endl;
    cout << "                                                                      " << "COMPLETED TASKS" << "    " << endl;

    const int width = 35;
    organize();

    int n = 0;
    for (auto &i : list)
        if (i.is_done())
        {
            cout << n + 1 << ") " << setw(width) << left << i.text() << setw(width) << (i.is_done() ? "Done" : "") << setw(width) << (i.getpriority()) << setw(width) << (i.date()) << setw(width) << (i.category()) << endl;
            ++n;
        }
    cout << setfill('-') << setw(width*5) << "-" << endl;
    cout << setfill(' ') << fixed;

    enter();

}

void TaskManagement::status(int option)
{
    while (true) {
        if (option == 1)
        {
            cout << endl;
            cout << "Enter number of task to mark off: ";
        }
        else if (option == 2)
        {
            cout << endl;
            cout << "Enter number of task to unmark: ";
        }

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
            int index = stoi(choice) - 1;
            if (index >= list.size() || index < 0)
                throw invalid_argument("Invalid Choice, Choice out of Range.");

            int x = 0;
            for (auto &i : list) {
                if (index == x) {
                    if (option == 1)
                    {
                        if (i.is_done())
                            throw invalid_argument("Task is already Done");
                        i.done();
                        //DatabaseManagement::updateData(i, 3, index);
                        break;
                    }
                    else if (option == 2)
                    {
                        if (!i.is_done())
                            throw invalid_argument("Task is already unmarked");
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
            DatabaseManagement::insertData();

            display();
        } catch (invalid_argument& e) {
            cerr << e.what() << "\nPlease Enter the Number Corresponding to your Choice\n" << endl;
        }
    }
}

bool TaskManagement::status_check(int x) { //checks if the task has been done to allow user to view done tasks
    try {
        int count = 0;
        for (auto &i : list)
            if (!i.is_done()) {
                count++;
            }
        if (count == list.size())
            throw invalid_argument("None of the Tasks have been Done");
        return true;
    }catch (invalid_argument& e) {
        if (x == 1)
        {
            cerr << e.what() << "\nPlease Mark Off Tasks to be able to use this Feature\n" << endl;
        } else cerr << e.what() << "\nThe Current list is what you have to Complete\n" << endl;
        return false;
    }
}

void TaskManagement::set_priority() {
    while (true) {
        cout << endl;
        cout << "Enter the number of the task you would like to set the priority for: ";

        try {
            string choice;
            getline(cin, choice); //takes input from user

            if (choice.empty()) break;
            for (char c : choice) {
                if (!isdigit(c)) {
                    throw invalid_argument(
                            "Invalid Choice, Choice cannot contain an Alphabet Character, Spaces, Symbols or Punctuation");
                }
            }
            int index = stoi(choice) - 1;
            if (index >= list.size() || index < 0)
                throw invalid_argument("Invalid Choice, Choice out of Range.");

            while (true) {
                cout << endl;
                cout << "Enter priority (low, medium, high, none): ";
                try {
                    string priority;
                    getline(cin, priority);

                    priority = Item::str_tolower(priority); //lowercases user input
                    if (!priority.empty()) {
                        for (char p : priority) {
                            if (!isalpha(p)) {
                                throw invalid_argument(
                                        "Invalid Choice, Choice cannot contain an Number, Spaces, Symbols or Punctuation");
                            }
                        }

                        if (priority == "low" || priority == "medium" || priority == "high" || priority == "none") {}
                        else throw invalid_argument("Invalid Priority.");

                        int x = 0;
                        for (auto &i : list) {
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
                            } else if (index != x || index > x) {
                                x++;
                            }
                        }
                        DatabaseManagement::insertData();
                        display();
                        break;
                    }
                } catch (invalid_argument &e) {
                    cerr << e.what() << "\nPlease Enter low, medium, high, none for the Priority\n" << endl;
                }
            }
        } catch (invalid_argument &e) {
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
    DatabaseManagement::selectPriority(1);
    display();
    enter();
}

void TaskManagement::priority_sort_by_low() {
    DatabaseManagement::selectPriority(2);
    display();
    enter();
}



void TaskManagement::set_date() {
    while (true) {
        cout << endl;
        cout << "Enter the number of the task you would like to set a due date for: ";

        try {
            string choice;
            getline(cin, choice);

            if (choice.empty()) break;
            for (char c : choice) {
                if (!isdigit(c)) {
                    throw invalid_argument("Invalid input");
                }
            }
            int index = stoi(choice) - 1; //converts the string to integer and subtracts 1 because our index starts at 0
            if (index >= list.size() || index < 0) //breaks if invalid number
                throw invalid_argument("Invalid Choice, Choice out of Range.");


            string day, month, year;
            bool leap_year;
            cout << "Format: yyyy-mm-dd" << endl;

            cout << "Enter year: ";
            getline(cin, year);
            for (char c : year) {
                if (!isdigit(c)) {
                    throw invalid_argument("Invalid input");
                }
            }

            if (stoi(year) < 2021 || stoi(year) > 9999) {
                throw invalid_argument("Invalid year. Enter a year from 2021 to 9999\n");
            }

            if (stoi(year) % 4 == 0) { //checks if year input is a leap year
                if (stoi(year) % 100 == 0) {
                    if (stoi(year) % 400 == 0)
                        leap_year = true;
                    else leap_year = false;
                }
                else leap_year = true;
            }
            else leap_year = false;

            cout << "Enter month: ";
            getline(cin, month);
            for (char c : month) {
                if (!isdigit(c)) {
                    throw invalid_argument("Invalid input");
                }
            }

            if (stoi(month) < 1 || stoi(month) > 12) {
                throw invalid_argument("Invalid month. Enter a month from 1 to 12\n");
            }

            cout << "Enter day: ";
            getline(cin, day);
            for (char c : day) {
                if (!isdigit(c)) {
                    throw invalid_argument("Invalid input");
                }
            }

            if (stoi(day) < 1 || stoi(day) > 31) {
                throw invalid_argument("Invalid day. Day cannot be less than 1 or more than 31.\n");
            }

            if (stoi(month) == 2) {
                if (stoi(day) > 29) {
                    throw invalid_argument("Invalid day. Enter a day from 1 to 29\n");
                }
            }

            if (stoi(month) == 2){
                if (!leap_year && stoi(day) > 28) {
                    throw invalid_argument("Invalid day. The year you entered is not a leap year.\n");
                }
                else if (leap_year && stoi(day) > 29) {
                    throw invalid_argument("Invalid day. Enter a day from 1 to 29\n");
                }
            }

            if (stoi(month) == 4 || stoi(month) == 6 || stoi(month) == 9 || stoi(month) == 11) {
                if (stoi(day) > 30) {
                    throw invalid_argument("Invalid day. Enter a day from 1 to 30\n");
                }
            }

            int x = 0;
            for (auto &i : list) {
                if (index == x) {
                    i.setDay(day);
                    i.setMonth(month);
                    i.setYear(year);
                    i.setDate();
                    break;
                } else {
                    x++;
                }
            }
            DatabaseManagement::insertData();
            display();
        }
        catch (invalid_argument &e) {
            cerr << e.what() << "" << endl;
        }
    }
}

void TaskManagement::set_category() {
    while (true) {
        cout << endl;
        cout << "Enter the number of the task you would like to add to a category: ";

        try {
            string choice;
            getline(cin, choice); //takes input from user

            if (choice.empty()) break;
            for (char c : choice) {
                if (!isdigit(c)) {
                    throw invalid_argument(
                            "Invalid Choice, Choice cannot contain an Alphabet Character, Spaces, Symbols or Punctuation");
                }
            }
            int index = stoi(choice) - 1;
            if (index >= list.size() || index < 0)
                throw invalid_argument("Invalid Choice, Choice out of Range.");

            while (true) {
                cout << endl;
                cout << "Enter category (none, other, home, work, entertainment): ";
                try {
                    string category;
                    getline(cin, category);
                    category = Item::str_tolower(category);
                    if (!category.empty()) {
                        for (char c : category) {
                            if (!isalpha(c)) {
                                throw invalid_argument(
                                        "Invalid Choice, Choice cannot contain an Number, Spaces, Symbols or Punctuation");
                            }
                        }

                        if (category == "work" || category == "home" || category == "entertainment" || category == "other" || category == "none") {}
                        else throw invalid_argument("Invalid Category.");

                        int x = 0;
                        for (auto &i : list) {
                            if (category == "work" && index == x) {
                                i.workcategory();
                                DatabaseManagement::insertData();
                                break;
                            } else if (category == "home" && index == x) {
                                i.homecategory();
                                DatabaseManagement::insertData();
                                break;
                            } else if (category == "entertainment" && index == x) {
                                i.entertainmentcategory();
                                DatabaseManagement::insertData();
                                break;
                            } else if (category == "other" && index == x) {
                                i.othercategory();
                                DatabaseManagement::insertData();
                                break;
                            } else if (category == "none" && index == x) {
                                i.nocategory();
                                DatabaseManagement::insertData();
                                break;
                            } else if (index != x || index > x) {
                                x++;
                            }
                        }
                        display();
                        break;
                    }
                } catch (invalid_argument &e) {
                    cerr << e.what() << "\nPlease Enter work, home, entertainment, other, or none for the Category\n"
                         << endl;
                }
            }
        } catch (invalid_argument &e) {
            cerr << e.what() << "\nPlease Enter the Number Corresponding to your Choice\n" << endl;
        }
    }
}

bool TaskManagement::date_check() { //checks if no due date is set
    try {
        int count = 0;
        for (auto &i : list)
            if (i.date() == "0000-00-00" || i.date().empty()) {
                count++;
            }
        if (count == list.size())
            throw invalid_argument("No Due Dates Set");
        return true;
    } catch (invalid_argument &e) {
        cerr << e.what() << "\nPlease Set Due Dates to be able to use this Feature\n" << endl;
        return false;
    }
}

void TaskManagement::date_sort_desc(){
    DatabaseManagement::selectDate(1);
    display();
    enter();
}

void TaskManagement::date_sort_asc() {
    DatabaseManagement::selectDate(2);
    display();
    enter();
}

bool TaskManagement::category_check(int x) {
    if (x == 1) {
        try {

            int count = 0;
            for (auto &i : list)
                if (i.category() == "none" || i.category().empty()) {
                    count++;
                }
            if (count == list.size())
                throw invalid_argument("No Categories Set");
        } catch (invalid_argument& e) {
            cerr << e.what() << "\nPlease Set Categories to be able to use this Feature\n" << endl;
            return false;
        }
        return true;
    } else if (x == 2) {
        try {
            int count = 0;
            for (auto &i : list)
                if (i.category() == "home") {
                    count++;
                }
            if (count == 0)
                throw invalid_argument("No Home Category Set");
        } catch (invalid_argument& e) {
            cerr << e.what() << "\nPlease Set Home Category to view it\n" << endl;
            return false;
        }
        return true;
    } else if (x == 3) {
        try {
            int count = 0;
            for (auto &i : list)
                if (i.category() == "other") {
                    count++;
                }
            if (count == 0)
                throw invalid_argument("No Other Category Set");
        } catch (invalid_argument &e) {
            cerr << e.what() << "\nPlease Set Other Category to view it\n" << endl;
            return false;
        }
        return true;
    } else if (x == 4) {
        try {
            int count = 0;
            for (auto &i : list)
                if (i.category() == "entertainment") {
                    count++;
                }
            if (count == 0)
                throw invalid_argument("No Entertainment Category Set");
        } catch (invalid_argument &e) {
            cerr << e.what() << "\nPlease Set Entertainment Category to view it\n" << endl;
            return false;
        }
        return true;
    } else if (x == 5) {
        try {
            int count = 0;
            for (auto &i : list)
                if (i.category() == "work") {
                    count++;
                }
            if (count == 0)
                throw invalid_argument("No Work Category Set");
        } catch (invalid_argument &e) {
            cerr << e.what() << "\nPlease Set Work Category to view it\n" << endl;
            return false;
        }
        return true;
    } else if (x == 6) {
        try {
            int count = 0;
            for (auto &i : list)
                if (i.category() == "none") {
                    count++;
                }
            if (count == 0)
                throw invalid_argument("You have Set Categories for all Tasks");
        } catch (invalid_argument &e) {
            cerr << e.what() << "\nPlease Set Tasks to None to view them\n" << endl;
            return false;
        }
        return true;
    }
    return false;
}

void TaskManagement::view_category()
{
    bool invalid = true;
    while (invalid) {

        cout << "--------------" << endl << endl;
        cout << "The Following Categories are available \n";
        cout << "--------------" << endl;
        cout << "1) Home \n2) Work \n3) Entertainment\n4) Other\n5) None\n";
        cout << "--------------" << endl;
        cout << "Choice: ";

        try {
            string choice;
            getline(cin, choice);

            if (choice.empty()) {
                break;
            }
            for (char c : choice) {
                if (!isdigit(c)) {
                    throw invalid_argument(
                            "Invalid Choice, Choice cannot contain an Alphabet Character, Spaces, Symbols or Punctuation");
                }
            }

            if (stoi(choice) > 5 || stoi(choice) < 1)
                throw invalid_argument("Invalid Choice, Choice out of Range.");


            const int width = 35;
            int n = 0;
            for (auto &i : list) {
                if (choice == "1") {
                    if (!category_check(2)) {
                        break;
                    }else {
                        if (i.category() == "home")
                        {
                            cout << endl;
                            cout << "                                                                           " << "HOME" << "    " << endl;
                            organize();
                            cout << n + 1 << ") " << setw(width) << left << i.text() << setw(width) << (i.is_done() ? "Done" : "") << setw(width) << (i.getpriority()) << setw(width) << (i.date()) << setw(width) << (i.category()) << endl;
                            ++n;
                            cout << setfill('-') << setw(width * 5) << "-" << endl;
                            cout << setfill(' ') << fixed;
                            cout << endl;
                        }
                    }
                } else if (choice == "2") {
                    if (!category_check(5)) {
                        break;
                    }else {
                        if (i.category() == "work")
                        {
                            cout << endl;
                            cout << "                                                                           " << "WORK" << "    " << endl;
                            organize();
                            cout << n + 1 << ") " << setw(width) << left << i.text() << setw(width) << (i.is_done() ? "Done" : "") << setw(width) << (i.getpriority()) << setw(width) << (i.date()) << setw(width) << (i.category()) << endl;
                            ++n;
                            cout << setfill('-') << setw(width * 5) << "-" << endl;
                            cout << setfill(' ') << fixed;
                            cout << endl;
                        }
                    }
                } else if (choice == "3") {
                    if (!category_check(4)) {
                        break;
                    }else {
                        if (i.category() == "entertainment")
                        {
                            cout << endl;
                            cout << "                                                                       " << "ENTERTAINMENT" << "    " << endl;
                            organize();
                            cout << n + 1 << ") " << setw(width) << left << i.text() << setw(width) << (i.is_done() ? "Done" : "") << setw(width) << (i.getpriority()) << setw(width) << (i.date()) << setw(width) << (i.category()) << endl;
                            ++n;
                            cout << setfill('-') << setw(width * 5) << "-" << endl;
                            cout << setfill(' ') << fixed;
                            cout << endl;
                        }
                    }
                } else if (choice == "4") {
                    if (!category_check(3)) {
                        break;
                    }else {
                        if (i.category() == "other")
                        {
                            cout << endl;
                            cout << "                                                                          " << "OTHER" << "    " << endl;
                            organize();
                            cout << n + 1 << ") " << setw(width) << left << i.text() << setw(width) << (i.is_done() ? "Done" : "") << setw(width) << (i.getpriority()) << setw(width) << (i.date()) << setw(width) << (i.category()) << endl;
                            ++n;
                            cout << setfill('-') << setw(width * 5) << "-" << endl;
                            cout << setfill(' ') << fixed;
                            cout << endl;
                        }
                    }
                } else if (choice == "5") {
                    if (!category_check(6)) {
                        break;
                    }else {
                        if (i.category().empty() || i.category() == "none")
                        {
                            cout << endl;
                            cout << "                                                                           " << "NONE" << "    " << endl;
                            organize();
                            cout << n + 1 << ") " << setw(width) << left << i.text() << setw(width) << (i.is_done() ? "Done" : "") << setw(width) << (i.getpriority()) << setw(width) << (i.date()) << setw(width) << (i.category()) << endl;
                            ++n;
                            cout << setfill('-') << setw(width * 5) << "-" << endl;
                            cout << setfill(' ') << fixed;
                            cout << endl;
                        }
                    }
                }
            }
        } catch (invalid_argument& e) {
            cerr << e.what() << "\nPlease Enter the Number Corresponding to your Choice\n" << endl;
        }
    }
}

/*
void TaskManagement::priority_sort_by_low() {
    list1.clear;
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
*/