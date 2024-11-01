#include <stdio.h>
#include <math.h>

void task1() {
    printf("I\n");
    printf("I\n");
    printf("+ 1 2\n");
    printf("< 3 1\n");
    printf("- 4\n");
    printf("O 5\n");
}

void task2() {
    printf("I\n");
    printf("< 1 4\n");
    printf("C 2 17\n");
    printf("S 3\n");
    printf("C 4 1\n");
    printf("- 5\n");
    printf("C 6 1\n");
    printf("/ 6 5\n");
    printf("O 7\n");
}

void task3() {
    printf("I\n");
    printf("P 1 1\n");
    printf("O 2\n");
}

void task4() {
    printf("I\n");
    printf("P 1 1\n");
    printf("< 2 1\n");
    printf("C 3 1\n");
    printf("- 1\n");
    printf("M 4 5\n");
    printf("O 6\n");
}

void task5() {
    int i;
    for (i = 0; i < 32; i++) {
        printf("I\n");
    }
    for (i = 1; i <= 31; i++) {
        printf("< %d 1\n", i);
    }
    for (i = 1; i <= 31; i++) {
        printf("+ %d %d\n", i+32, i+33);
    }
    printf("O 64\n");
}

void task6() {
    printf("I\n");
    int i;
    for (i = 0; i < 32; i++) {
        printf("> 1 %d\n", i);
        printf("C %d 1\n", i+2);
        printf("P %d %d\n", i+2, i+3);
        printf("O %d\n", i+4);
    }
}

void task7() {
    printf("I\n");
    printf("I\n");
    int i;
    for (i = 0; i < 32; i++) {
        printf("> 1 %d\n", i);
        printf("> 2 %d\n", i);
        printf("C %d 1\n", 2*i+3);
        printf("P %d %d\n", 2*i+3, 2*i+4);
        printf("C %d 1\n", 2*i+5);
        printf("P %d %d\n", 2*i+5, 2*i+6);
        printf("+ %d %d\n", 2*i+7, 2*i+8);
        printf("< %d %d\n", 2*i+9, i);
    }
    for (i = 0; i < 31; i++) {
        printf("+ %d %d\n", 65+i*2, 67+i*2);
    }
    printf("O 127\n");
}

void task8() {
    printf("I\n");
    printf("> 1 1\n");
    printf("C 2 0.1\n");
    printf("* 1 2\n");
    printf("O 3\n");
}

void task9() {
    int i, j;
    for (i = 0; i < 16; i++) {
        printf("I\n");
    }
    for (i = 0; i < 15; i++) {
        for (j = i+1; j < 16; j++) {
            printf("P %d %d\n", i+1, j+1);
            printf("C %d 1\n", 16+i*15+j);
            printf("P %d %d\n", 17+i*15+j, 18+i*15+j);
            printf("M %d %d\n", i+1, j+1);
            printf("M %d %d\n", 19+i*15+j, 20+i*15+j);
        }
    }
    for (i = 0; i < 16; i++) {
        printf("O %d\n", 241+i);
    }
}

void task10() {
    printf("I\n");
    printf("I\n");
    printf("I\n");
    printf("* 1 2\n");
    printf("/ 4 3\n");
    printf("* 5 3\n");
    printf("- 4 6\n");
    printf("O 7\n");
}

int main() {
    int task;
    scanf("%d", &task);
    switch(task) {
        case 1: task1(); break;
        case 2: task2(); break;
        case 3: task3(); break;
        case 4: task4(); break;
        case 5: task5(); break;
        case 6: task6(); break;
        case 7: task7(); break;
        case 8: task8(); break;
        case 9: task9(); break;
        case 10: task10(); break;
    }
    return 0;
}