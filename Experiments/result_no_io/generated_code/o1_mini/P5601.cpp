#include <stdio.h>
#include <string.h>

int main(){
    int n, q;
    scanf("%d %d", &n, &q);
    char q_text[100][101];
    char q_ans[100][101];
    for(int i=0;i<n;i++) {
        scanf("%s %s", q_text[i], q_ans[i]);
    }
    for(int i=0;i<q;i++) {
        char exam_q[101];
        char A[101], B[101], C[101], D[101];
        scanf("%s %s %s %s %s", exam_q, A, B, C, D);
        int found = -1;
        for(int j=0;j<n;j++) {
            if(strcmp(exam_q, q_text[j])==0){
                char* ans = q_ans[j];
                if(strcmp(ans, A)==0){
                    found = 0;
                }
                else if(strcmp(ans, B)==0){
                    found =1;
                }
                else if(strcmp(ans, C)==0){
                    found =2;
                }
                else if(strcmp(ans, D)==0){
                    found =3;
                }
                break;
            }
        }
        char option = 'A';
        if(found ==1) option = 'B';
        else if(found ==2) option = 'C';
        else if(found ==3) option = 'D';
        printf("%c\n", option);
    }
    return 0;
}