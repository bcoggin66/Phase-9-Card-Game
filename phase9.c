// include stdio library header file
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "phase9.h"

// These are used to declare the following macros
//#define ZERO 0
//#define ONE 1
//#define TWO 2
//#define FOURTEEN 14
//#define NAME 20
//#define PLAY 1
//#define LEAD 2
//#define EXIT 3
//#define FALSE 0
//#define TRUE 1
//#define HAND 10
//#define DECK 108
//#define FOUR 4
//#define EIGHT 8
//#define TWELVE 12
//#define WILD 13
//#define SKIP 14
//#define LINE 100
//#define FIELDS 3
//#define DATA 45
//#define DISCARD 1
//#define DRAW 2
//#define THREE 3
//#define FIVE 5
//#define SIX 6
//#define SEVEN 7
//#define NINE 9
//#define TEN 10
//#define ELEVEN 11
//#define THIRTEEN 13


//struct Player
//{
//    int playerNum;
//    char playerName[NAME];
//    int playerHand[HAND];
//    int currentPhase;
//    int wins;
//};

// function prototypes for the assignment
//void welcomeScreen();
//void displayHand();
//void displayDiscard();
//void playGame();
//int displayMenu();
//void displayLeaderboard();
//void randomHand(char player[NAME]);
//int drawCard();
//void randomDiscard();
//void initializeDeck(int deck[DECK]);
//void shuffleDeck(int deck[DECK]);
//void displayDeck(int deck[DECK]);
//void dealHand(int deck[DECK], int *deckIdx, int playerHand[HAND]);
//void displayPlayerHand(char player[NAME], int playerHand[HAND]);
//int dealDiscard(int deck[DECK], int *deckIdx);
//void displaySingle(int discard);
//int comp(const void *a, const void *b);
//void readLeaderboardFile();
//int playerOption(char player[NAME]);
//int draw(int deck[DECK], int *deckIdx);
//int discardCard(char player[NAME], int playerHand[HAND], int pickUp);
//void updateHand(char player[NAME], int playerHand[HAND], int playerDiscard, int *discard, int newCard);
//char *trim(char *str);
//int checkPhase(struct Player player);
//int countRuns(int playerHand[HAND], int size, int runSize);
//int countSets(int playerHand[HAND], int size, int setSize);
//void updatePhase(struct Player *player);
//void displayPhase(int currentPhase);
//int isGameOver(struct Player playerOne, struct Player playerTwo);

