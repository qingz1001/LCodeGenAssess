#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int *a = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", &a[i]);

    // Initialize deque
    int *deque = (int*)malloc(n * sizeof(int));
    int head = 0, tail = 0;

    for(int i=0;i<n;i++){
        if(i > 0){
            // Remove indices out of window
            while(head < tail && deque[head] < i - m) head++;
            // Remove from tail all elements >= current a[i-1]
            while(head < tail && a[i-1] <= a[deque[tail-1]]) tail--;
            // Add the previous element index
            deque[tail++] = i-1;
        }

        if(i == 0){
            printf("0\n");
        }
        else{
            if(head < tail){
                printf("%d\n", a[deque[head]]);
            }
            else{
                printf("0\n");
            }
        }
    }

    free(a);
    free(deque);
    return 0;
}