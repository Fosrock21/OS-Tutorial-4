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
 
 // Structure to hold all questions
 question questions[NUM_QUESTIONS];
 
 // Initializes the array of questions for the game
 void initialize_game(void)
 {
     // Sample questions (populate as needed)
     strcpy(questions[0].category, "Science");
     questions[0].value = 100;
     strcpy(questions[0].question, "What is the chemical symbol for Carbon Dioxide?");
     strcpy(questions[0].answer, "CO2");
     questions[0].answered = false;
 
     strcpy(questions[1].category, "History");
     questions[1].value = 100;
     strcpy(questions[1].question, "Who is the current president of the United States?");
     strcpy(questions[1].answer, "Donald Trump");
     questions[1].answered = false;
 
     // Add more questions as needed
 }
 
 // Displays each of the remaining categories and question dollar values that have not been answered
 void display_categories(void)
 {
     printf("Available questions:\n");
     for (int i = 0; i < NUM_QUESTIONS; i++) {
         if (!questions[i].answered) {
             printf("Category: %s, Value: $%d\n", questions[i].category, questions[i].value);
         }
     }
 }
 
 // Displays the question for the category and dollar value
 void display_question(char *category, int value)
 {
     for (int i = 0; i < NUM_QUESTIONS; i++) {
         if (strcmp(questions[i].category, category) == 0 && questions[i].value == value && !questions[i].answered) {
             printf("Question: %s\n", questions[i].question);
             return;
         }
     }
     printf("Sorry, question not found or already answered.\n");
 }
 
 // Returns true if the answer is correct for the question for that category and dollar value
 bool valid_answer(char *category, int value, char *answer)
 {
     for (int i = 0; i < NUM_QUESTIONS; i++) {
         if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
             return strcmp(questions[i].answer, answer) == 0;
         }
     }
     return false;
 }
 
 // Returns true if the question has already been answered
 bool already_answered(char *category, int value)
 {
     for (int i = 0; i < NUM_QUESTIONS; i++) {
         if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
             return questions[i].answered;
         }
     }
     return false;
 }
 
 