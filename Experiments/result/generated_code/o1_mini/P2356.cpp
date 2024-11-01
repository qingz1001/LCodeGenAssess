#include <stdio.h>

#define MAX_N 1000
#define MAX_SAFE 10000

struct pos {
    int i;
    int j;
};

int main(){
    int n;
    scanf("%d", &n);
    int row_sum[MAX_N] = {0};
    int col_sum[MAX_N] = {0};
    struct pos safe_positions[MAX_SAFE];
    int count = 0;
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int val;
            scanf("%d", &val);
            if(val > 0){
                row_sum[i] += val;
                col_sum[j] += val;
            }
            else{
                if(count < MAX_SAFE){
                    safe_positions[count].i = i;
                    safe_positions[count].j = j;
                    count++;
                }
            }
        }
    }
    
    if(count == 0){
        printf("Bad Game!\n");
        return 0;
    }
    
    int max_score = -1;
    for(int k = 0; k < count; k++){
        int i = safe_positions[k].i;
        int j = safe_positions[k].j;
        int total = row_sum[i] + col_sum[j];
        if(total > max_score){
            max_score = total;
        }
    }
    
    printf("%d\n", max_score);
    return 0;
}