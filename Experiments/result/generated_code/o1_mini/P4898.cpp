#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_HW 1000000

int main(){
    int H, W, Q;
    scanf("%d %d %d", &H, &W, &Q);
    int HW = H * W;
    int *row = (int*)malloc(HW * sizeof(int));
    int *col = (int*)malloc(HW * sizeof(int));
    for(int i=0;i<HW;i++) scanf("%d %d", &row[i], &col[i]);
    long long *min_row = (long long*)malloc((HW+1)*sizeof(long long));
    long long *max_row = (long long*)malloc((HW+1)*sizeof(long long));
    long long *min_col = (long long*)malloc((HW+1)*sizeof(long long));
    long long *max_col = (long long*)malloc((HW+1)*sizeof(long long));
    char *valid = (char*)calloc(HW+1, sizeof(char));
    min_row[0] = LONG_MAX;
    max_row[0] = LONG_MIN;
    min_col[0] = LONG_MAX;
    max_col[0] = LONG_MIN;
    long long count =0;
    for(int k=1; k<=HW; k++){
        if(row[k-1] < min_row[k-1]) min_row[k] = row[k-1];
        else min_row[k] = min_row[k-1];
        if(row[k-1] > max_row[k-1]) max_row[k] = row[k-1];
        else max_row[k] = max_row[k-1];
        if(col[k-1] < min_col[k-1]) min_col[k] = col[k-1];
        else min_col[k] = min_col[k-1];
        if(col[k-1] > max_col[k-1]) max_col[k] = col[k-1];
        else max_col[k] = max_col[k-1];
        long long area = (max_row[k] - min_row[k] +1)*(max_col[k] - min_col[k] +1);
        if(area ==k){
            valid[k] =1;
            count++;
        }
    }
    for(int i=0;i<Q;i++){
        int A, B;
        scanf("%d %d", &A, &B);
        // Swap rows and cols of A and B
        int temp_r = row[A];
        int temp_c = col[A];
        row[A] = row[B];
        col[A] = col[B];
        row[B] = temp_r;
        col[B] = temp_c;
        // Determine the range of k to update
        int min_k = A < B ? A+1 : B+1;
        for(int k = min_k; k<=HW; k++){
            // Recompute min_row[k], max_row[k], min_col[k], max_col[k]
            if(k ==1){
                min_row[k] = row[0];
                max_row[k] = row[0];
                min_col[k] = col[0];
                max_col[k] = col[0];
            }
            else{
                if(row[k-1] < min_row[k-1]) min_row[k] = row[k-1];
                else min_row[k] = min_row[k-1];
                if(row[k-1] > max_row[k-1]) max_row[k] = row[k-1];
                else max_row[k] = max_row[k-1];
                if(col[k-1] < min_col[k-1]) min_col[k] = col[k-1];
                else min_col[k] = min_col[k-1];
                if(col[k-1] > max_col[k-1]) max_col[k] = col[k-1];
                else max_col[k] = max_col[k-1];
            }
            long long area = (max_row[k] - min_row[k] +1)*(max_col[k] - min_col[k] +1);
            if(area ==k){
                if(!valid[k]){
                    valid[k]=1;
                    count++;
                }
            }
            else{
                if(valid[k]){
                    valid[k]=0;
                    count--;
                }
            }
        }
        printf("%lld\n", count);
    }
    free(row);
    free(col);
    free(min_row);
    free(max_row);
    free(min_col);
    free(max_col);
    free(valid);
    return 0;
}