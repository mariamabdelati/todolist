#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include "item.h"
#include "filemanagement.h"


using namespace std;

class TaskManagement : public FileManagement
{
public:;

    TaskManagement();
    TaskManagement(const char *filename);
    ~TaskManagement();


    //void read();
    void display();
    void create();
    //void write();
    void add();
    void del();
    void edit();
    void view_incomplete();
    void view_complete();
    //void reset();
    void check();
    void uncheck();
    void set_priority();

    int get_count();

};