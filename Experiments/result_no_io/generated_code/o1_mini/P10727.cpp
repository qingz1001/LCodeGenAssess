#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    long long h, w;
    long long max_area = 0;
    for(int i=0;i<n;i++){
        scanf("%lld %lld", &h, &w);
        long long area = h * w;
        if(area > max_area){
            max_area = area;
        }
    }
    printf("%lld\n", max_area);
    return 0;
}