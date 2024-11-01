#include <stdio.h>
#include <stdlib.h>

#define MAX_EVENTS 1000000
#define MAX_VARIABLES 100

typedef struct {
    int type; // 0: constant, 1: variable
    int value;
} Quantity;

typedef struct {
    int type; // 0: normal, 1: choice, 2: conditional
    int variable;
    Quantity quantity;
    int choice1;
    int choice2;
} Event;

Event events[MAX_EVENTS];
int num_events = 0;
int num_variables = 0;

void parse_quantity(char *str, Quantity *q) {
    if (str[0] == 'c') {
        q->type = 0;
        q->value = atoi(str + 2);
    } else if (str[0] == 'v') {
        q->type = 1;
        q->value = atoi(str + 2);
    }
}

void parse_event(char *str) {
    Event e;
    char *token = strtok(str, " ");
    if (token[0] == 'v') {
        e.type = 0;
        e.variable = atoi(token + 2);
        token = strtok(NULL, " ");
        if (token[0] == '+') {
            e.quantity.type = 0;
            e.quantity.value = atoi(token + 2);
        } else if (token[0] == '-') {
            e.quantity.type = 0;
            e.quantity.value = -atoi(token + 2);
        }
    } else if (token[0] == 's') {
        e.type = 1;
        token = strtok(NULL, " ");
        e.choice1 = atoi(token);
        token = strtok(NULL, " ");
        e.choice2 = atoi(token);
    } else if (token[0] == 'i') {
        e.type = 2;
        token = strtok(NULL, " ");
        parse_quantity(token, &e.quantity);
        token = strtok(NULL, " ");
        parse_quantity(token, &e.quantity);
        token = strtok(NULL, " ");
        e.choice1 = atoi(token);
        token = strtok(NULL, " ");
        e.choice2 = atoi(token);
    }
    events[num_events++] = e;
}

int main() {
    FILE *input_file = fopen("train1.in", "r");
    FILE *output_file = fopen("train1.out", "w");
    fscanf(input_file, "%d %d", &num_events, &num_variables);

    char line[100];
    for (int i = 0; i < num_events; i++) {
        fgets(line, sizeof(line), input_file);
        parse_event(line);
    }

    int current_event = 0;
    int achievements = 0;

    while (current_event < num_events) {
        Event e = events[current_event];
        if (e.type == 0) {
            if (e.quantity.type == 0) {
                achievements += e.quantity.value;
            } else {
                // Variable value increment/decrement
            }
        } else if (e.type == 1) {
            // Choice
            fprintf(output_file, "1\n");
            current_event = e.choice1 - 1;
        } else if (e.type == 2) {
            // Conditional
            if (e.quantity.type == 0) {
                if (e.quantity.value < e.choice1) {
                    fprintf(output_file, "1\n");
                    current_event = e.choice1 - 1;
                } else {
                    fprintf(output_file, "2\n");
                    current_event = e.choice2 - 1;
                }
            } else {
                // Variable comparison
            }
        }
        current_event++;
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}