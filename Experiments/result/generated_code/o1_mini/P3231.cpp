#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define maximum size based on constraints
#define MAX_TOTAL 5000

typedef struct {
    int i, j, k;
} Position;

int main(){
    int D;
    scanf("%d", &D);
    while(D--){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        int total = a * b * c;
        // Allocate memory for the grid
        char *grid = (char*)malloc(total * sizeof(char));
        // Read the grid
        for(int i=0;i<a;i++){
            for(int j=0;j<b;j++){
                for(int l=0;l<c;l++){
                    char temp;
                    scanf(" %c", &temp);
                    grid[i*b*c + j*c + l] = (temp == '1') ? 1 : 0;
                }
            }
        }
        // Create list of '1's
        Position ones[MAX_TOTAL];
        int count =0;
        for(int idx=0; idx<total; idx++){
            if(grid[idx]){
                int i = idx / (b*c);
                int rem = idx % (b*c);
                int j = rem / c;
                int l = rem % c;
                ones[count].i = i;
                ones[count].j = j;
                ones[count].k = l;
                count++;
            }
        }
        // Initialize covered array
        char *covered = (char*)calloc(total, sizeof(char));
        long long total_cost =0;
        // Determine max_k
        int max_k = a;
        if(b < max_k) max_k = b;
        if(c < max_k) max_k = c;
        // For k from max_k down to 1
        for(int k = max_k; k >=1; k--){
            for(int p=0; p<count; p++){
                int idx = ones[p].i * b * c + ones[p].j * c + ones[p].k;
                if(grid[idx] && !covered[idx]){
                    int i_start = ones[p].i;
                    int j_start = ones[p].j;
                    int l_start = ones[p].k;
                    // Check if box of size k can be placed
                    if(i_start + k > a || j_start + k > b || l_start + k > c){
                        continue;
                    }
                    int can_place = 1;
                    // Check all cells in the box
                    for(int di=0; di<k && can_place; di++){
                        for(int dj=0; dj<k && can_place; dj++){
                            for(int dl=0; dl<k && can_place; dl++){
                                int ni = i_start + di;
                                int nj = j_start + dj;
                                int nl = l_start + dl;
                                int nidx = ni * b * c + nj * c + nl;
                                if(!grid[nidx] || covered[nidx]){
                                    can_place = 0;
                                }
                            }
                        }
                    }
                    if(can_place){
                        // Mark all as covered
                        for(int di=0; di<k; di++){
                            for(int dj=0; dj<k; dj++){
                                for(int dl=0; dl<k; dl++){
                                    int ni = i_start + di;
                                    int nj = j_start + dj;
                                    int nl = l_start + dl;
                                    int nidx = ni * b * c + nj * c + nl;
                                    covered[nidx] = 1;
                                }
                            }
                        }
                        // Add cost
                        total_cost += k;
                    }
                }
            }
        }
        // Cover remaining '1's with k=1
        for(int p=0; p<count; p++){
            int idx = ones[p].i * b * c + ones[p].j * c + ones[p].k;
            if(grid[idx] && !covered[idx]){
                total_cost +=1;
                covered[idx]=1;
            }
        }
        // Print the result
        printf("%lld\n", total_cost);
        // Free memory
        free(grid);
        free(covered);
    }
    return 0;
}