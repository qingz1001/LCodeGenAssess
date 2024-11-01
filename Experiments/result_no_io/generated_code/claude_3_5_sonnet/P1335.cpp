#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EVENTS 100000
#define MAX_VARS 1000

typedef struct {
    int type;  // 1: 普通事件, 2: 选择跳转, 3: 条件跳转
    int var;   // 变量编号 (仅用于普通事件)
    int op;    // 操作符 (1: +, -1: -) (仅用于普通事件)
    int val;   // 值 (仅用于普通事件)
    int jump1, jump2;  // 跳转目标 (用于选择跳转和条件跳转)
    int cond1_type, cond2_type;  // 条件类型 (0: 常数, 1: 变量) (仅用于条件跳转)
    int cond1_val, cond2_val;    // 条件值 (仅用于条件跳转)
} Event;

Event events[MAX_EVENTS];
int vars[MAX_VARS];
int n, m;

void read_input(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("无法打开文件 %s\n", filename);
        exit(1);
    }

    fscanf(file, "%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        char event_type[3];
        fscanf(file, "%s", event_type);

        if (strcmp(event_type, "v") == 0) {
            int var, op_val;
            char op[2];
            fscanf(file, "%d %s", &var, op);
            if (op[0] == '+') {
                events[i].op = 1;
            } else {
                events[i].op = -1;
            }
            fscanf(file, "%s %d", event_type, &op_val);
            events[i].type = 1;
            events[i].var = var;
            events[i].val = op_val;
        } else if (strcmp(event_type, "s") == 0) {
            events[i].type = 2;
            fscanf(file, "%d %d", &events[i].jump1, &events[i].jump2);
        } else if (strcmp(event_type, "i") == 0) {
            events[i].type = 3;
            char cond1[3], cond2[3];
            fscanf(file, "%s %d %s %d %d %d", cond1, &events[i].cond1_val, cond2, &events[i].cond2_val, &events[i].jump1, &events[i].jump2);
            events[i].cond1_type = (cond1[0] == 'v');
            events[i].cond2_type = (cond2[0] == 'v');
        }
    }

    fclose(file);
}

int simulate(const char* choices, int* choice_count) {
    int pos = 1;
    *choice_count = 0;
    memset(vars, 0, sizeof(vars));

    while (pos >= 1 && pos <= n) {
        Event e = events[pos - 1];

        if (e.type == 1) {
            vars[e.var - 1] += e.op * e.val;
            pos++;
        } else if (e.type == 2) {
            int choice = choices[*choice_count] - '0';
            (*choice_count)++;
            pos = (choice == 1) ? e.jump1 : e.jump2;
        } else if (e.type == 3) {
            int cond1 = e.cond1_type ? vars[e.cond1_val - 1] : e.cond1_val;
            int cond2 = e.cond2_type ? vars[e.cond2_val - 1] : e.cond2_val;
            pos = (cond1 < cond2) ? e.jump1 : e.jump2;
        }
    }

    return vars[0];  // 返回成就值
}

void generate_output(const char* input_file, const char* output_file) {
    read_input(input_file);

    char* best_choices = malloc(MAX_EVENTS);
    int best_score = -1;

    // 简单的随机搜索策略
    for (int i = 0; i < 1000000; i++) {
        char choices[MAX_EVENTS];
        for (int j = 0; j < MAX_EVENTS; j++) {
            choices[j] = (rand() % 2) + '1';
        }

        int choice_count;
        int score = simulate(choices, &choice_count);

        if (score > best_score) {
            best_score = score;
            memcpy(best_choices, choices, choice_count);
            best_choices[choice_count] = '\0';
        }
    }

    FILE* out_file = fopen(output_file, "w");
    if (!out_file) {
        printf("无法创建输出文件 %s\n", output_file);
        exit(1);
    }

    for (int i = 0; best_choices[i]; i++) {
        fprintf(out_file, "%c\n", best_choices[i]);
    }

    fclose(out_file);
    free(best_choices);
}

int main() {
    srand(time(NULL));

    for (int i = 1; i <= 10; i++) {
        char input_file[20], output_file[20];
        sprintf(input_file, "train%d.in", i);
        sprintf(output_file, "train%d.out", i);
        generate_output(input_file, output_file);
        printf("已生成 %s\n", output_file);
    }

    return 0;
}