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

private:
    string _text;
    bool _done;
    string _priority;

private:
    string str_tolower(string);
};