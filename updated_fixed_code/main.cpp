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
    TaskManagement tasks("todolist.db");
    bool exit = false;
    while (!exit) {
        //this reads the items in the file
        //TaskManagement::selectData(tasks);
        tasks.selectData();
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
            cout << "10) Set Date" << endl;
            cout << "11) Sort by Date" << endl;
            cout << "12) Set Category" << endl;
            cout << "13) Quit Program" << endl;
            cout << "14) Restore Original List" << endl << endl;
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
                    if (!isdigit(c)) {
                        throw invalid_argument(
                                "Invalid Choice, Choice cannot contain an Alphabet Character, Spaces, Symbols or Punctuation");
                    }
                }
                /*if (choice[0] == ' ' || choice[choice.length()-1] == ' ')
                {
                    throw 0;
                }*/
                if (stoi(choice) > 13 || stoi(choice) < 1)
                    throw invalid_argument("Invalid Choice, Choice out of Range.");


                if (choice == "1") {
                    tasks.add();
                } else if (choice == "2") {
                    tasks.del();
                } else if (choice == "3") {
                    bool invalid = true;
                    while (invalid)
                    {
                        cout << "--------------" << endl << endl;
                        cout << "The Following Edits are available \n";
                        cout << "--------------" << endl;
                        cout << "1) Edit Line (removes done status and priority) \n2) Edit Task ONLY \n" ;
                        cout << "--------------" << endl;
                        cout << "Choice: ";

                        try {
                            string edit;
                            getline(cin, edit);

                            if (edit.empty())
                            {
                                break;
                            }
                            for (char c : edit) {
                                if (!isdigit(c)) {
                                    throw invalid_argument(
                                            "Invalid Choice, Choice cannot contain an Alphabet Character, Spaces, Symbols or Punctuation");
                                }
                            }

                            if (stoi(edit) > 2 || stoi(edit) < 1)
                                throw invalid_argument("Invalid Choice, Choice out of Range.");

                            if (edit == "1") {
                                invalid = false;
                                tasks.edit(1);
                            } else if (edit == "2") {
                                //function from class runs to view the tasks that are done
                                invalid = false;
                                tasks.edit(2);
                            }
                        }catch (invalid_argument& e) {
                            cerr << e.what() << "\nPlease Enter the Number Corresponding to your Choice\n" << endl;
                        }
                    }
                } else if (choice == "4") {
                    tasks.status(1);
                } else if (choice == "5") {
                    tasks.status(2);
                } else if (choice == "6") {
                    tasks.deleteData();
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
                                if (!isdigit(c)) {
                                    throw invalid_argument(
                                            "Invalid Choice, Choice cannot contain an Alphabet Character, Spaces, Symbols or Punctuation");
                                }
                            }

                            if (stoi(view) > 2 || stoi(view) < 1)
                                throw invalid_argument("Invalid Choice, Choice out of Range.");

                            if (view == "1") {
                                if (!tasks.status_check(2))
                                {
                                    break;
                                } else {
                                    invalid = false;
                                    tasks.view_incomplete();
                                }
                            } else if (view == "2") {
                                //function from class runs to view the tasks that are done
                                if (!tasks.status_check(1)) {
                                    break;
                                }else {
                                    invalid = false;
                                    tasks.view_complete();
                                }
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
                                if (!isdigit(c)) {
                                    throw invalid_argument(
                                            "Invalid Choice, Choice cannot contain an Alphabet Character, Spaces, Symbols or Punctuation");
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
                else if (choice == "10") {
                    tasks.set_date();
                }else if (choice == "11") {
                    bool invalid = true;
                    while (invalid) {
                        if (!tasks.date_check())
                        {
                            break;
                        }
                        cout << "--------------" << endl << endl;
                        cout << "The Following Sort by Dates are available \n";
                        cout << "--------------" << endl;
                        cout << "1) DESCENDING \n2) ASCENDING \n";
                        cout << "--------------" << endl;
                        cout << "Choice: ";

                        try {
                            string view;
                            getline(cin, view);

                            if (view.empty()) {
                                break;
                            }
                            for (char c : view) {
                                if (!isdigit(c)) {
                                    throw invalid_argument(
                                            "Invalid Choice, Choice cannot contain an Alphabet Character, Spaces, Symbols or Punctuation");
                                }
                            }

                            if (stoi(view) > 2 || stoi(view) < 1)
                                throw invalid_argument("Invalid Choice, Choice out of Range.");

                            if (view == "1") {
                                invalid = false;
                                tasks.date_sort_desc();
                            } else if (view == "2") {
                                //function from class runs to view the tasks that are done
                                invalid = false;
                                tasks.date_sort_asc();
                            }
                        } catch (invalid_argument &e) {
                            cerr << e.what() << "\nPlease Enter the Number Corresponding to your Choice\n" << endl;
                        }
                    }
                }else if (choice == "12") {
                    tasks.set_category();
                }
                else if (choice == "13")
                {
                    tasks.restore_list();
                    exit = true;
                }
                else if (choice == "14")
                {
                    if (!tasks.restore_list())
                    {
                        throw invalid_argument("List has not been Sorted");
                    } else
                    {
                        tasks.restore_list();
                    }
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
            tasks.DatabaseManagement::insertData();
        }
    }

    return 0;
}