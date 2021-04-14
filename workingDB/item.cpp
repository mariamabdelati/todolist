#include "item.h"
Item::Item()
{
    _tasktext = "";
    _done = false;
    _priority = "";
}

Item::Item(string item)
{
    int startfalse = item.find("false");
    /*
    if found, the index for when the string starts is stored
    if not found, the index stored is -1
    */
    int starttrue = item.find("true");
    string str;
    string pr;

    if (startfalse > -1 && starttrue == -1) // item has false
    {
        //this stores the line substring without the word done/not done (subtract one to end right before the index of done)
        str = item.substr(0, startfalse - 1);
        _done = false;
        pr = item.substr(startfalse + 6, startfalse + 7);
    }
    else if (starttrue > -1 && startfalse == -1) { // item has true
        str = item.substr(0, starttrue - 1);
        _done = true;
        pr = item.substr(starttrue + 5, starttrue + 6);
    }
    else if (startfalse == -1 && starttrue == -1) { // item is user input (no true or false)
        str = item;
        _done = false;
        pr = "";
    }

    _tasktext = str;
    _priority = pr;
}

/*Item::~Item()
{
    // do nothing
}*/

//this function will return the line text
string Item::text()
{
    return _tasktext;
}

//this function marks off a task
void Item::done()
{
    _done = true;
}

//this function unmarks a task
void Item::notdone()
{
    _done = false;
}

//this function identifies if a task is done
bool Item::is_done()
{
    return _done;
}

//this function sets high priority
void Item::highpriority()
{
    _priority = "3";
}

//this function sets medium priority
void Item::mediumpriority()
{
    _priority = "2";
}

//this function sets low priority
void Item::lowpriority()
{
    _priority = "1";
}

//this function sets no priority
void Item::nopriority()
{
    _priority = "0";
}

//this function returns the priority of a specified item as a name rather than a value
string Item::getpriority()
{
    string p;
    if (_priority == "0")
    {
        p = "";
    }
    else if (_priority == "1")
    {
        p = "low";
    }
    else if (_priority == "2")
    {
        p = "medium";
    }
    else if (_priority == "3")
    {
        p = "high";
    }
    return p;
}

//this function returns the priority of a specified item
string Item::priority()
{
    return _priority;
}

//this changes the text to lowercase so it is easier to deal with
string Item::str_tolower(string str)
{
    string temp = str;
    for (int i = 0; i < temp.size(); ++i)
        temp[i] = tolower(temp[i]);
    return temp;
}

bool Item::operator==(Item& other) //passing other by reference so it can be modified, faster since we passing a class
{
    //operator overloading for == helps compare the object text to other object of same type (item)
    //compares lowercase text to each other
    bool text_equal = str_tolower(_tasktext) == str_tolower(other.text());
    bool done_equal = _done == other.is_done();
    bool priority_equal = str_tolower(_priority) == str_tolower(other.priority());
    return text_equal && done_equal && priority_equal;
}

/*
bool Item::operator!=(Item& other) //passing other by reference so it can be modified, faster since we passing a class
{
    //operator overloading for == helps compare the object text to other object of same type (item)
    //compares lowercase text to each other
    bool text_equal = str_tolower(_tasktext) != str_tolower(other.text());
    bool done_equal = _done != other.is_done();
    bool priority_equal = str_tolower(_priority) != str_tolower(other.priority());
    return text_equal && done_equal && priority_equal;
}*/
