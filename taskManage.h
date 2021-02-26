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

    //void start_todo();
    void add();
    void remove();
    void view_tocomplete();
    int get_count();
};
