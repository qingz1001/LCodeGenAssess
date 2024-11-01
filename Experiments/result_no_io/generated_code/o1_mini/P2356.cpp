#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int row_sum[n];
    int col_sum[n];
    for(int i=0;i<n;i++) row_sum[i]=0;
    for(int j=0;j<n;j++) col_sum[j]=0;
    int good_i[10000], good_j[10000];
    int good_cnt=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int cell;
            scanf("%d", &cell);
            if(cell > 0){
                row_sum[i] += cell;
                col_sum[j] += cell;
            }
            else{
                if(good_cnt < 10000){
                    good_i[good_cnt] = i;
                    good_j[good_cnt] = j;
                    good_cnt++;
                }
            }
        }
    }
    if(good_cnt ==0){
        printf("Bad Game!\n");
        return 0;
    }
    int max_score = -1;
    for(int k=0; k<good_cnt; k++){
        int score = row_sum[good_i[k]] + col_sum[good_j[k]];
        if(score > max_score){
            max_score = score;
        }
    }
    printf("%d\n", max_score);
    return 0;
}