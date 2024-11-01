#include<stdio.h>
#include<string.h>

#define MAX_N 20
#define HASH_SIZE 5000003

typedef struct {
    unsigned long long key;
    char result;
    char used;
} hash_entry_t;

hash_entry_t memo_table[HASH_SIZE];

unsigned long long get_key(int node, int N, int edges[]) {
    unsigned long long key = node;
    for(int i=0;i<N;i++) {
        key = key * 31 + edges[i];
    }
    return key;
}

char lookup(int node, int N, int edges[]) {
    unsigned long long key = get_key(node, N, edges);
    unsigned long long hash = key % HASH_SIZE;
    while(memo_table[hash].used && memo_table[hash].key != key){
        hash = (hash + 1) % HASH_SIZE;
    }
    if(memo_table[hash].used && memo_table[hash].key == key){
        return memo_table[hash].result;
    }
    return -1;
}

void store_result(int node, int N, int edges[], char result){
    unsigned long long key = get_key(node, N, edges);
    unsigned long long hash = key % HASH_SIZE;
    while(memo_table[hash].used && memo_table[hash].key != key){
        hash = (hash + 1) % HASH_SIZE;
    }
    if(!memo_table[hash].used){
        memo_table[hash].key = key;
        memo_table[hash].result = result;
        memo_table[hash].used = 1;
    }
    else{
        memo_table[hash].result = result;
    }
}

char can_win(int node, int N, int edges[]) {
    char memo = lookup(node, N, edges);
    if (memo != -1) return memo;
    // Find left and right edges
    int left = (node -1 + N) % N;
    int right = node;
    if(edges[left]==0 && edges[right]==0){
        store_result(node, N, edges, 0);
        return 0;
    }
    // Try all possible moves
    for(int dir=0; dir<2; dir++){
        int edge = (dir==0)? left : right;
        if(edges[edge] >0){
            for(int decrease=1; decrease<=edges[edge]; decrease++){
                int new_edges[MAX_N];
                for(int i=0;i<N;i++) new_edges[i] = edges[i];
                new_edges[edge] -= decrease;
                int new_node;
                if(dir==0){
                    new_node = edge;
                }
                else{
                    new_node = (node +1) % N;
                }
                if(!can_win(new_node, N, new_edges)){
                    store_result(node, N, edges, 1);
                    return 1;
                }
            }
        }
    }
    store_result(node, N, edges, 0);
    return 0;
}

int main(){
    int N;
    scanf("%d", &N);
    int edges[MAX_N];
    for(int i=0;i<N;i++) scanf("%d", &edges[i]);
    int start_node =0;
    if(can_win(start_node, N, edges)){
        printf("YES\n");
    }
    else{
        printf("NO\n");
    }
    return 0;
}