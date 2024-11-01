#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100005

int n, m, q;
int people[MAXN]; // 记录每个人所在的房间
bool visited[MAXN]; // 记录每个房间是否被访问过
int room_count[MAXN]; // 记录每个房间的人数

int main() {
    scanf("%d %d %d", &n, &m, &q);
    
    // 初始化每个人都在1号房间
    for (int i = 1; i <= n; i++) {
        people[i] = 1;
        room_count[1]++;
    }
    
    char op[2];
    int i, j, l, r;
    for (int k = 0; k < q; k++) {
        scanf("%s", op);
        if (op[0] == 'C') {
            scanf("%d %d", &i, &j);
            // 将第i个人移动到房间j
            room_count[people[i]]--;
            people[i] = j;
            room_count[j]++;
        } else if (op[0] == 'W') {
            scanf("%d %d", &l, &r);
            int points = 0;
            for (int room = l; room <= r; room++) {
                if (!visited[room]) {
                    points += room_count[room];
                    visited[room] = true;
                }
            }
            printf("%d\n", points);
        }
    }
    
    return 0;
}