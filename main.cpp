#include "taskmanagement.h"

using namespace std;

int main()
{
    //this creates an object of type TaskManagement
    TaskManagement tasks("todolist.db");
    bool exit = false; // this boolean value checks if the user has chosen to exit the program
    //bool sorted = false;
    while (!exit) {
        //this reads the items in the file
        tasks.selectData();

        //this makes sure there are tasks to display in the list after it has been populated from the db
        if (tasks.get_count() > 0) {
            tasks.display();
            cout << endl <<endl;

            cout << "---- MENU ----" << endl << endl;
            cout << "1) Add Task" << endl;
            cout << "2) Remove Task" << endl;
            cout << "3) Edit Line or Task" << endl;
            cout << "4) Mark Off Task" << endl;
            cout << "5) Unmark Task" << endl;
            cout << "6) Reset Current List" << endl;
            cout << "7) View Tasks" << endl;
            cout << "8) Set Priority" << endl;
            cout << "9) Sort by Priority" << endl;
            cout << "10) Set Date" << endl;
            cout << "11) Sort by Date" << endl;
            cout << "12) Set Category" << endl;
            cout << "13) Quit Program" << endl << endl;
            cout << "--------------" << endl;
            cout << "Choice: ";

            try //handles errors for if the user doesn't enter a number
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

                if (stoi(choice) > 13 || stoi(choice) < 1)
                    throw invalid_argument("Invalid Choice, Choice out of Range.");


                if (choice == "1") {
                    tasks.add();
                } else if (choice == "2") {
                    tasks.del();
                } else if (choice == "3") {
                    tasks.edit();
                } else if (choice == "4") {
                    tasks.status(1);
                } else if (choice == "5") {
                    tasks.status(2);
                } else if (choice == "6") {
                    TaskManagement::deleteData();
                } else if (choice == "7") {

                    bool invalid = true;
                    while (invalid)
                    {

                        cout << "--------------" << endl << endl;
                        cout << "The Following Views are available \n";
                        cout << "--------------" << endl;
                        cout << "1) To Complete \n2) Completed \n3) Category\n" ;
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

                            if (stoi(view) > 3 || stoi(view) < 1)
                                throw invalid_argument("Invalid Choice, Choice out of Range.");

                            if (view == "1") {
                                //function from class runs to view the tasks that are not done
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
                            } else if (view == "3") {
                                if (!tasks.category_check(1)) {
                                    break;
                                }else {
                                    invalid = false;
                                    tasks.view_category();
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
                                //sorted = true;
                                tasks.priority_sort_by_high();
                            } else if (pr_sort == "2") {
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
                    //tasks.restore_list();
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

            //tasks entered are saved into the file
            tasks.DatabaseManagement::insertData();
        }
    }

    return 0;
}