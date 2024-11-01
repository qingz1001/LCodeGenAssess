#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_Q 100
#define MAX_LEN 105

typedef struct {
    char question[MAX_LEN];
    char answer[MAX_LEN];
} QA;

int main(){
    int n, q;
    scanf("%d %d", &n, &q);
    QA qa_list[MAX_N];
    for(int i=0;i<n;i++) {
        scanf("%s %s", qa_list[i].question, qa_list[i].answer);
    }
    char q_text[MAX_LEN];
    char options[4][MAX_LEN];
    for(int i=0;i<q;i++) {
        scanf("%s %s %s %s %s", q_text, options[0], options[1], options[2], options[3]);
        char correct[MAX_LEN];
        // Find the answer
        for(int j=0;j<n;j++) {
            if(strcmp(qa_list[j].question, q_text) == 0){
                strcpy(correct, qa_list[j].answer);
                break;
            }
        }
        // Compare with options
        char res = 'A';
        for(int j=0;j<4;j++) {
            if(strcmp(options[j], correct) == 0){
                res = 'A' + j;
                break;
            }
        }
        printf("%c\n", res);
    }
    return 0;
}