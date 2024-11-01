#include <stdio.h>
#include <stdint.h>
#include <string.h>

int n, m;
char grid_chars[30][31];

void backtrack(int l_num, uint32_t remaining[], int count_ptr, int *count) {
    if (l_num == 3) {
        for(int i=0;i<n;i++) if(remaining[i]!=0) return;
        (*count)++;
        return;
    }
    // Find first set bit
    int first_x = -1, first_y = -1;
    for(int i=0;i<n;i++) {
        if(remaining[i] !=0){
            first_x =i;
            for(int j=0; j<m; j++) if(remaining[i] & (1U<<j)){
                first_y =j;
                break;
            }
            break;
        }
    }
    if(first_x ==-1){
        return;
    }
    // Enumerate all possible L-shapes covering (first_x, first_y)
    for(int ori=0; ori <4; ori++){
        int dx1, dy1, dx2, dy2;
        switch(ori){
            case 0:
                dx1=0; dy1=1;
                dx2=1; dy2=0;
                break;
            case1:
                dx1=0; dy1=-1;
                dx2=1; dy2=0;
                break;
            case2:
                dx1=0; dy1=1;
                dx2=-1; dy2=0;
                break;
            case3:
                dx1=0; dy1=-1;
                dx2=-1; dy2=0;
                break;
        }
        // Enumerate arm lengths a and b
        for(int a=1; ; a++){
            int nx1 = first_x + dx2 * a;
            int ny1 = first_y + dy2 * a;
            if(nx1 <0 || nx1 >=n || ny1 <0 || ny1 >=m || !(remaining[nx1] & (1U<<ny1))) break;
            for(int b=1; ; b++){
                int nx2 = first_x + dx1 * b;
                int ny2 = first_y + dy1 * b;
                if(nx2 <0 || nx2 >=n || ny2 <0 || ny2 >=m || !(remaining[first_x] & (1U<<ny2))) break;
                // Collect L-shape
                uint32_t temp[30];
                for(int t=0; t<n; t++) temp[t]=0;
                temp[first_x] |= (1U<<first_y);
                for(int k=1; k <=a; k++){
                    int tx = first_x + dx2 * k;
                    int ty = first_y + dy2 * k;
                    temp[tx] |= (1U<<ty);
                }
                for(int k=1; k <=b; k++){
                    int tx = first_x + dx1 * k;
                    int ty = first_y + dy1 * k;
                    temp[tx] |= (1U<<ty);
                }
                // Check if all temp cells are in remaining
                int valid =1;
                for(int t=0; t<n; t++) if( (temp[t] & remaining[t]) != temp[t] ){
                    valid=0;
                    break;
                }
                if(valid){
                    // Create new_remaining as remaining ^ temp
                    uint32_t new_remaining[30];
                    for(int t=0; t<n; t++) new_remaining[t] = remaining[t] ^ temp[t];
                    // Recurse
                    backtrack(l_num +1, new_remaining, count_ptr, count);
                }
            }
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=0;i<n;i++) scanf("%s", grid_chars[i]);
    uint32_t available[30];
    for(int i=0;i<n;i++){
        available[i]=0;
        for(int j=0; j<m; j++) if(grid_chars[i][j] == '.') available[i] |= (1U<<j);
    }
    int count =0;
    backtrack(0, available, 0, &count);
    printf("%d\n", count);
    return 0;
}