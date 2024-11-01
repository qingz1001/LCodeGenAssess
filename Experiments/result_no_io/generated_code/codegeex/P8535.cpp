#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    // 计算可以使用的 '*' 的数量
    int ones = n / 5; // 每个一需要5个 '*'
    int twos = (n - ones * 5) / 4; // 每个二需要4个 '*'
    int threes = (n - ones * 5 - twos * 4) / 3; // 每个三需要3个 '*'
    int fours = (n - ones * 5 - twos * 4 - threes * 3) / 2; // 每个四需要2个 '*'
    int fives = (n - ones * 5 - twos * 4 - threes * 3 - fours * 2) / 1; // 每个五需要1个 '*'
    int sixes = (n - ones * 5 - twos * 4 - threes * 3 - fours * 2 - fives * 1) / 4; // 每个六需要4个 '*'
    int sevens = (n - ones * 5 - twos * 4 - threes * 3 - fours * 2 - fives * 1 - sixes * 4) / 5; // 每个七需要5个 '*'
    int eights = (n - ones * 5 - twos * 4 - threes * 3 - fours * 2 - fives * 1 - sixes * 4 - sevens * 5) / 4; // 每个八需要4个 '*'
    int nines = (n - ones * 5 - twos * 4 - threes * 3 - fours * 2 - fives * 1 - sixes * 4 - sevens * 5 - eights * 4) / 5; // 每个九需要5个 '*'

    // 输出最大数字
    printf("%d", 1 * ones + 2 * twos + 3 * threes + 4 * fours + 5 * fives + 6 * sixes + 7 * sevens + 8 * eights + 9 * nines);

    return 0;
}