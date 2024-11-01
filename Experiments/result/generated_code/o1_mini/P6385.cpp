#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){
    int n, q;
    scanf("%d %d", &n, &q);
    char S[n+1];
    scanf("%s", S);
    while(q--){
        int i, p, k;
        scanf("%d %d %d", &i, &p, &k);
        int max_j = i;
        while(max_j <= n && S[max_j-1] == S[p-1 + (max_j - i)]){
            max_j++;
        }
        max_j--;
        if(p-1 + (max_j - i) >= n) {
            max_j--;
        }
        int teleport_cost = n - max_j;
        int operations = abs(k - i);
        printf("%d\n", teleport_cost + operations);
    }
    return 0;
}