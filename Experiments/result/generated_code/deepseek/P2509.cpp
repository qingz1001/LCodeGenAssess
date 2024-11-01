#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 50
#define MAX_LINE_LENGTH 100

typedef struct {
    int line;
    char var;
    int type; // 0: unreachable, 1: uninitialized
} Warning;

int compare_warnings(const void *a, const void *b) {
    Warning *wa = (Warning *)a;
    Warning *wb = (Warning *)b;
    if (wa->line != wb->line) return wa->line - wb->line;
    if (wa->type != wb->type) return wa->type - wb->type;
    return wa->var - wb->var;
}

int main() {
    char lines[MAX_LINES][MAX_LINE_LENGTH];
    int line_count = 0;
    while (fgets(lines[line_count], MAX_LINE_LENGTH, stdin)) {
        lines[line_count][strcspn(lines[line_count], "\n")] = 0;
        line_count++;
    }

    int params[26] = {0};
    int initialized[26] = {0};
    int reachable[MAX_LINES] = {0};
    Warning warnings[MAX_LINES * 26];
    int warning_count = 0;

    // Parse the PARAM line
    char *param_line = lines[0];
    char *token = strtok(param_line, " ");
    token = strtok(NULL, " ");
    while (token != NULL) {
        if (isupper(token[0])) {
            params[token[0] - 'A'] = 1;
        }
        token = strtok(NULL, " ");
    }

    // Mark the first line as reachable
    reachable[0] = 1;

    // Process each line
    for (int i = 0; i < line_count; i++) {
        char *line = lines[i];
        if (strncmp(line, "IF", 2) == 0) {
            reachable[i] = 1;
            reachable[i + 1] = 1; // Assume the next line is reachable
        } else if (strncmp(line, "ELSE", 4) == 0) {
            reachable[i + 1] = 1; // Assume the next line is reachable
        } else if (strncmp(line, "END IF", 6) == 0) {
            reachable[i] = 1;
        } else if (strncmp(line, "RETURN", 6) == 0) {
            reachable[i] = 1;
        } else if (strncmp(line, "PARAM", 5) == 0) {
            // Do nothing
        } else {
            // Assignment statement
            reachable[i] = 1;
            char *token = strtok(line, " =");
            if (isupper(token[0])) {
                initialized[token[0] - 'A'] = 1;
            }
            token = strtok(NULL, " ");
            while (token != NULL) {
                if (isupper(token[0])) {
                    if (!params[token[0] - 'A'] && !initialized[token[0] - 'A']) {
                        warnings[warning_count].line = i + 1;
                        warnings[warning_count].var = token[0];
                        warnings[warning_count].type = 1;
                        warning_count++;
                    }
                }
                token = strtok(NULL, " ");
            }
        }
    }

    // Check for unreachable code
    for (int i = 1; i < line_count; i++) {
        if (!reachable[i]) {
            warnings[warning_count].line = i + 1;
            warnings[warning_count].var = 0;
            warnings[warning_count].type = 0;
            warning_count++;
        }
    }

    // Sort warnings
    qsort(warnings, warning_count, sizeof(Warning), compare_warnings);

    // Print warnings
    for (int i = 0; i < warning_count; i++) {
        if (warnings[i].type == 0) {
            printf("Line %d: unreachable code\n", warnings[i].line);
        } else {
            printf("Line %d: variable %c might not have been initialized\n", warnings[i].line, warnings[i].var);
        }
    }

    return 0;
}