// main function
int main()
{
    // call function welcomeScreen
    welcomeScreen();

    // random seed function
    srand ((unsigned int) time (NULL));

    // call function playGame
    playGame();

    // call function displayHand
//    displayHand();

    // call function displayDiscard
//    displayDiscard();

    // program executed successfully
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
    // local variables
    struct Player playerOne;
//    char one[NAME]; // arrays are inherently pointers to index 0 of the array
//    int oneHand[HAND];

    struct Player playerTwo;
//    char two[NAME];
//    int twoHand[HAND];

    int currentPlayer = ONE;
    int choice = ZERO;
    // int turn = ZERO;

    // the playing deck
    int deck[DECK];
    int deckIdx = ZERO;

    int discardOrDraw = ZERO;
    int pickUp = ZERO;
    int playerDiscard = ZERO;

    // store player's choice in local variable
    // priming read for menu selection
    choice = displayMenu();

    while(choice != EXIT)
    {
        if(choice == PLAY)
        {
            // these are printf and scanf statements to prompt players name nested in the if statement
            printf("Player One, enter your name\n");
//            scanf("%s", one);
            scanf("%s", playerOne.playerName);
            // set the player one struct members
            playerOne.playerNum = ONE;
            playerOne.currentPhase = ONE;
            playerOne.wins = ZERO;

            printf("Player Two, enter your name\n");
//            scanf("%s", two);
            scanf("%s", playerTwo.playerName);
            // set the player two struct members
            playerTwo.playerNum = TWO;
            playerTwo.currentPhase = ONE;
            playerTwo.wins = ZERO;

//            printf("\n%s and %s let's play Phase 9!\n\n", one, two);
            printf("\n%s and %s let's play Phase 9!\n\n", playerOne.playerName, playerTwo.playerName);

            // initialize the deck
            initializeDeck(deck);
            // display the unshuffled deck
//            displayDeck(deck);

            // shuffle the deck
            shuffleDeck(deck);
            // display the shuffled deck
//            displayDeck(deck);

            // deal player one's hand
//            dealHand(deck, &deckIdx, oneHand);
            dealHand(deck, &deckIdx, playerOne.playerHand);

            // sort player one's hand
//            qsort(oneHand, HAND, sizeof(oneHand[ZERO]), comp);
            qsort(playerOne.playerHand, HAND, sizeof(playerOne.playerHand[ZERO]), comp);

            // deal player two's hand
//            dealHand(deck, &deckIdx, twoHand);
            dealHand(deck, &deckIdx, playerTwo.playerHand);

            // sort player two's hand
//            qsort(twoHand, HAND, sizeof(twoHand[ZERO]), comp);
            qsort(playerTwo.playerHand, HAND, sizeof(playerTwo.playerHand[ZERO]), comp);

            // deal the first discard
            int discard = dealDiscard(deck, &deckIdx);

            // two turns per player
            while(!isGameOver(playerOne, playerTwo))
            {
//                if(currentPlayer == ONE)
                if(currentPlayer == playerOne.playerNum)
                {
//                    displayPlayerHand(one, oneHand);
                    displayPhase(playerOne.currentPhase);
                    displayPlayerHand(playerOne.playerName, playerOne.playerHand);
                    while (discard == SKIP)
                    {
                        printf("\nDiscard pile is a SKIP! Drawing a new discard...\n");
                        discard = dealDiscard(deck, &deckIdx);
                    }
                    printf("\nDiscard pile\n\n");
                    displaySingle(discard);

                    // pick up discard or card from pile?
//                    discardOrDraw = playerOption(one);
                    discardOrDraw = playerOption(playerOne.playerName);

                    if(discardOrDraw == DISCARD)
                    {
//                        printf("%s chose to pick up the discard\n", one);
                        printf("%s chose to pick up the discard\n", playerOne.playerName);
                        pickUp = discard;
                        printf("\nNew card\n");
                        displaySingle(pickUp);
                    }
                    else if(discardOrDraw == DRAW)
                    {
//                        printf("%s chose to draw from the deck\n", one);
                        printf("%s chose to draw from the deck\n", playerOne.playerName);
                        pickUp = draw(deck, &deckIdx);
                        printf("\nNew card\n");
                        displaySingle(pickUp);
                    }

                    if (pickUp == SKIP)
                    {
                        printf("\nSkip card drawn! %s skips %s's turn!\n", playerOne.playerName, playerTwo.playerName);
                        if (currentPlayer == playerOne.playerNum)
                        {
                            currentPlayer = playerOne.playerNum;
                        }
                        else
                        {   
                            currentPlayer = playerTwo.playerNum;
                        }

                        continue;
                    }

                    // get the player's discard
//                    playerDiscard = discardCard(one, oneHand, pickUp);
                    playerDiscard = discardCard(playerOne.playerName, playerOne.playerHand, pickUp);

                    // update player's hand and discard pile
//                    updateHand(one, oneHand, playerDiscard, &discard, pickUp);
                    updateHand(playerOne.playerName, playerOne.playerHand, playerDiscard, &discard, pickUp);
                    if (discard == SKIP)
                    {
                        printf("\n%s discarded a SKIP! %s loses a turn!\n", playerOne.playerName, playerTwo.playerName);
                        currentPlayer = playerOne.playerNum;
                        continue;
                    }

                    if (checkPhase(playerOne))
                    {
                        printf("Player %s completed their phase!\n", playerOne.playerName);

                        // Move to the next phase
                        updatePhase(&playerOne);
                    }
                    else
                    {
                        printf("Player %s did not complete their phase.\n", playerOne.playerName);
                    }

                    // switch players
//                    currentPlayer = TWO;
                    currentPlayer = playerTwo.playerNum;
                }
//                else if(currentPlayer == TWO)
                else if(currentPlayer == playerTwo.playerNum)
                {
//                    displayPlayerHand(two, twoHand);
                    displayPhase(playerTwo.currentPhase);
                    displayPlayerHand(playerTwo.playerName, playerTwo.playerHand);
                    while (discard == SKIP)
                    {
                        printf("\nDiscard pile is a SKIP! Drawing a new discard...\n");
                        discard = dealDiscard(deck, &deckIdx);
                    }
                    printf("\nDiscard pile\n\n");
                    displaySingle(discard);

                    // pick up discard or card from pile?
//                    discardOrDraw = playerOption(two);
                    discardOrDraw = playerOption(playerTwo.playerName);

                    if(discardOrDraw == DISCARD)
                    {
//                        printf("%s chose to pick up the discard\n", two);
                        printf("%s chose to pick up the discard\n", playerTwo.playerName);
                        pickUp = discard;
                        printf("\nNew card\n");
                        displaySingle(pickUp);
                    }
                    else if(discardOrDraw == DRAW)
                    {
//                        printf("%s chose to draw from the deck\n", two);
                        printf("%s chose to draw from the deck\n", playerTwo.playerName);
                        pickUp = draw(deck, &deckIdx);
                        printf("\nNew card\n");
                        displaySingle(pickUp);
                    }
                    
                    if (pickUp == SKIP)
                    {
                        printf("\nSkip card drawn! %s skips %s's turn!\n", playerOne.playerName, playerTwo.playerName);
                        if (currentPlayer == playerOne.playerNum)
                        {
                            currentPlayer = playerOne.playerNum;
                        }
                        else
                        {   
                            currentPlayer = playerTwo.playerNum;
                        }

                        continue;
                    }
                    

                    // get the player's discard
//                    playerDiscard = discardCard(two, twoHand, pickUp);
                    playerDiscard = discardCard(playerTwo.playerName, playerTwo.playerHand, pickUp);

                    // update player's hand and discard pile
//                    updateHand(two, twoHand, playerDiscard, &discard, pickUp);
                    updateHand(playerTwo.playerName, playerTwo.playerHand, playerDiscard, &discard, pickUp);
                    if (discard == SKIP)
                    {
                        printf("\n%s discarded a SKIP! %s loses a turn!\n", playerTwo.playerName, playerOne.playerName);
                        currentPlayer = playerTwo.playerNum;
                        continue;
                    }

                    // Check if player can complete their phase
                    if (checkPhase(playerTwo))
                    {
                        printf("Player %s completed their phase!\n", playerTwo.playerName);
                        // Move to the next phase
                        updatePhase(&playerTwo);
                    }
                    else
                    {
                        printf("Player %s did not complete their phase.\n", playerTwo.playerName);
                    }

                    // switch players
//                    currentPlayer = ONE;
                    currentPlayer = playerOne.playerNum;
                }

                //turn++;
            }
        }
        
        //print statement for game ending
        printf("\nThe game is over!\n");

        // if statement for player one if they won the game
        if (playerOne.currentPhase > 9)
        {
            printf("%s has completed Phase 9!\n", playerOne.playerName);
            playerOne.wins++;
        }

        // if statement for player two if they won the game
        if (playerTwo.currentPhase > 9)
        {
            printf("%s has completed Phase 9!\n", playerTwo.playerName);
            playerTwo.wins++;
        }

        else if(choice == LEAD)
        {
//            displayLeaderboard();
            readLeaderboardFile();
        }
        else
        {
            printf("\nThank you for playing Phase 9!\n");
            exit(ZERO);
        }

        // redisplay the menu for option 1 and 2
        choice = displayMenu();
        deckIdx = ZERO;
        // turn = ZERO;
    }
    
}

