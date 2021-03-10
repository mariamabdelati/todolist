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

    bool operator==(Item&);

private:
    string _text;
    bool _done;

private:
    string str_tolower(string);
};

