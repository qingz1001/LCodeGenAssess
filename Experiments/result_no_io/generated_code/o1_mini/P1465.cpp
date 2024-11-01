#include <stdio.h>
#include <string.h>

int main(){
    int n;
    scanf("%d", &n);
    int count_I=0, count_V=0, count_X=0, count_L=0, count_C=0, count_D=0, count_M=0;

    int values[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
    char *symbols[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
    int len = sizeof(values)/sizeof(values[0]);

    for(int num=1; num<=n; num++){
        int temp = num;
        for(int i=0;i<len;i++){
            while(temp >= values[i]){
                char *s = symbols[i];
                for(int j=0; j < strlen(s); j++){
                    switch(s[j]){
                        case 'I': count_I++; break;
                        case 'V': count_V++; break;
                        case 'X': count_X++; break;
                        case 'L': count_L++; break;
                        case 'C': count_C++; break;
                        case 'D': count_D++; break;
                        case 'M': count_M++; break;
                    }
                }
                temp -= values[i];
            }
        }
    }

    if(count_I) printf("I %d\n", count_I);
    if(count_V) printf("V %d\n", count_V);
    if(count_X) printf("X %d\n", count_X);
    if(count_L) printf("L %d\n", count_L);
    if(count_C) printf("C %d\n", count_C);
    if(count_D) printf("D %d\n", count_D);
    if(count_M) printf("M %d\n", count_M);
    return 0;
}