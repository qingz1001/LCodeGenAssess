#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007

typedef struct Node {
    int val;
    struct Node* next;
} Node;

int main(){
    int n, k, p;
    scanf("%d %d %d", &n, &k, &p);
    
    // Allocate array for forbidden next persons
    Node** forbidden = (Node**)calloc(n+1, sizeof(Node*));
    
    for(int i=0;i<k;i++){
        int a, b;
        scanf("%d %d", &a, &b);
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->val = b;
        newNode->next = forbidden[a];
        forbidden[a] = newNode;
    }
    
    // Initialize DP array
    long long* dp = (long long*)calloc(n+1, sizeof(long long));
    dp[n] = 1;
    
    // To optimize sum queries, use prefix sums
    long long* prefix = (long long*)calloc(n+2, sizeof(long long));
    prefix[n] = dp[n];
    for(int i=n-1;i>=1;i--){
        // Calculate allowed next persons: [i-p, i+p] excluding out of range
        int left = i - p;
        int right = i + p;
        if(left <1) left =1;
        if(right >n) right =n;
        
        // Total possible sum from left to right
        long long total = prefix[left] - prefix[right+1];
        if(total <0) total += MOD;
        if(total >= MOD) total %= MOD;
        
        // Subtract forbidden transitions
        Node* ptr = forbidden[i];
        while(ptr){
            int b = ptr->val;
            if(b >= left && b <= right){
                total -= dp[b];
                if(total <0) total += MOD;
            }
            ptr = ptr->next;
        }
        
        dp[i] = total % MOD;
        prefix[i] = (prefix[i+1] + dp[i]) % MOD;
    }
    
    // Now, to complete the circle, the last person should connect to n
    // So we need to ensure that the last person's next can connect to n
    // Which means |last - n| <=p and last not forbidden to have n next
    // But since n is fixed at the start, and we've built linear arrangements,
    // The first person in the sequence is to the right of n
    // So the answer is dp[n], which already accounts for connections starting from n
    
    printf("%lld\n", dp[n]);
    
    // Free memory
    for(int i=1;i<=n;i++){
        Node* ptr = forbidden[i];
        while(ptr){
            Node* tmp = ptr;
            ptr = ptr->next;
            free(tmp);
        }
    }
    free(forbidden);
    free(dp);
    free(prefix);
    
    return 0;
}