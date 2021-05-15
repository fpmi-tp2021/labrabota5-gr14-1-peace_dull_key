// 
// db_functions.c
// MusicalStore
//
// Created by Arseniy Borsukov and Ann Filon
//

#include "db_functions.h"
#include <stdio.h>
#include <stdlib.h>

void insert_record(sqlite3* db)
{
    printf("\nChoose the table you want to insert record into:\n");

    printf("\t1 - Album styles\n");
    printf("\t2 - Albums\n");
    printf("\t3 - Authors\n");
    printf("\t4 - Discs\n");
    printf("\t5 - Operations\n");
    printf("\t6 - Performers\n");
    printf("\t0 - Back to the main menu\t");

    int choice = 0;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
    {
        insert_Album_Styles(&db);
        break;
    }
    case 2:
    {
        insert_Album(&db);
        break;
    }
    case 3:
    {
        insert_Author(&db);
        break;
    }
    case 4:
    {
        insert_Disc(&db);
        break;
    }
    case 5:
    {
        insert_Operation(&db);
        break;
    }
    case 6:
    {
        insert_Performer(&db);
        break;
    }
    case 0:
    {
        break;
    }
    default:
    {
        printf("\nThere is no such option!\n");
        break;
    }
    }
}

void insert_Album_Styles(sqlite3* db) 
{
    char style_type[50];
    printf("\n\tEnter style: ");
    scanf("%s", &style_type);

    char buff_request[200];
    sprintf(buff_request, "INSERT INTO Album_Styles (style_type VALUES ('%s')", style_type);

    char* err = 0;
    if (sqlite3_exec(db, buff_request, callback, 0, &err) != SQLITE_OK)
        printf("%s", err);
    else
        printf("The record has been added.");
}

void insert_Album(sqlite3* db) 
{
    char album_creation_date[10];
    char album_name[100];
    int author_code;
    char composition_listcode[500];
    int performer_code;
    int style_code;

    printf("\n\tEnter album creation date (YYYYMMDD): ");
    scanf("%s", &album_creation_date);

    printf("\n\tEnter the name of album: ");
    scanf("%s", &album_name);

    printf("\n\tEnter author code: ");
    scanf("%i", &author_code);

    printf("\n\tEnter the list of compositions: ");
    scanf("%s", &composition_listcode);

    printf("\n\tEnter performer code: ");
    scanf("%i", &performer_code);

    printf("\n\tEnter style code: ");
    scanf("%i", &style_code);

    char buff_request[1000];
    sprintf(buff_request, "INSERT INTO Albums (album_creation_date, album_name, author_code, composition_listcode, performer_code, style_code  VALUES ('%s', '%s','%i', '%s', '%i', '%i')", 
        album_creation_date, album_name, author_code, composition_listcode, performer_code, style_code);

    char* err = 0;
    if (sqlite3_exec(db, buff_request, callback, 0, &err) != SQLITE_OK)
        printf("%s", err);
    else
        printf("The element has been added.");
}

void insert_Author(sqlite3* db) 
{
    char author_name[50];
    printf("\n\tEnter style: ");
    scanf("%s", &author_name);

    char buff_request[200];
    sprintf(buff_request, "INSERT INTO Authors (author_name VALUES ('%s')", author_name);

    char* err = 0;
    if (sqlite3_exec(db, buff_request, callback, 0, &err) != SQLITE_OK)
        printf("%s", err);
    else
        printf("The element has been added.");
}

void insert_Disc(sqlite3* db) 
{
    int album_code;
    char disc_company[50];
    double disc_cost;
    char disk_creation_date[10];
    char disk_name[50];

    printf("\n\tEnter album code: ");
    scanf("%i", &album_code);

    printf("\n\tEnter the company that made this disk: ");
    scanf("%s", &disc_company);

    printf("\n\tEnter disk cost: ");
    scanf("%d", &disc_cost);

    printf("\n\tEnter disk creation date (YYYY-MM-DD): ");
    scanf("%s", &disk_creation_date);

    printf("\n\tEnter disc name: ");
    scanf("%s", &disk_name);

    char buff_request[1000];
    sprintf(buff_request, "INSERT INTO Discs (album_code, disc_company, disc_cost, disk_creation_date, disk_name VALUES ('%i', '%s','%d', '%s', '%s')",
        album_code, disc_company, disc_cost, disk_creation_date, disk_name);

    char* err = 0;
    if (sqlite3_exec(db, buff_request, callback, 0, &err) != SQLITE_OK)
        printf("%s", err);
    else 
        printf("The element has been added.");
}

