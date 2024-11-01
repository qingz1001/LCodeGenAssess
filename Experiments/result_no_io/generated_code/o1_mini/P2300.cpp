#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    int n;
    scanf("%d", &n);
    ll *p = (ll*)malloc(n * sizeof(ll));
    for(int i=0;i<n;i++) scanf("%lld", &p[i]);
    ll *stack = (ll*)malloc(n * sizeof(ll));
    int top =0;
    int count =0;
    for(int i=0;i<n;i++){
        stack[top++] = p[i];
        while(top >=2 && stack[top-2] > stack[top-1]){
            ll merged = stack[top-2] + stack[top-1];
            top -=2;
            stack[top++] = merged;
            count++;
        }
    }
    printf("%d\n", count);
    free(p);
    free(stack);
    return 0;
}