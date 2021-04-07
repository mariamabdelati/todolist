#pragma once
#include <iostream>
#include <iomanip>
#include <iterator>
#include "item.h"
#include "filemanagement.h"


using namespace std;

class TaskManagement : public FileManagement
{
public:;

    TaskManagement();
    TaskManagement(const char *filename);
    ~TaskManagement();


    static void organize(); //static method since it is accessed from within the class and no object requires it
    void display();
    void create();

    void add();
    void del();
    void edit();
    void view_incomplete();
    void view_complete();
    void check();
    void uncheck();
    void set_priority();
    void priority_sort_by_low();
    void priority_sort_by_high();
    bool priority_check();

    int get_count();

    ;

};
