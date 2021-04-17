#pragma once
#include <string>
#include <cctype>

using namespace std;

class Item
{
public:
    Item();
    Item(string);
    ~Item();

    string text();
    void done();
    void notdone();
    bool is_done();
    void highpriority();
    void mediumpriority();
    void lowpriority();
    void nopriority();
    void cathome();
    void catwork();
    void catentertainment();
    void catother();
    void catnone();
    string getpriority();
    string priority();
    string getcategory();

    void setDay(string);
    void setMonth(string);
    void setYear(string);
    string getDay();
    string getMonth();
    string getYear();

    bool operator==(Item&);

private:
    string _tasktext;
    bool _done;
    string _priority;
    string _dateDay;
    string _dateMonth;
    string _dateYear;
    string _date;
    string _category;

private:
    static string str_tolower(string);
};