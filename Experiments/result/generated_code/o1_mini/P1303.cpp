#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 4005

int main(){
    char num1[2005], num2[2005];
    int a[2005] = {0}, b[2005] = {0};
    int result[MAX] = {0};
    scanf("%s", num1);
    scanf("%s", num2);
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    for(int i=0;i<len1;i++) a[i] = num1[len1-1-i]-'0';
    for(int i=0;i<len2;i++) b[i] = num2[len2-1-i]-'0';
    for(int i=0;i<len1;i++){
        for(int j=0;j<len2;j++){
            result[i+j] += a[i]*b[j];
        }
    }
    for(int i=0;i<len1+len2;i++){
        if(result[i] >=10){
            result[i+1] += result[i]/10;
            result[i] %=10;
        }
    }
    int size = len1 + len2;
    while(size >1 && result[size-1]==0) size--;
    for(int i=size-1;i>=0;i--) printf("%d", result[i]);
    printf("\n");
    return 0;
}