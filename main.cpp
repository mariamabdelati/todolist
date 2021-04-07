#include <iostream>
#include "taskmanagement.h"

using namespace std;

int main(int argc, char const* argv[])
/*
int argc is used to count the arguments that the user has inputed
int argv stores the values in an array which can let us print it if we want to
*/
{
    //this creates an object of type TaskManagement
    TaskManagement tasks("todolist.txt");
    bool exit = false;
    while (!exit) {
        //this reads the items in the file
        tasks.read();

        //this makes sure there are tasks to display in the txt
        if (tasks.get_count() > 0) {
            tasks.display();
            cout << endl <<endl;

            cout << "---- MENU ----" << endl << endl;
            cout << "1) Add Task" << endl;
            cout << "2) Remove Task" << endl;
            cout << "3) Edit Task" << endl;
            cout << "4) Mark Off Task" << endl;
            cout << "5) Unmark Task" << endl;
            cout << "6) Reset Current List" << endl;
            cout << "7) View Tasks" << endl;
            cout << "8) Set Priority" << endl;
            cout << "9) Sort by Priority" << endl;
            cout << "10) Quit Program" << endl << endl;
            cout << "--------------" << endl;
            cout << "Choice: ";

            try
            {
                string choice;
                getline(cin, choice);

                if (choice.empty())
                {
                    throw invalid_argument("Invalid Choice, Choice cannot be Empty");
                }

                for (char c : choice)
                {
                    if (isalpha(c))
                    {
                        throw invalid_argument("Invalid Choice, Choice cannot contain an Alphabet Character.");
                    } else if (isspace(c))
                    {
                        throw invalid_argument("Invalid Choice, Choice cannot contain Spaces.");
                    } else if (ispunct(c))
                    {
                        throw invalid_argument("Invalid Choice, Choice cannot contain Punctuation.");
                    }
                }
                /*if (choice[0] == ' ' || choice[choice.length()-1] == ' ')
                {
                    throw 0;
                }*/
                if (stoi(choice) > 10 || stoi(choice) < 1)
                    throw invalid_argument("Invalid Choice, Choice out of Range.");

                if (choice == "1") {
                    tasks.add();
                } else if (choice == "2") {
                    tasks.del();
                } else if (choice == "3") {
                    tasks.edit();
                } else if (choice == "4") {
                    tasks.check();
                } else if (choice == "5") {
                    tasks.uncheck();
                } else if (choice == "6") {
                    tasks.reset();
                } else if (choice == "7") {

                    bool invalid = true;
                    while (invalid)
                    {
                    cout << "--------------" << endl << endl;
                    cout << "The Following Views are available \n";
                    cout << "--------------" << endl;
                    cout << "1) To Complete \n2) Completed \n" ;
                    cout << "--------------" << endl;
                    cout << "Choice: ";

                        try {
                            string view;
                            getline(cin, view);

                            if (view.empty())
                            {
                                break;
                            }
                            for (char c : view) {
                                if (isalpha(c))
                                {
                                    throw invalid_argument("Invalid Choice, Choice cannot contain an Alphabet Character.");
                                } else if (isspace(c))
                                {
                                    throw invalid_argument("Invalid Choice, Choice cannot contain Spaces.");
                                } else if (ispunct(c))
                                {
                                    throw invalid_argument("Invalid Choice, Choice cannot contain Punctuation.");
                                }
                            }

                            if (stoi(view) > 2 || stoi(view) < 1)
                                throw invalid_argument("Invalid Choice, Choice out of Range.");

                            if (view == "1") {
                                invalid = false;
                                tasks.view_incomplete();
                            } else if (view == "2") {
                                //function from class runs to view the tasks that are done
                                invalid = false;
                                tasks.view_complete();
                            }
                        }catch (invalid_argument& e) {
                            cerr << e.what() << "\nPlease Enter the Number Corresponding to your Choice\n" << endl;
                        }
                    }

                } else if (choice == "8") {
                    tasks.set_priority();
                } else if (choice == "9") {
                    bool invalid = true; // another bool value to identify invalid input and keep looping
                    while (invalid) {
                        if (!tasks.priority_check())
                        {
                            break;
                        }
                        cout << "--------------" << endl << endl;
                        cout << "Sort by Priority\n";
                        cout << "--------------" << endl;
                        cout << "1) from High to Low \n2) from Low to High \n";
                        cout << "--------------" << endl;
                        cout << "Choice: ";

                        try { //checks for invalid input
                            string pr_sort;
                            getline(cin, pr_sort);

                            if (pr_sort.empty()) //the user can enter space to get out of the loop
                            {
                                break;
                            }
                            for (char c : pr_sort) {
                                if (isalpha(c)) {
                                    throw invalid_argument(
                                            "Invalid Choice, Choice cannot contain an Alphabet Character.");
                                } else if (isspace(c)) {
                                    throw invalid_argument("Invalid Choice, Choice cannot contain Spaces.");
                                } else if (ispunct(c)) {
                                    throw invalid_argument("Invalid Choice, Choice cannot contain Punctuation.");
                                }
                            }

                            if (stoi(pr_sort) > 2 || stoi(pr_sort) < 1)
                                throw invalid_argument("Invalid Choice, Choice out of Range.");

                            if (pr_sort == "1") {
                                invalid = false;
                                tasks.priority_sort_by_high();
                            } else if (pr_sort == "2") {
                                //function from class runs to view the tasks that are done
                                invalid = false;
                                tasks.priority_sort_by_low();
                            }
                        } catch (invalid_argument &e) { // catches the invalid argument
                            cerr << e.what() << "\nPlease Enter the Number Corresponding to your Choice\n" << endl;
                            //what() returns a pointer with content related to the exception
                        }
                    }
                }
                else if (choice == "10")
                {
                    exit = true;
                }
            }
            catch (invalid_argument& e) {
                cerr << e.what() << "\nPlease Enter the Number Corresponding to your Choice\n" << endl;
            }
            

        } else {
            //program automatically creates new list when first started or reset
            cout << "A New List Has Been Created ..." << endl;
            cout << "Press Enter to finish adding tasks." << endl;
            tasks.create();

            cout << endl;
            //new tasks displayed
            //tasks.display();

            //tasks entered are saved into the file
            tasks.write();
        }
    }

    return 0;
}
