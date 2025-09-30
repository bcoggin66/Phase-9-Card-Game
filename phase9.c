// include stdio library header file
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "phase9.h"


// main function
int main()
{
    // call function welcomeScreen
    welcomeScreen();

    // random seed function
    srand ((unsigned int) time (NULL));

    int choice;
    do {
        choice = displayMenu();
        if (choice == PLAY) {
            playGame();
        } else if (choice == LEAD) {
            readLeaderboardFile();
        }
    } while (choice != EXIT);

    return 0;
}

// welcomeScreen function displays the Phase 9 logo and phases of the game
void welcomeScreen()
{
	printf ("PPPP   H  H     A      SSSS  EEEE    9999  \n");
	printf ("P   P  H  H    A A    SS     E      9    9 \n");
	printf ("PPPP   HHHH   AA AA    SS    EEE     9999  \n");
	printf ("P      H  H   A   A      SS  E         9  \n" );
	printf ("P      H  H  A     A  SSSS   EEEE    99    \n");
	printf ("\n");
	printf ("PHASE 9 PHASES\n\n");
    printf("1. 2 sets of 3\n");
    printf("2. 1 set of 3 + 1 run of 4\n");
    printf("3. 1 set of 4 + 1 run of 4\n");
    printf("4. 1 run of 7\n");
    printf("5. 1 run of 8\n");
    printf("6. 1 run of 9\n");
    printf("7. 2 sets of 4\n");
    printf("8. 1 set of 5 + 1 set of 2\n");
    printf("9. 1 set of 5 + 1 set of 3\n\n");
}

// function playGame controls the game play
void playGame()
{
    int numPlayers;
    printf("Enter number of players: ");
    while (scanf("%d", &numPlayers) != 1) {
        printf("Invalid input, try again: ");
        while (getchar() != '\n'); // clear buffer
    }

    // dynamic array of players
    struct Player players[numPlayers];

    // initialize deck
    int deck[DECK];
    int deckIdx = ZERO;
    initializeDeck(deck);
    shuffleDeck(deck);

    // setup each player
    for (int i = 0; i < numPlayers; i++) {
        printf("Player %d, enter your name: ", i + 1);
        scanf("%19s", players[i].playerName);

        players[i].playerNum = i + 1;
        players[i].currentPhase = ONE;
        players[i].wins = ZERO;

        // deal and sort hand
        dealHand(deck, &deckIdx, players[i].playerHand);
        qsort(players[i].playerHand, HAND, sizeof(players[i].playerHand[0]), comp);
    }

    // initial discard
    int discard = dealDiscard(deck, &deckIdx);

    int currentPlayer = 0; // index into players[]

    while (!isGameOverMulti(players, numPlayers)) {
        struct Player *p = &players[currentPlayer];

        printf("\n--- %s's Turn ---\n", p->playerName);

        displayPhase(p->currentPhase);
        displayPlayerHand(p->playerName, p->playerHand);

        // make sure discard isn't a SKIP
        while (discard == SKIP) {
            printf("\nDiscard pile is a SKIP! Drawing a new discard...\n");
            discard = dealDiscard(deck, &deckIdx);
        }

        printf("\nDiscard pile\n\n");
        displaySingle(discard);

        // pick up discard or draw
        int discardOrDraw = playerOption(p->playerName);
        int pickUp;
        if (discardOrDraw == DISCARD) {
            printf("%s chose to pick up the discard\n", p->playerName);
            pickUp = discard;
        } else {
            printf("%s chose to draw from the deck\n", p->playerName);
            pickUp = draw(deck, &deckIdx);
        }

        printf("\nNew card\n");
        displaySingle(pickUp);

        if (pickUp == SKIP) {
            printf("\nSkip card drawn! %s loses their turn!\n", p->playerName);
            discard = SKIP;
            currentPlayer = (currentPlayer + 1) % numPlayers;
            continue;
        }

        // get discard choice
        int playerDiscard = discardCard(p->playerName, p->playerHand, pickUp);

        // update hand + discard
        updateHand(p->playerName, p->playerHand, playerDiscard, &discard, pickUp);

        if (discard == SKIP) {
            printf("\n%s discarded a SKIP! Next player loses a turn!\n", p->playerName);
            currentPlayer = (currentPlayer + 2) % numPlayers;
            continue;
        }

        // check phase completion
        if (checkPhase(*p)) {
            printf("Player %s completed their phase!\n", p->playerName);
            updatePhase(p);
        } else {
            printf("Player %s did not complete their phase.\n", p->playerName);
        }

        // move to next player
        currentPlayer = (currentPlayer + 1) % numPlayers;
    }

    // game over
    printf("\nThe game is over!\n");

    for (int i = 0; i < numPlayers; i++) {
        if (players[i].currentPhase > 9) {
            printf("%s has completed Phase 9!\n", players[i].playerName);
            players[i].wins++;
            writeLeaderboardFile(players[i].playerName, players[i].wins);
        }
    }
}


