#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_N 20005
#define MAX_M 20005

int n, m;
bool can_attend[MAX_N][MAX_M];
bool assigned[MAX_N];

bool dfs(int classroom) {
    if (classroom > m) return true;
    
    for (int student = 1; student <= n; student++) {
        if (can_attend[student][classroom] && !assigned[student]) {
            assigned[student] = true;
            if (dfs(classroom + 1)) return true;
            assigned[student] = false;
        }
    }
    
    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        scanf("%d %d", &m, &n);
        
        memset(can_attend, 0, sizeof(can_attend));
        memset(assigned, 0, sizeof(assigned));
        
        for (int i = 1; i <= m; i++) {
            int k;
            scanf("%d", &k);
            for (int j = 0; j < k; j++) {
                int student;
                scanf("%d", &student);
                can_attend[student][i] = true;
            }
        }
        
        if (dfs(1)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    return 0;
}