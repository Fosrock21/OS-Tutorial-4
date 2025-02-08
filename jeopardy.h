#ifndef JEOPARDY_H_
#define JEOPARDY_H_

#include "players.h"

// Processes the answer from the user containing "what is" or "who is" and extracts the answer
extern void tokenize(char *input, char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
extern void show_results(player *players, int num_players);

#endif /* JEOPARDY_H_ */

