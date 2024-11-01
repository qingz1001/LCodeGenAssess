#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    int n;
    scanf("%d", &n);
    int *A_L = (int*)malloc(n * sizeof(int));
    int *A_R = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) scanf("%d %d", &A_L[i], &A_R[i]);
    
    // Initialize B_L and B_R
    int *B_L = (int*)malloc(n * sizeof(int));
    int *B_R = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++){
        B_L[i] = A_L[i];
        B_R[i] = A_R[i];
    }
    
    // Adjust B_L
    // Left to right
    for(int i=1;i<n;i++){
        if(B_L[i] > B_L[i-1] +1){
            B_L[i] = B_L[i-1] +1;
            if(B_L[i] > A_L[i]) B_L[i] = A_L[i];
        }
    }
    // Right to left
    for(int i=n-2;i>=0;i--){
        if(B_L[i] > B_L[i+1] +1){
            B_L[i] = B_L[i+1] +1;
            if(B_L[i] > A_L[i]) B_L[i] = A_L[i];
        }
    }
    
    // Adjust B_R
    // Left to right
    for(int i=1;i<n;i++){
        if(B_R[i] < B_R[i-1] -1){
            B_R[i] = B_R[i-1] -1;
            if(B_R[i] < A_R[i]) B_R[i] = A_R[i];
        }
    }
    // Right to left
    for(int i=n-2;i>=0;i--){
        if(B_R[i] < B_R[i+1] -1){
            B_R[i] = B_R[i+1] -1;
            if(B_R[i] < A_R[i]) B_R[i] = A_R[i];
        }
    }
    
    // Now check feasibility
    // B_L[i] must <= A_L[i]
    for(int i=0;i<n;i++) {
        if(B_L[i] > A_L[i]) {
            // Impossible, as A must be included in B
            // But problem guarantees A is valid
            // So do nothing
        }
    }
    // B_R[i] must >= A_R[i]
    for(int i=0;i<n;i++) {
        if(B_R[i] < A_R[i]){
            // Impossible, but A is valid
        }
    }
    
    // Calculate cost
    ll cost =0;
    for(int i=0;i<n;i++) {
        ll totalB = (ll)(B_R[i] - B_L[i] +1);
        ll totalA = (ll)(A_R[i] - A_L[i] +1);
        cost += (totalB - totalA);
    }
    printf("%lld", cost);
    
    free(A_L);
    free(A_R);
    free(B_L);
    free(B_R);
    return 0;
}