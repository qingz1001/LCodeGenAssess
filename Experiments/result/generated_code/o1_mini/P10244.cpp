#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d", &n);
    
    char *a = (char*)malloc((n+1) * sizeof(char));
    char *b = (char*)malloc((n+1) * sizeof(char));
    char *c = (char*)malloc((n+1) * sizeof(char));
    char *d = (char*)malloc((n+1) * sizeof(char));
    char *res_b = (char*)malloc((n+1) * sizeof(char));
    
    scanf("%s %s %s %s", a, b, c, d);
    
    for(int i=0; i<n; i++){
        if(a[i] < c[i]){
            res_b[i] = b[i];
        }
        else if(a[i] > c[i]){
            res_b[i] = d[i];
        }
        else{
            res_b[i] = (b[i] <= d[i]) ? b[i] : d[i];
        }
    }
    res_b[n] = '\0';
    printf("%s\n", res_b);
    
    free(a);
    free(b);
    free(c);
    free(d);
    free(res_b);
    return 0;
}