#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
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
    vector<Item> list;
};