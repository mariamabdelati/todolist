#include "filehandler.h"
#include "list.h"

void FileHandler::write(vector<string> list){
    /* 
    ofstream: output file stream (writes out to a file)
    */
    ofstream tasklist;
    tasklist.open("lists.txt");
    if(tasklist.is_open()){
        //this will store all the list items to the db file 
        for(int line_index=0; line_index < (int)list.size(); line_index++){
            tasklist << list[line_index] << "\n";
        }
    }
    else{
        cout << "cannot open file for writing.\n";
    }

    tasklist.close();
}

void FileHandler::read_file(){
    string line;
    /*
    ifstream: input file stream (read in from a file)
    */
    readlist.clear();
    ifstream tasklist;
    tasklist.open("lists.txt");
    if (tasklist.is_open()){
        while(getline(tasklist,line,'\n')){ //character definition in single quotes
            if (line == "") continue;
		    List List(line);
		    readlist.push_back(line);
        }
    }
    else {
        cout << "cannot open file for reading.\n";
    }

    tasklist.close();
}