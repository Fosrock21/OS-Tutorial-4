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
 
 // Initializes the game and sets up players
 int main(int argc, char *argv[])
 {
     player players[NUM_PLAYERS];
     char buffer[BUFFER_LEN] = {0};
     
     // Prompt for player names
     printf("Enter names of four players:\n");
     for (int i = 0; i < NUM_PLAYERS; i++) {
         printf("Player %d: ", i + 1);
         fgets(players[i].name, MAX_LEN, stdin);
         players[i].name[strcspn(players[i].name, "\n")] = 0; // Remove newline
         players[i].score = 0;
     }
     
     // Initialize questions
     initialize_game();
     
     // Game loop
     while (1) {
         display_categories();
         printf("Enter player's name who will choose the question: ");
         fgets(buffer, BUFFER_LEN, stdin);
         buffer[strcspn(buffer, "\n")] = 0;
         
         if (!player_exists(players, NUM_PLAYERS, buffer)) {
             printf("Sorry, invalid player name. Try again.\n");
             continue;
         }
         
         char category[MAX_LEN];
         int value;
         printf("Enter category: ");
         fgets(category, MAX_LEN, stdin);
         category[strcspn(category, "\n")] = 0;
         
         printf("Enter dollar value: ");
         scanf("%d", &value);
         getchar(); // Consume newline
         
         if (already_answered(category, value)) {
             printf("This question has already been answered. Choose another.\n");
             continue;
         }
         
         display_question(category, value);
         
         char answer[MAX_LEN];
         printf("Enter your answer: ");
         fgets(answer, MAX_LEN, stdin);
         answer[strcspn(answer, "\n")] = 0;
         
         if (valid_answer(category, value, answer)) {
             printf("Correct! You earn $%d.\n", value);
             update_score(players, NUM_PLAYERS, buffer, value);
         } else {
             printf("Incorrect. You lose $%d.\n", value);
             update_score(players, NUM_PLAYERS, buffer, -value);
         }
         
         // Check if all questions are answered, then break the loop
     }
     
     show_results(players, NUM_PLAYERS);
     return EXIT_SUCCESS;
 }
 
 bool player_exists(player *players, int num_players, char *name) {
     for (int i = 0; i < num_players; i++) {
         if (strcmp(players[i].name, name) == 0) {
             return true;
         }
     }
     return false;
 }
 
 void update_score(player *players, int num_players, char *name, int score) {
     for (int i = 0; i < num_players; i++) {
         if (strcmp(players[i].name, name) == 0) {
             players[i].score += score;
             return;
         }
     }
 }
 
 void initialize_game(void) {
     // Example: Initialize questions with dummy data
     printf("The game has been initialized with sample questions.\n");
 }
 
 void display_categories(void) {
     printf("Here are the categories: Science, History, Biology, Sports\n");
 }
 
 bool already_answered(char *category, int value) {
     return false; // Placeholder
 }
 
 void display_question(char *category, int value) {
     printf("Displaying question from %s for $%d.\n", category, value);
 }
 
 bool valid_answer(char *category, int value, char *answer) {
     return true; 
 }
 
 void show_results(player *players, int num_players) {
     printf("Game Over. The final Scores:\n");
     for (int i = 0; i < num_players; i++) {
         printf("%s: $%d\n", players[i].name, players[i].score);
     }
 }
 
 