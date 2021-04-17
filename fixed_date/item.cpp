#include "item.h"

#include <utility>
Item::Item()
{
    _tasktext = "";
    _done = false;
    _priority = "0";
    _dateDay = "00";
    _dateMonth = "00";
    _dateYear = "0000";
    _date = _dateDay + "/" + _dateMonth + "/" + _dateYear;
    _category = "cat";
}

Item::Item(const string& item)
{

    int startfalse = int(item.find("false"));
    /*
    if found, the index for when the string starts is stored
    if not found, the index stored is -1
    */
    int starttrue = int(item.find("true"));
    string str;
    string pr;
    string dt;
    string ct;

    if (startfalse > -1 && starttrue == -1) // item has false
    {
        //this stores the line substring without the word done/not done (subtract one to end right before the index of done)
        str = item.substr(0, startfalse - 1);
        _done = false;
        pr = item.substr(startfalse + 6, startfalse + 7);
        dt = item.substr(startfalse + 9, startfalse + 18);
        ct = item.substr(startfalse + 20, startfalse + 23);
    }
    else if (starttrue > -1 && startfalse == -1) { // item has true
        str = item.substr(0, starttrue - 1);
        _done = true;
        pr = item.substr(starttrue + 5, starttrue + 6);
        dt = item.substr(starttrue + 8, starttrue + 17);
        ct = item.substr(starttrue + 19, starttrue + 22);
    }
    else if (startfalse == -1 && starttrue == -1) { // item is user input (no true or false)
        str = item;
        _done = false;
        pr = "0";
        dt = "00/00/0000";
        ct = "cat0";
    }

    _tasktext = str;
    _priority = pr;
    _date = dt;
    _category = ct;
}

Item::~Item()
{
    // do nothing
}

void Item::set_text(string x)
{
    _tasktext = std::move(x);
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
bool Item::is_done() const
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

//this function returns the category for a task
string Item::getcategory()
{
    string p;
    if (_category == "cat0")
    {
        p = "none";
    }
    else if (_category == "cat1")
    {
        p = "other";
    }
    else if (_category == "cat2")
    {
        p = "home";
    }
    else if (_category == "cat3")
    {
        p = "work";
    }
    else if (_category == "cat4")
    {
        p = "entertainment";
    }
    return p;
}

string Item::category()
{
    return _category;
}

//these functions get the due date
/*string Item::getDay() {
    return _dateDay;
}
string Item::getMonth() {
    return _dateMonth;
}
string Item::getYear() {
    return _dateYear;
}*/

string Item::date() {
    return _date;
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

//these functions set the due date
void Item::setDay(const string& day)
{
    while (day.length() != 2)
        _dateMonth = "0" + day;
}
void Item::setMonth(const string& month)
{
    while (month.length() != 2)
        _dateMonth = "0" + month;
}
void Item::setYear(string year)
{
    _dateYear = std::move(year);
}





//this changes the text to lowercase so it is easier to deal with
string Item::str_tolower(string str)
{
    string temp = std::move(str);
    for (char & i : temp)
        i = char(tolower(i));
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
