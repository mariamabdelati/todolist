#pragma once
#include <iostream>
#include <list>
#include <sqlite3.h>
#include "item.h"


using namespace std;

class DatabaseManagement
{
public:
    //DatabaseManagement();
    DatabaseManagement(const char*);
    ~DatabaseManagement();


    static void deleteData();
    void insertData();
    //void appendData(Item, int);
    void selectData();
    void selectPriority(int);
    void selectDate(int x);

    //void updateData(Item, int, int);

protected:
    const char* filename;
    sqlite3 *db;
    char *ErrorMessage = nullptr;
    int not_connected;
    string sql2;
    list<Item> list;

};