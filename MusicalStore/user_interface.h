// 
// user_interface.h
// MusicalStore
// 
// Created by Arseniy Borsukov and Ann Filon
//

#pragma once

#include "account.h"
#include "db_functions.h"
#include "sqlite3.h"

void employee_interface(bool* app_working,sqlite3* db);
void customer_interface(bool* app_working, sqlite3* db);
