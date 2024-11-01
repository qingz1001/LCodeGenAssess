#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    int count;
} Item;

int cmp(const void *a, const void *b) {
    Item *ia = (Item*)a;
    Item *ib = (Item*)b;
    if (ib->count != ia->count)
        return ib->count - ia->count;
    return ia->index - ib->index;
}

int main(){
    int M, N, K, L, D;
    scanf("%d %d %d %d %d", &M, &N, &K, &L, &D);
    
    int horizontal[M+1];
    int vertical[N+1];
    for(int i=1;i<M;i++) horizontal[i]=0;
    for(int i=1;i<N;i++) vertical[i]=0;
    
    for(int i=0;i<D;i++){
        int X, Y, P, Q;
        scanf("%d %d %d %d", &X, &Y, &P, &Q);
        if(X == P){
            int b = Y < Q ? Y : Q;
            if(b >=1 && b <=N-1)
                vertical[b]++;
        }
        else{
            int a = X < P ? X : P;
            if(a >=1 && a <=M-1)
                horizontal[a]++;
        }
    }
    
    Item h_items[M-1];
    for(int i=1;i<M;i++){
        h_items[i-1].index = i;
        h_items[i-1].count = horizontal[i];
    }
    qsort(h_items, M-1, sizeof(Item), cmp);
    
    Item v_items[N-1];
    for(int i=1;i<N;i++){
        v_items[i-1].index = i;
        v_items[i-1].count = vertical[i];
    }
    qsort(v_items, N-1, sizeof(Item), cmp);
    
    // Select top K horizontal corridors
    int selected_h[K];
    for(int i=0;i<K;i++) selected_h[i] = h_items[i].index;
    // Sort selected_h in ascending order
    for(int i=0;i<K-1;i++){
        for(int j=i+1;j<K;j++){
            if(selected_h[i] > selected_h[j]){
                int temp = selected_h[i];
                selected_h[i] = selected_h[j];
                selected_h[j] = temp;
            }
        }
    }
    
    // Select top L vertical corridors
    int selected_v[L];
    for(int i=0;i<L;i++) selected_v[i] = v_items[i].index;
    // Sort selected_v in ascending order
    for(int i=0;i<L-1;i++){
        for(int j=i+1;j<L;j++){
            if(selected_v[i] > selected_v[j]){
                int temp = selected_v[i];
                selected_v[i] = selected_v[j];
                selected_v[j] = temp;
            }
        }
    }
    
    // Print horizontal corridors
    if(K > 0){
        printf("%d", selected_h[0]);
        for(int i=1;i<K;i++) printf(" %d", selected_h[i]);
    }
    printf("\n");
    
    // Print vertical corridors
    if(L > 0){
        printf("%d", selected_v[0]);
        for(int i=1;i<L;i++) printf(" %d", selected_v[i]);
    }
    printf("\n");
    
    return 0;
}