#pragma once
#include <fstream>
#include <list>
//#include <vector>
#include <string>
#include <cstdio>
#include "item.h"


using namespace std;

class FileManagement
{
public:
    FileManagement();
    FileManagement(const char*);
    ~FileManagement();

    void read();
    void write();
    void reset();

protected:
    const char* filename;
    //vector<Item> list;
    list<Item> list;
};