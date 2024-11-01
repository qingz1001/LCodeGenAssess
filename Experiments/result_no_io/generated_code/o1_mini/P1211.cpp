#include <stdio.h>

int is_allowed_digits(int num, int is_allowed[]) {
    while (num > 0) {
        int digit = num % 10;
        if (!is_allowed[digit]) return 0;
        num /= 10;
    }
    return 1;
}

int main(){
    int n, a[10];
    scanf("%d", &n);
    int is_allowed[10] = {0};
    for(int i=0;i<n;i++) {scanf("%d", &a[i]); is_allowed[a[i]]=1;}
    int count=0;
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            for(int k=0;k<n;k++) {
                int ABC = 100*a[i] + 10*a[j] + a[k];
                for(int l=0;l<n;l++) {
                    for(int m=0;m<n;m++) {
                        int D = a[l];
                        int E = a[m];
                        int DE = 10*D + E;
                        int partial1 = ABC * E;
                        if(partial1 < 100 || partial1 > 999) continue;
                        if(!is_allowed_digits(partial1, is_allowed)) continue;
                        int partial2 = ABC * D;
                        if(partial2 < 100 || partial2 > 999) continue;
                        if(!is_allowed_digits(partial2, is_allowed)) continue;
                        int final = ABC * DE;
                        if(final < 1000 || final > 9999) continue;
                        if(!is_allowed_digits(final, is_allowed)) continue;
                        count++;
                    }
                }
            }
        }
    }
    printf("%d", count);
}