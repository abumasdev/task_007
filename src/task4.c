#include <stdio.h>
#include <string.h>
#include "sqlite3.h"

#define STRSIZE 128
#define SQLSIZE 512
#define COMMANDSTRSIZE 16

enum commands { NONE, SHOW, SHOWALL, ADD, REMOVE, EXIT };

void menu_operate(enum commands command);
int callback_show(void *, int, char **, char **);
int check_function_call(int bool);
int callback_showall(void *, int, char **, char **);
void remove_extreme_spaces_str(char *str);
void delete_newline_stdin();

int main() {
    enum commands command;
    char command_str[COMMANDSTRSIZE] = "";
    do {
        if (scanf("%s", command_str)) {
            command = NONE;
            if (!strcmp(command_str, "SHOW")) command = SHOW;
            if (!strcmp(command_str, "SHOWALL")) command = SHOWALL;
            if (!strcmp(command_str, "ADD")) command = ADD;
            if (!strcmp(command_str, "REMOVE")) command = REMOVE;
            if (!strcmp(command_str, "EXIT")) command = EXIT;
            if (command != NONE) menu_operate(command);
        }
    } while (command != EXIT);
    return 0;
}

void menu_operate(enum commands command) {
    char *err_msg = 0;
    int dbres;
    static sqlite3 *db = NULL;  // указатель на базу данных
    if (db == NULL) {           // открываем подключение к базе данных
        dbres = sqlite3_open("../data-samples/task007.db", &db);
        if (dbres != SQLITE_OK) {
            sqlite3_close(db);
            db = NULL;
        }
    }
    switch (command) {
        case SHOW:
            if (db != NULL) {
                int id;
                if (scanf("%d", &id)) {
                    char sql[SQLSIZE] = "";
                    sprintf(sql, "SELECT id, Name, Age, email FROM Students WHERE id = %d", id);
                    int chk = check_function_call(1);
                    dbres = sqlite3_exec(db, sql, callback_show, 0, &err_msg);
                    if (chk == check_function_call(1)) printf("NO DATA\n");
                    if (dbres != SQLITE_OK) {
                        printf("SQL error: %s\n", err_msg);
                        sqlite3_free(err_msg);
                        sqlite3_close(db);
                        db = NULL;
                    }
                }
            }
            break;
        case SHOWALL:
            if (db != NULL) {
                char *sql = "SELECT id, Name, Age, email FROM Students";
                dbres = sqlite3_exec(db, sql, callback_showall, 0, &err_msg);
                if (dbres != SQLITE_OK) {
                    printf("SQL error: %s\n", err_msg);
                    sqlite3_free(err_msg);
                    sqlite3_close(db);
                    db = NULL;
                }
            }
            break;
        case ADD:
            if (db != NULL) {
                char name_str[STRSIZE] = "";
                int age_val;
                char email_str[STRSIZE] = "";
                delete_newline_stdin();
                if (scanf("%[^0-9]%d%s", name_str, &age_val, email_str)) {
                    remove_extreme_spaces_str(name_str);
                    remove_extreme_spaces_str(email_str);
                    char sql[SQLSIZE] = "";
                    sprintf(sql, "INSERT INTO Students (Name, Age, email) VALUES ('%s', %d, '%s')", name_str,
                            age_val, email_str);
                    dbres = sqlite3_exec(db, sql, 0, 0, &err_msg);
                    if (dbres != SQLITE_OK) {
                        printf("SQL error: %s\n", err_msg);
                        sqlite3_free(err_msg);
                        sqlite3_close(db);
                        db = NULL;
                    }
                }
            }
            break;
        case REMOVE:
            if (db != NULL) {
                int id;
                if (scanf("%d", &id)) {
                    char sql[STRSIZE] = "";
                    sprintf(sql, "DELETE FROM Students WHERE id = %d", id);
                    dbres = sqlite3_exec(db, sql, 0, 0, &err_msg);
                    if (dbres != SQLITE_OK) {
                        printf("SQL error: %s\n", err_msg);
                        sqlite3_free(err_msg);
                        sqlite3_close(db);
                        db = NULL;
                    }
                }
            }
            break;
        case EXIT:
            if (db != NULL) {
                sqlite3_close(db);
            }
            break;
        case NONE:
            break;
    }
}

int callback_show(void *notUsed, int colCount, char **columns, char **colNames) {
    check_function_call(0);
    for (int i = 0; i < colCount; i++) {
        printf("%s ", columns[i] ? columns[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int check_function_call(int bool) {
    static int check = 0;
    if (!bool) check++;
    return check;
}

int callback_showall(void *notUsed, int colCount, char **columns, char **colNames) {
    for (int i = 0; i < colCount; i++) {
        printf("%s ", columns[i] ? columns[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void delete_newline_stdin() {
    int c = getchar();
    if (c != '\n') ungetc(c, stdin);
}

void remove_extreme_spaces_str(char *str) {
    int start = 0;
    int end = -1;
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && end == -1) start = i;
        if (str[i] != ' ') end = i;
    }
    if (start < end) {
        for (i = start; i <= end; i++) {
            str[i - start] = str[i];
        }
        str[i - start] = '\0';
    }
}