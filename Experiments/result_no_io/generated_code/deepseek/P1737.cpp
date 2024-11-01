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
    // Input nodes
    nodes[1].type = 'I';
    nodes[2].type = 'I';

    // Calculate -2a
    nodes[3].type = 'C';
    nodes[3].operands[0] = 1;
    nodes[3].constant = -2.0;

    // Calculate -2b
    nodes[4].type = 'C';
    nodes[4].operands[0] = 2;
    nodes[4].constant = -2.0;

    // Sum -2a and -2b
    nodes[5].type = '+';
    nodes[5].operands[0] = 3;
    nodes[5].operands[1] = 4;

    // Output result
    nodes[6].type = 'O';
    nodes[6].operands[0] = 5;

    // Print nodes
    for (int i = 1; i <= 6; i++) {
        printf("%c", nodes[i].type);
        if (nodes[i].type == 'I' || nodes[i].type == 'O') {
            printf("\n");
        } else if (nodes[i].type == 'C') {
            printf(" %d %lf\n", nodes[i].operands[0], nodes[i].constant);
        } else {
            printf(" %d %d\n", nodes[i].operands[0], nodes[i].operands[1]);
        }
    }
}

void task2() {
    // Input node
    nodes[1].type = 'I';

    // Calculate 17a
    nodes[2].type = 'C';
    nodes[2].operands[0] = 1;
    nodes[2].constant = 17.0;

    // Calculate e^(17a)
    nodes[3].type = 'S';
    nodes[3].operands[0] = 2;

    // Calculate 1 + e^(17a)
    nodes[4].type = 'C';
    nodes[4].operands[0] = 3;
    nodes[4].constant = 1.0;

    // Calculate 1 / (1 + e^(17a))
    nodes[5].type = '/';
    nodes[5].operands[0] = 4;
    nodes[5].operands[1] = 3;

    // Output result
    nodes[6].type = 'O';
    nodes[6].operands[0] = 5;

    // Print nodes
    for (int i = 1; i <= 6; i++) {
        printf("%c", nodes[i].type);
        if (nodes[i].type == 'I' || nodes[i].type == 'O') {
            printf("\n");
        } else if (nodes[i].type == 'C') {
            printf(" %d %lf\n", nodes[i].operands[0], nodes[i].constant);
        } else {
            printf(" %d %d\n", nodes[i].operands[0], nodes[i].operands[1]);
        }
    }
}

void task3() {
    // Input node
    nodes[1].type = 'I';

    // Compare with 0
    nodes[2].type = 'P';
    nodes[2].operands[0] = 1;
    nodes[2].operands[1] = 0;

    // Output result
    nodes[3].type = 'O';
    nodes[3].operands[0] = 2;

    // Print nodes
    for (int i = 1; i <= 3; i++) {
        printf("%c", nodes[i].type);
        if (nodes[i].type == 'I' || nodes[i].type == 'O') {
            printf("\n");
        } else {
            printf(" %d %d\n", nodes[i].operands[0], nodes[i].operands[1]);
        }
    }
}

void task4() {
    // Input node
    nodes[1].type = 'I';

    // Compare with 0
    nodes[2].type = 'P';
    nodes[2].operands[0] = 1;
    nodes[2].operands[1] = 0;

    // Calculate absolute value
    nodes[3].type = 'M';
    nodes[3].operands[0] = 1;
    nodes[3].operands[1] = 2;

    // Output result
    nodes[4].type = 'O';
    nodes[4].operands[0] = 3;

    // Print nodes
    for (int i = 1; i <= 4; i++) {
        printf("%c", nodes[i].type);
        if (nodes[i].type == 'I' || nodes[i].type == 'O') {
            printf("\n");
        } else {
            printf(" %d %d\n", nodes[i].operands[0], nodes[i].operands[1]);
        }
    }
}

void task5() {
    // Input nodes
    for (int i = 1; i <= 32; i++) {
        nodes[i].type = 'I';
    }

    // Calculate binary value
    int result = 0;
    for (int i = 1; i <= 32; i++) {
        nodes[32 + i].type = '*';
        nodes[32 + i].operands[0] = i;
        nodes[32 + i].operands[1] = (1 << (32 - i));
        result += (1 << (32 - i));
    }

    // Output result
    nodes[65].type = 'O';
    nodes[65].operands[0] = 64;

    // Print nodes
    for (int i = 1; i <= 65; i++) {
        printf("%c", nodes[i].type);
        if (nodes[i].type == 'I' || nodes[i].type == 'O') {
            printf("\n");
        } else {
            printf(" %d %d\n", nodes[i].operands[0], nodes[i].operands[1]);
        }
    }
}