// Assignment 1, no longer used
// function displayHand displays a hardcoded version of a player's cards
//void displayHand()
//{
//    printf("\nPlayer's hand\n\n");
//    printf("+-----------------------------------------------------------+\n");
//    printf("|     |     |     |     |     |     |     |     |     |     |\n");
//    printf("|  2  |  2  |  4  |  4  |  5  |  7  |  8  |  8  |  9  |  9  |\n");
//    printf("|     |     |     |     |     |     |     |     |     |     |\n");
//    printf("+-----------------------------------------------------------+\n");
// }

// Assignment 1, no longer used
// function displayDiscard displays a hardcoded version of the discard pile
//void displayDiscard()
//{
//    printf("\nDiscard pile\n\n");
//    printf("+-----+\n");
//    printf("|     |\n");
//    printf("| 12  |\n");
//    printf("|     |\n");
//    printf("+-----+\n");
//}

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

        scanf("%d", &choice);

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

// Assignment 4 no longer used
//void displayLeaderboard()
//{
//    printf("___________________________________________\n\n");
//    printf("\tPhase 9 Leaderboard\n");
//    printf("___________________________________________\n\n");
//
//    printf("%-15s %-20s %-4s\n","Position", "Player", "Wins");
//    printf("%-15s %-20s %-4s\n\n","________", "______", "____");
//    printf("%-15d %-20s %-4d\n",1, "Blaze", 39);
//    printf("%-15d %-20s %-4d\n",2, "Smoke", 33);
//    printf("%-15d %-20s %-4d\n",3, "Karin", 30);
//    printf("%-15d %-20s %-4d\n",4, "Samuel", 29);
//    printf("%-15d %-20s %-4d\n",5, "Keystone", 26);
//    printf("%-15d %-20s %-4d\n",6, "Natty", 20);
//    printf("%-15d %-20s %-4d\n",7, "Storm", 9);
//}

