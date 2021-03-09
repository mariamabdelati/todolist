//
// Created by Mariam on 3/9/21.
//
#include "todo_list.h"

TodoList::TodoList()
{
    filename = nullptr; //file is null
}

TodoList::TodoList(const char* filename)
{
    this->filename = filename;
    /*
    this is a pointer, arrow is used to dereference, helps assign the variable of same name to itself
    */
}

TodoList::~TodoList()
{
    // do nothing
}

void TodoList::read()
{
    //creates and instance of a file and opens it for reading
    fstream fs(filename, fstream::in);
    string line;

    //this ensures the vector is empty
    list.clear();

    while(getline(fs, line)) //while can read the lines in file
    {
        if (line == "") continue; //if it encounters an empty line skip iteration
        Item item(line); //makes line an instance of class item (similar to type casting)
        list.push_back(item); //adds to list vector
    }

    fs.close();
}

void TodoList::display()
{
    cout << "Your todo list: " << endl << endl;

    const int W = 40; //read-only cannot be modified by program
    cout << "   " << setw(W) << left << "TASK" << "DONE" << endl; //nice looking to do list
    cout << "   " << setw(W) << left << "----" << "----" << endl;

    //for loop iterates over the list and prints each line
    for (int i = 0; i < list.size(); ++i)
        cout << i + 1 << ") " << setw(W) << left << list[i].text() << (list[i].is_done() ? "Done" : "" ) << endl;
    //? is a conditional operator that returns X if condition true or Y if condition false [? X:Y]
    //list[i].text returns the text from that line as defined in the item class
}


void TodoList::create() //this creates a new list
{
    bool is_finished = false;
    int count = 1;
    string task;

    list.clear();

    while(!is_finished) //while user gives in an input
    {
        cout << count << ": ";

        getline(cin, task);
        if (task == "") is_finished = true; //loop breaks if user presses enter

        Item item(task); //cast task as an item
        list.push_back(item); //add item to list vector
        count++;
    }
}

void TodoList::save() //this function writes to the file
{

    fstream fs(filename, fstream::out);

    //for loop iterates over the items in list
    for (Item item:list)
    {
        if (item.text().empty()) continue; //if empty line skip iteration

        fs << item.text() << " " << (item.is_done() ? "true" : "false") << endl;
        //otherwise it will add the item text to the file
        //then it will check if the item is done and save a true or false value in file
    }

    fs.close();
}

int TodoList::get_count() //this function returns the size of the list vector, to check if file has items
{
    return list.size();
};

void TodoList::add()
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

    save(); //saves the list
};

void TodoList::clear()
{
    list.clear(); //clears list
    remove(filename); //deletes file
}

void TodoList::check()
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

    save();
};