// Writes the player's results to leaderboard.txt
void writeLeaderboardFile(char playerName[NAME], int wins)
{
    FILE *fp = fopen("leaderboard.txt", "a"); // open in append mode
    if (fp == NULL)
    {
        perror("Error opening leaderboard file for writing\n");
        return;
    }

    // Count lines to figure out new position (optional improvement)
    // For now, just append new entry at the end
    fprintf(fp, "%s,%d\n", playerName, wins);

    fclose(fp);
}

// function displayMenu provides players with their options
int displayMenu()
{
    int choice = ZERO;
    int valid = FALSE;

    // continue looping until player selects a valid option
    while(!valid)
    {
        printf("\nSelect a menu option:\n");
        printf("1. Play Phase 9\n");
        printf("2. View Leaderboard\n");
        printf("3. Exit Game\n");

        while (scanf("%d", &choice) != 1) {
            printf("Invalid input, try again: ");
            while (getchar() != '\n'); // clear buffer
        }

        // data validation
        if(choice != PLAY && choice != LEAD && choice != EXIT)
        {
            valid = FALSE;
        }
        else
        {
            valid = TRUE;
        }
    }

    return choice;
}

// create the Phase 9 deck of cards
void initializeDeck(int deck[DECK])
{
    // index used for the array position
    int idx = ZERO;

    // add eight cards for each value (2 red, 2 blue, 2 green, 2 yellow)
    // total 96 numbered cards
    for(int c = ZERO; c < EIGHT; c++)
    {
        // twelve numbered values, 1 - 12
        for(int v = ONE; v <= TWELVE; v++)
        {
            deck[idx] = v;

            // increment the index
            idx++;
        }
    }

    // add the eight wild cards
    for(int w = ZERO; w < EIGHT; w++)
    {
        deck[idx] = WILD;

        // increment the index
        idx++;
    }

    // add the four skip cards
    for(int s = ZERO; s < FOUR; s++)
    {
        deck[idx] = SKIP;

        // increment the index
        idx++;
    }
}

// shuffle the deck using the Durstenfeld shuffle algorithm
void shuffleDeck(int deck[DECK])
{
    for (int d = ZERO; d < DECK; d++)
    {
        // randomly select a card index
        int c = rand() % DECK;

        // save the card a the looping index
        int card = deck[d];

        // switch the card at the looping index with the card at the randomly selected index
        deck[d] = deck[c];

        // update the card at the randomly select index with the saved card
        deck[c] = card;
    }
}

// deal the player's their hand
void dealHand(int deck[DECK], int *deckIdx, int playerHand[HAND])
{
    // deal 10 random cards from the deck
    for(int c = ZERO; c < HAND; c++)
    {
        // add the card to the player's hand
        // be sure to dereference the pointer for the deck index
        playerHand[c] = deck[*deckIdx];

        // dereference the pointer and increase the index
        (*deckIdx)++;
    }
}

// display the player's hand
void displayPlayerHand(char player[NAME], int playerHand[HAND])
{

    printf("\n%s's hand\n\n", player);
    printf("+---------------------------------------------------------------------+\n");
    printf("|      |      |      |      |      |      |      |      |      |      |\n");

    for(int c = ZERO; c < HAND; c++)
    {
        if(playerHand[c] == WILD)
        {
            printf("| %3c  ", 'W');
        }
        else if(playerHand[c] == SKIP)
        {
            printf("| %3c  ", 'S');
        }
        else
        {
            printf("| %3d  ", playerHand[c]);
        }
    }

    printf("|\n|      |      |      |      |      |      |      |      |      |      |\n");
    printf("+---------------------------------------------------------------------+\n");
}

