#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50001

int n;
int wish[MAX_N][2];
int visited[MAX_N];
int circle[MAX_N];
int circle_size;

int find_circle(int start) {
    int current = start;
    circle_size = 0;
    while (!visited[current]) {
        visited[current] = 1;
        circle[circle_size++] = current;
        if (circle_size > 1 && (wish[current][0] == circle[circle_size-2] || wish[current][1] == circle[circle_size-2])) {
            current = (wish[current][0] == circle[circle_size-2]) ? wish[current][1] : wish[current][0];
        } else {
            return 0;
        }
    }
    return (current == start && circle_size > 2);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &wish[i][0], &wish[i][1]);
    }

    memset(visited, 0, sizeof(visited));
    int total_cost = 0;
    int valid = 1;

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            if (find_circle(i)) {
                total_cost += circle_size;
            } else {
                valid = 0;
                break;
            }
        }
    }

    if (valid) {
        printf("%d\n", total_cost);
    } else {
        printf("-1\n");
    }

    return 0;
}