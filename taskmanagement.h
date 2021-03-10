#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include "item.h"

using namespace std;

class TaskManagement
{
public:
    TaskManagement();
    TaskManagement(const char*);
    ~TaskManagement();

    void read();
    void display();
    void create();
    void write();
    void add();
    void del();
    void view_incomplete();
    void view_complete();
    void reset();
    void check();
    void uncheck();

    int get_count();

private:
    const char* filename;
    vector<Item> list;
};