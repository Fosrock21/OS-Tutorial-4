/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
 #ifndef QUESTIONS_H_
 #define QUESTIONS_H_
 
 #include <stdbool.h>
 
 #define NUM_QUESTIONS 10
 #define MAX_LEN 256
 
 // Structure for a question
 typedef struct {
     char category[MAX_LEN];
     int value;
     char question[MAX_LEN];
     char answer[MAX_LEN];
     bool answered;
 }
 question;
 
 // Function declarations
 extern void initialize_game(void);
 extern void display_categories(void);
 extern void display_question(char *category, int value);
 extern bool valid_answer(char *category, int value, char *answer);
 extern bool already_answered(char *category, int value);
 
 #endif /* QUESTIONS_H_ */
 
 