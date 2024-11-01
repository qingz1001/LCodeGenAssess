#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    int count;
} Item;

int cmp_rows(const void *a, const void *b){
    Item ia = *(Item*)a;
    Item ib = *(Item*)b;
    if(ib.count != ia.count){
        return ib.count - ia.count;
    }
    return ia.index - ib.index;
}

int cmp_cols(const void *a, const void *b){
    Item ia = *(Item*)a;
    Item ib = *(Item*)b;
    if(ib.count != ia.count){
        return ib.count - ia.count;
    }
    return ia.index - ib.index;
}

int main(){
    int M, N, K, L, D;
    scanf("%d %d %d %d %d", &M, &N, &K, &L, &D);
    int *row_counts = (int*)calloc(M, sizeof(int));
    int *col_counts = (int*)calloc(N, sizeof(int));
    for(int i=0;i<D;i++){
        int X, Y, P, Q;
        scanf("%d %d %d %d", &X, &Y, &P, &Q);
        if(X == P){
            int col = Y < Q ? Y : Q;
            if(col >=1 && col <= N-1){
                col_counts[col]++;
            }
        }
        else{
            int row = X < P ? X : P;
            if(row >=1 && row <= M-1){
                row_counts[row]++;
            }
        }
    }
    // Prepare rows
    Item *rows = (Item*)malloc((M-1)*sizeof(Item));
    for(int i=1;i<=M-1;i++){
        rows[i-1].index = i;
        rows[i-1].count = row_counts[i];
    }
    qsort(rows, M-1, sizeof(Item), cmp_rows);
    // Prepare columns
    Item *cols = (Item*)malloc((N-1)*sizeof(Item));
    for(int i=1;i<=N-1;i++){
        cols[i-1].index = i;
        cols[i-1].count = col_counts[i];
    }
    qsort(cols, N-1, sizeof(Item), cmp_cols);
    // Select top K rows
    int selected_rows[K];
    for(int i=0;i<K;i++) {
        selected_rows[i] = rows[i].index;
    }
    // Sort selected rows ascendingly
    for(int i=0;i<K-1;i++){
        for(int j=i+1;j<K;j++){
            if(selected_rows[i] > selected_rows[j]){
                int temp = selected_rows[i];
                selected_rows[i] = selected_rows[j];
                selected_rows[j] = temp;
            }
        }
    }
    // Select top L columns
    int selected_cols[L];
    for(int i=0;i<L;i++) {
        selected_cols[i] = cols[i].index;
    }
    // Sort selected columns ascendingly
    for(int i=0;i<L-1;i++){
        for(int j=i+1;j<L;j++){
            if(selected_cols[i] > selected_cols[j]){
                int temp = selected_cols[i];
                selected_cols[i] = selected_cols[j];
                selected_cols[j] = temp;
            }
        }
    }
    // Print rows
    if(K > 0){
        for(int i=0;i<K;i++){
            if(i>0) printf(" ");
            printf("%d", selected_rows[i]);
        }
    }
    printf("\n");
    // Print columns
    if(L > 0){
        for(int i=0;i<L;i++){
            if(i>0) printf(" ");
            printf("%d", selected_cols[i]);
        }
    }
    printf("\n");
    // Free memory
    free(row_counts);
    free(col_counts);
    free(rows);
    free(cols);
    return 0;
}