// Assignment 2, no longer used
// function randomHand displays a random version of a player's cards
//void randomHand(char player[NAME])
//{
//    int cOne = drawCard();
//    int cTwo = drawCard();
//    int cThree = drawCard();
//    int cFour = drawCard();
//    int cFive = drawCard();
//    int cSix = drawCard();
//    int cSeven = drawCard();
//    int cEight = drawCard();
//    int cNine = drawCard();
//    int cTen = drawCard();
//
//    printf("\n%s's hand\n\n", player);
//    printf("+---------------------------------------------------------------------+\n");
//    printf("|      |      |      |      |      |      |      |      |      |      |\n");
//    printf("| %3d  | %3d  | %3d  | %3d  | %3d  | %3d  | %3d  | %3d  | %3d  | %3d  |\n",
//           cOne, cTwo, cThree, cFour, cFive, cSix, cSeven, cEight, cNine, cTen);
//    printf("|      |      |      |      |      |      |      |      |      |      |\n");
//    printf("+---------------------------------------------------------------------+\n");
//}

// randomly draws one card from 1 - 14
//int drawCard()
//{
//    // declare and initialize the random card value
//    int cardValue = rand() % FOURTEEN + ONE;
//
//    // return the value
//    return cardValue;
//}

// Assignment 2, no longer used
// function displayDiscard displays a hardcoded version of the discard pile
//void randomDiscard()
//{
//    int discard = drawCard();
//
//    printf("\nDiscard pile\n\n");
//    printf("+------+\n");
//    printf("|      |\n");
//    printf("| %3d  |\n", discard);
//    printf("|      |\n");
//    printf("+------+\n");
//}

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

// display the deck of cards
//void displayDeck(int deck[DECK])
//{
//    printf("Phase 9 deck of cards:\n");
//
//    // iterate through the deck of cards and display its value
//    for(int c = ZERO; c < DECK; c++)
//    {
//        printf("%d ", deck[c]);
//    }
//
//    printf("\n\n");
//}

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

// reads the data in file leaderboard.txt one line at a time
// use strtok() function and delimiter ',' to parse the 3 fields of each line
// copy the parsed data elements into array data
void readLeaderboardFile()
{
    char line[LINE];
    int fieldIdx = ZERO;

    // an array of 45 strings, 15 records with 3 data elements per record (15 * 3)
    char *data[DATA];

    // open file for read only
    FILE *fp = fopen("leaderboard.txt", "r");

    // display the header
    printf("___________________________________________\n\n");
    printf("\tPhase 9 Leaderboard\n");
    printf("___________________________________________\n\n");

    printf("%-15s %-20s %-4s\n","Position", "Player", "Wins");
    printf("%-15s %-20s %-4s\n\n","________", "______", "____");

    // verify the file pointer is not NULL
    if (fp == NULL)
    {
        perror("Error opening file\n");
        return;
    }

    // reads the data in the file one line at a time
    // until it reaches EOF indicated by a NULL
    while (fgets(line, LINE, fp) != NULL)
    {
        // first data element read
        char *field = strtok(line, ",");

        // trim the white space
        field = trim(field);

        // loop until all data elements in the line are parsed
        while (field != NULL)
        {
            // Allocate memory for the string
            data[fieldIdx] = malloc(strlen(field) + 1);

            // Copy variable field into data array at index fieldIdx
            strcpy(data[fieldIdx], field);

            // Subsequent strtok requires passing NULL in place of variable line
            field = strtok(NULL, ",");

            // trim leading and trailing white space
            field = trim(field);

            // increment the index for array data
            fieldIdx++;
        } // end inner while to parse data line
    } // end outer while loop to read data line

    // close the file
    fclose(fp);

    // display the data to the console
    // increment the loop control variable by 3 for each iteration
    for (int i = 0; i < DATA; i+=FIELDS)
    {
        printf("%-15s %-20s %-4s\n", data[i], data[i+1], data[i+2]);
    }

//    // deallocate the memory in array data
//    for (int i = 0; i < DATA; i++)
//    {
//        free(data[i]);
//    }
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

        scanf("%d", &choice);

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

        scanf("%d", &choice);

        // data validation
        if(choice >= ONE && choice <= ELEVEN)
        {
            valid = TRUE;
        }
        else
        {
            valid = FALSE;
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

int isGameOver(struct Player playerOne, struct Player playerTwo)
{
    int gameOver = 0; // FALSE

    if (playerOne.currentPhase > 9 || playerTwo.currentPhase > 9)
    {
        gameOver = 1; // TRUE
    }
    else
    {
        gameOver = 0; // FALSE
    }

    return gameOver;
}