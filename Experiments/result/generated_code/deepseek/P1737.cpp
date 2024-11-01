#include <stdio.h>
#include <math.h>

#define MAX_NODES 10000

typedef struct {
    char type;
    int operands[2];
    double constant;
} Node;

Node nodes[MAX_NODES];

void task1() {
    nodes[1].type = 'I';
    nodes[2].type = '+';
    nodes[2].operands[0] = 1;
    nodes[2].operands[1] = 1;
    nodes[3].type = '-';
    nodes[3].operands[0] = 2;
    nodes[4].type = 'I';
    nodes[5].type = '+';
    nodes[5].operands[0] = 4;
    nodes[5].operands[1] = 4;
    nodes[6].type = '-';
    nodes[6].operands[0] = 5;
    nodes[7].type = '+';
    nodes[7].operands[0] = 3;
    nodes[7].operands[1] = 6;
    nodes[8].type = '-';
    nodes[8].operands[0] = 7;
    nodes[9].type = '-';
    nodes[9].operands[0] = 8;
    nodes[10].type = 'O';
    nodes[10].operands[0] = 9;
}

void task2() {
    nodes[1].type = 'I';
    nodes[2].type = 'C';
    nodes[2].operands[0] = 1;
    nodes[2].constant = 17.0;
    nodes[3].type = 'S';
    nodes[3].operands[0] = 2;
    nodes[4].type = 'C';
    nodes[4].operands[0] = 3;
    nodes[4].constant = -1.0;
    nodes[5].type = 'O';
    nodes[5].operands[0] = 4;
}

void task3() {
    nodes[1].type = 'I';
    nodes[2].type = 'P';
    nodes[2].operands[0] = 1;
    nodes[2].operands[1] = 1;
    nodes[3].type = 'O';
    nodes[3].operands[0] = 2;
}

void task4() {
    nodes[1].type = 'I';
    nodes[2].type = 'P';
    nodes[2].operands[0] = 1;
    nodes[2].operands[1] = 1;
    nodes[3].type = 'M';
    nodes[3].operands[0] = 1;
    nodes[3].operands[1] = 2;
    nodes[4].type = 'O';
    nodes[4].operands[0] = 3;
}

void task5() {
    nodes[1].type = 'I';
    for (int i = 2; i <= 32; i++) {
        nodes[i].type = 'I';
    }
    int result = 0;
    for (int i = 1; i <= 32; i++) {
        nodes[32 + i].type = '*';
        nodes[32 + i].operands[0] = i;
        nodes[32 + i].operands[1] = 32 - i;
        result += (1 << (32 - i)) * nodes[32 + i].operands[0];
    }
    nodes[65].type = 'O';
    nodes[65].operands[0] = result;
}

void task6() {
    nodes[1].type = 'I';
    for (int i = 2; i <= 33; i++) {
        nodes[i].type = '>';
        nodes[i].operands[0] = 1;
        nodes[i].operands[1] = 32 - i;
    }
    for (int i = 34; i <= 65; i++) {
        nodes[i].type = 'O';
        nodes[i].operands[0] = i - 32;
    }
}

void task7() {
    nodes[1].type = 'I';
    nodes[2].type = 'I';
    for (int i = 3; i <= 34; i++) {
        nodes[i].type = '>';
        nodes[i].operands[0] = 1;
        nodes[i].operands[1] = 32 - i;
    }
    for (int i = 35; i <= 66; i++) {
        nodes[i].type = '>';
        nodes[i].operands[0] = 2;
        nodes[i].operands[1] = 32 - i;
    }
    for (int i = 67; i <= 98; i++) {
        nodes[i].type = 'P';
        nodes[i].operands[0] = i - 34;
        nodes[i].operands[1] = i - 33;
    }
    for (int i = 99; i <= 130; i++) {
        nodes[i].type = 'M';
        nodes[i].operands[0] = i - 66;
        nodes[i].operands[1] = i - 33;
    }
    nodes[131].type = 'O';
    nodes[131].operands[0] = 130;
}

void task8() {
    nodes[1].type = 'I';
    nodes[2].type = '>';
    nodes[2].operands[0] = 1;
    nodes[2].operands[1] = 1;
    nodes[3].type = 'O';
    nodes[3].operands[0] = 2;
}

void task9() {
    nodes[1].type = 'I';
    for (int i = 2; i <= 16; i++) {
        nodes[i].type = 'I';
    }
    for (int i = 17; i <= 31; i++) {
        nodes[i].type = 'P';
        nodes[i].operands[0] = i - 16;
        nodes[i].operands[1] = i - 15;
    }
    for (int i = 32; i <= 46; i++) {
        nodes[i].type = 'M';
        nodes[i].operands[0] = i - 31;
        nodes[i].operands[1] = i - 16;
    }
    for (int i = 47; i <= 61; i++) {
        nodes[i].type = 'O';
        nodes[i].operands[0] = i - 31;
    }
}

void task10() {
    nodes[1].type = 'I';
    nodes[2].type = 'I';
    nodes[3].type = 'I';
    nodes[4].type = '*';
    nodes[4].operands[0] = 1;
    nodes[4].operands[1] = 2;
    nodes[5].type = 'P';
    nodes[5].operands[0] = 4;
    nodes[5].operands[1] = 3;
    nodes[6].type = 'O';
    nodes[6].operands[0] = 5;
}

int main() {
    int task_number;
    scanf("%d", &task_number);

    switch (task_number) {
        case 1:
            task1();
            break;
        case 2:
            task2();
            break;
        case 3:
            task3();
            break;
        case 4:
            task4();
            break;
        case 5:
            task5();
            break;
        case 6:
            task6();
            break;
        case 7:
            task7();
            break;
        case 8:
            task8();
            break;
        case 9:
            task9();
            break;
        case 10:
            task10();
            break;
    }

    for (int i = 1; i <= MAX_NODES; i++) {
        if (nodes[i].type == '\0') break;
        printf("%c", nodes[i].type);
        if (nodes[i].type == 'I' || nodes[i].type == 'O') {
            printf(" %d\n", nodes[i].operands[0]);
        } else if (nodes[i].type == 'C') {
            printf(" %d %.9f\n", nodes[i].operands[0], nodes[i].constant);
        } else {
            printf(" %d %d\n", nodes[i].operands[0], nodes[i].operands[1]);
        }
    }

    return 0;
}