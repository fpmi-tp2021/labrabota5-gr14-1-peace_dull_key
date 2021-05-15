// 
// user_interface.c
// MusicalStore
// 
// Created by Arseniy Borsukov and Ann Filon
//

#include "user_interface.h"

void employee_interface(bool* app_working, sqlite3* db) 
{
    int option = 1;

    while (option != 0)
    {
        printf("Choose the option:\n");
        printf("\t1 - Insert new element\n");
        printf("\t2 - Update database\n");
        printf("\t3 - Delete element\n");
        printf("\t4 - Sql-requests\n");
        printf("\t0 - Exit\n\n");

        int temp = 1;
        scanf("%d", &temp);

        switch (temp) {
        case 1:
        {
            insert_record(&db);
            break;
        }

        case 2:
        {
            update_record(&db);
            break;
        }

        case 3:
        {
            bool delete = delete_record(&db);
            if (delete == true)
                printf("\nThe record has been deleted!\n");
            else
                printf("\nThe is no such record in data base!\n");
            break;
        }

        case 4:
        {
            sql_request_exec(&db);
            break;
        }
        case 0:
        {
            option = 0;
            break;
        }
        default:
        {
            printf("\nInvaid option!");
            continue;
        }
        }
    }
}

void customer_interface(bool* app_working, sqlite3* db)
{
    int option = 1;

    while (option != 0)
    {
        printf("Chooise the option:\n");
        printf("\t1 - Show info about the most popular disc\n");
        printf("\t2 - Show info about the most popular performer\n");
        printf("\t0 - exit\n\n");

        int temp = 1;
        scanf("%d", &temp);

        switch (temp) {
        case 1:
        {
            show_most_popular_disc(&db);

            break;
        }

        case 2:
        {
            show_most_popular_performer(&db);
            break;
        }
        case 0:
        {
            option = 0;
            break;
        }
        default:
        {
            printf("\nInvaid option!");
            continue;
        }
        }
    }
}