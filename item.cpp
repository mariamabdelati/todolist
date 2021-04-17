#include "item.h"
Item::Item()
{
    _tasktext = "";
    _done = false;
    _priority = "pr0";
    _dateDay = "00";
    _dateMonth = "00";
    _dateYear = "0000";
    _date = _dateDay + _dateMonth + _dateYear;
    _category = "cat0";
}

Item::Item(string item)
{
    long startfalse = item.find("false");
    long starttrue = item.find("true");
    string str;
    string pr;
    string dt;
    string cat;

    if (startfalse > -1 && starttrue == -1) // item has false
    {
        str = item.substr(0, startfalse - 1); //this stores the line substring without the word done/not done (subtract one to end right before the index of done)
        _done = false;
        pr = item.substr(startfalse + 6, startfalse + 9);
        //dt = item.substr(startfalse + 10, startfalse + 18);
        cat = item.substr(startfalse + 10, startfalse + 14);
    }
    else if (starttrue > -1 && startfalse == -1) { // item has true
        str = item.substr(0, starttrue - 1);
        _done = true;
        pr = item.substr(starttrue + 5, starttrue + 8);
        //dt = item.substr(starttrue + 9, starttrue + 17);
        cat = item.substr(starttrue + 9, starttrue + 13);
    }
    else if (startfalse == -1 && starttrue == -1) { // item is user input (no true or false)
        str = item;
        _done = false;
        pr = "pr0";
        //dt = "00000000";
        cat = "cat0";
    }
     
    _tasktext = str;
    _priority = pr;
    _date = dt;
    _category = cat;
}

Item::~Item()
{
    // do nothing
}

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
    _priority = "pr3";
}

//this function sets medium priority
void Item::mediumpriority()
{
    _priority = "pr2";
}

//this function sets low priority
void Item::lowpriority()
{
    _priority = "pr1";
}

//this function sets no priority
void Item::nopriority()
{
    _priority = "pr0";
}

//this function returns the priority of a specified item as a name rather than a value
string Item::getpriority()
{
    string p;
    if (_priority == "pr0")
    {
        p = "";
    }
    else if (_priority == "pr1")
    {
        p = "low";
    }
    else if (_priority == "pr2")
    {
        p = "medium";
    }
    else if (_priority == "pr3")
    {
        p = "high";
    }
    return p;
}

//this function returns the category for a task
string Item::getcategory()
{
    string p;
    if (_category == "none")
    {
        p = "cat0";
    }
    else if (_category == "other")
    {
        p = "cat1";
    }
    else if (_category == "home")
    {
        p = "cat2";
    }
    else if (_category == "work")
    {
        p = "cat3";
    }
    else if (_category == "entertainment")
    {
        p = "cat4";
    }
    return p;
}

//this function returns the priority of a specified item
string Item::priority()
{
    return _priority;
}

//these functions set the due date
void Item::setDay(string day)
{
    while (day.length() != 2)
        _dateMonth = 0 + stoi(day);
}
void Item::setMonth(string month)
{
    while (month.length() != 2)
        _dateMonth = 0 + stoi(month);
}
void Item::setYear(string year)
{
    _dateYear = year;
}

//these functions get the due date
string Item::getDay() {
    return _dateDay;
}
string Item::getMonth() {
    return _dateMonth;
}
string Item::getYear() {
    return _dateYear;
}

//these functions set the category for a task
void Item::catnone() {
    _category = "none";
}
void Item::catother() {
    _category = "other";
}
void Item::cathome() {
    _category = "home";
}
void Item::catwork() {
    _category = "work";
}
void Item::catentertainment() {
    _category = "entertainment";
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
    return text_equal && done_equal;
}