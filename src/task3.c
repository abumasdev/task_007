#include <stdio.h>
#include <string.h>
#define STRSIZE 256

char* strhalf(char* str);

int main() {
    char str[STRSIZE] = "";
    if (scanf("%s", str)) {
        while (strlen(str) > 1) {
            printf("%s\n", strhalf(str));
        }
    }
    return 0;
}

char* strhalf(char* str) {
    int len = strlen(str);
    len = len / 2 + (len % 2);
    str[len] = '\0';
    return str;
}
