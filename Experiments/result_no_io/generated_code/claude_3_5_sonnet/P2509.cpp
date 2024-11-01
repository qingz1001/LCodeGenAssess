#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINES 50
#define MAX_LINE_LENGTH 100
#define MAX_VARS 26

char program[MAX_LINES][MAX_LINE_LENGTH];
int line_count = 0;
bool reachable[MAX_LINES];
bool initialized[MAX_VARS];
bool if_stack[MAX_LINES];
int if_top = -1;

void parse_head(char *line) {
    char *token = strtok(line, " ");
    token = strtok(NULL, " ");
    while (token != NULL) {
        initialized[token[0] - 'A'] = true;
        token = strtok(NULL, " ");
    }
}

void check_uninitialized(int line_num, char *line) {
    char *token = strtok(line, " ");
    while (token != NULL) {
        if (strlen(token) == 1 && token[0] >= 'A' && token[0] <= 'Z') {
            if (!initialized[token[0] - 'A']) {
                printf("WARNING: Possible use of uninitialized variable %s on line %d\n", token, line_num + 1);
            }
        }
        token = strtok(NULL, " ");
    }
}

void check_assignment(char *line) {
    char var = line[0];
    initialized[var - 'A'] = true;
}

void analyze_program() {
    memset(reachable, true, sizeof(reachable));
    memset(initialized, false, sizeof(initialized));
    
    parse_head(program[0]);
    
    for (int i = 1; i < line_count; i++) {
        if (strncmp(program[i], "IF ", 3) == 0) {
            if_top++;
            if_stack[if_top] = reachable[i];
        } else if (strcmp(program[i], "ELSE") == 0) {
            reachable[i] = if_stack[if_top];
            if_stack[if_top] = !if_stack[if_top];
        } else if (strcmp(program[i], "END IF") == 0) {
            reachable[i] = if_stack[if_top];
            if_top--;
        } else {
            if (reachable[i]) {
                if (strchr(program[i], '=') != NULL) {
                    check_assignment(program[i]);
                }
                check_uninitialized(i, program[i]);
            } else {
                printf("WARNING: Unreachable code on line %d\n", i + 1);
            }
        }
    }
}

int main() {
    while (fgets(program[line_count], MAX_LINE_LENGTH, stdin) != NULL) {
        program[line_count][strcspn(program[line_count], "\n")] = 0;
        if (strlen(program[line_count]) == 0) break;
        line_count++;
    }
    
    analyze_program();
    
    return 0;
}