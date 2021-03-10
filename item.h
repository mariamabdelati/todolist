//
// Created by Mariam on 3/9/21.
//

#ifndef TODOLISTMASTER_ITEM_H
#define TODOLISTMASTER_ITEM_H
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

    static bool operator==(Item&);

private:
    string _text;
    bool _done;

private:
    string str_tolower(string);
};

#endif //TODOLISTMASTER_ITEM_H
