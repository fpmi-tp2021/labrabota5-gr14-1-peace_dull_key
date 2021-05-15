//  
// db_functions.h
//  MusicalStore
//
//  Created by Arseniy Borsukov and Ann Filon
//

#pragma once
#ifndef db_functions_h
#define db_functions_h

#include "account.h"
#include "sqlite3.h"

void insert_record(sqlite3* db);

void insert_Album_Styles(sqlite3* db);
void insert_Album(sqlite3* db);
void insert_Author(sqlite3* db);
void insert_Disc(sqlite3* db);
bool insert_Operation(sqlite3* db);
void insert_Performer(sqlite3* db);

bool check_user_data(sqlite3* db, char* log, char* passw);
bool insert_Account(sqlite3* db, account* Account);
bool func_is_allowed(sqlite3* db, int disc_code);

void update_record(sqlite3* db);

void update_Album_Styles(sqlite3* db);
void update_Album(sqlite3* db);
void update_Author(sqlite3* db);
void update_Disc(sqlite3* db);
void update_Performer(sqlite3* db);

bool delete_record(sqlite3* db);

bool delete_Album_Styles(sqlite3* db);
bool delete_Album(sqlite3* db);
bool delete_Author(sqlite3* db);
bool delete_Disc(sqlite3* db);
bool delete_Operation(sqlite3* db);
bool delete_Performer(sqlite3* db);

static int callback(void* NotUsed, int argc, char** argv, char** azColName);

void sql_request_exec(sqlite3* db);

void show_most_popular_disc(sqlite3* db);
void show_most_popular_performer(sqlite3* db);
void show_all_discs(sqlite3* db);
void show_sold_discs_by_date(sqlite3* db);
void show_author_info(sqlite3* db);

#endif /* db_functions_h */
