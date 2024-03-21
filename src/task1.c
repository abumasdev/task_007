#include <stdio.h>

#include "sqlite3.h"

int callback(void *, int, char **, char **);

int main() {
    sqlite3 *db;  // указатель на базу данных
    char *err_msg = 0;

    // открываем подключение к базе данных
    int rc = sqlite3_open("../data-samples/task007.db", &db);

    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 1;
    }

    // получаем все данные из таблицы Students
    // char *sql = "SELECT * FROM Students";
    char *sql = "SELECT id, Name, Age, email FROM Students WHERE id = 7";
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    if (rc != SQLITE_OK) {
        printf("SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    // printf("result = %d\n", result);

    // закрываем подключение
    sqlite3_close(db);
    return 0;
}

int callback(void *notUsed, int colCount, char **columns, char **colNames) {
    for (int i = 0; i < colCount; i++) {
        // printf("%s = %s\n", colNames[i], columns[i] ? columns[i] : "NULL");
        printf("%s ", columns[i] ? columns[i] : "NULL");
    }
    printf("\n");
    return 0;
}