// deal one card for the discard pile
int dealDiscard(int deck[DECK], int *deckIdx)
{
    // deal one card from the deck
    // dereference the pointer parameter
    int discard = deck[*deckIdx];

    // dereference the pointer and increase the index
    // must use parenthesis around dereferencing
    (*deckIdx)++;

    return discard;
}

// display the top card of the discard pile
void displaySingle(int discard)
//void displayDiscard(int discard)
{
//    printf("\nDiscard pile\n\n");
    printf("+------+\n");
    printf("|      |\n");

    if(discard == WILD)
    {
        printf("| %3c  |\n", 'W');
    }
    else if(discard == SKIP)
    {
        printf("| %3c  |\n", 'S');
    }
    else
    {
        printf("| %3d  |\n", discard);
    }

    printf("|      |\n");
    printf("+------+\n");
}

// used for supporting the qsort function
// provide function to students
int comp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int cmpLeaderboard(const void *a, const void *b) {
    const struct LeaderboardEntry *entryA = (const struct LeaderboardEntry *)a;
    const struct LeaderboardEntry *entryB = (const struct LeaderboardEntry *)b;
    return entryB->wins - entryA->wins;  // descending order
}

void readLeaderboardFile()
{
    struct LeaderboardEntry entries[DATA]; 
    int entryCount = 0;

    FILE *fp = fopen("leaderboard.txt", "r");
    if (fp == NULL) {
        perror("Error opening file\n");
        return;
    }

    char line[LINE];
    while (fgets(line, LINE, fp) != NULL) {
        char *name = strtok(line, ",");
        char *winsStr = strtok(NULL, ",");

        if (name && winsStr) {
            name = trim(name);
            winsStr = trim(winsStr);
            int wins = atoi(winsStr);

            int found = 0;
            for (int i = 0; i < entryCount; i++) {
                if (strcmp(entries[i].name, name) == 0) {
                    entries[i].wins += wins;
                    found = 1;
                    break;
                }
            }

            if (!found && entryCount < DATA) {
                strncpy(entries[entryCount].name, name, NAME);
                entries[entryCount].wins = wins;
                entryCount++;
            }
        }
    }
    fclose(fp);

    // sort by wins (descending)
    qsort(entries, entryCount, sizeof(struct LeaderboardEntry), cmpLeaderboard);

    // print leaderboard
    printf("___________________________________________\n\n");
    printf("\tPhase 9 Leaderboard\n");
    printf("___________________________________________\n\n");
    printf("%-20s %-4s\n","Player", "Wins");
    printf("%-20s %-4s\n\n","______", "____");

    for (int i = 0; i < entryCount; i++) {
        printf("%-20s %-4d\n", entries[i].name, entries[i].wins);
    }
}

int playerOption(char player[NAME])
{
    int choice = ZERO;
    int valid = FALSE;

    // continue looping until player selects a valid option
    while(!valid)
    {
        printf("%s, select an option:\n", player);
        printf("1. Pick up discard\n");
        printf("2. Draw from deck\n");

        while (scanf("%d", &choice) != 1) {
            printf("Invalid input, try again: ");
            while (getchar() != '\n'); // clear buffer
        }

        // data validation
        if(choice != DISCARD && choice != DRAW)
        {
            valid = FALSE;
        }
        else
        {
            valid = TRUE;
        }
    }

    return choice;
}

// deal one card from the deck
int draw(int deck[DECK], int *deckIdx)
{
    // deal one card from the deck
    // dereference the pointer parameter
    int card = deck[*deckIdx];

    // dereference the pointer and increase the index
    // must use parenthesis around dereferencing
    (*deckIdx)++;

    return card;
}

