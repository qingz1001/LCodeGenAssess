#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
typedef struct {
    long long sum;
    int i, j;
} HeapNode;

long long A[MAXN], B[MAXN];
HeapNode heap_node[2000005];
int heap_size = 0;

void push(long long sum, int i, int j){
    heap_size++;
    heap_node[heap_size].sum = sum;
    heap_node[heap_size].i = i;
    heap_node[heap_size].j = j;
    int pos = heap_size;
    while(pos > 1){
        int parent = pos / 2;
        if(heap_node[pos].sum < heap_node[parent].sum){
            HeapNode temp = heap_node[pos];
            heap_node[pos] = heap_node[parent];
            heap_node[parent] = temp;
            pos = parent;
        }
        else{
            break;
        }
    }
}

HeapNode pop_node(){
    HeapNode top = heap_node[1];
    heap_node[1] = heap_node[heap_size];
    heap_size--;
    int pos = 1;
    while(2*pos <= heap_size){
        int left = 2*pos;
        int right = left + 1;
        int smallest = left;
        if(right <= heap_size && heap_node[right].sum < heap_node[left].sum){
            smallest = right;
        }
        if(heap_node[pos].sum > heap_node[smallest].sum){
            HeapNode temp = heap_node[pos];
            heap_node[pos] = heap_node[smallest];
            heap_node[smallest] = temp;
            pos = smallest;
        }
        else{
            break;
        }
    }
    return top;
}

int main(){
    int N;
    scanf("%d", &N);
    for(int i=0;i<N;i++) scanf("%lld", &A[i]);
    for(int i=0;i<N;i++) scanf("%lld", &B[i]);
    push(A[0] + B[0], 0, 0);
    for(int k=0;k<N;k++){
        HeapNode current = pop_node();
        printf("%lld ", current.sum);
        if(current.i + 1 < N){
            push(A[current.i + 1] + B[current.j], current.i + 1, current.j);
        }
        if(current.j + 1 < N){
            push(A[current.i] + B[current.j + 1], current.i, current.j + 1);
        }
    }
    printf("\n");
    return 0;
}