bool insert_Operation(sqlite3* db) 
{
    int disc_code = -1;

    printf("\n\tEnter disc code: ");
    scanf("%i", &disc_code);

    bool check = func_is_allowed(&db, &disc_code);
    if (check == false)
        return false;

    int discs_amount;
    char operation_date[10];
    int operation_state_code;
    printf("\n\tEnter discs amount: ");
    scanf("%i", &discs_amount);

    printf("\n\tEnter operation date (YYYYMMDD): ");
    scanf("%s", &operation_date);

    printf("\n\tEnter operation state code: ");
    scanf("%i", &operation_state_code);

    char buff_request[1000];
    sprintf(buff_request, "INSERT INTO Operations (disc_code, discs_amount, operation_date, operation_state_code VALUES ('%i', '%i','%s', '%i')",
        disc_code, discs_amount, operation_date, operation_state_code);

    char* err = 0;
    if (sqlite3_exec(db, buff_request, callback, 0, &err) != SQLITE_OK)
    {
        printf("%s", err);
        return false;
    }
    else
        printf("The element has been added.");
    return true;
}

void insert_Performer(sqlite3* db) 
{
    char performer_name[50];
    printf("\n\tEnter style: ");
    scanf("%s", &performer_name);

    char buff_request[200];
    sprintf(buff_request, "INSERT INTO Performers (style_type VALUES ('%s')", performer_name);

    char* err = 0;
    if (sqlite3_exec(db, buff_request, callback, 0, &err) != SQLITE_OK)
        printf("%s", err);
    else
        printf("The element has been added.");
}

bool check_user_data(sqlite3* db, char* log, char* passw)
{
    //char buff_request[150];
    char* err = 0;

    char* buff_request = "SELECT * FROM \"Users_list\" WHERE \"user_login\"=\"hannafilon\" AND \"user_password\"=\"1111\";";

    sqlite3_stmt* result;
    if (sqlite3_prepare_v2(db, buff_request, -1, &result, 0) != SQLITE_OK)
    {
        printf("Something is wrong");
    }
    sqlite3_bind_text(result, 1, log, -1, NULL);
    sqlite3_bind_text(result, 2, passw, -1, NULL);

    if (sqlite3_step(result) == SQLITE_ROW)
        return true;
    else return false;
}

bool insert_Account(sqlite3* db, account* Account)
{
    char buff_request[200];
    sprintf(buff_request, "INSERT INTO Users_list(user_login, user_password, user_type_code) VALUES (\"%s\", \"%s\", %i);",
        Account->login, Account->password, Account->role);

    char* err = 0;
    if (sqlite3_exec(db, buff_request, 0, 0, &err) != SQLITE_OK)
    {
        printf("%s", err);
        return;
    }
    return true;
}

bool func_is_allowed(sqlite3 * db, int disc_code)
{
    char buff_request[500];
    char* err = 0;
   
    sprintf(buff_request, "SELECT SUM(Operations.discs_amount) "
        "FROM Operations inner join Operation_States On Operations.operation_state_code = Operation_States.state_code "
        "Where Operations.disc_code = %d and Operation_States.state_name Like 'Arrival';", disc_code);
  
    sqlite3_stmt* result;
    if (sqlite3_prepare_v2(db, buff_request, -1, &result, 0) != SQLITE_OK) {

        printf("Failed to select data\n");
        printf("SQL error: %s\n", err);
        return;
    }

    int arrived = 0;
    if (sqlite3_step(result) == SQLITE_ROW) 
        arrived = sqlite3_column_int(result, 0);

    sprintf(buff_request, "SELECT SUM(Operations.discs_amount) "
        "FROM Operations inner join Operation_States On Operations.operation_state_code = Operation_States.state_code "
        "Where Operations.disc_code = %d and Operation_States.state_name Like 'Sale';", disc_code);

    if (sqlite3_prepare_v2(db, buff_request, -1, &result, 0) != SQLITE_OK) {

        printf("Failed to select data\n");
        printf("SQL error: %s\n", err);
        return;
    }

    int sold = 0;
    if (sqlite3_step(result) == SQLITE_ROW)
        sold = sqlite3_column_int(result, 0);

    return (sold <= arrived);
}

