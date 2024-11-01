#include <stdio.h>

int main(){
    int N;
    scanf("%d", &N);
    int a[10];
    for(int i=0;i<N;i++) scanf("%d", &a[i]);
    
    // Step 1: Find the first index from the end where a[i-1] > a[i]
    int i = N-1;
    while(i >0 && a[i-1] <= a[i]) i--;
    
    if(i ==0){
        printf("ERROR");
        return 0;
    }
    
    // Step 2: Find the largest j such that a[j] < a[i-1]
    int j = N-1;
    while(a[j] >= a[i-1]) j--;
    
    // Step 3: Swap a[j] and a[i-1]
    int temp = a[j];
    a[j] = a[i-1];
    a[i-1] = temp;
    
    // Step 4: Reverse a[i..N-1]
    int left = i, right = N-1;
    while(left < right){
        temp = a[left];
        a[left] = a[right];
        a[right] = temp;
        left++;
        right--;
    }
    
    for(int k=0;k<N;k++) printf("%d%c", a[k], k<N-1?' ':'\n');
}