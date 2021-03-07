#include<iostream>
#include<vector>
#include<fstream>
#include<string>

using namespace std;

class FileHandler {
private:
protected:
public:
    FileHandler() {
        //constructor
    }
    ~FileHandler() {
        //destructor
    }

    vector<string> list;
    string name;

    void write(vector<string> list); //passing the list from the other class 
    void read_file();
};

