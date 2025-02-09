/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

#define BUFFER_LEN 256
#define NUM_PLAYERS 4

int main(int argc, char *argv[])
{
    player players[NUM_PLAYERS];
    char buffer[BUFFER_LEN];

    printf("\n====================================\n");
    printf(" Welcome to the Jeopardy Game Setup\n Enter 4 names \n");
    printf("====================================\n\n");

    // Prompt for 4 player names
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        printf("Enter name of Player %d: ", i + 1);
        fgets(players[i].name, MAX_LEN, stdin);
        players[i].name[strcspn(players[i].name, "\n")] = 0;
        players[i].score = 0;
    }

    printf("\nGreat! Let's initialize the questions...\n\n");
    initialize_game();

    while (1)
    {
        if (all_questions_answered())
        {
            printf("\nAll questions have been answered!\n");
            break;
        }

        display_categories();

        printf("Enter the player's name who will choose a question: ");
        fgets(buffer, BUFFER_LEN, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        if (!player_exists(players, NUM_PLAYERS, buffer))
        {
            printf("\n  [!] That is not a valid player. Please try again.\n\n");
            continue;
        }

        char category[MAX_LEN];
        int value = 0;

        printf("Enter category: ");
        fgets(category, MAX_LEN, stdin);
        category[strcspn(category, "\n")] = 0;

        printf("Enter dollar value: ");
        if (scanf("%d", &value) != 1)
        {
            printf("\n  [!] Invalid dollar value. Please try again.\n\n");
            getchar(); // consume leftover invalid input
            continue;
        }
        getchar(); // consume newline

        if (already_answered(category, value))
        {
            printf("\n  [!] That question is unavailable or already answered.\n\n");
            continue;
        }

        display_question(category, value);

        printf("\nEnter your answer (e.g. 'what is CO2' or 'who is Washington'): ");
        fgets(buffer, BUFFER_LEN, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        {
            char *tokens[3] = {0};
            tokenize(buffer, tokens);

            if (tokens[0] == NULL || tokens[1] == NULL || tokens[2] == NULL)
            {
                for (int i = 0; i < NUM_QUESTIONS; i++)
                {
                    if (!questions[i].answered &&
                        strcmp(questions[i].category, category) == 0 &&
                        questions[i].value == value)
                    {
                        printf("\nIncorrect format. The correct answer was: %s\n\n", questions[i].answer);
                        questions[i].answered = true;
                        break;
                    }
                }
                continue;
            }

            if (valid_answer(category, value, tokens[2]))
            {
                printf("\nCorrect! You earn $%d.\n\n", value);
                update_score(players, NUM_PLAYERS, buffer, value);
            }
            else
            {
                for (int i = 0; i < NUM_QUESTIONS; i++)
                {
                    if (!questions[i].answered &&
                        strcmp(questions[i].category, category) == 0 &&
                        questions[i].value == value)
                    {
                        printf("\nIncorrect. The correct answer was: %s\n\n", questions[i].answer);
                        break;
                    }
                }
            }

            for (int i = 0; i < NUM_QUESTIONS; i++)
            {
                if (strcmp(questions[i].category, category) == 0 &&
                    questions[i].value == value)
                {
                    questions[i].answered = true;
                    break;
                }
            }
        }
    }

    show_results(players, NUM_PLAYERS);
    return EXIT_SUCCESS;
}

bool all_questions_answered(void)
{
    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        if (!questions[i].answered)
        {
            return false;
        }
    }
    return true;
}

void tokenize(char *input, char **tokens)
{
    char *delim = " ";
    char *ptr = strtok(input, delim);
    int idx = 0;

    while (ptr != NULL && idx < 3)
    {
        tokens[idx++] = ptr;
        ptr = strtok(NULL, delim);
    }

    if (idx == 2 && ptr != NULL)
    {
        tokens[2] = ptr;
        char leftover[BUFFER_LEN] = {0};
        while ((ptr = strtok(NULL, "")) != NULL)
        {
            strncat(leftover, " ", BUFFER_LEN - 1);
            strncat(leftover, ptr, BUFFER_LEN - 1);
        }
        if (strlen(leftover) > 0)
        {
            strncat(tokens[2], leftover, BUFFER_LEN - 1);
        }
    }
}

void show_results(player *players, int num_players)
{
    for (int i = 0; i < num_players - 1; i++)
    {
        for (int j = 0; j < num_players - i - 1; j++)
        {
            if (players[j].score < players[j + 1].score)
            {
                player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }

    printf("\n========================================\n");
    printf("          FINAL RESULTS\n");
    printf("========================================\n\n");

    for (int i = 0; i < num_players; i++)
    {
        printf("%d) %s: $%d\n", i + 1, players[i].name, players[i].score);
    }

    printf("\nThanks for playing Jeopardy!\n\n");
}
