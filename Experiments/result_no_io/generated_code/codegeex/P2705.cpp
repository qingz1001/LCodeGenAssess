#include <stdio.h>

int main() {
    int R, B, C, D, E;
    scanf("%d%d%d%d%d", &R, &B, &C, &D, &E);

    int max_score = 0;

    // 如果 E 大于 C 和 D，则将所有小球都放在不相匹配的盒子里得分最高
    if (E > C && E > D) {
        max_score = E * (R + B);
    } 
    // 如果 E 小于等于 C 和 D，则将所有小球都放在相匹配的盒子里得分最高
    else {
        max_score = C * R + D * B;
    }

    printf("%d\n", max_score);
    return 0;
}