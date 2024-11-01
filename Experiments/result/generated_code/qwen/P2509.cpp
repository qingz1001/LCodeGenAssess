#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 50
#define MAX_VARIABLES 26

typedef struct {
    int reachable;
    int initialized[MAX_VARIABLES];
} LineInfo;

void analyze_program(const char* program[], int line_count) {
    LineInfo lines[MAX_LINES];
    for (int i = 0; i < line_count; i++) {
        lines[i].reachable = 0;
        memset(lines[i].initialized, 0, sizeof(lines[i].initialized));
    }

    // Mark the first line as reachable and initialize parameters
    lines[0].reachable = 1;
    const char* head_line = program[0];
    if (strncmp(head_line, "PARAM", 5) == 0) {
        const char* var = head_line + 6;
        while (*var != '\0') {
            if (*var >= 'A' && *var <= 'Z') {
                lines[0].initialized[*var - 'A'] = 1;
            }
            var++;
        }
    } else {
        printf("Invalid head line\n");
        return;
    }

    // Analyze each line to mark reachability and initialization
    for (int i = 1; i < line_count; i++) {
        const char* line = program[i];
        if (strncmp(line, "IF", 2) == 0 || strncmp(line, "ELSE", 4) == 0 || strncmp(line, "END IF", 6) == 0) {
            continue;
        }
        if (strncmp(line, "RETURN", 6) == 0) {
            lines[i].reachable = 1;
            continue;
        }
        const char* equals = strchr(line, '=');
        if (equals != NULL) {
            char var = *(equals - 1);
            if (var >= 'A' && var <= 'Z') {
                lines[i].reachable = 1;
                lines[i].initialized[var - 'A'] = 1;
            }
        }
    }

    // Check for unreachable code and uninitialzed variables
    for (int i = 0; i < line_count; i++) {
        if (!lines[i].reachable) {
            printf("Line %d: unreachable code\n", i + 1);
        }
        for (int j = 0; j < MAX_VARIABLES; j++) {
            if (lines[i].initialized[j]) {
                continue;
            }
            char var = 'A' + j;
            printf("Line %d: variable %c might not have been initialized\n", i + 1, var);
        }
    }
}

int main() {
    const char* program[MAX_LINES];
    int line_count = 0;

    while (fgets(program[line_count], 256, stdin) != NULL) {
        line_count++;
        if (line_count >= MAX_LINES) {
            break;
        }
    }

    analyze_program(program, line_count);

    return 0;
}