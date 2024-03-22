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
void remove_newline_str(char *str);
int parse_add_str(char *str, char *output_name, char *output_age, char *output_email);

int main() {
    enum commands command = NONE;
    char command_str[COMMANDSTRSIZE] = "";
    do {
        if (scanf("%15s", command_str)) {
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
                char param_str[STRSIZE] = "";
                char name_str[STRSIZE] = "";
                char age_str[STRSIZE] = "";
                char email_str[STRSIZE] = "";
                delete_newline_stdin();
                fgets(param_str, STRSIZE, stdin);
                // if (scanf("%127[^0-9]%d%s", name_str, &age_val, email_str)) {
                if (parse_add_str(param_str, name_str, age_str, email_str)) {
                    char sql[SQLSIZE] = "";
                    sprintf(sql, "INSERT INTO Students (Name, Age, email) VALUES ('%s', %s, '%s')", name_str,
                            age_str, email_str);
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

void remove_newline_str(char *str) {
    while (*str) {
        if (*str == '\n') {
            *str = ' ';
        }
        str++;
    }
}

int parse_add_str(char *str, char *output_name, char *output_age, char *output_email) {
    int age_pos = 0;
    remove_newline_str(str);
    for (int i = 0; str[i] != '\0'; i++) {
        if ((age_pos == 0) && (strchr("0123456789", str[i]) != NULL) && (i > 0)) {
            if (str[i - 1] == ' ') {
                age_pos = i;
                str[i - 1] = '\0';
                strncpy(output_name, str, i);
            }
        }
        if ((age_pos > 0) && (strchr("0123456789", str[i]) == NULL)) {
            if (str[i] == ' ') {
                str[i] = '\0';
                strncpy(output_age, str + age_pos, i - age_pos);
                strcpy(output_email, (str + i + 1));
                break;
            }
        }
    }
    if (strlen(output_name)) remove_extreme_spaces_str(output_name);
    if (strlen(output_age)) remove_extreme_spaces_str(output_age);
    if (strlen(output_email)) remove_extreme_spaces_str(output_email);
    // printf("name=%s, ", output_name);
    // printf("age=%s, ", output_age);
    // printf("email=%s\n", output_email);
    return strlen(output_name) && strlen(output_age) && strlen(output_email);
}