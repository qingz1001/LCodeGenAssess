#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 20
#define MAX_PEOPLE 20
#define MAX_STATEMENTS 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    int always_lies;
} Person;

typedef struct {
    char speaker[MAX_NAME_LENGTH];
    char statement[MAX_STATEMENTS];
} Statement;

int main() {
    int M, N, P;
    scanf("%d %d %d", &M, &N, &P);

    Person people[MAX_PEOPLE];
    for (int i = 0; i < M; ++i) {
        scanf("%s", people[i].name);
        people[i].always_lies = 0;
    }

    Statement statements[MAX_STATEMENTS];
    for (int i = 0; i < P; ++i) {
        scanf("%s : %s", statements[i].speaker, statements[i].statement);
    }

    int guilty_count[MAX_PEOPLE] = {0};
    for (int i = 0; i < P; ++i) {
        int speaker_index = -1;
        for (int j = 0; j < M; ++j) {
            if (strcmp(people[j].name, statements[i].speaker) == 0) {
                speaker_index = j;
                break;
            }
        }
        if (speaker_index == -1) continue;

        char *token = strtok(statements[i].statement, " .");
        while (token != NULL) {
            if (strcmp(token, "I") == 0) {
                token = strtok(NULL, " .");
                if (strcmp(token, "am") == 0) {
                    token = strtok(NULL, " .");
                    if (strcmp(token, "guilty.") == 0) {
                        if (people[speaker_index].always_lies) {
                            for (int j = 0; j < M; ++j) {
                                if (j != speaker_index) guilty_count[j]++;
                            }
                        } else {
                            guilty_count[speaker_index]++;
                        }
                    } else if (strcmp(token, "not") == 0 && strcmp(strtok(NULL, " ."), "guilty.") == 0) {
                        if (people[speaker_index].always_lies) {
                            guilty_count[speaker_index]++;
                        } else {
                            for (int j = 0; j < M; ++j) {
                                if (j != speaker_index) guilty_count[j]++;
                            }
                        }
                    }
                } else if (strcmp(token, "is") == 0) {
                    token = strtok(NULL, " .");
                    if (strcmp(token, "guilty.") == 0) {
                        if (people[speaker_index].always_lies) {
                            for (int j = 0; j < M; ++j) {
                                if (j != speaker_index) guilty_count[j]++;
                            }
                        } else {
                            guilty_count[speaker_index]++;
                        }
                    } else if (strcmp(token, "not") == 0 && strcmp(strtok(NULL, " ."), "guilty.") == 0) {
                        if (people[speaker_index].always_lies) {
                            guilty_count[speaker_index]++;
                        } else {
                            for (int j = 0; j < M; ++j) {
                                if (j != speaker_index) guilty_count[j]++;
                            }
                        }
                    }
                }
            } else if (strcmp(token, "Today") == 0) {
                token = strtok(NULL, " .");
                if (strcmp(token, "is") == 0) {
                    // Ignore the day of the week
                }
            }
            token = strtok(NULL, " .");
        }
    }

    int possible_guilty = -1;
    for (int i = 0; i < M; ++i) {
        if (guilty_count[i] == 1) {
            if (possible_guilty == -1) {
                possible_guilty = i;
            } else {
                printf("Cannot Determine\n");
                return 0;
            }
        }
    }

    if (possible_guilty == -1) {
        printf("Impossible\n");
    } else {
        printf("%s\n", people[possible_guilty].name);
    }

    return 0;
}