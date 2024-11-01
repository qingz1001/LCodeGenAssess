#include <stdio.h>
#include <string.h>

int main(){
    int n;
    scanf("%d", &n);
    char a[n+1], b_str[n+1], c[n+1], d[n+1];
    scanf("%s %s %s %s", a, b_str, c, d);
    char b_prime[n+1];
    for(int i=0;i<n;i++){
        if(a[i] < c[i]){
            b_prime[i] = b_str[i];
        }
        else if(a[i] > c[i]){
            b_prime[i] = d[i];
        }
        else{
            b_prime[i] = (b_str[i] < d[i]) ? b_str[i] : d[i];
        }
    }
    b_prime[n] = '\0';
    printf("%s", b_prime);
}