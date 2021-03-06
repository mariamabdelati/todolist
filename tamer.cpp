#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    string line;
    ifstream t("tasks.txt");
    ofstream ft("ftasks.txt");
    string searchword = "//";

    if (t.is_open()) {
        cout << "COMPLETED TASKS:" << endl;
        while (!t.eof()) {
            getline(t, line);
            if (line.find(searchword) != string::npos) {
                ft << line << "\n";
                cout << line << "\n";
            }
        }
    }
    ft.close();
    t.close();
}