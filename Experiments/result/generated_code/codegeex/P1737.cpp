#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void solve_task1() {
    printf("I\n");
    printf("+ 1 1\n");
    printf("- 2\n");
    printf("I\n");
    printf("+ 4 4\n");
    printf("- 5\n");
    printf("+ 3 6\n");
    printf("- 7\n");
    printf("- 8\n");
    printf("O 9\n");
}

void solve_task2() {
    printf("I\n");
    printf("C 1 17\n");
    printf("S 2\n");
    printf("C 3 1\n");
    printf("O 4\n");
}

void solve_task3() {
    printf("I\n");
    printf("C 1 0\n");
    printf("O 2\n");
}

void solve_task4() {
    printf("I\n");
    printf("C 1 0\n");
    printf("O 2\n");
}

void solve_task5() {
    printf("I\n");
    printf("C 1 0\n");
    printf("O 2\n");
}

void solve_task6() {
    printf("I\n");
    printf("C 1 0\n");
    printf("O 2\n");
}

void solve_task7() {
    printf("I\n");
    printf("C 1 0\n");
    printf("O 2\n");
}

void solve_task8() {
    printf("I\n");
    printf("C 1 1\n");
    printf("O 2\n");
}

void solve_task9() {
    printf("I\n");
    printf("C 1 0\n");
    printf("O 2\n");
}

void solve_task10() {
    printf("I\n");
    printf("C 1 0\n");
    printf("O 2\n");
}

int main() {
    int task_id;
    scanf("%d", &task_id);
    switch (task_id) {
        case 1:
            solve_task1();
            break;
        case 2:
            solve_task2();
            break;
        case 3:
            solve_task3();
            break;
        case 4:
            solve_task4();
            break;
        case 5:
            solve_task5();
            break;
        case 6:
            solve_task6();
            break;
        case 7:
            solve_task7();
            break;
        case 8:
            solve_task8();
            break;
        case 9:
            solve_task9();
            break;
        case 10:
            solve_task10();
            break;
        default:
            printf("Invalid task ID\n");
    }
    return 0;
}