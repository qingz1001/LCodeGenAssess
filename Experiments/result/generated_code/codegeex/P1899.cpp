#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, P_i;
    scanf("%d %d", &N, &P_i);

    int total_money = 0;
    int count_magic = 0;

    for (int i = 0; i < N; i++) {
        int P_1, P_2;
        scanf("%d", &P_1);
        total_money += P_1;
        count_magic++;
    }

    for (int i = 0; i < N - count_magic; i++) {
        int P_1, P_2;
        scanf("%d %d", &P_1, &P_2);
        if (P_2 - P_1 >= P_i) {
            total_money += P_2 - P_i;
        } else {
            total_money += P_1;
        }
    }

    printf("%d\n", total_money);
    return 0;
}