#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LABEL 2000000
#define MAX_LOG 22
#define MAX_MONTH 2000000

int parent_arr[MAX_LABEL + 1];
int depth_arr[MAX_LABEL + 1];
int up[MAX_LABEL + 1][MAX_LOG];
int reproduction_count[MAX_MONTH + 1];
int reproduction_list[MAX_MONTH + 1][20]; // Assuming max 20 reproductions per month

int main(){
    int m;
    scanf("%d", &m);
    long long queries[m][2];
    long long a, b;
    long long max_label = 1;
    for(int i=0;i<m;i++){
        scanf("%lld %lld", &a, &b);
        queries[i][0]=a;
        queries[i][1]=b;
        if(a > max_label) max_label = a;
        if(b > max_label) max_label = b;
    }

    // Initialize
    parent_arr[1] = 0;
    depth_arr[1] = 0;
    // Initialize reproduction list
    // Assuming months start from 1
    // Pair 1 reproduces starting from month3
    reproduction_count[3] = 1;
    reproduction_list[3][0] = 1;
    long long label =2;
    for(int month=3; label <= max_label; month++){
        for(int i=0;i<reproduction_count[month];i++){
            if(label > max_label) break;
            int pair_id = reproduction_list[month][i];
            parent_arr[label] = pair_id;
            depth_arr[label] = depth_arr[pair_id] +1;
            // Schedule next reproduction for the new pair
            if(month +2 <= MAX_MONTH){
                reproduction_list[month +2][reproduction_count[month +2]++] = label;
            }
            label++;
        }
    }

    // Binary lifting
    for(int i=1;i<=max_label;i++){
        up[i][0] = parent_arr[i];
    }
    for(int j=1; j < MAX_LOG; j++){
        for(int i=1;i<=max_label;i++){
            if(up[i][j-1] != 0){
                up[i][j] = up[ up[i][j-1] ][j-1];
            }
            else{
                up[i][j] = 0;
            }
        }
    }

    // Function to find LCA
    for(int i=0;i<m;i++){
        int u = queries[i][0];
        int v = queries[i][1];
        if(u == v){
            printf("%d\n", u);
            continue;
        }
        if(depth_arr[u] < depth_arr[v]){
            int temp = u;
            u = v;
            v = temp;
        }
        // Lift u up to depth of v
        for(int j = MAX_LOG-1; j >=0; j--){
            if(depth_arr[u] - (1<<j) >= depth_arr[v]){
                u = up[u][j];
            }
        }
        if(u == v){
            printf("%d\n", u);
            continue;
        }
        // Lift both up until their ancestors match
        for(int j = MAX_LOG-1; j >=0; j--){
            if(up[u][j] !=0 && up[u][j] != up[v][j]){
                u = up[u][j];
                v = up[v][j];
            }
        }
        printf("%d\n", parent_arr[u]);
    }

    return 0;
}