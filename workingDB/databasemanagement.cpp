#include "databasemanagement.h"
/*DatabaseManagement::DatabaseManagement()
{
    filename = nullptr; //file is null
}*/
DatabaseManagement::DatabaseManagement(const char* filename)
{
    //this->filename = filename;
    not_connected = sqlite3_open(filename, &db);

    if( not_connected ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));

    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    sqlite3_close(db);

    /*
    this is a pointer, arrow is used to dereference, helps assign the variable of same name to itself
    */
}
DatabaseManagement::~DatabaseManagement()= default;

/*int createDB(const char* s)
{
    sqlite3* db;
    int exit = 0;
    exit = sqlite3_open(s, &db);

    sqlite3_close(db);
}

*/
string quotesql( const string& s ) {
    return string("'") + s + string("'");
}
/*int DatabaseManagement::connect()
{
    not_connected = sqlite3_open(filename, &db);

    if( not_connected ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    sqlite3_close(db);

    return(0);
}*/

void DatabaseManagement::deleteData()
{
    //connect();
    string sql3 = "DELETE FROM TODO";

    sqlite3* db;
    try
    {
        sqlite3_open("todolist.db", &db);

        char* messageError;
        int exit = sqlite3_exec(db, sql3.c_str(), nullptr, nullptr, &messageError);

        if (exit != SQLITE_OK)
        {
            cerr << "Error Delete" << endl;
            sqlite3_free(messageError);
        } else
        {
            cout << "Delete Successful" << endl;
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
        sql2 = "INSERT INTO TODO (ID, TASK,STATUS,PRIORITY) VALUES (" + quotesql(to_string(insert)) + "," + quotesql(item.text()) + "," + quotesql((item.is_done() ? "true" : "false")) + "," + quotesql(item.priority()) + ");";
        try
        {
            sqlite3_open("todolist.db", &db);

            char* messageError;
            int exit = sqlite3_exec(db, sql2.c_str(), nullptr, nullptr, &messageError);

            if (exit != SQLITE_OK)
            {
                cerr << "Error Insert" << endl;
                sqlite3_free(messageError);
            } else
            {
                cout << "Insert Successful" << endl;
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
        for( int i = 1; i < 4; i++ )
        {
            line += std::string( (char *)sqlite3_column_text( stmt, i ));
            if (i != 3)
                line += " ";
        }
        //cout <<line << endl;
        sqlite3_step( stmt );
        Item item(line);
        list.emplace_back(line);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

//this function works generally so if you wanna use that for edit then you can
//needa get this to work with everything other than add and remove (for remove we might need another delete function so we can delete at a specific index)
/*
void DatabaseManagement::updateData(int s, const string& edit)
{
    int exit = sqlite3_open(filename, &db);

    string sql = "UPDATE TODO SET TASK =" + quotesql(edit) + "WHERE ID =" + quotesql(to_string(s)) + ");";

    sqlite3_exec(db, sql.c_str(), NULL, 0, &ErrorMessage);

    if (exit != SQLITE_OK)
    {
        cerr << "Error Insert" << endl;
        sqlite3_free(ErrorMessage);
    } else
    {
        cout << "Records updated Successfully" << endl;
    }
}
*/

