#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200

typedef struct {
    long long S;
    long long E;
} Activity;

int parent[MAXN];
int find_set(int x){
    if(parent[x] != x)
        parent[x] = find_set(parent[x]);
    return parent[x];
}

int main(){
    int n;
    scanf("%d", &n);
    Activity activities[MAXN];
    for(int i=0;i<n;i++){
        scanf("%lld %lld", &activities[i].S, &activities[i].E);
        activities[i].E += activities[i].S;
    }
    // Initialize Union-Find
    for(int i=0;i<n;i++) parent[i] = i;
    // Find overlaps and union
    for(int i=0;i<n;i++) {
        for(int j=i+1;j<n;j++) {
            if(!(activities[i].E <= activities[j].S || activities[j].E <= activities[i].S)){
                int fi = find_set(i);
                int fj = find_set(j);
                if(fi != fj){
                    parent[fi] = fj;
                }
            }
        }
    }
    // Count component sizes
    int comp_size[MAXN];
    memset(comp_size, 0, sizeof(comp_size));
    for(int i=0;i<n;i++){
        int fi = find_set(i);
        comp_size[fi]++;
    }
    // Collect unique components
    int components[MAXN];
    int num_comp = 0;
    for(int i=0;i<n;i++) {
        if(find_set(i) == i){
            components[num_comp++] = comp_size[i];
        }
    }
    // DP for main case
    int dp_main[201][201];
    memset(dp_main, 0, sizeof(dp_main));
    dp_main[0][0] = 1;
    for(int i=0;i<num_comp;i++){
        int s = components[i];
        int dp_new[201][201];
        memset(dp_new, 0, sizeof(dp_new));
        for(int a=0;a<=200;a++){
            for(int b=0;b<=200;b++){
                if(dp_main[a][b]){
                    // Assign to A
                    if(a + s <= 200){
                        dp_new[a+s][b] = 1;
                    }
                    // Assign to B
                    if(b + s <= 200){
                        dp_new[a][b+s] = 1;
                    }
                    // Assign to neither
                    dp_new[a][b] = 1;
                }
            }
        }
        // Update dp_main
        for(int a=0;a<=200;a++){
            for(int b=0;b<=200;b++){
                dp_main[a][b] = dp_new[a][b];
            }
        }
    }
    // Find max min(a,b)
    int max_min = 0;
    for(int a=0;a<=200;a++){
        for(int b=0;b<=200;b++){
            if(dp_main[a][b]){
                if(a < b){
                    if(a > max_min) max_min = a;
                }
                else{
                    if(b > max_min) max_min = b;
                }
            }
        }
    }
    printf("%d\n", max_min);
    // Prepare components and their indices
    int comp_ids[MAXN];
    for(int i=0;i<n;i++) comp_ids[i] = find_set(i);
    // Collect sizes per component id
    int comp_size_map[MAXN];
    memset(comp_size_map, 0, sizeof(comp_size_map));
    for(int i=0;i<n;i++) comp_size_map[comp_ids[i]]++;
    // Assign unique component index
    int unique_comp_ids[MAXN];
    int unique_num = 0;
    for(int i=0;i<n;i++) {
        if(comp_ids[i] == i){
            unique_comp_ids[unique_num++] = i;
        }
    }
    // For each activity
    for(int idx=0;idx<n;idx++){
        // Find which component it belongs to
        int comp = find_set(idx);
        // Prepare component sizes with constraints
        int comp_sizes[MAXN];
        int new_num = 0;
        for(int i=0;i<num_comp;i++){
            if(components[i] > 0){
                if(find_set(i)==comp){
                    comp_sizes[new_num++] = components[i];
                }
                else{
                    comp_sizes[new_num++] = components[i];
                }
            }
        }
        // Reinitialize DP
        int dp[201][201];
        memset(dp, 0, sizeof(dp));
        // Assign first component with constraint
        dp[0][0] = 1;
        for(int i=0;i<num_comp;i++){
            int s = components[i];
            int dp_newi[201][201];
            memset(dp_newi, 0, sizeof(dp_newi));
            for(int a=0;a<=200;a++){
                for(int b=0;b<=200;b++){
                    if(dp[a][b]){
                        // If this component contains idx, assign only to A or B
                        if(find_set(idx) == find_set(i)){
                            // Assign to A
                            if(a + s <= 200){
                                dp_newi[a+s][b] = 1;
                            }
                            // Assign to B
                            if(b + s <= 200){
                                dp_newi[a][b+s] = 1;
                            }
                        }
                        else{
                            // Assign to A
                            if(a + s <= 200){
                                dp_newi[a+s][b] = 1;
                            }
                            // Assign to B
                            if(b + s <= 200){
                                dp_newi[a][b+s] = 1;
                            }
                            // Assign to neither
                            dp_newi[a][b] = 1;
                        }
                    }
                }
            }
            // Update dp
            for(int a=0;a<=200;a++){
                for(int b=0;b<=200;b++){
                    dp[a][b] = dp_newi[a][b];
                }
            }
        }
        // Find max min(a,b)
        int current_max = 0;
        for(int a=0;a<=200;a++){
            for(int b=0;b<=200;b++){
                if(dp[a][b]){
                    if(a < b){
                        if(a > current_max) current_max = a;
                    }
                    else{
                        if(b > current_max) current_max = b;
                    }
                }
            }
        }
        printf("%d\n", current_max);
    }
    return 0;
}