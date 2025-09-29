#define ZERO 0
#define ONE 1
#define TWO 2
#define FOURTEEN 14
#define NAME 20
#define PLAY 1
#define LEAD 2
#define EXIT 3
#define FALSE 0
#define TRUE 1
#define HAND 10
#define DECK 108
#define FOUR 4
#define EIGHT 8
#define TWELVE 12
#define WILD 13
#define SKIP 14
#define LINE 100
#define FIELDS 3
#define DATA 45
#define DISCARD 1
#define DRAW 2
#define THREE 3
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define NINE 9
#define TEN 10
#define ELEVEN 11
#define THIRTEEN 13

struct Player
{
    int playerNum;
    char playerName[NAME];
    int playerHand[HAND];
    int currentPhase;
    int wins;
};

struct LeaderboardEntry
{
    char name[NAME];
    int wins;
};

// function prototypes for the assignment
void welcomeScreen();
void playGame();
int displayMenu();
void initializeDeck(int deck[DECK]);
void shuffleDeck(int deck[DECK]);
void dealHand(int deck[DECK], int *deckIdx, int playerHand[HAND]);
void displayPlayerHand(char player[NAME], int playerHand[HAND]);
int dealDiscard(int deck[DECK], int *deckIdx);
void displaySingle(int discard);
int comp(const void *a, const void *b);
void readLeaderboardFile();
int playerOption(char player[NAME]);
int draw(int deck[DECK], int *deckIdx);
int discardCard(char player[NAME], int playerHand[HAND], int pickUp);
void updateHand(char player[NAME], int playerHand[HAND], int playerDiscard, int *discard, int newCard);
char *trim(char *str);
int checkPhase(struct Player player);
int countRuns(int playerHand[HAND], int size, int runSize);
int countSets(int playerHand[HAND], int size, int setSize);
void updatePhase(struct Player *player);
void displayPhase(int currentPhase);
void writeLeaderboardFile(char playerName[NAME], int wins);
int isGameOverMulti(struct Player players[], int numPlayers);
