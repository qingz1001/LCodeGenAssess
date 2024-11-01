#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 50
#define MAX_LINE_LENGTH 100
#define MAX_VARIABLES 26

typedef struct {
    int line;
    char variable[MAX_VARIABLES];
} Warning;

int is_valid_variable(char *var) {
    return var[0] >= 'A' && var[0] <= 'Z';
}

void parse_assignment(const char *line, char *variable, int *value) {
    sscanf(line, "%s = %d", variable, value);
}

void parse_if(const char *line, char *variable, int *value, char *relation) {
    sscanf(line, "IF %s %s %d THEN", variable, relation, value);
}

void find_unreachable_lines(int num_lines, const char lines[MAX_LINES][MAX_LINE_LENGTH], int *unreachable_lines, int *num_unreachable) {
    for (int i = 1; i < num_lines - 1; i++) {
        if (strncmp(lines[i], "IF ", 3) == 0 || strncmp(lines[i], "ELSE", 4) == 0 || strncmp(lines[i], "END IF", 6) == 0) {
            unreachable_lines[*num_unreachable] = i;
            (*num_unreachable)++;
        }
    }
}

void find_undefined_variables(int num_lines, const char lines[MAX_LINES][MAX_LINE_LENGTH], int *defined_vars, int *num_defined, int *warnings, int *num_warnings) {
    for (int i = 1; i < num_lines - 1; i++) {
        char line[MAX_LINE_LENGTH];
        strcpy(line, lines[i]);
        char *token = strtok(line, " ");
        while (token != NULL) {
            if (is_valid_variable(token)) {
                if (!defined_vars[token[0] - 'A']) {
                    warnings[*num_warnings].line = i + 1;
                    snprintf(warnings[*num_warnings].variable, MAX_VARIABLES, "%s", token);
                    (*num_warnings)++;
                }
                defined_vars[token[0] - 'A'] = 1;
            }
            token = strtok(NULL, " ");
        }
    }
}

int main() {
    int num_lines;
    scanf("%d\n", &num_lines);

    char lines[MAX_LINES][MAX_LINE_LENGTH];
    for (int i = 0; i < num_lines; i++) {
        fgets(lines[i], MAX_LINE_LENGTH, stdin);
    }

    int unreachable_lines[MAX_LINES];
    int num_unreachable = 0;
    find_unreachable_lines(num_lines, lines, unreachable_lines, &num_unreachable);

    int defined_vars[MAX_VARIABLES] = {0};
    int num_defined = 0;
    Warning warnings[MAX_LINES * MAX_VARIABLES];
    int num_warnings = 0;
    find_undefined_variables(num_lines, lines, defined_vars, &num_defined, warnings, &num_warnings);

    // Sort warnings by line number and then by variable name
    for (int i = 0; i < num_warnings - 1; i++) {
        for (int j = i + 1; j < num_warnings; j++) {
            if (warnings[i].line > warnings[j].line || (warnings[i].line == warnings[j].line && strcmp(warnings[i].variable, warnings[j].variable) > 0)) {
                Warning temp = warnings[i];
                warnings[i] = warnings[j];
                warnings[j] = temp;
            }
        }
    }

    // Print warnings
    for (int i = 0; i < num_unreachable; i++) {
        printf("Line %d: Unreachable code.\n", unreachable_lines[i] + 1);
    }
    for (int i = 0; i < num_warnings; i++) {
        printf("Line %d: Undefined variable %s.\n", warnings[i].line, warnings[i].variable);
    }

    return 0;
}