#include<iostream>
#include<vector>
#include<fstream>
#include<string>

using namespace std;

class Task {
private:
protected:
public:
    Task() {
        //constructor
    }
    ~Task() {
        //destructor
    }
    vector<string> list;

    void Add_Task(vector<string> list);
    void Remove_Task(vector<string> list);
};
