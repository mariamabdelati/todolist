#include "item.h"

Item::Item()
{
    _tasktext = "";
    _done = false;
    _priority = "0";
    _dateDay = "00";
    _dateMonth = "00";
    _dateYear = "0000";
    _date =  _dateYear + "-" + _dateMonth + "-" + _dateDay;
    _category = "none";
}

Item::Item(const string& item)
{
    string::size_type startfalse = item.find("false");

    //if found, the index for when the string starts is stored
    //if not found, the index stored is -1

    string::size_type starttrue = item.find("true");
    string str;
    string pr;
    string dt;
    string ct;

    if (startfalse == std::string::npos && starttrue == std::string::npos) { // item is user input (no true or false)
        str = item;
        _done = false;
        pr = "0";
        dt = "0000-00-00";
        ct = "none";
    } else if (startfalse == std::string::npos) //item has true
    {
        str = item.substr(0, starttrue - 1);
        _done = true;
        string substr;
        int count = 0;
        string temp = item.substr(starttrue + 5);
        for (char & i : temp)
        {
            if (i != ' ')
            {
                substr += i;
            } else
            {
                ++count;
                if (count == 1)
                {
                    if (substr.empty())
                    {
                        pr = "0";
                    }
                    else {
                        pr = substr;
                    }
                    substr = "";
                } else if (count == 2) {
                    if (substr.empty()) {
                        dt = "0000-00-00";
                    } else dt = substr;
                    substr = "";
                }
            }
        }
        if (substr.empty())
            ct = "none";
        else ct = substr;
    } else if (starttrue == std::string::npos) //item has false
    {
        str = item.substr(0, startfalse - 1);
        _done = false;
        string substr;
        int count = 0;
        string temp = item.substr(startfalse + 6);
        for (char &i : temp) {
            if (i != ' ') {
                substr += i;
            } else {
                ++count;
                if (count == 1) {
                    if (substr.empty()) {
                        pr = "0";
                    } else {
                        pr = substr;
                    }
                    substr = "";
                } else if (count == 2) {
                    if (substr.empty()) {
                        dt = "0000-00-00";
                    } else dt = substr;
                    substr = "";
                }
            }
        }
        if (substr.empty())
            ct = "none";
        else ct = substr;
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
    _tasktext = x;
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

//these functions set the category for a task
void Item::nocategory() {
    _category = "none";
}
void Item::othercategory() {
    _category = "other";
}
void Item::homecategory() {
    _category = "home";
}
void Item::workcategory() {
    _category = "work";
}
void Item::entertainmentcategory() {
    _category = "entertainment";
}


/*//this function returns the category for a task
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
}*/

string Item::category()
{
    if (_category == "none")
    {
        string c;
        return c;
    } else
        return _category;
}

//these functions set the due date
void Item::setDay(const string& day)
{
    if (day.length() != 2)
    {
        _dateDay = "0" + day;
    } else _dateDay = day;
}
void Item::setMonth(const string& month)
{
    if (month.length() != 2)
    {
        _dateMonth = "0" + month;
    } else _dateMonth = month;

}
void Item::setYear(string year)
{
    _dateYear = year;
}

/*void Item::setDate(const string& a, const string& b, const string& c) {
    _date = c + "-" + b + "-" + a;
}*/
void Item::setDate() {
    _date = _dateYear + "-" + _dateMonth + "-" + _dateDay;
}

string Item::date() {
    if (_date == "0000-00-00")
    {
        string c;
        return c;
    } else
        return _date;
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
    bool date_equal = str_tolower(_date) == str_tolower(other.date());
    bool category_equal = str_tolower(_category) == str_tolower(other.category());
    return text_equal && done_equal && priority_equal && date_equal && category_equal;
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

/*Item::Item(const string& item)
{

    int startfalse = int(item.find("false"));
    *//*
    if found, the index for when the string starts is stored
    if not found, the index stored is -1
    *//*
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
        dt = item.substr(startfalse + 8, startfalse + 17);
        ct = item.substr(startfalse + 19, startfalse + 22);
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
}*/