#pragma once
#include <string>
#include <cctype>

using namespace std;

class Item
{
public:
    Item();
    Item(const string&);
    ~Item();

    void set_text(string x);
    string text();
    void done();
    void notdone();
    bool is_done() const;
    void highpriority();
    void mediumpriority();
    void lowpriority();
    void nopriority();
    string getpriority();
    string priority();

    void homecategory();
    void workcategory();
    void entertainmentcategory();
    void othercategory();
    void nocategory();
    //string getcategory();
    string category();



    void setDay(const string&);
    void setMonth(const string&);
    void setYear(string);
    void setDate();
    string date();

    bool operator==(Item&);
    //bool operator!=(Item&);

    static string str_tolower(string);

private:
    string _tasktext;
    bool _done;
    string _priority;
    string _dateDay;
    string _dateMonth;
    string _dateYear;
    string _date;
    string _category;

};
