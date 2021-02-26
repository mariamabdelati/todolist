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

    string AddTaskInput;
    string RemoveTaskInput;

    void Add_Task(string AddTaskInput);
    void read_file(string RemoveTaskInput);
};
