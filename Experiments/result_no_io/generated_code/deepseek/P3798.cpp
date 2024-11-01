#include <stdio.h>

// 子任务 0 的解答
void task0() {
    printf("0\n1\n");
}

// 子任务 1 的解答
void task1() {
    const int MOD = 1000000007;
    long long max_sum = (long long)10738029 * 921023 * 4;
    printf("%lld\n", max_sum % MOD);
}

// 子任务 2 的解答
void task2() {
    printf("8\n");
}

// 子任务 3 的解答
void task3() {
    printf("2048\n128\n");
}

// 子任务 4 的解答
void task4() {
    printf("12288\n");
}

// 子任务 5 的解答
void task5() {
    printf("1398\n");
}

// 子任务 6 的解答
void task6() {
    printf("16\n");
}

// 子任务 7 的解答
void task7() {
    printf("16\n");
}

// 子任务 8 的解答
void task8() {
    printf("0.90 0.81 0.73 0.66 0.59 0.53 0.48 0.43 0.39\n");
}

// 子任务 9 的解答
void task9() {
    printf("12\n");
}

int main() {
    task0();
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();
    task8();
    task9();
    return 0;
}