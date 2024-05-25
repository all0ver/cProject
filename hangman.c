#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void print(char *pAnswer);
void assign(char *pWord, char *pAnswer);
void title();
void ran_word(char *pWord);
int check_guess(char guesses[100], char guess);
int hangman(char *pWord, char *pAnswer, int round);


int main() {
    srand(time(0));

    char word[100];
    char *pWord = word;
    char answer[100];
    char *pAnswer = answer;
    int round = 0;
    char game;
    while (1) {
        printf("Menu:\n0. exit\n1. New Game\n");
        scanf(" %c", &game);
        while (game > '1' || game < '0') {
            printf("Wrong value, please enter new value: ");
            scanf(" %c", &game);
        }
        switch(game) {
            case '0':
                exit(0);
                break;
            case '1':
                hangman(pWord,pAnswer, round);
                break;
            default:
                break;
        }
    }
    return 0;
}

void print(char *pAnswer) {
    for(int i = 0; *(pAnswer+i); i++) {
        printf("%c ", *(pAnswer+i));
    }
}

void assign(char *pWord, char *pAnswer) {
    for (int i = 0; *(pWord+i); i++) {
        *(pAnswer+i) = '_';
    }
    *(pAnswer + strlen(pWord)) = '\0';
}

int check(char *pWord, char *pAnswer) {
    for(int i = 0; *(pWord+i); i++) {
        if (*(pWord+i) != *(pAnswer+i)) {
            return 1;
        }
    }
    return 0;
}

void ran_word(char *pWord) {
    FILE *file;
    char line[100];
    file = fopen("words.txt", "r");
    int words = 3000;
    int ran_line = rand() % words;
    int i = 1;

    while(i<=ran_line) {
        fgets(line, 100, file);
        i++;
    }
    fclose(file);
    line[strcspn(line, "\n")] = '\0';
    strcpy(pWord, line);
}


int check_guess(char *guesses, char guess) {
    for (int i = 0; *(guesses+i); i++) {
        if(guess == *(guesses+i)) {
            return 1;
        }
    }
}

int hangman(char *pWord, char *pAnswer, int round) {
    ran_word(pWord);
    assign(pWord, pAnswer);
    printf("\nanswer: ");
    for (int i = 0; *(pWord+i); i++) {
        printf("%c ", *(pAnswer+i));
    }

    printf("\n\nLet's start:\n");
    int lives = 10;
    char guess;
    int help = 0;
    char guesses[100];
    char *pGuesses = guesses;
    int j = 0;
    int guess_help;
    while (lives > 0 && check(pWord, pAnswer) != 0) {
        printf("You have %i lives to guess the word!\n", lives);
        printf("Guess the letter: ");
        scanf(" %c", &guess);
        while(check_guess(pGuesses, guess) == 1) {
            printf("You already used that letter. Use another one: ");
            scanf(" %c", &guess);
        }


        guesses[j] = guess;
        j++;
        for (int i = 0; *(pWord+i); i++) {
            if (*(pWord+i) == guess) {
                *(pAnswer+i) = *(pWord+i);
                help += 1;
            }
        }
        if (help == 0) {
            lives -= 1;
        }
        printf("answer: ");
        print(pAnswer);
        printf("\n");
        help = 0;
    }
    if (check(pWord, pAnswer) != 0) {
        printf("You lost!\nThe answer was: \n");
        print(pWord);
    } else {
        printf("You won!\nThe answer was: \n");
        print(pWord);
    }
    printf("\n");
    return 0; 
}