int discardCard(char player[NAME], int playerHand[HAND], int pickUp)
{
    int valid = FALSE;
    int choice = ZERO;

    // display the current hand with numbers to select the card to discard
    displayPlayerHand(player, playerHand);
    printf(" (%2d)   (%2d)   (%2d)   (%2d)   (%2d)   (%2d)   (%2d)   (%2d)   (%2d)   (%2d)   \n",
           ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN);

    // display the new card (discard pile or deck)
    displaySingle(pickUp);
    printf(" (%2d)  \n", ELEVEN);

    // Karin ~ add data validation for Assignment 5

    // continue looping until player selects a valid option
    while(!valid)
    {
        printf("Select which card to discard (1 - 11)\n");

        while (scanf("%d", &choice) != 1) {
            printf("Invalid input, try again: ");
            while (getchar() != '\n'); // clear buffer
        }

        // data validation
        if (choice == ELEVEN) {
            valid = TRUE; // discarding new card
        }
        else if (choice >= ONE && choice <= TEN) {
            valid = TRUE; // discarding from hand
        } 
        else {
            printf("Invalid choice!\n");
        }
    }

    return choice;
}

// Updates the player's hand with the drawn card
// Updates the discard pile with the player's discard
// If the player enters card 11, that is the drawn card and no update is required
void updateHand(char player[NAME], int playerHand[HAND], int discardIdx, int *discard, int newCard)
{
    // if the player is discarding the new card
    // just update the discard pile and leave
    if(discardIdx == ELEVEN)
    {
        printf("%s selected the drawn card to discard, hand does not change\n", player);
        return;
    }
    else
    {
        // get the card the player is discarding
        // discardIdx is used as the index, need to subtract 1 to access the array
        int card = playerHand[(discardIdx - ONE)];

        // update the player's hand with the new card
        // need to subtract 1 from the value, player entered 1 - 11,
        // index for the array is 0 - 10
        playerHand[(discardIdx - ONE)] = newCard;

        // display the player's hand after the new card is swapped for the discard
//        displayPlayerHand(player, playerHand);

        // resort the player's hand
        qsort(playerHand, HAND, sizeof(playerHand[ZERO]), comp);

        // update the discard with the one the player is discarding
        *discard = card;

        // redisplay the updated player's hand
        displayPlayerHand(player, playerHand);

        // redisplay the discard pile
        printf("\nDiscarded card\n\n");
        displaySingle(*discard);

//system("pause");
    }
}

// trims leading and trailing white space
char *trim(char *str)
{
    // check if the string is empty
    if (str == NULL || *str == '\0')
    {
        return str;
    }

    // trim leading white space
    char *start = str;

    while (isspace((unsigned char)*start))
    {
        start++;
    }

    // trim trailing white space
    char *end = str + strlen(str) - 1;

    while (end > start && isspace((unsigned char)*end))
    {
        end--;
    }

    // add the null terminator
    end[1] = '\0';

    // return the updated string
    return start;
}

// Function checks if the player has completed the current phase (Phases 1 - 9)
int checkPhase(struct Player player)
{
    // Check the player's hand against the required phase combination
    int sets = ZERO;
    int setsTwo = ZERO;
    int runs = ZERO;

    switch (player.currentPhase)
    {
        // Phase 1: 2 sets of 3
        case ONE:
            sets = countSets(player.playerHand, HAND, THREE);
            return sets >= 2;
        // Phase 2: 1 set of 3 + 1 run of 4
        case TWO:
            sets = countSets(player.playerHand, HAND, THREE);
            runs = countRuns(player.playerHand, HAND, FOUR);
            return sets >= 1 && runs >= 1;
        // Phase 3: 1 set of 4 + 1 run of 4
        case THREE:
            sets = countSets(player.playerHand, HAND, FOUR);
            runs = countRuns(player.playerHand, HAND, FOUR);
            return sets >= 1 && runs >= 1;
        // Phase 4: 1 run of 7
        case FOUR:
            runs = countRuns(player.playerHand, HAND, SEVEN);
            return runs >= 1;
        // Phase 5: 1 run of 8
        case FIVE:
            runs = countRuns(player.playerHand, HAND, EIGHT);
            return runs >= 1;
        // Phase 6: 1 run of 9
        case SIX:
            runs = countRuns(player.playerHand, HAND, NINE);
            return runs >= 1;
        // Phase 7: 2 sets of 4
        case SEVEN:
            sets = countSets(player.playerHand, HAND, FOUR);
            return sets >= 2;
        // Phase 8: 1 set of 5 + 1 set of 2
        case EIGHT:
            sets = countSets(player.playerHand, HAND, FIVE);
            setsTwo = countSets(player.playerHand, HAND, TWO);
            return sets >= ONE && setsTwo >= ONE;
        // Phase 9: 1 set of 5 + 1 set of 3
        case NINE:
            sets = countSets(player.playerHand, HAND, FIVE);
            setsTwo = countSets(player.playerHand, HAND, THREE);
            return sets >= 1 && setsTwo >= ONE;
        // default for no match
        default:
            return ZERO;
    }
}