bool delete_record(sqlite3* db) 
{
    printf("\nChoose the table you want to delete record from:\n");

    printf("\t1 - Album styles\n");
    printf("\t2 - Albums\n");
    printf("\t3 - Aauthors\n");
    printf("\t4 - Discs\n");
    printf("\t5 - Operations\n");
    printf("\t6 - Performers\n");
    printf("\t0 - Back to the main menu\t");

    int choice = 0;
    scanf("%d", &choice);
    bool delete = false;
    switch (choice)
    {
    case 1:
    {
        delete = delete_Album_Styles(&db);
        break;
    }
    case 2:
    {
        delete = delete_Album(&db);
        break;
    }
    case 3:
    {
        delete = delete_Author(&db);
        break;
    }
    case 4:
    {
        delete = delete_Disc(&db);
        break;
    }
    case 5:
    {
        delete = delete_Operation(&db);
        break;
    }
    case 6:
    {
        delete = delete_Performer(&db);
        break;
    }
    case 0:
    {
        break;
    }
    default:
    {
        printf("There is no such option!\n");
        break;
    }
    }
    return delete;
}

bool delete_Album_Styles(sqlite3* db) 
{
    char buff_request[200];
    char* err = 0;

    printf("\nEnter style code:");
    int style_code;
    scanf("%d\n", &style_code);
    sprintf(buff_request, "DELETE FROM Album_Styles WHERE style_code=%d;", style_code);

    if (sqlite3_exec(db, buff_request, callback, 0, &err) != SQLITE_OK)
    {
        printf("%s", err);
        return false;
    }
    return true;
}

bool delete_Album(sqlite3* db) 
{
    char buff_request[200];
    char* err = 0;

    printf("\nEnter album code:");
    int album_code;
    scanf("%d\n", &album_code);
    sprintf(buff_request, "DELETE FROM Albums WHERE album_code=%d;", album_code);

    if (sqlite3_exec(db, buff_request, callback, 0, &err) != SQLITE_OK)
    {
        printf("%s", err);
        return false;
    }
    return true;
}

bool delete_Author(sqlite3* db) 
{
    char buff_request[200];
    char* err = 0;

    printf("\nEnter author code:");
    int author_code;
    scanf("%d\n", &author_code);
    sprintf(buff_request, "DELETE FROM Authors WHERE author_code=%d;", author_code);

    if (sqlite3_exec(db, buff_request, callback, 0, &err) != SQLITE_OK)
    {
        printf("%s", err);
        return false;
    }
    return true;
}

bool delete_Disc(sqlite3* db)
{
    char buff_request[200];
    char* err = 0;

    printf("\nEnter disc code:");
    int disc_code;
    scanf("%d\n", &disc_code);
    sprintf(buff_request, "DELETE FROM Discs WHERE disc_code=%d;", disc_code);

    if (sqlite3_exec(db, buff_request, callback, 0, &err) != SQLITE_OK)
    {
        printf("%s", err);
        return false;
    }
    return true;
}

bool delete_Operation(sqlite3* db) 
{
    char buff_request[200];
    char* err = 0;

    printf("\nEnter operation code:");
    int operation_code;
    scanf("%d\n", &operation_code);
    sprintf(buff_request, "DELETE FROM Operations WHERE operation_code=%d;", operation_code);

    if (sqlite3_exec(db, buff_request, callback, 0, &err) != SQLITE_OK)
    {
        printf("%s", err);
        return false;
    }
    return true;
}

bool delete_Performer(sqlite3* db) 
{
    char buff_request[200];
    char* err = 0;

    printf("\nEnter performer code:");
    int performer_code;
    scanf("%d\n", &performer_code);
    sprintf(buff_request, "DELETE FROM Performers WHERE performer_code=%d;", performer_code);

    if (sqlite3_exec(db, buff_request, callback, 0, &err) != SQLITE_OK)
    {
        printf("%s", err);
        return false;
    }
    return true;
}

void update_record(sqlite3* db) 
{
    printf("\nChoose the table you want to update record in:\n");

    printf("\t1 - Album styles\n");
    printf("\t2 - Albums\n");
    printf("\t3 - Authors\n");
    printf("\t4 - Discs\n");
    printf("\t5 - Performers\n");
    printf("\t0 - Back to the main menu\t");

    int choice = 0;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
    {
        update_Album_Styles(&db);
        break;
    }
    case 2:
    {
        update_Album(&db);
        break;
    }
    case 3:
    {
        update_Author(&db);
        break;
    }
    case 4:
    {
        update_Disc(&db);
        break;
    }
    case 5:
    {
        update_Performer(&db);
        break;
    }
    case 0:
    {
        break;
    }
    default:
    {
        printf("\nThere is no such option!\n");
        break;
    }
    }

}

