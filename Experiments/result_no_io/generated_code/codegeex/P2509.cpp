#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE 50

typedef struct {
    bool is_initialized;
    int value;
} Variable;

Variable variables[26];
int num_lines;
char lines[MAX_LINE][100];

void initialize_variables(char* params) {
    char* token = strtok(params, " ");
    while (token != NULL) {
        int index = token[0] - 'A';
        variables[index].is_initialized = true;
        token = strtok(NULL, " ");
    }
}

bool is_variable_initialized(char c) {
    int index = c - 'A';
    return variables[index].is_initialized;
}

void process_assignment(char* line) {
    char* token = strtok(line, " =");
    char variable = token[0];
    int index = variable - 'A';
    variables[index].is_initialized = true;
    token = strtok(NULL, " =");
    variables[index].value = atoi(token);
}

bool evaluate_expression(char* variable, char* relation, char* value) {
    int var_value = variables[variable[0] - 'A'].value;
    int val_value = atoi(value);
    if (relation[0] == '<') {
        return var_value < val_value;
    } else if (relation[0] == '=') {
        return var_value == val_value;
    } else if (relation[0] == '>') {
        return var_value > val_value;
    }
    return false;
}

void process_if_statement(int line_index, bool* reachable) {
    char* line = lines[line_index];
    char* token = strtok(line, " <=");
    char variable = token[0];
    token = strtok(NULL, " <=");
    char relation = token[0];
    token = strtok(NULL, " <=");
    bool condition = evaluate_expression(&variable, &relation, token);
    int else_index = -1, end_if_index = -1;
    for (int i = line_index + 1; i < num_lines; i++) {
        if (strcmp(lines[i], "ELSE") == 0) {
            else_index = i;
        } else if (strcmp(lines[i], "END IF") == 0) {
            end_if_index = i;
            break;
        }
    }
    bool* new_reachable = (bool*)malloc(sizeof(bool) * (num_lines + 1));
    memcpy(new_reachable, reachable, sizeof(bool) * (line_index + 1));
    for (int i = line_index + 1; i < end_if_index; i++) {
        new_reachable[i] = false;
    }
    if (else_index != -1) {
        for (int i = else_index + 1; i < end_if_index; i++) {
            new_reachable[i] = true;
        }
    }
    if (condition) {
        process_if_statement(end_if_index, new_reachable);
    } else {
        if (else_index != -1) {
            process_if_statement(else_index, reachable);
        }
    }
    free(new_reachable);
}

void print_unreachable_lines(bool* reachable) {
    for (int i = 0; i < num_lines; i++) {
        if (!reachable[i]) {
            printf("%d\n", i + 1);
        }
    }
}

void print_uninitialized_variables() {
    for (int i = 0; i < num_lines; i++) {
        char* line = lines[i];
        if (strncmp(line, "RETURN", 6) == 0) {
            char* token = strtok(line, " ");
            token = strtok(NULL, " ");
            if (!is_variable_initialized(token[0])) {
                printf("%d: %c\n", i + 1, token[0]);
            }
        } else if (strncmp(line, "IF", 2) == 0) {
            char* token = strtok(line, " ");
            token = strtok(NULL, " ");
            if (!is_variable_initialized(token[0])) {
                printf("%d: %c\n", i + 1, token[0]);
            }
        }
    }
}

int main() {
    char first_line[100];
    fgets(first_line, sizeof(first_line), stdin);
    initialize_variables(first_line);
    for (int i = 1; i < MAX_LINE; i++) {
        char line[100];
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }
        num_lines++;
        strcpy(lines[i], line);
    }
    bool reachable[num_lines + 1];
    memset(reachable, true, sizeof(reachable));
    reachable[0] = true;
    process_if_statement(0, reachable);
    print_unreachable_lines(reachable);
    print_uninitialized_variables();
    return 0;
}