#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINES 50
#define MAX_LINE_LENGTH 100

typedef struct {
    char type[10];
    char var1[2];
    char var2[2];
    char op[2];
    int value;
} Statement;

Statement program[MAX_LINES];
bool initialized[26];
bool reachable[MAX_LINES];

void parse_line(char *line, int line_num) {
    sscanf(line, "%s", program[line_num].type);
    if (strcmp(program[line_num].type, "PARAM") == 0) {
        char *token = strtok(line, " ");
        while ((token = strtok(NULL, " ")) != NULL) {
            initialized[token[0] - 'A'] = true;
        }
    } else if (strcmp(program[line_num].type, "IF") == 0) {
        sscanf(line, "IF %s %s %d THEN", program[line_num].var1, program[line_num].op, &program[line_num].value);
    } else if (strcmp(program[line_num].type, "RETURN") == 0) {
        sscanf(line, "RETURN %s", program[line_num].var1);
    } else if (strcmp(program[line_num].type, "ELSE") == 0 || strcmp(program[line_num].type, "END") == 0) {
        // Do nothing
    } else {
        sscanf(line, "%s = %s", program[line_num].var1, program[line_num].var2);
    }
}

void analyze_program(int num_lines) {
    memset(reachable, true, sizeof(reachable));
    for (int i = 0; i < num_lines; i++) {
        if (strcmp(program[i].type, "IF") == 0) {
            int end_if_line = i;
            int else_line = -1;
            for (int j = i + 1; j < num_lines; j++) {
                if (strcmp(program[j].type, "END") == 0) {
                    end_if_line = j;
                    break;
                }
                if (strcmp(program[j].type, "ELSE") == 0) {
                    else_line = j;
                }
            }
            if (else_line != -1) {
                reachable[else_line] = false;
                reachable[end_if_line] = false;
            } else {
                reachable[end_if_line] = false;
            }
        }
    }

    for (int i = 0; i < num_lines; i++) {
        if (!reachable[i]) {
            printf("Warning: Line %d is unreachable.\n", i + 1);
        } else if (strcmp(program[i].type, "RETURN") == 0 || strcmp(program[i].type, "IF") == 0) {
            if (!initialized[program[i].var1[0] - 'A']) {
                printf("Warning: Line %d uses uninitialized variable %s.\n", i + 1, program[i].var1);
            }
        } else if (strcmp(program[i].type, "ASSIGN") == 0) {
            if (!initialized[program[i].var2[0] - 'A']) {
                printf("Warning: Line %d uses uninitialized variable %s.\n", i + 1, program[i].var2);
            }
        }
    }
}

int main() {
    char line[MAX_LINE_LENGTH];
    int line_num = 0;

    while (fgets(line, MAX_LINE_LENGTH, stdin)) {
        line[strcspn(line, "\n")] = 0; // Remove newline character
        parse_line(line, line_num);
        line_num++;
    }

    analyze_program(line_num);

    return 0;
}