// Function to count how many sets of 'setSize' cards of the same value are in the player's hand
int countSets(int playerHand[HAND], int size, int setSize)
{
    // Still need to add logic for wild card
    int counts[THIRTEEN] = {ZERO}; // Track counts for card values 1 to 12
    int wildCount = ZERO;
    int setCount = ZERO;

    // Count occurrences of card values (ignoring wild and skip cards)
    for (int i = ZERO; i < size; i++)
    {
        if (playerHand[i] >= ONE && playerHand[i] <= TWELVE)
        {
            counts[playerHand[i] - ONE]++;
        }
        else if (playerHand[i] == WILD)
        {
            wildCount++;
        }
        
    }

    // Count sets
    for (int i = ZERO; i < THIRTEEN; i++)
    {
        if (counts[i] + wildCount >= setSize)
        {
            setCount++;
            if (counts[i] < setSize)
            {
                wildCount -= (setSize - counts[i]);
            }
        }
    }

    return setCount;
}

// Function to count how many runs of 'runSize' cards are in the player's hand
int countRuns(int playerHand[HAND], int size, int runSize)
{
    int counts[THIRTEEN] = {ZERO};  // For cards 1-12
    int wildCount = 0;
    int maxRun = 0;

    for (int i = 0; i < size; i++)
    {
        if (playerHand[i] >= ONE && playerHand[i] <= TWELVE)
        {
           counts[playerHand[i] - ONE]++;
        }
        else if (playerHand[i] == WILD)
        {
            wildCount++;
        }
    }   


    for (int start = 0; start <= 11; start++)
    {
        int runLength = 0;
        int availableWilds = wildCount;

        for (int card = start; card <= 11; card++)
        {
            if (counts[card] > 0)
            {
                runLength++;
            }
            else if (availableWilds > 0)
            {
                availableWilds--;
                runLength++;
            }
            else
            {
                break;
            }

        
            if (runLength > maxRun)
            {
                maxRun = runLength;
            }
        }
    }


    if (maxRun >= runSize)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

void updatePhase(struct Player *player)
{
    if (player->currentPhase < TEN)
    {
        // Move to the next phase
        player->currentPhase++;
    }
}

void displayPhase(int currentPhase)
{
    printf("\nCurrent phase: ");
    switch(currentPhase)
    {
        case ONE:
            printf("2 sets of 3\n");
            break;
        case TWO:
            printf("1 set of 3 + 1 run of 4\n");
            break;
        case THREE:
            printf("1 set of 4 + 1 run of 4\n");
            break;
        case FOUR:
            printf("1 run of 7\n");
            break;
        case FIVE:
            printf("1 run of 8\n");
            break;
        case SIX:
            printf("1 run of 9\n");
            break;
        case SEVEN:
            printf("2 sets of 4\n");
            break;
        case EIGHT:
            printf("1 set of 5 + 1 set of 2\n");
            break;
        case NINE:
            printf("1 set of 5 + 1 set of 3\n");
            break;
        default:
            printf("Incorrect phase number received\n");
            break;
    }
}

int isGameOverMulti(struct Player players[], int numPlayers)
{
    for (int i = 0; i < numPlayers; i++) {
        if (players[i].currentPhase > 9) {
            return TRUE;
        }
    }
    return FALSE;
}