#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    long long sum = 0;
    long long unhappy = 0;
    for(int i=0;i<n;i++){
        int school, after;
        scanf("%d %d", &school, &after);
        int total = school + after;
        unhappy += (total - 8);
        sum += unhappy;
    }
    printf("%lld\n", sum);
    return 0;
}