#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 6

char grid_chars[MAX_N][MAX_M+1];
int N, M, Q;

// Function to get connections for a cell based on its type
int get_connections(char c) {
    // Return a bitmask where bit0=up, bit1=down, bit2=left, bit3=right
    if(c == '|') return (1<<0) | (1<<1);
    if(c == '-') return (1<<2) | (1<<3);
    if(c == '+') return (1<<0) | (1<<1) | (1<<2) | (1<<3);
    return 0;
}

int main(){
    // Fast IO
    ios_flag:
    setbuf(stdout, NULL);
    
    // Read N and M
    scanf("%d %d", &N, &M);
    
    // Read grid
    for(int i=1;i<=N;i++) {
        scanf("%s", grid_chars[i]);
    }
    
    // Read Q
    scanf("%d", &Q);
    
    // Process queries
    char op[2];
    for(int q=0; q<Q; q++) {
        scanf("%s", op);
        if(op[0] == 'C') {
            int i, j;
            char k;
            scanf("%d %d %c", &i, &j, &k);
            grid_chars[i][j-1] = k;
        }
        else { // Q operation
            int l, r;
            scanf("%d %d", &l, &r);
            // Initialize Union-Find
            int parent[MAX_M];
            int hasO_flag[MAX_M];
            for(int m=0; m<M; m++) { parent[m] = m; hasO_flag[m] = 0; }
            // Previous row connections
            int prev_connected[MAX_M];
            memset(prev_connected, -1, sizeof(prev_connected));
            for(int row=l; row<=r; row++) {
                // Current row connections
                // Initialize current row parent
                int current_parent[MAX_M];
                for(int m=0; m<M; m++) current_parent[m] = m;
                // Handle horizontal connections
                for(int m=0; m<M; m++) {
                    char c = grid_chars[row][m];
                    if(c == '.' ) continue;
                    if(c == 'O' || c == '|' || c == '-' || c == '+') {
                        int conn = get_connections(c);
                        // Check right connection
                        if(m < M-1 && ((conn & (1<<3)) && ((get_connections(grid_chars[row][m+1]) & (1<<2))))) {
                            // Union m and m+1
                            // Find roots
                            int a = current_parent[m];
                            while(current_parent[a] != a) a = current_parent[a];
                            int b = current_parent[m+1];
                            while(current_parent[b] != b) b = current_parent[b];
                            if(a != b) current_parent[b] = a;
                        }
                        // Check left connection is already handled
                    }
                }
                // Handle vertical connections with previous row
                if(row > l){
                    for(int m=0; m<M; m++) {
                        char c1 = grid_chars[row-1][m];
                        char c2 = grid_chars[row][m];
                        if(c1 == '.' || c2 == '.') continue;
                        int conn1 = get_connections(c1);
                        int conn2 = get_connections(c2);
                        if( (conn1 & (1<<1)) && (conn2 & (1<<0)) ) {
                            // Union m in previous and current
                            int a = parent[m];
                            while(parent[a] != a) a = parent[a];
                            int b = current_parent[m];
                            while(current_parent[b] != b) b = current_parent[b];
                            if(a != b){
                                parent[b] = a;
                                hasO_flag[a] |= hasO_flag[b];
                            }
                        }
                    }
                }
                // Update hasO_flag
                for(int m=0; m<M; m++) {
                    if(grid_chars[row][m] == 'O') {
                        int a = current_parent[m];
                        while(current_parent[a] != a) a = current_parent[a];
                        hasO_flag[a] = 1;
                        parent[m] = a;
                    }
                    else {
                        int a = current_parent[m];
                        while(current_parent[a] != a) a = current_parent[a];
                        parent[m] = a;
                    }
                }
                // Merge current_parent into parent
                for(int m=0; m<M; m++) {
                    if(parent[m] != current_parent[m]){
                        int a = parent[m];
                        int b = current_parent[m];
                        while(parent[a] != a) a = parent[a];
                        while(parent[b] != b) b = parent[b];
                        if(a != b){
                            parent[b] = a;
                            hasO_flag[a] |= hasO_flag[b];
                        }
                    }
                }
            }
            // Count unique parents with hasO_flag
            int count =0;
            int seen[MAX_M];
            memset(seen, 0, sizeof(seen));
            for(int m=0; m<M; m++) {
                int a = parent[m];
                while(parent[a] != a) a = parent[a];
                if(!seen[a] && hasO_flag[a]){
                    seen[a] =1;
                    count++;
                }
            }
            printf("%d\n", count);
        }
    }
}