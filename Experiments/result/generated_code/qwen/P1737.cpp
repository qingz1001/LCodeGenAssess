#include <stdio.h>
#include <math.h>

int main() {
    int task;
    scanf("%d", &task);

    if (task == 1) {
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
    } else if (task == 2) {
        printf("I\n");
        printf("* 1 17\n");
        printf("S 2\n");
        printf("C 2 -1\n");
        printf("O 3\n");
    } else if (task == 3) {
        printf("I\n");
        printf("C 1 0\n");
        printf("C 2 1\n");
        printf("P 1 2\n");
        printf("O 3\n");
    } else if (task == 4) {
        printf("I\n");
        printf("C 1 0\n");
        printf("C 2 1\n");
        printf("P 1 2\n");
        printf("O 3\n");
    } else if (task == 5) {
        printf("I\n");
        printf("< 1 32\n");
        printf("O 2\n");
    } else if (task == 6) {
        printf("I\n");
        printf("> 1 32\n");
        printf("O 2\n");
    } else if (task == 7) {
        printf("I\n");
        printf("^ 1 2\n");
        printf("O 2\n");
    } else if (task == 8) {
        printf("I\n");
        printf("C 1 10\n");
        printf("/ 2 1\n");
        printf("O 3\n");
    } else if (task == 9) {
        printf("I\n");
        printf("S 1\n");
        printf("S 2\n");
        printf("S 3\n");
        printf("S 4\n");
        printf("S 5\n");
        printf("S 6\n");
        printf("S 7\n");
        printf("S 8\n");
        printf("S 9\n");
        printf("S 10\n");
        printf("S 11\n");
        printf("S 12\n");
        printf("S 13\n");
        printf("S 14\n");
        printf("S 15\n");
        printf("S 16\n");
        printf("O 1\n");
        printf("O 2\n");
        printf("O 3\n");
        printf("O 4\n");
        printf("O 5\n");
        printf("O 6\n");
        printf("O 7\n");
        printf("O 8\n");
        printf("O 9\n");
        printf("O 10\n");
        printf("O 11\n");
        printf("O 12\n");
        printf("O 13\n");
        printf("O 14\n");
        printf("O 15\n");
        printf("O 16\n");
    } else if (task == 10) {
        printf("I\n");
        printf("* 1 2\n");
        printf("% 2 3\n");
        printf("O 3\n");
    }

    return 0;
}