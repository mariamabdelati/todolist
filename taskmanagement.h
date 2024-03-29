#pragma once
#include <iostream>
#include <iomanip>
#include "databasemanagement.h"


using namespace std;

class TaskManagement : public DatabaseManagement
{
public:;

    //TaskManagement();
    TaskManagement(const char *filename);
    ~TaskManagement();


    static void organize(); //static method since it is accessed from within the class and no object requires it
    static void enter();
    void display();
    void create();

    void add();
    void del();
    void edit();
    void view_incomplete();
    void view_complete();
    void status(int);
    bool status_check(int);
    void set_priority();
    bool priority_check();
    void priority_sort_by_high();
    void priority_sort_by_low();


    void set_date();
    bool date_check();
    void date_sort_asc();
    void date_sort_desc();
    void set_category();
    bool category_check(int x);
    void view_category();

    int get_count();
    //::list<Item> list1;

};