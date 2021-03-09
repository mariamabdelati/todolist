//
// Created by Mariam on 3/9/21.
//

#ifndef TODOLISTMASTER_TODO_LIST_H
#define TODOLISTMASTER_TODO_LIST_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include "item.h"

using namespace std;

class TodoList
{
public:
    TodoList();
    TodoList(const char*);
    ~TodoList();

    void read();
    void display();
    void create();
    void save();
    void add();
    void clear();
    void check();

    int get_count();

private:
    const char* filename;
    vector<Item> list;
};
#endif //TODOLISTMASTER_TODO_LIST_H
