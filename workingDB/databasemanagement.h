#pragma once
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <cstdio>
#include <sqlite3.h>
#include "item.h"


using namespace std;

class DatabaseManagement
{
public:
    //DatabaseManagement();
    DatabaseManagement(const char*);
    ~DatabaseManagement();
    void deleteData();
    void insertData();
    void selectData();
    //void updateData(int, const string&);
    //void reset();

protected:
    const char* filename;
    sqlite3 *db;
    char *ErrorMessage = 0;
    int not_connected;
    string sql2;
    string sql1;
    list<Item> list;

};