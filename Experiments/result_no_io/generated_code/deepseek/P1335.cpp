#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EVENTS 100000
#define MAX_VARS 100
#define MAX_LINE_LENGTH 100

typedef struct {
    int type; // 0: constant, 1: variable
    int value;
} Quantity;

typedef struct {
    int type; // 0: normal, 1: select jump, 2: conditional jump
    int var;
    Quantity q1, q2;
    int jump1, jump2;
} Event;

int n, m;
int variables[MAX_VARS];
Event events[MAX_EVENTS];

Quantity parse_quantity(char *token) {
    Quantity q;
    if (token[0] == 'c') {
        q.type = 0;
        q.value = atoi(token + 2);
    } else if (token[0] == 'v') {
        q.type = 1;
        q.value = atoi(token + 2);
    }
    return q;
}

void parse_event(char *line, int index) {
    char *token = strtok(line, " ");
    if (strcmp(token, "v") == 0) {
        events[index].type = 0;
        events[index].var = atoi(strtok(NULL, " "));
        token = strtok(NULL, " ");
        if (strcmp(token, "+") == 0) {
            events[index].q1 = parse_quantity(strtok(NULL, " "));
        } else if (strcmp(token, "-") == 0) {
            events[index].q1 = parse_quantity(strtok(NULL, " "));
        }
    } else if (strcmp(token, "s") == 0) {
        events[index].type = 1;
        events[index].jump1 = atoi(strtok(NULL, " "));
        events[index].jump2 = atoi(strtok(NULL, " "));
    } else if (strcmp(token, "i") == 0) {
        events[index].type = 2;
        events[index].q1 = parse_quantity(strtok(NULL, " "));
        events[index].q2 = parse_quantity(strtok(NULL, " "));
        events[index].jump1 = atoi(strtok(NULL, " "));
        events[index].jump2 = atoi(strtok(NULL, " "));
    }
}

int main() {
    FILE *input = fopen("train1.in", "r");
    FILE *output = fopen("train1.out", "w");

    fscanf(input, "%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        variables[i] = 0;
    }

    char line[MAX_LINE_LENGTH];
    for (int i = 0; i < n; i++) {
        fgets(line, MAX_LINE_LENGTH, input);
        parse_event(line, i);
    }

    int current_event = 0;
    int choice_count = 0;
    while (current_event < n) {
        Event *event = &events[current_event];
        if (event->type == 0) {
            if (event->q1.type == 0) {
                variables[event->var] += event->q1.value;
            } else {
                variables[event->var] += variables[event->q1.value];
            }
            current_event++;
        } else if (event->type == 1) {
            fprintf(output, "1\n");
            current_event = event->jump1;
            choice_count++;
        } else if (event->type == 2) {
            int val1 = (event->q1.type == 0) ? event->q1.value : variables[event->q1.value];
            int val2 = (event->q2.type == 0) ? event->q2.value : variables[event->q2.value];
            if (val1 < val2) {
                current_event = event->jump1;
            } else {
                current_event = event->jump2;
            }
        }
    }

    fclose(input);
    fclose(output);
    return 0;
}