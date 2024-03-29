#include "databasemanagement.h"
/*DatabaseManagement::DatabaseManagement()
{
    filename = nullptr; //file is null
}*/
DatabaseManagement::DatabaseManagement(const char* filename)
{
    not_connected = sqlite3_open(filename, &db);

    if( not_connected ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));

    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    sqlite3_close(db);

}
DatabaseManagement::~DatabaseManagement()= default;

string quotesql( const string& s ) {
    return string("'") + s + string("'");
}


void DatabaseManagement::deleteData()
{
    string sql3 = "DELETE FROM TODO";

    sqlite3* db;
    try
    {
        sqlite3_open("todolist.db", &db);

        char* messageError;
        int exit = sqlite3_exec(db, sql3.c_str(), nullptr, nullptr, &messageError);

        if (exit != SQLITE_OK)
        {
            //cerr << "Error Delete" << endl;
            sqlite3_free(messageError);
        } else
        {
            //cout << "Delete Successful" << endl;
        }
        sqlite3_close(db);
    } catch (const exception & e)
    {
        cerr << e.what();
    }
}

void DatabaseManagement::appendData(Item item, int append) {

    sql2 = "INSERT INTO TODO (ID, TASK,STATUS,PRIORITY,DUEDATE,CATEGORY) VALUES (" + quotesql(to_string(append)) + "," + quotesql(item.text()) + "," + quotesql((item.is_done() ? "true" : "false")) + "," + quotesql(item.priority()) + "," + quotesql(item.date()) + "," + quotesql(item.category()) + ");";
        try
        {
            sqlite3_open("todolist.db", &db);

            char* messageError;
            int exit = sqlite3_exec(db, sql2.c_str(), nullptr, nullptr, &messageError);

            if (exit != SQLITE_OK)
            {
                //cerr << "Error Insert" << endl;
                sqlite3_free(messageError);
            } else
            {
                //cout << "Insert Successful" << endl;
            }
            sqlite3_close(db);
        } catch (const exception & e)
        {
            cerr << e.what();
        }

}

void DatabaseManagement::insertData() {

    deleteData();

    int insert = 0;
    for (Item item : list)
    {
        if (item.text().empty()) continue;
        else insert++;
        sql2 = "INSERT INTO TODO (ID, TASK,STATUS,PRIORITY,DUEDATE,CATEGORY) VALUES (" + quotesql(to_string(insert)) + "," + quotesql(item.text()) + "," + quotesql((item.is_done() ? "true" : "false")) + "," + quotesql(item.priority()) + "," + quotesql(item.date()) + "," + quotesql(item.category()) + ");";
        try
        {
            sqlite3_open("todolist.db", &db);

            char* messageError;
            int exit = sqlite3_exec(db, sql2.c_str(), nullptr, nullptr, &messageError);

            if (exit != SQLITE_OK)
            {
                //cerr << "Error Insert" << endl;
                sqlite3_free(messageError);
            } else
            {
                //cout << "Insert Successful" << endl;
            }
            sqlite3_close(db);
        } catch (const exception & e)
        {
            cerr << e.what();
        }
    }
}

