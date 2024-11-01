#include<stdio.h>

int main(){
    int n, T;
    scanf("%d %d", &n, &T);
    int vi, ti;
    long long height;
    long long max_height = -1;
    int index = -1;
    for(int i=1;i<=n;i++){
        scanf("%d %d", &vi, &ti);
        if(ti <= T){
            height = (long long)vi * (T - ti);
        }
        else{
            height = 0;
        }
        if(height > max_height){
            max_height = height;
            index = i;
        }
        else if(height == max_height && i < index){
            index = i;
        }
    }
    printf("%d\n", index);
    return 0;
}