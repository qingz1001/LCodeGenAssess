#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 15
#define MAX_M 15
#define MAX_PATTERNS 20
#define MAX_CELLS 225
#define MAX_STATE 233
#define MAX_QUEUE 1000000

typedef struct {
    int bits[4];
} Bitmask;

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n, m, k;
        scanf("%d %d %d", &n, &m, &k);
        int c[n][m];
        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                scanf("%d", &c[i][j]);
            }
        }
        int a[n][m];
        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                scanf("%d", &a[i][j]);
            }
        }
        // Map unique patterns
        int pattern_map[MAX_PATTERNS];
        int pattern_count =0;
        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                if(c[i][j]!=-1){
                    int exists = 0;
                    for(int p=0;p<pattern_count;p++){
                        if(pattern_map[p]==c[i][j]){
                            exists =1;
                            break;
                        }
                    }
                    if(!exists){
                        pattern_map[pattern_count++] = c[i][j];
                    }
                }
            }
        }
        if(pattern_count < k){
            printf("-1 -1\n");
            continue;
        }
        // Prepare list of cells
        int total =0;
        int cells[MAX_CELLS][2];
        int patterns[MAX_CELLS];
        int a_list[MAX_CELLS];
        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                if(c[i][j]!=-1){
                    cells[total][0] = i;
                    cells[total][1] = j;
                    // Map pattern to id
                    int pid = -1;
                    for(int p=0;p<pattern_count;p++) if(pattern_map[p]==c[i][j]) {pid=p; break;}
                    patterns[total] = pid;
                    a_list[total] = a[i][j];
                    total++;
                }
            }
        }
        if(total < k){
            printf("-1 -1\n");
            continue;
        }
        // Enumerate all connected subsets using BFS
        // Initialize BFS queue
        typedef struct {
            int mask;
            int included[4]; // up to 225 bits
            int size;
            int median;
        } State;
        State queue[MAX_QUEUE];
        int front =0, rear=0;
        // Initialize queue with each cell
        for(int i=0;i<total;i++) {
            State st;
            st.mask = 1 << patterns[i];
            memset(st.included, 0, sizeof(st.included));
            st.included[0] = 1 << i;
            st.size =1;
            st.median = a_list[i];
            queue[rear++] = st;
        }
        int found =0;
        int min_s = -1, min_m = -1;
        while(front < rear && !found){
            int current_level = rear - front;
            for(int qf=0; qf<current_level; qf++){
                State st = queue[front++];
                // Check patterns
                int cnt =0;
                for(int p=0;p<pattern_count;p++) if(st.mask & (1<<p)) cnt++;
                if(cnt >=k){
                    // Collect a_list
                    int vals[225];
                    int idx=0;
                    for(int cidx=0;cidx<total;cidx++) {
                        if(st.included[cidx/64] & ((st.included[cidx/64] >> (cidx%64)) &1)){
                            vals[idx++] = a_list[cidx];
                        }
                    }
                    // Sort vals
                    for(int x=0;x<idx-1;x++) {
                        for(int y=x+1;y<idx;y++) {
                            if(vals[x] > vals[y]){
                                int tmp = vals[x];
                                vals[x] = vals[y];
                                vals[y] = tmp;
                            }
                        }
                    }
                    int median = vals[(idx-1)/2];
                    if(!found || st.size < min_s || (st.size == min_s && median < min_m)){
                        min_s = st.size;
                        min_m = median;
                        found =1;
                    }
                }
                // Expand to neighbors
                // Find included cells
                for(int cidx=0;cidx<total;cidx++) {
                    if((st.included[cidx/64] >> (cidx%64)) &1){
                        // Check neighbors
                        int x = cells[cidx][0];
                        int y = cells[cidx][1];
                        int dirs[4][2] = {{x-1,y},{x+1,y},{x,y-1},{x,y+1}};
                        for(int d=0;d<4;d++){
                            int nx = dirs[d][0];
                            int ny = dirs[d][1];
                            if(nx>=0 && nx<n && ny>=0 && ny<m){
                                // Find the cell index
                                int ni = -1;
                                for(int ni_idx=0; ni_idx<total; ni_idx++) {
                                    if(cells[ni_idx][0]==nx && cells[ni_idx][1]==ny){
                                        ni = ni_idx;
                                        break;
                                    }
                                }
                                if(ni != -1){
                                    if(!((st.included[ni/64] >> (ni%64)) &1)){
                                        // Create new state
                                        State new_st = st;
                                        new_st.mask |= (1 << patterns[ni]);
                                        new_st.size +=1;
                                        // Set the bit
                                        new_st.included[ni/64] |= (1 << (ni%64));
                                        // Update median later
                                        queue[rear++] = new_st;
                                        if(rear >= MAX_QUEUE){
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if(rear >= MAX_QUEUE) break;
                }
                if(rear >= MAX_QUEUE) break;
            }
        }
        if(found){
            printf("%d %d\n", min_s, min_m);
        }
        else{
            printf("-1 -1\n");
        }
    }
}