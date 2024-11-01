#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

int n, m, q;
int room[MAXN]; // room[i] 表示第 i 个人所在的房间
int room_count[MAXN]; // room_count[i] 表示房间 i 中的人数
int room_experimented[MAXN]; // room_experimented[i] 表示房间 i 中已经做过实验的人数

int main() {
    scanf("%d %d %d", &n, &m, &q);
    memset(room, 1, sizeof(room)); // 初始化所有人都在 1 号房间
    memset(room_count, 0, sizeof(room_count));
    memset(room_experimented, 0, sizeof(room_experimented));
    room_count[1] = n; // 初始时 1 号房间有 n 个人

    char op[2];
    int i, j, l, r;
    for (int k = 0; k < q; k++) {
        scanf("%s", op);
        if (op[0] == 'C') {
            scanf("%d %d", &i, &j);
            room_count[room[i]]--;
            room[i] = j;
            room_count[j]++;
        } else if (op[0] == 'W') {
            scanf("%d %d", &l, &r);
            int points = 0;
            for (int x = l; x <= r; x++) {
                if (room_count[x] > room_experimented[x]) {
                    points += room_count[x] - room_experimented[x];
                    room_experimented[x] = room_count[x];
                }
            }
            printf("%d\n", points);
        }
    }

    return 0;
}