// 
// app_login.h
// MusicalStore
//
// Created by Arseniy Borsukov and Ann Filon
//

#pragma once

#include "account.h"
#include "sqlite3.h"

#ifndef app_login_h
#define app_login_h

bool start_app(sqlite3* db, int* user_role);

int menu();

void request_data(char* log, char* passw);
#endif