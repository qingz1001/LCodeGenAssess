#include <stdio.h>

int main(){
    int arr[8];
    for(int i=0;i<8;i++) scanf("%d", &arr[i]);
    
    int ascending=1, descending=1;
    for(int i=0;i<8;i++){
        if(arr[i]!=i+1) ascending=0;
        if(arr[i]!=8-i) descending=0;
    }
    
    if(ascending) printf("ascending");
    else if(descending) printf("descending");
    else printf("mixed");
    
    return 0;
}