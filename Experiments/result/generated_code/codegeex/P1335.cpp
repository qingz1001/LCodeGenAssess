#include <stdio.h>
#include <stdlib.h>

#define MAX_EVENTS 1000000
#define MAX_VARIABLES 100

int variables[MAX_VARIABLES];

void executeEvent(char* event) {
    char type = event[0];
    int variableIndex = 0;
    int value = 0;
    int quantityType = 0;
    int quantityIndex = 0;

    sscanf(event + 2, "%d", &variableIndex);

    if (type == 'v') {
        sscanf(event + 4, " %c %d", &quantityType, &value);
        if (quantityType == 'c') {
            variables[variableIndex] += value;
        } else if (quantityType == 'v') {
            variables[variableIndex] += variables[value];
        }
    } else if (type == 's') {
        int choice1 = 0, choice2 = 0;
        sscanf(event + 3, "%d %d", &choice1, &choice2);
        printf("%d\n", choice1);
    } else if (type == 'i') {
        int conditionType1 = 0, conditionType2 = 0;
        int conditionIndex1 = 0, conditionIndex2 = 0;
        int choice1 = 0, choice2 = 0;
        sscanf(event + 3, " %c %d %c %d %d %d", &conditionType1, &conditionIndex1, &conditionType2, &conditionIndex2, &choice1, &choice2);
        int conditionValue1 = 0, conditionValue2 = 0;
        if (conditionType1 == 'c') {
            conditionValue1 = conditionIndex1;
        } else if (conditionType1 == 'v') {
            conditionValue1 = variables[conditionIndex1];
        }
        if (conditionType2 == 'c') {
            conditionValue2 = conditionIndex2;
        } else if (conditionType2 == 'v') {
            conditionValue2 = variables[conditionIndex2];
        }
        if (conditionValue1 < conditionValue2) {
            printf("%d\n", choice1);
        } else {
            printf("%d\n", choice2);
        }
    }
}

int main() {
    FILE *inputFile, *outputFile;
    char inputFileName[20], outputFileName[20];
    int n, m;
    char event[MAX_EVENTS][100];

    for (int i = 1; i <= 10; i++) {
        sprintf(inputFileName, "train%d.in", i);
        sprintf(outputFileName, "train%d.out", i);
        inputFile = fopen(inputFileName, "r");
        outputFile = fopen(outputFileName, "w");

        fscanf(inputFile, "%d %d", &n, &m);

        for (int j = 0; j < n; j++) {
            fscanf(inputFile, "%s", event[j]);
            executeEvent(event[j]);
        }

        fclose(inputFile);
        fclose(outputFile);
    }

    return 0;
}