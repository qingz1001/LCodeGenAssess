#include <stdio.h>
#include <stdlib.h>

#define MAX_EVENTS 1000000
#define MAX_VARIABLES 100

typedef enum {
    EVENT_TYPE_CONSTANT,
    EVENT_TYPE_VARIABLE,
    EVENT_TYPE_NORMAL,
    EVENT_TYPE_CHOICE_JUMP,
    EVENT_TYPE_CONDITIONAL_JUMP
} EventType;

typedef struct {
    EventType type;
    int value;
} Event;

typedef struct {
    int id;
    int value;
} Variable;

Event events[MAX_EVENTS];
Variable variables[MAX_VARIABLES];

int execute_script(int n, int m) {
    int current_event = 0;
    int choice_count = 0;

    while (current_event >= 0 && current_event < n) {
        Event event = events[current_event];

        switch (event.type) {
            case EVENT_TYPE_CONSTANT:
                // Constants are ignored in this context
                break;
            case EVENT_TYPE_VARIABLE:
                // Variables are ignored in this context
                break;
            case EVENT_TYPE_NORMAL:
                if (event.value == 1) {
                    variables[0].value++;
                } else {
                    variables[0].value--;
                }
                current_event++;
                break;
            case EVENT_TYPE_CHOICE_JUMP:
                printf("%d\n", event.value);
                choice_count++;
                current_event = rand() % 2 == 0 ? event.value : event.value + 1;
                break;
            case EVENT_TYPE_CONDITIONAL_JUMP:
                if (variables[event.value].value < event.value + 2) {
                    current_event = event.value;
                } else {
                    current_event = event.value + 1;
                }
                break;
        }
    }

    return choice_count;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        char type[2];
        scanf("%s", type);
        if (type[0] == 'c') {
            events[i].type = EVENT_TYPE_CONSTANT;
            scanf("%d", &events[i].value);
        } else if (type[0] == 'v') {
            events[i].type = EVENT_TYPE_VARIABLE;
            scanf("%d", &events[i].value);
        } else if (type[0] == 's') {
            events[i].type = EVENT_TYPE_CHOICE_JUMP;
            scanf("%d %d", &events[i].value, &events[i+1].value);
            i++; // Skip the next event as it's already read
        } else if (type[0] == 'i') {
            events[i].type = EVENT_TYPE_CONDITIONAL_JUMP;
            scanf("%d %d %d %d", &events[i].value, &events[i+1].value, &events[i+2].value, &events[i+3].value);
            i += 3; // Skip the next three events as they're already read
        }
    }

    srand(time(NULL));
    execute_script(n, m);

    return 0;
}