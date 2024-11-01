#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LINES 50
#define MAX_LINE_LENGTH 100

char program[MAX_LINES][MAX_LINE_LENGTH];
bool initialized[26];
bool reachable[MAX_LINES];
int line_count = 0;

void parse_param(char *line) {
    char *token = strtok(line, " ");
    while ((token = strtok(NULL, " ")) != NULL) {
        initialized[token[0] - 'A'] = true;
    }
}

void parse_assignment(char *line) {
    char var = line[0];
    initialized[var - 'A'] = true;
}

void check_uninitialized(char *line, int line_num) {
    char *token = strtok(line, " ");
    while ((token = strtok(NULL, " ")) != NULL) {
        if (strlen(token) == 1 && isupper(token[0])) {
            if (!initialized[token[0] - 'A']) {
                printf("Line %d: variable %c might not have been initialized\n", line_num, token[0]);
            }
        }
    }
}

void analyze_program() {
    int if_stack[MAX_LINES], if_top = -1;
    bool in_else = false;

    for (int i = 0; i < line_count; i++) {
        reachable[i] = true;
        char *line = program[i];

        if (strncmp(line, "PARAM", 5) == 0) {
            parse_param(line);
        } else if (strchr(line, '=') != NULL) {
            if (reachable[i]) {
                parse_assignment(line);
                check_uninitialized(line, i + 1);
            }
        } else if (strncmp(line, "IF", 2) == 0) {
            if_stack[++if_top] = i;
            if (reachable[i]) {
                check_uninitialized(line, i + 1);
            }
        } else if (strcmp(line, "ELSE") == 0) {
            in_else = true;
        } else if (strcmp(line, "END IF") == 0) {
            if_top--;
            in_else = false;
        } else if (strncmp(line, "RETURN", 6) == 0) {
            if (reachable[i]) {
                check_uninitialized(line, i + 1);
                for (int j = i + 1; j < line_count; j++) {
                    reachable[j] = false;
                }
            }
        }

        if (i > 0 && !reachable[i] && strcmp(line, "ELSE") != 0 && strcmp(line, "END IF") != 0) {
            printf("Line %d: unreachable code\n", i + 1);
        }
    }
}

int main() {
    while (fgets(program[line_count], MAX_LINE_LENGTH, stdin) && line_count < MAX_LINES) {
        program[line_count][strcspn(program[line_count], "\n")] = 0;
        if (strlen(program[line_count]) > 0) {
            line_count++;
        }
    }

    analyze_program();

    return 0;
}