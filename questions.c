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
#include "questions.h"

question questions[NUM_QUESTIONS];

void initialize_game(void)
{
    strcpy(questions[0].category, "Science");
    questions[0].value = 100;
    strcpy(questions[0].question, "CO2 is the chemical formula for this compound.");
    strcpy(questions[0].answer, "CO2");
    questions[0].answered = false;

    strcpy(questions[1].category, "Science");
    questions[1].value = 200;
    strcpy(questions[1].question, "H2O is commonly known as what substance?");
    strcpy(questions[1].answer, "H2O");
    questions[1].answered = false;

    strcpy(questions[2].category, "History");
    questions[2].value = 100;
    strcpy(questions[2].question, "He was the first President of the United States.");
    strcpy(questions[2].answer, "Washington");
    questions[2].answered = false;

    strcpy(questions[3].category, "History");
    questions[3].value = 200;
    strcpy(questions[3].question, "In 1492, this explorer sailed the ocean blue.");
    strcpy(questions[3].answer, "Columbus");
    questions[3].answered = false;

    strcpy(questions[4].category, "Biology");
    questions[4].value = 100;
    strcpy(questions[4].question, "This organ pumps blood throughout the body.");
    strcpy(questions[4].answer, "heart");
    questions[4].answered = false;

    strcpy(questions[5].category, "Biology");
    questions[5].value = 200;
    strcpy(questions[5].question, "This is the largest organ in the human body.");
    strcpy(questions[5].answer, "skin");
    questions[5].answered = false;

    strcpy(questions[6].category, "Sports");
    questions[6].value = 100;
    strcpy(questions[6].question, "He is considered the greatest basketball player of all time (No. 23).");
    strcpy(questions[6].answer, "Jordan");
    questions[6].answered = false;

    strcpy(questions[7].category, "Sports");
    questions[7].value = 200;
    strcpy(questions[7].question, "This sport is known as the 'beautiful game'.");
    strcpy(questions[7].answer, "soccer");
    questions[7].answered = false;
}

void display_categories(void)
{
    printf("\n========================================\n");
    printf("          REMAINING QUESTIONS\n");
    printf("========================================\n\n");

    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        if (!questions[i].answered && strlen(questions[i].category) > 0 && questions[i].value > 0)
        {
            printf("  Category: %-8s  |  Value: $%d\n", questions[i].category, questions[i].value);
        }
    }
    printf("\n");
}

void display_question(char *category, int value)
{
    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        if (strcmp(questions[i].category, category) == 0 &&
            questions[i].value == value &&
            !questions[i].answered)
        {
            printf("\nQuestion for $%d (%s): %s\n",
                   value, category, questions[i].question);
            return;
        }
    }
    printf("\nNo matching question found or it has already been answered!\n");
}

bool valid_answer(char *category, int value, char *answer)
{
    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        if (strcmp(questions[i].category, category) == 0 &&
            questions[i].value == value)
        {
            return strcmp(questions[i].answer, answer) == 0;
        }
    }
    return false;
}

bool already_answered(char *category, int value)
{
    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        if (strcmp(questions[i].category, category) == 0 &&
            questions[i].value == value)
        {
            return questions[i].answered;
        }
    }
    return true;
}
