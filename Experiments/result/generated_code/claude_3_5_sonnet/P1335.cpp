#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EVENTS 100000
#define MAX_VARIABLES 1000

typedef long long ll;

enum EventType {
    NORMAL,
    CHOICE,
    CONDITION
};

struct Event {
    enum EventType type;
    int var;
    char op;
    ll value;
    int choice1, choice2;
    ll cond1, cond2;
};

struct Event events[MAX_EVENTS];
ll variables[MAX_VARIABLES];
int n, m;

void read_input(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file\n");
        exit(1);
    }

    fscanf(file, "%d %d", &n, &m);

    char type[5], value_type[5];
    for (int i = 0; i < n; i++) {
        fscanf(file, "%s", type);
        if (type[0] == 'v') {
            fscanf(file, "%d %c %s %lld", &events[i].var, &events[i].op, value_type, &events[i].value);
            events[i].type = NORMAL;
        } else if (type[0] == 's') {
            fscanf(file, "%d %d", &events[i].choice1, &events[i].choice2);
            events[i].type = CHOICE;
        } else if (type[0] == 'i') {
            char cond1_type[5], cond2_type[5];
            int cond1_val, cond2_val;
            fscanf(file, "%s %d %s %d %d %d", cond1_type, &cond1_val, cond2_type, &cond2_val, &events[i].choice1, &events[i].choice2);
            events[i].type = CONDITION;
            events[i].cond1 = (cond1_type[0] == 'c') ? cond1_val : variables[cond1_val];
            events[i].cond2 = (cond2_type[0] == 'c') ? cond2_val : variables[cond2_val];
        }
    }

    fclose(file);
}

void simulate(const char* output_filename) {
    FILE* output = fopen(output_filename, "w");
    if (!output) {
        printf("Error opening output file\n");
        exit(1);
    }

    int pos = 1;
    int choice_count = 0;
    while (pos <= n) {
        struct Event e = events[pos - 1];
        if (e.type == NORMAL) {
            if (e.op == '+') {
                variables[e.var] += e.value;
            } else {
                variables[e.var] -= e.value;
            }
            pos++;
        } else if (e.type == CHOICE) {
            int choice = (rand() % 2) + 1;
            fprintf(output, "%d\n", choice);
            pos = (choice == 1) ? e.choice1 : e.choice2;
            choice_count++;
        } else if (e.type == CONDITION) {
            pos = (e.cond1 < e.cond2) ? e.choice1 : e.choice2;
        }

        if (choice_count > 1000000) {
            printf("Exceeded maximum number of choices\n");
            fclose(output);
            exit(1);
        }
    }

    fclose(output);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    read_input(argv[1]);
    simulate(argv[2]);

    return 0;
}