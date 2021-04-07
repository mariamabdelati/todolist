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

    //void read();
    //int connect();
    static int callback(void* NotUsed, int argc, char** argv, char** azColName);


    //int creat();
    void deleteData();
    void insertData();
    void inData();
    void inserData(int, string, string, string);
    void selectData(DatabaseManagement obj);
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
    DatabaseManagement *s; // will hold the object


    int callbackAux(int argc, char ** argv, char ** azColName);
};