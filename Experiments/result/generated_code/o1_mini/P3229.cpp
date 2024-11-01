#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

// Fast IO
#define gc getchar_unlocked

inline int read_int() {
    int x = 0, c = gc(), neg = 0;
    while (c < '0' || c > '9') { if (c == '-') neg = 1; c = gc(); }
    while (c >= '0' && c <= '9') { x = x *10 + c - '0'; c = gc(); }
    return neg ? -x : x;
}

long long abs_ll(long long x){
    return x < 0 ? -x : x;
}

int main(){
    int n = read_int();
    int m = read_int();
    // Allocate memory
    int *a = (int*)malloc((n+1)*sizeof(int));
    int *B = (int*)malloc((n+1)*sizeof(int));
    long long *S = (long long*)malloc((n+1)*sizeof(long long));
    S[0] = 0;
    for(int i=1;i<=n;i++){
        a[i] = read_int();
        B[i] = read_int();
        S[i] = S[i-1] + B[i];
    }
    // Binary search for minimal d
    int left =0, right = n;
    while(left < right){
        int mid = left + (right - left)/2;
        int count =1;
        long long sum =0;
        int len =0;
        for(int i=1;i<=n;i++){
            sum += B[i];
            len +=1;
            long long val = 2*sum - len;
            if(val < 0) val = -val;
            if(val > mid){
                count++;
                sum = B[i];
                len =1;
                if(2*sum - len <0){
                    if(- (2*sum - len) > mid){
                        count = m+1;
                        break;
                    }
                }
                else{
                    if(2*sum - len > mid){
                        count = m+1;
                        break;
                    }
                }
            }
        }
        if(count <=m){
            right = mid;
        }
        else{
            left = mid+1;
        }
    }
    int d = left;
    // Now assign partitions
    int *X = (int*)malloc(m * sizeof(int));
    int current_pos =1;
    for(int i=1;i<m;i++){
        // Find the earliest end_pos
        for(int end_pos = current_pos; end_pos <= n - (m -i); end_pos++){
            long long sum_seg = S[end_pos] - S[current_pos-1];
            int len_seg = end_pos - current_pos +1;
            long long val = 2*sum_seg - len_seg;
            if(val <0) val = -val;
            if(val <=d){
                X[i-1] = a[end_pos];
                current_pos = end_pos +1;
                break;
            }
        }
    }
    // Last partition
    X[m-1] = a[n];
    // Print the result
    for(int i=0;i<m;i++){
        if(i>0) putchar(' ');
        printf("%d", X[i]);
    }
    putchar('\n');
    // Free memory
    free(a);
    free(B);
    free(S);
    free(X);
    return 0;
}