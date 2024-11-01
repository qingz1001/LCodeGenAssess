#include <stdio.h>

int main(){
    int N;
    scanf("%d", &N);
    int a[N];
    for(int i=0;i<N;i++) scanf("%d", &a[i]);
    // Step 1: Find k
    int k = -1;
    for(int i=N-2;i>=0;i--){
        if(a[i] > a[i+1]){
            k = i;
            break;
        }
    }
    if(k == -1){
        printf("ERROR");
        return 0;
    }
    // Step 2: Find l
    int l = -1;
    for(int i=N-1;i>k;i--){
        if(a[i] < a[k]){
            l = i;
            break;
        }
    }
    // Swap a[k] and a[l]
    int temp = a[k];
    a[k] = a[l];
    a[l] = temp;
    // Reverse from k+1 to end
    int start = k+1, end = N-1;
    while(start < end){
        temp = a[start];
        a[start] = a[end];
        a[end] = temp;
        start++;
        end--;
    }
    // Print the result
    for(int i=0;i<N;i++){
        if(i>0) printf(" ");
        printf("%d", a[i]);
    }
    return 0;
}