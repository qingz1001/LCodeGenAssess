#include <stdio.h>
#include <string.h>

#define MAX_N 45
#define MAX_M 1000

int T, n;
int lines[MAX_N];
int connections[MAX_M][2];
int conn_count = 0;

int find_connection(int a, int b) {
    for (int i = 0; i < conn_count; i++) {
        if ((connections[i][0] == a && connections[i][1] == b) ||
            (connections[i][0] == b && connections[i][1] == a)) {
            return 1;
        }
    }
    return 0;
}

void add_connection(int a, int b) {
    if (!find_connection(a, b)) {
        connections[conn_count][0] = a;
        connections[conn_count][1] = b;
        conn_count++;
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &lines[i]);
        }
        
        conn_count = 0;
        memset(connections, 0, sizeof(connections));
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                add_connection(lines[i], lines[j]);
            }
        }
        
        int result = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (!find_connection(i, j)) {
                    result++;
                }
            }
        }
        
        printf("%d\n", result);
    }
    return 0;
}