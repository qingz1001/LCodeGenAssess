#include<stdio.h>
#include<string.h>

int main(){
    int n, count5=0, count0=0;
    scanf("%d", &n);
    char digits[n+1];
    for(int i=0;i<n;i++){
        char c;
        scanf(" %c", &c);
        if(c=='5') count5++;
        else if(c=='0') count0++;
    }
    if(count0 ==0){
        printf("-1");
        return 0;
    }
    int max5 = count5 - (count5 % 9);
    if(max5 ==0){
        printf("0");
        return 0;
    }
    char result[max5 + count0 +1];
    int pos=0;
    for(int i=0;i<max5;i++) result[pos++] = '5';
    for(int i=0;i<count0;i++) result[pos++] = '0';
    result[pos] = '\0';
    printf("%s", result);
    return 0;
}