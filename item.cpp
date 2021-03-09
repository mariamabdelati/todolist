//
// Created by Mariam on 3/9/21.
//

#include "item.h"
Item::Item()
{
    _text = "";
    _done = false;
}

Item::Item(string item)
{
    int startf = item.find("false");
    /*
    if found, the index for when the string starts is stored
    if not found, the index stored is -1
    */
    int startt = item.find("true");
    string str;

    if (startf > -1 && startt == -1) // item has false
    {
        //this stores the line substring without the word done/not done (subtract one to end right before the index of done)
        str = item.substr(0, startf - 1);
        _done = false;
    } else if (startt > -1 && startf == -1) { // item has true
        str = item.substr(0, startt - 1);
        _done = true;
    } else if (startf == -1 && startt == -1) { // item is user input (no true or false)
        str = item;
        _done = false;
    }

    _text = str;
}

Item::~Item()
{
    // do nothing
}

//this function will return the line text
string Item::text()
{
    return _text;
}

//this function marks off a task
void Item::done()
{
    _done = true;
}

//this function identifies if a task is done
bool Item::is_done()
{
    return _done;
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
    bool text_equal = str_tolower(_text) == str_tolower(other.text());
    bool done_equal = _done == other.is_done();
    return text_equal && done_equal;
}