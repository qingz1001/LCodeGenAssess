#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int front;
    int rear;
    int size;
} Deque;

Deque* createDeque(int size) {
    Deque* dq = (Deque*)malloc(sizeof(Deque));
    dq->data = (int*)malloc(sizeof(int) * size);
    dq->front = 0;
    dq->rear = 0;
    dq->size = size;
    return dq;
}

void pushBack(Deque* dq, int val) {
    dq->data[dq->rear++] = val;
}

void popBack(Deque* dq) {
    dq->rear--;
}

void popFront(Deque* dq) {
    dq->front++;
}

int front(Deque* dq) {
    return dq->data[dq->front];
}

int back(Deque* dq) {
    return dq->data[dq->rear -1];
}

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    int *a = (int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++) scanf("%d", &a[i]);
    
    Deque *minD = createDeque(n);
    Deque *maxD = createDeque(n);
    
    char *minOut = (char*)malloc((n*12 + 1)*sizeof(char));
    char *maxOut = (char*)malloc((n*12 + 1)*sizeof(char));
    minOut[0] = '\0';
    maxOut[0] = '\0';
    
    for(int i=0;i<n;i++){
        while(minD->rear > minD->front && a[i] <= a[back(minD)]) popBack(minD);
        pushBack(minD, i);
        while(minD->front < minD->rear && front(minD) <= i - k) popFront(minD);
        
        while(maxD->rear > maxD->front && a[i] >= a[back(maxD)]) popBack(maxD);
        pushBack(maxD, i);
        while(maxD->front < maxD->rear && front(maxD) <= i - k) popFront(maxD);
        
        if(i >= k-1){
            char buffer[12];
            int len = sprintf(buffer, "%d ", a[front(minD)]);
            strcat(minOut, buffer);
            len = sprintf(buffer, "%d ", a[front(maxD)]);
            strcat(maxOut, buffer);
        }
    }
    // Remove trailing space
    if(k <= n){
        int len = strlen(minOut);
        if(len >0 && minOut[len-1]==' ') minOut[len-1] = '\0';
        len = strlen(maxOut);
        if(len >0 && maxOut[len-1]==' ') maxOut[len-1] = '\0';
    }
    printf("%s\n%s\n", minOut, maxOut);
    
    free(a);
    free(minD->data);
    free(minD);
    free(maxD->data);
    free(maxD);
    free(minOut);
    free(maxOut);
    return 0;
}