// 
// main.c
// MusicalStore
// 
// Created by Arseniy Borsukov and Ann Filon
//

#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "app_login.h"
#include "db_functions.h"
#include "user_interface.h"
#include "account.h"

int main()
{
    sqlite3* db;

    char* db_file_path = "Musical_store.db";
    int openDB = sqlite3_open_v2(db_file_path, &db, SQLITE_OPEN_READWRITE, NULL);
    if (openDB != SQLITE_OK) 
    {
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }
    
    int user_role = 0;
    bool app_working =  start_app(&db, &user_role);
  
    if (app_working == false)
        return 0;
 
    switch (user_role)
    {
    case 1: 
    {
        employee_interface(&app_working, &db);
        break;
    }
    case 2: 
    {
        customer_interface(&app_working, &db);
        break;
    }
    default: 
    {
        app_working = false;
        break;
    }
    }

    sqlite3_close(&db);
    return 0;    
}
