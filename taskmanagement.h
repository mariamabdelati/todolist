#pragma once
#include <iostream>
#include <iomanip>
#include <iterator>
#include "item.h"
#include "databasemanagement.h"


using namespace std;

class TaskManagement : public DatabaseManagement
{
public:;

    //TaskManagement();
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

    int get_count();

};