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
    string getpriority();
    string priority();

    bool operator==(Item&);
    //bool operator!=(Item&);

    static string str_tolower(string);

private:
    string _tasktext;
    bool _done;
    string _priority;

};