void DatabaseManagement::selectData()
{
    sqlite3 *db;
    sqlite3_stmt *stmt = nullptr;


    if (sqlite3_open("todolist.db", &db) == SQLITE_OK)
    {
        sqlite3_prepare( db, "SELECT * from TODO;", -1, &stmt, nullptr );//preparing the statement
        sqlite3_step( stmt );//executing the statement
        //char * str = (char *) sqlite3_column_text( stmt, 0 ); //reading the 1st column of the result
    }
    else
    {
        cout << "Failed to open db\n";
    }


    list.clear();
    while( sqlite3_column_text( stmt, 0 ) )
    {
        string line;
        for( int i = 1; i < 6; i++ )
        {
            line += std::string( (char *)sqlite3_column_text( stmt, i ));
            if (i != 5)
                line += " ";
        }

        sqlite3_step( stmt );
        Item item(line);
        list.emplace_back(line);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void DatabaseManagement::selectPriority(int x)
{
    sqlite3 *db;
    sqlite3_stmt *stmt = nullptr;


    if (sqlite3_open("todolist.db", &db) == SQLITE_OK)
    {
        if (x == 1)
        {
            sqlite3_prepare( db, "SELECT * FROM TODO ORDER BY PRIORITY DESC;", -1, &stmt, nullptr );
        } else if (x == 2)
        {
            sqlite3_prepare( db, "SELECT * FROM TODO ORDER BY PRIORITY ASC;", -1, &stmt, nullptr );
        }

        sqlite3_step( stmt );
    }
    else
    {
        cout << "Failed to open db\n";
    }

    list.clear();
    while( sqlite3_column_text( stmt, 0 ) )
    {
        string line;
        for( int i = 1; i < 6; i++ )
        {
            line += std::string( (char *)sqlite3_column_text( stmt, i ));
            if (i != 5)
                line += " ";
        }
        sqlite3_step( stmt );
        Item item(line);
        list.emplace_back(line);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void DatabaseManagement::selectDate(int x)
{
    sqlite3 *db;
    sqlite3_stmt *stmt = nullptr;


    if (sqlite3_open("todolist.db", &db) == SQLITE_OK)
    {
        if (x == 1)
        {
            sqlite3_prepare( db, "SELECT * FROM TODO ORDER BY date(DUEDATE) DESC", -1, &stmt, nullptr );
        } else if (x == 2)
        {
            sqlite3_prepare( db, "SELECT * FROM TODO ORDER BY date(DUEDATE) ASC", -1, &stmt, nullptr );
        }

        sqlite3_step( stmt );
    }
    else
    {
        cout << "Failed to open db\n";
    }

    list.clear();
    while( sqlite3_column_text( stmt, 0 ) )
    {
        string line;
        for( int i = 1; i < 6; i++ )
        {
            line += std::string( (char *)sqlite3_column_text( stmt, i ));
            if (i != 5)
                line += " ";
        }
        sqlite3_step( stmt );
        Item item(line);
        list.emplace_back(line);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

/*void DatabaseManagement::updateData(Item item, int taskmanage, int id)
{
    int exit = sqlite3_open(filename, &db);

    if (taskmanage == 1)
    {
        sql2 = "UPDATE TODO SET TASK =" + quotesql(item.text()) + ", STATUS =" + quotesql((item.is_done() ? "true" : "false")) + ", PRIORITY =" + quotesql(item.priority()) + "WHERE ID =" + quotesql(to_string(id)) + ";";
    } else if (taskmanage == 2)
    {
        sql2 = "UPDATE TODO SET PRIORITY =" + quotesql(item.priority()) + "WHERE ID =" + quotesql(to_string(id)) + ";";
    } else if (taskmanage == 3)
    {
        sql2 = "UPDATE TODO SET STATUS =" + quotesql((item.is_done() ? "true" : "false")) + " WHERE ID =" + quotesql(to_string(id)) + ";";
                //"UPDATE TODO SET STATUS =" + quotesql((item.is_done() ? "true" : "false")) + "WHERE ID =" + quotesql(to_string(id)) + ";";
        exit = sqlite3_exec(db, sql2.c_str(), nullptr, nullptr, &ErrorMessage);
    } else if (taskmanage == 4)
    {
        sql2 = "UPDATE TODO SET CATEGORY =" + quotesql( item.category()) + "WHERE ID =" + quotesql(to_string(id)) + ";";
    } else if (taskmanage == 5)
    {
        sql2 = "UPDATE TODO SET DUEDATE =" + quotesql((item.date())) + "WHERE ID =" + quotesql(to_string(id)) + ";";
    }


    if (exit != SQLITE_OK)
    {
        cerr << "Error Update" << endl;
        sqlite3_free(ErrorMessage);
    } else
    {
        cout << "Records updated Successfully" << endl;
    }
    sqlite3_close(db);
}*/

