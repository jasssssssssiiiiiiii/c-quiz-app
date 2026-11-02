#include <stdio.h>
#include <string.h>

#define NUM_Q 5
#define SCORE_FILE "highscore.txt"

typedef struct {
    char text[200];
    char options[4][80];
    int correct; /* 1 to 4 */
} Question;

Question quiz[NUM_Q] = {
    {"Which symbol is used to end a statement in C?",
     {"Colon (:)", "Semicolon (;)", "Period (.)", "Comma (,)"}, 2},
    {"Which header file is needed for printf()?",
     {"stdlib.h", "string.h", "stdio.h", "math.h"}, 3},
    {"What is the size of int on most modern systems (in bytes)?",
     {"1", "2", "4", "8"}, 3},
    {"Which operator is used to get the address of a variable?",
     {"*", "&", "->", "%"}, 2},
    {"Which loop is guaranteed to run at least once?",
     {"for", "while", "do-while", "foreach"}, 3}
};

int readHighScore(void) {
    FILE *fp = fopen(SCORE_FILE, "r");
    int score = 0;
    if (fp != NULL) {
        if (fscanf(fp, "%d", &score) != 1) score = 0;
        fclose(fp);
    }
    return score;
}

void saveHighScore(int score) {
    FILE *fp = fopen(SCORE_FILE, "w");
    if (fp != NULL) {
        fprintf(fp, "%d", score);
        fclose(fp);
    }
}

int getAnswer(void) {
    int ans;
    while (1) {
        printf("Your answer (1-4): ");
        if (scanf("%d", &ans) == 1 && ans >= 1 && ans <= 4)
            return ans;
        while (getchar() != '\n');
        printf("Invalid input. Enter a number from 1 to 4.\n");
    }
}

void playQuiz(void) {
    int score = 0;
    for (int i = 0; i < NUM_Q; i++) {
        printf("\nQ%d. %s\n", i + 1, quiz[i].text);
        for (int j = 0; j < 4; j++)
            printf("  %d) %s\n", j + 1, quiz[i].options[j]);

        if (getAnswer() == quiz[i].correct) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Wrong! Correct answer: %d) %s\n",
                   quiz[i].correct, quiz[i].options[quiz[i].correct - 1]);
        }
    }

    printf("\n===== RESULT =====\n");
    printf("You scored %d out of %d\n", score, NUM_Q);

    int best = readHighScore();
    if (score > best) {
        printf("New high score!\n");
        saveHighScore(score);
    } else {
        printf("High score: %d\n", best);
    }
}

int main(void) {
    int choice;
    do {
        printf("\n=== C QUIZ APP ===\n");
        printf("1. Start Quiz\n2. View High Score\n3. Exit\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = 0;
        }
        switch (choice) {
            case 1: playQuiz(); break;
            case 2: printf("High score: %d\n", readHighScore()); break;
            case 3: printf("Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 3);
    return 0;
}