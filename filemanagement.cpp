#include "filemanagement.h"
FileManagement::FileManagement()
{
    filename = nullptr; //file is null
}

FileManagement::FileManagement(const char* filename) //const char makes sure that file won't be changed
{
    this->filename = filename;
    /*
    this is a pointer, arrow is used to dereference, helps assign the variable of same name to itself
    */
}

FileManagement::~FileManagement()
{
    // do nothing
}

void FileManagement::read()
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

void FileManagement::write() //this function writes the list into the file
{
    //file is open for writing
    fstream fs(filename, fstream::out);

    //for loop iterates over the items in list
    for (Item item : list)
    {
        if (item.text().empty()) continue; //if empty line skip iteration
        fs << item.text() << " " << (item.is_done() ? "true" : "false") << " " << item.priority() << " " << item.getDay() << item.getMonth() << item.getYear() << item.getcategory() << endl;
        //otherwise it will add the item text to the file
        //then it will check if the item is done and save a true or false value in file
        //then it will save the item priority into file
    }
    fs.close();
}

void FileManagement::reset()
{
    list.clear(); //clears list
    remove(filename); //deletes file
}