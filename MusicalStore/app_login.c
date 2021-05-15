// 
// app_login.c
// MusicalStore
//
// Created by Arseniy Borsukov and Ann Filon
//

#include "app_login.h"
#include "db_functions.h"
#include <stdio.h>
#include <stdlib.h>

bool start_app(sqlite3* db, int* user_role)
{
    account* Account = malloc(sizeof(account));
    char* log = malloc(sizeof(char) * 150);
    char* passw = malloc(sizeof(char) * 150);

    user_role = 0;

    bool app_working = true;
    bool insert = false;
    while (app_working == true)
    {
        int item = menu();

        switch (item)
        {
        case 1: {
            request_data(log, passw);
            
            bool check = check_user_data(&db, log, passw);
            if (check == true)
            {
                Account->login = log;
                Account->password = passw;
                Account->role = user_role;

                insert = insert_Account(&db, Account);
                if (insert == false)
                {
                    printf("\nProblem! Couldn't enter your account data. Exitting...\n");
                    app_working = false;
                }
            }
            else
                printf("\nWrong login or password! Try once again.\n");

            break;
        }
        case 2: {
            request_data(log, passw);

            user_role = 2;

            Account->login = log;
            Account->password = passw;
            Account->role = user_role;

            insert = insert_Account(&db, Account);
            if (insert == false)
            {
                printf("\nProblem! Couldn't enter your account data. Exitting...\n");
                app_working = false;
            }
            break;
        }
        case 3: {
            app_working = false;
            break;
        }
        default: {
            printf("\nThere is no such option! Choose again.\n"); }
            break;
        }
    }  
}

int menu() 
{
    printf("\nAuthorization\n1: sign in\n2: sign up\n3: exit\n");
    int choice;
    scanf("%i", &choice);
    return choice;
}

void request_data(char* log, char* passw) 
{
    printf("\nLogin:");
    scanf("%s", log);
    printf("\nPassword:");
    scanf("%s", passw);
}