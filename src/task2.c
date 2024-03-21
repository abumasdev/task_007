#include <stdio.h>
#define STRSIZE 256

void change_separator_str(char* input, char sep);

int main() {
    char str[STRSIZE];
    char new_separator;
    if (fgets(str, STRSIZE, stdin) != NULL && scanf("%c", &new_separator)) {
        change_separator_str(str, new_separator);
        printf("%s", str);
    }
    return 0;
}

void change_separator_str(char* input, char sep) {
    while (*input != '\0') {
        if (*input == ' ') *input = sep;
        input++;
    }
}

/*
void change_separator_str(char* input, char sep) {
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == ' ') input[i] = sep;
    }
}
*/