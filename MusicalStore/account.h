// 
// account.h
// MusicalStore
//
// Created by Arseniy Borsukov and Ann Filon
//

#pragma once

#ifndef account_h
#define account_h

typedef enum { true, false } bool;

typedef struct Account {
    char* login;
    char* password;
    int role; //1 - employee , 2 - customer
} account;
#endif