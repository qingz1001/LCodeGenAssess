#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE 50
#define MAX_TOKEN 100
#define MAX_VAR 26

char lines[MAX_LINE][100];
int num_lines;
bool initialized[MAX_VAR];
bool reachable[MAX_LINE];

void parse_line(int line) {
    char tokens[MAX_TOKEN][100];
    int num_tokens = 0;
    char *token = strtok(lines[line], " ");
    while (token != NULL) {
        strcpy(tokens[num_tokens++], token);
        token = strtok(NULL, " ");
    }

    if (strcmp(tokens[0], "PARAM") == 0) {
        for (int i = 1; i < num_tokens; i++) {
            initialized[tokens[i][0] - 'A'] = true;
        }
    } else if (strcmp(tokens[0], "IF") == 0) {
        reachable[line] = true;
        int condition_line = line;
        while (strcmp(lines[++condition_line], "END IF") != 0) {
            if (strcmp(lines[condition_line], "ELSE") == 0) {
                reachable[condition_line] = true;
            }
        }
        reachable[condition_line] = true;
    } else if (strcmp(tokens[0], "RETURN") == 0) {
        reachable[line] = true;
    } else if (strcmp(tokens[0], "ELSE") == 0 || strcmp(tokens[0], "END IF") == 0) {
        reachable[line] = true;
    } else {
        reachable[line] = true;
        char *var = tokens[0];
        if (!initialized[var[0] - 'A']) {
            printf("Line %d: variable %c might not have been initialized\n", line + 1, var[0]);
        }
    }
}

int main() {
    while (fgets(lines[num_lines], sizeof(lines[num_lines]), stdin)) {
        lines[num_lines][strlen(lines[num_lines]) - 1] = '\0';
        num_lines++;
    }

    for (int i = 0; i < num_lines; i++) {
        parse_line(i);
    }

    for (int i = 0; i < num_lines; i++) {
        if (!reachable[i]) {
            printf("Line %d: unreachable code\n", i + 1);
        }
    }

    return 0;
}