void task6() {
    // Input node
    nodes[1].type = 'I';

    // Output binary representation
    for (int i = 0; i < 32; i++) {
        nodes[2 + i].type = '>';
        nodes[2 + i].operands[0] = 1;
        nodes[2 + i].operands[1] = i;
        nodes[34 + i].type = 'O';
        nodes[34 + i].operands[0] = 2 + i;
    }

    // Print nodes
    for (int i = 1; i <= 65; i++) {
        printf("%c", nodes[i].type);
        if (nodes[i].type == 'I' || nodes[i].type == 'O') {
            printf("\n");
        } else {
            printf(" %d %d\n", nodes[i].operands[0], nodes[i].operands[1]);
        }
    }
}

void task7() {
    // Input nodes
    nodes[1].type = 'I';
    nodes[2].type = 'I';

    // XOR operation
    for (int i = 0; i < 32; i++) {
        nodes[3 + i].type = '>';
        nodes[3 + i].operands[0] = 1;
        nodes[3 + i].operands[1] = i;
        nodes[35 + i].type = '>';
        nodes[35 + i].operands[0] = 2;
        nodes[35 + i].operands[1] = i;
        nodes[67 + i].type = 'P';
        nodes[67 + i].operands[0] = 3 + i;
        nodes[67 + i].operands[1] = 35 + i;
        nodes[99 + i].type = 'M';
        nodes[99 + i].operands[0] = 67 + i;
        nodes[99 + i].operands[1] = 67 + i;
    }

    // Output result
    nodes[131].type = 'O';
    nodes[131].operands[0] = 130;

    // Print nodes
    for (int i = 1; i <= 131; i++) {
        printf("%c", nodes[i].type);
        if (nodes[i].type == 'I' || nodes[i].type == 'O') {
            printf("\n");
        } else {
            printf(" %d %d\n", nodes[i].operands[0], nodes[i].operands[1]);
        }
    }
}

void task8() {
    // Input node
    nodes[1].type = 'I';

    // Calculate a / 10
    nodes[2].type = '>';
    nodes[2].operands[0] = 1;
    nodes[2].operands[1] = -1;

    // Output result
    nodes[3].type = 'O';
    nodes[3].operands[0] = 2;

    // Print nodes
    for (int i = 1; i <= 3; i++) {
        printf("%c", nodes[i].type);
        if (nodes[i].type == 'I' || nodes[i].type == 'O') {
            printf("\n");
        } else {
            printf(" %d %d\n", nodes[i].operands[0], nodes[i].operands[1]);
        }
    }
}

void task9() {
    // Input nodes
    for (int i = 1; i <= 16; i++) {
        nodes[i].type = 'I';
    }

    // Sorting
    for (int i = 1; i <= 16; i++) {
        for (int j = i + 1; j <= 16; j++) {
            nodes[16 + (i - 1) * 16 + j].type = 'P';
            nodes[16 + (i - 1) * 16 + j].operands[0] = i;
            nodes[16 + (i - 1) * 16 + j].operands[1] = j;
            nodes[272 + (i - 1) * 16 + j].type = 'M';
            nodes[272 + (i - 1) * 16 + j].operands[0] = i;
            nodes[272 + (i - 1) * 16 + j].operands[1] = j;
        }
    }

    // Output sorted result
    for (int i = 1; i <= 16; i++) {
        nodes[528 + i].type = 'O';
        nodes[528 + i].operands[0] = 527 + i;
    }

    // Print nodes
    for (int i = 1; i <= 544; i++) {
        printf("%c", nodes[i].type);
        if (nodes[i].type == 'I' || nodes[i].type == 'O') {
            printf("\n");
        } else {
            printf(" %d %d\n", nodes[i].operands[0], nodes[i].operands[1]);
        }
    }
}

void task10() {
    // Input nodes
    nodes[1].type = 'I';
    nodes[2].type = 'I';
    nodes[3].type = 'I';

    // Calculate a * b
    nodes[4].type = '*';
    nodes[4].operands[0] = 1;
    nodes[4].operands[1] = 2;

    // Calculate (a * b) % m
    nodes[5].type = '%';
    nodes[5].operands[0] = 4;
    nodes[5].operands[1] = 3;

    // Output result
    nodes[6].type = 'O';
    nodes[6].operands[0] = 5;

    // Print nodes
    for (int i = 1; i <= 6; i++) {
        printf("%c", nodes[i].type);
        if (nodes[i].type == 'I' || nodes[i].type == 'O') {
            printf("\n");
        } else {
            printf(" %d %d\n", nodes[i].operands[0], nodes[i].operands[1]);
        }
    }
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
        default:
            printf("Invalid task number\n");
            break;
    }

    return 0;
}