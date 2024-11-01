#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b){
    int y1 = *(int*)a;
    int y2 = *(int*)b;
    return y1 - y2;
}

int main(){
    int n;
    int s;
    scanf("%d %d", &n, &s);
    
    int a, b;
    scanf("%d %d", &a, &b);
    
    int *y = (int*)malloc(n * sizeof(int));
    int count = 0;
    for(int i = 0; i < n; i++){
        int x_i, y_i;
        scanf("%d %d", &x_i, &y_i);
        if(x_i <= a + b){
            y[count++] = y_i;
        }
    }
    
    qsort(y, count, sizeof(int), cmp);
    
    int result = 0;
    int total = 0;
    for(int i = 0; i < count; i++){
        if(total + y[i] > s){
            break;
        }
        total += y[i];
        result++;
    }
    
    printf("%d\n", result);
    
    free(y);
    return 0;
}