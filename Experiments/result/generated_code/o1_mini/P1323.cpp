#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long long ull;

typedef struct {
    ull *data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createHeap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (ull*)malloc(sizeof(ull) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(ull *a, ull *b){
    ull temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MinHeap *heap, int idx){
    while(idx > 0){
        int parent = (idx - 1) / 2;
        if(heap->data[parent] > heap->data[idx]){
            swap(&heap->data[parent], &heap->data[idx]);
            idx = parent;
        }
        else break;
    }
}

void heapifyDown(MinHeap *heap, int idx){
    while(1){
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        if(left < heap->size && heap->data[left] < heap->data[smallest]){
            smallest = left;
        }
        if(right < heap->size && heap->data[right] < heap->data[smallest]){
            smallest = right;
        }
        if(smallest != idx){
            swap(&heap->data[smallest], &heap->data[idx]);
            idx = smallest;
        }
        else break;
    }
}

int pushHeap(MinHeap *heap, ull val){
    if(heap->size >= heap->capacity){
        heap->capacity *= 2;
        ull *newData = (ull*)realloc(heap->data, sizeof(ull) * heap->capacity);
        if(!newData) return -1;
        heap->data = newData;
    }
    heap->data[heap->size] = val;
    heapifyUp(heap, heap->size);
    heap->size++;
    return 0;
}

ull popHeap(MinHeap *heap){
    ull min = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return min;
}

int main(){
    int k, m;
    scanf("%d %d", &k, &m);
    
    MinHeap *heap = createHeap(65536);
    pushHeap(heap, 1);
    
    ull *res = (ull*)malloc(sizeof(ull) * k);
    int count = 0;
    
    while(count < k){
        ull current = popHeap(heap);
        res[count++] = current;
        pushHeap(heap, 2 * current + 1);
        pushHeap(heap, 4 * current + 5);
    }
    
    // Concatenate the numbers
    // Maximum digits: 300000 + 1
    char *concatenated = (char*)malloc(sizeof(char) * 500005);
    int pos = 0;
    for(int i = 0; i < k; i++){
        char temp[21];
        int len = 0;
        ull num = res[i];
        if(num == 0){
            concatenated[pos++] = '0';
        }
        else{
            char buffer[21];
            int idx = 0;
            while(num > 0){
                buffer[idx++] = '0' + (num % 10);
                num /= 10;
            }
            for(int j = idx - 1; j >= 0; j--){
                concatenated[pos++] = buffer[j];
            }
        }
    }
    concatenated[pos] = '\0';
    
    printf("%s\n", concatenated);
    
    // Perform deletion to maximize the number
    int n = pos;
    char *stack_digits = (char*)malloc(sizeof(char) * (n + 1));
    int stack_top = 0;
    for(int i = 0; i < n; i++){
        while(m > 0 && stack_top > 0 && stack_digits[stack_top - 1] < concatenated[i]){
            stack_top--;
            m--;
        }
        stack_digits[stack_top++] = concatenated[i];
    }
    while(m > 0 && stack_top > 0){
        stack_top--;
        m--;
    }
    stack_digits[stack_top] = '\0';
    
    printf("%s\n", stack_digits);
    
    // Free allocated memory
    free(heap->data);
    free(heap);
    free(res);
    free(concatenated);
    free(stack_digits);
    
    return 0;
}