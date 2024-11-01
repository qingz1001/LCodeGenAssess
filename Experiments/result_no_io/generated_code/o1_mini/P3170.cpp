#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_L 50000
#define MAX_DOT 192

typedef struct {
    unsigned long long mask[3];
} LShape;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    char grid[30][31];
    for(int i=0;i<n;i++) scanf("%s", grid[i]);
    
    // Assign unique IDs to '.' cells
    int cell_id[30][30];
    int total_dot = 0;
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            if(grid[i][j]=='.') {
                cell_id[i][j] = total_dot;
                total_dot++;
            }
            else {
                cell_id[i][j] = -1;
            }
        }
    }
    
    // If total_dot is 0, no L-shapes needed
    if(total_dot ==0){
        printf("1");
        return 0;
    }
    
    // Precompute total_mask
    unsigned long long total_mask[3] = {0,0,0};
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            if(grid[i][j]=='.'){
                int id = cell_id[i][j];
                if(id < 64){
                    total_mask[0] |= (1ULL << id);
                }
                else if(id < 128){
                    total_mask[1] |= (1ULL << (id - 64));
                }
                else{
                    total_mask[2] |= (1ULL << (id - 128));
                }
            }
        }
    }
    
    LShape* shapes = (LShape*)malloc(sizeof(LShape)*MAX_L);
    int num_L =0;
    
    // Directions: 0: Right & Down, 1: Left & Down, 2: Right & Up, 3: Left & Up
    int dirs[4][2][2] = {
        { {0,1}, {1,0} },
        { {0,-1}, {1,0} },
        { {0,1}, {-1,0} },
        { {0,-1}, {-1,0} }
    };
    
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(grid[i][j] != '.') continue;
            for(int ori=0; ori<4; ori++){
                for(int l1=1; ; l1++){
                    int ni = i + dirs[ori][0][0]*l1;
                    int nj = j + dirs[ori][0][1]*l1;
                    if(ni <0 || ni >=n || nj <0 || nj >=m || grid[ni][nj] != '.') break;
                    for(int l2=1; ; l2++){
                        int mi = i + dirs[ori][1][0]*l2;
                        int mj = j + dirs[ori][1][1]*l2;
                        if(mi <0 || mi >=n || mj <0 || mj >=m || grid[mi][mj] != '.') break;
                        // Now collect all cells in L-shape
                        // Start with corner
                        unsigned long long m0=0, m1=0, m2=0;
                        int valid =1;
                        // Corner
                        int id = cell_id[i][j];
                        if(id <64){ m0 |= (1ULL << id); }
                        else if(id <128){ m1 |= (1ULL <<(id-64)); }
                        else{ m2 |= (1ULL <<(id-128)); }
                        // First leg
                        for(int a=1; a<=l1; a++){
                            int ci = i + dirs[ori][0][0]*a;
                            int cj = j + dirs[ori][0][1]*a;
                            int cid = cell_id[ci][cj];
                            if(cid <64){ m0 |= (1ULL << cid); }
                            else if(cid <128){ m1 |= (1ULL <<(cid-64)); }
                            else{ m2 |= (1ULL <<(cid-128)); }
                        }
                        // Second leg
                        for(int a=1; a<=l2; a++){
                            int ci = i + dirs[ori][1][0]*a;
                            int cj = j + dirs[ori][1][1]*a;
                            int cid = cell_id[ci][cj];
                            if(cid <64){ m0 |= (1ULL << cid); }
                            else if(cid <128){ m1 |= (1ULL <<(cid-64)); }
                            else{ m2 |= (1ULL <<(cid-128)); }
                        }
                        // Add to shapes
                        LShape ls;
                        ls.mask[0] = m0;
                        ls.mask[1] = m1;
                        ls.mask[2] = m2;
                        shapes[num_L++] = ls;
                        if(num_L >= MAX_L) break;
                    }
                    if(num_L >= MAX_L) break;
                }
                if(num_L >= MAX_L) break;
            }
            if(num_L >= MAX_L) break;
        }
        if(num_L >= MAX_L) break;
    }
    
    if(num_L <3){
        printf("0");
        return 0;
    }
    
    // Count triplets
    unsigned long long count =0;
    for(int i=0;i<num_L;i++){
        for(int j=i+1;j<num_L;j++){
            // Check overlap between i and j
            if( (shapes[i].mask[0] & shapes[j].mask[0]) ||
                (shapes[i].mask[1] & shapes[j].mask[1]) ||
                (shapes[i].mask[2] & shapes[j].mask[2]) )
                continue;
            // Combined mask of i and j
            unsigned long long c0 = shapes[i].mask[0] | shapes[j].mask[0];
            unsigned long long c1 = shapes[i].mask[1] | shapes[j].mask[1];
            unsigned long long c2 = shapes[i].mask[2] | shapes[j].mask[2];
            for(int k=j+1;k<num_L;k++){
                // Check overlap with combined
                if( (shapes[k].mask[0] & c0) ||
                    (shapes[k].mask[1] & c1) ||
                    (shapes[k].mask[2] & c2) )
                    continue;
                // Check if combined with k equals total_mask
                if( (c0 | shapes[k].mask[0]) == total_mask[0] &&
                    (c1 | shapes[k].mask[1]) == total_mask[1] &&
                    (c2 | shapes[k].mask[2]) == total_mask[2] )
                    count++;
            }
        }
    }
    
    printf("%llu", count);
    free(shapes);
    return 0;
}