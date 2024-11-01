#include<stdio.h>
#include<string.h>
#include<ctype.h>

int char_to_val(char c){
    if(c >= '0' && c <= '9') return c - '0';
    return c - 'A' + 10;
}

char val_to_char(int v){
    if(v >=0 && v <=9) return '0' + v;
    return 'A' + (v -10);
}

int main(){
    int n, m;
    char s[20];
    scanf("%d", &n);
    scanf("%s", s);
    scanf("%d", &m);
    long long dec =0;
    for(int i=0; s[i]; i++) {
        dec = dec * n + char_to_val(toupper(s[i]));
    }
    if(dec ==0){
        printf("0");
        return 0;
    }
    char res[20];
    int idx=0;
    while(dec >0){
        res[idx++] = val_to_char(dec % m);
        dec /=m;
    }
    for(int i=idx-1;i>=0;i--) printf("%c", res[i]);
    return 0;
}