void update_Album_Styles(sqlite3* db)
{
    char buff_request[200];
    char* err = 0;

    printf("\nEnter style code:");
    int style_code;
    scanf("%d\n", &style_code);

    printf("\nEnter style name:");
    char style_type[50];
    scanf("%s\n", &style_type);

    sprintf(buff_request, "UPDATE Album_styles SET style_type = '%s' WHERE style_code = %d;", style_type, style_code);
  
    if (sqlite3_exec(db, buff_request, callback, 0, &err) != SQLITE_OK)
    {
        printf("%s", err);
    }
}

void update_Album(sqlite3* db)
{
    char buff_request[200];
    char* err = 0;

    printf("\nEnter album code:");
    int album_code;
    scanf("%d\n", &album_code);

    printf("\nEnter the list of compositions:");
    char compositions_listcode[1000];
    scanf("%s\n", &compositions_listcode);

    sprintf(buff_request, "UPDATE Albums SET compositions_listcode = '%s' WHERE album_code = %d;", compositions_listcode, album_code);

    if (sqlite3_exec(db, buff_request, callback, 0, &err) != SQLITE_OK)
    {
        printf("%s", err);
    }
}

void update_Author(sqlite3* db)
{
    char buff_request[200];
    char* err = 0;

    printf("\nEnter author code:");
    int author_code;
    scanf("%d\n", &author_code);

    printf("\nEnter author name:");
    char author_name[50];
    scanf("%s\n", &author_name);

    sprintf(buff_request, "UPDATE Authors SET author_name = '%s' WHERE author_code = %d;", author_name, author_code);

    if (sqlite3_exec(db, buff_request, callback, 0, &err) != SQLITE_OK)
    {
        printf("%s", err);
    }
}

void update_Disc(sqlite3* db)
{
    char buff_request[200];
    char* err = 0;

    printf("\nEnter disc name:");
    char disc_name[100];
    scanf("%s\n", &disc_name);

    printf("\nEnter disk cost:");
    double disc_cost;
    scanf("%d\n", &disc_cost);

    sprintf(buff_request, "UPDATE Discs SET disc_cost = %d WHERE disc_name = '%s';", disc_cost, disc_name);

    if (sqlite3_exec(db, buff_request, callback, 0, &err) != SQLITE_OK)
    {
        printf("%s", err);
    }
}

void update_Performer(sqlite3* db) 
{
    char buff_request[200];
    char* err = 0;

    printf("\nEnter performer code:");
    int performer_code;
    scanf("%d\n", &performer_code);

    printf("\nEnter performer name:");
    char performer_name[50];
    scanf("%s\n", &performer_name);

    sprintf(buff_request, "UPDATE Performers SET performer_name = '%s' WHERE performer_code = '%d';", performer_name, performer_code);

    if (sqlite3_exec(db, buff_request, callback, 0, &err) != SQLITE_OK)
    {
        printf("%s", err);
    }
}

