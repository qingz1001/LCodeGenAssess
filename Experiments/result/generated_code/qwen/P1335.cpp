#include <stdio.h>
#include <stdlib.h>

#define MAX_EVENTS 1000000
#define MAX_VARIABLES 100

typedef struct {
    int type;
    int value;
} Event;

typedef struct {
    int id;
    int value;
} Variable;

int main() {
    FILE *in = fopen("train1.in", "r");
    if (!in) {
        printf("Input file does not exist.\n");
        return 1;
    }

    int n, m;
    fscanf(in, "%d %d", &n, &m);

    Event events[MAX_EVENTS];
    Variable variables[MAX_VARIABLES] = {0};

    for (int i = 0; i < n; i++) {
        char type[2];
        fscanf(in, "%s", type);
        if (type[0] == 'c') {
            fscanf(in, "%d", &events[i].value);
        } else if (type[0] == 'v') {
            fscanf(in, "%d", &events[i].value);
            events[i].type = 1;
        }
    }

    fclose(in);

    FILE *out = fopen("train1.out", "w");
    if (!out) {
        printf("Output file cannot be created.\n");
        return 1;
    }

    int current_event = 1;
    int choices = 0;

    while (current_event > 0 && current_event <= n) {
        if (events[current_event - 1].type == 1) {
            if (events[current_event - 1].value == 1) {
                variables[1].value += events[current_event].value;
            } else {
                variables[1].value -= events[current_event].value;
            }
            current_event++;
        } else if (events[current_event - 1].type == 2) {
            fprintf(out, "1\n");
            choices++;
            current_event = events[current_event].value;
        } else if (events[current_event - 1].type == 3) {
            if (variables[events[current_event].value].value < events[current_event].value) {
                fprintf(out, "1\n");
                choices++;
                current_event = events[current_event + 1].value;
            } else {
                fprintf(out, "2\n");
                choices++;
                current_event = events[current_event + 2].value;
            }
        }
    }

    fclose(out);

    printf("Choices made: %d\n", choices);

    return 0;
}