static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    for (int i = 0; i < argc; i++)
    {
        printf(" %s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

void sql_request_exec(sqlite3* db) 
{
    printf("\nChoose the table you want to delete element from:\n");

    printf("\t1 - Show info about each of the disks\n");
    printf("\t2 - Show info about the exact one disc\n");
    printf("\t3 - Show info about the most popular disc\n");
    printf("\t4 - Show info about the most popular performer\n");
    printf("\t5 - Show info about each of the authors\n");
    printf("\t0 - Back to the main menu\n");

    int choice = 0;
    scanf("%d", &choice);
    bool delete = false;
    switch (choice)
    {
    case 1:
    {
        show_all_discs(&db);
        break;
    }
    case 2:
    {
        show_sold_discs_by_date(&db);
        break;
    }
    case 3:
    {
        show_most_popular_disc(&db);
        break;
    }
    case 4:
    {
        show_most_popular_performer(&db);
        break;
    }
    case 5:
    {
        delete_Operation(&db);
        break;
    }
    case 0:
    {
        break;
    }
    default:
    {
        printf("There is no such option!\n");
        break;
    }
    }
}

void show_most_popular_disc(sqlite3* db)
{
    char buff_request[500];
    sprintf(buff_request, "SELECT Discs.disc_name, Discs.disc_company, Albums.compostions_listcode, SUM(Operations.discs_amount) AS sold_copies\n"
        "FROM Discs\n"
        "INNER JOIN Albums ON Discs.album_code = Albums.album_code\n"
        "INNER JOIN(Operations INNER JOIN Operation_States ON Operations.operation_state_code = Operation_States.state_code) ON Discs.disc_code = Operations.disc_code\n"
        "WHERE Operation_States.state_name LIKE 'Sale'\n"
        "GROUP BY Discs.disc_code\n"
        "ORDER BY sold_copies DESC\n"
        "LIMIT 1;");

    char* err = 0;

    if (sqlite3_exec(db, buff_request, callback, 0, &err) != SQLITE_OK) {
        printf("%s", err);
    }
}

void show_most_popular_performer(sqlite3* db)
{
    char buff_request[500];
    char* err = 0;

    sprintf(buff_request, "SELECT Performers.performer_name, SUM(Operations.discs_amount) AS sold_copies\n"
        "FROM Discs\n"
        "INNER JOIN(Albums INNER JOIN Performers ON Albums.performer_code = Performers.performer_code) ON Discs.album_code = Albums.album_code\n"
        "INNER JOIN(Operations INNER JOIN Operation_States ON Operations.operation_state_code = Operation_States.state_code) ON Discs.disc_code = Operations.disc_code\n"
        "WHERE Operation_States.state_name LIKE 'Sale'\n"
        "GROUP BY Discs.disc_code\n"
        "Order By sold_copies DESC\n"
        "LIMIT 1;");

    if (sqlite3_exec(db, buff_request, callback, 0, &err) != SQLITE_OK)
    {
        printf("%s", err);
    }
}

void show_all_discs(sqlite3* db)
{
    char buff_request[500];
    char* err = 0;

    char first_date[8];
    printf("\n\tEnter first date (YYYYMMDD): ");
    scanf("%s", &first_date);

    char second_date[8];
    printf("\n\tEnter second date (YYYYMMDD): ");
    scanf("%s", &second_date);

    sprintf(buff_request, "SELECT Discs.disc_name, SUM(Operations.discs_amount) AS sold_copies, Discs.disc_cost\n"
        "FROM Discs\n"
        "INNER JOIN(Operations INNER JOIN Operation_States ON Operations.operation_state_code = Operation_States.state_code) ON Discs.disc_code = Operations.disc_code\n"
        "WHERE Operation_States.state_name LIKE 'Sale'\ns"
        "AND Discs.disc_code = ?\n"
        "AND Operations.operation_date >= '%s'\n"
        "AND Operations.operation_date <= '%s'; ", first_date, second_date);

    if (sqlite3_exec(db, buff_request, callback, 0, &err) != SQLITE_OK)
    {
        printf("%s", err);
    }
}

void show_sold_discs_by_date(sqlite3* db)
{
    char buff_request[500];
    char* err = 0;

    char first_date[8];
    printf("\n\tEnter first date (YYYYMMDD): ");
    scanf("%s", &first_date);

    char second_date[8];
    printf("\n\tEnter second date (YYYYMMDD): ");
    scanf("%s", &second_date);

    sprintf(buff_request, "SELECT Discs.disc_name, SUM(Operations.discs_amount) AS sold_copies, Discs.disc_cost\n"
        "FROM Discs\n"
        "INNER JOIN(Operations INNER JOIN Operation_States ON Operations.operation_state_code = Operation_States.state_code) ON Discs.disc_code = Operations.disc_code\n"
        "WHERE Operation_States.state_name LIKE 'Sale'\ns"
        "AND Discs.disc_code = ?\n"
        "AND Operations.operation_date >= '%s'\n"
        "AND Operations.operation_date <= '%s'; ", first_date, second_date);

    if (sqlite3_exec(db, buff_request, callback, 0, &err) != SQLITE_OK)
    {
        printf("%s", err);
    }
}

void show_author_info(sqlite3* db)
{
    char buff_request[250];
    char* err = 0;

    sprintf(buff_request, "SELECT Authors.author_name, SUM(Operations.discs_amount) AS sold_copies, SUM(Operations.discs_amount * Discs.disc_cost) as money\n"
        "FROM Discs\n"
        "INNER JOIN(Albums INNER JOIN Authors ON Albums.author_code = Authors.author_code) ON Discs.album_code = Albums.album_code\n"
        "INNER JOIN(Operations INNER JOIN Operation_States ON Operations.operation_state_code = Operation_States.state_code) ON Discs.disc_code = Operations.disc_code\n"
        "WHERE Operation_States.state_name LIKE 'Sale'\n"
        "GROUP BY Discs.disc_code;");
    if (sqlite3_exec(db, buff_request, callback, 0, &err) != SQLITE_OK)
    {
        printf("%s", err);
    }
}