// ------------------------------------ 7 CARD POKER PROBABILITY TABLE ------------------------------------------------------------
// keep in mind at last the total sum of probabilities should be 1 and every probability may vary from specified value but will be close enough
// Set the MACRO values accordingly.
 
// Program Creates a text File which contains all the Probability Data, be sure to check it.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
//defining MACROS
#define CARDS 52                //no. of cards
#define NO_OF_PLAYERS 1         //no. of players
#define CARD_IN_HAND 7          //no. of cards in a hand
#define HAND_RANKS 10           // Maximum possible hand ranking count
#define SHUFFLE_COUNT 300       // Number of times Shuffling of deck occurs
#define NO_OF_ITERATIONS 133784560 // 100,000,000 takes around an hour ,133784560.0 (can be set, takes more than an hour), No. of generated hands
#define MAX_SUIT 4              //No. of Suits
#define MAX_RANK 13             // Maximum Rank
 
// Enumerating pip values ie the Rank of a card, Starts with ace = 1, ends with king = 13.
typedef enum pips
{
    ace = 1,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king
} pips;
 
// Enumerating Suits starting from Hearts =1
typedef enum suits
{
    hearts = 1,
    diamonds,
    spade,
    clubs
} suits;
 
// Enumerating HandRanking starting from Royal Flush=1
typedef enum handRanks
{
    royalFlush = 1,
    straightFlush,
    fourOfaKind,
    fullHouse,
    flush,
    straight,
    threeOfaKind,
    twoPair,
    pair,
    highCard
} handRanks;
 
//Defining Structure card, consists of pips rank and suits suit
typedef struct card
{
    pips rank;
    suits suit;
} card;
 
// deckMaker - makes deck ie creates 52 card structures
void deckMaker(card deck[])
{
    // First suitValue is initiated
    int suitValue = 0;
 
    // for loop to set all cards(done without two for loops)
    for (int i = 0; i < CARDS; i++)
    {
        //
        if (i % 13 == 0)
        {
            suitValue++;
        }
        //deck rank & suit initiatialization
        //for every 13 card i will become 1
        deck[i].rank = i % 13 + 1;
 
        //for every 13 card value is incremented by 1 till max 4 is reacghed, ie number of suits
        deck[i].suit = i / 13 + 1;
    }
}
 
void viewDeck(card deck[])
{
    for (int i = 0; i < CARDS; i++)
    {
 
        printf("\nCard:%d\nRank : %d\n Suit : %d\n", i + 1, deck[i].rank, deck[i].suit);
    }
    return;
}
 
// shuffler - shuffles all the card structures
void shuffler(card deck[])
{
    card temp;
    int j, k;
 
    //time variable
    time_t seed;
 
    // setting seed for complete randomness
    srand((unsigned)time(&seed));
 
    // for loop - shuffles
    for (int i = 0; i < SHUFFLE_COUNT; i++)
    {
        // initializing random values (lesser Than CARDS)
        j = rand() % CARDS;
        k = rand() % CARDS;
 
        // swapping occurs only when j != k
        if (j != k)
        {
            // swap(deck[j],deck[k]);
            temp = deck[j];
            deck[j] = deck[k];
            deck[k] = temp;
        }
    }
    return;
}
 
// dealCards - deals cards to PLAYERS
void dealCards(card deck[], card player[][CARD_IN_HAND])
{
    // deals all cards
    for (int i = 0; i < CARD_IN_HAND; i++)
    {
        // Distribution takes place player-wise
        for (int j = 0; j < NO_OF_PLAYERS; j++)
 
            player[j][i] = deck[i];
    }
    return;
}
 
void viewHand(card player[][CARD_IN_HAND])
{
    for (int i = 0; i < NO_OF_PLAYERS; i++)
    {
 
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - -");
 
        for (int j = 0; j < CARD_IN_HAND; j++)
        {
            printf("\nPlayer %d Card: %d %d\n", i + 1, player[i][j].rank, player[i][j].suit);
        }
    }
}
 
// Calculates Repeated Ranks and stores them in an array
int rankRepeatCheck(card playerHand[])
{
    // MAX_RANK +1 because Rank Value starts from Ace which is 1, Array items are all initialized to zero
    int rankCount[MAX_RANK + 1] = {
        0,
    },
                             max = 0;
 
    // checks all ranks and calculates how many times a rank is seen throughout the hand of the player
    for (int i = 0; i < CARD_IN_HAND; i++)
    {
        rankCount[playerHand[i].rank]++;
    }
 
    // Finds for maximum value in rankCount
    for (int i = 0; i < 14; i++)
    {
        if (rankCount[i] > max)
        {
            max = rankCount[i];
        }
    }
 
    //returns highest rankCount
    return max;
}
 
// cardCheck - looks for a particular card in the hand
int cardCheck(card playerHand[], pips rankValue, int suitValue)
{
    // Browses through Hand looking for card
    for (int i = 0; i < CARD_IN_HAND; i++)
    {
        // rank checking
        if (playerHand[i].rank == rankValue)
        {
            // if suitValue is given then card suit is also checked (used only in flush cases)
            if (suitValue > 0 && suitValue != (int)playerHand[i].suit)
            {
                // returns zero if card suit is not asked suit
                return 0;
            }
            // if all conditions satisfy
            return 1;
        }
    }
    return 0;
}
// straightCheck - checks for straight in the hand also checks for straightFlush when suitValue is set above zero
int straightCheck(card playerHand[], int suitValue)
{
    // count = 1 as the first card in straight is always counted
    int count = 1;
    // for loop - first loop sets a card
    for (int i = 0; i < CARD_IN_HAND; i++)
    {
        // second loop looks for the consecutive cards and increments count
        for (int j = 1; j < 5; j++)
        {
            // Calls cardCheck to find for the next consecutive card in straight
            // ace,2,3,4,5 straightCheck
            if (cardCheck(playerHand, ace, suitValue) == 1 && cardCheck(playerHand, two, suitValue) == 1 && cardCheck(playerHand, three, suitValue) == 1 && cardCheck(playerHand, four, suitValue) == 1 && cardCheck(playerHand, five, suitValue) == 1)
            {
                return 1;
            }
            else if (cardCheck(playerHand, playerHand[i].rank + j, suitValue) == 1)
            {
                count++;
            }
        }
        // if straight is present in hand then count is 5
        if (count == 5)
        {
            return 1;
        }
        else
        {
            // if not 5 count is reset
            count = 1;
        }
    }
    // when no straight
    return 0;
}
 
// checks for the presence of flush ie 5 or more cards in hand, returns type of suit which makes the flush
int flushCheck(card playerHand[])
{
    // suitCount is array which keeps counts of all suits, all items are initialized to 0;
    int suitCount[5] = {
        0,
    },
        suitValue;
 
    // counts all suit values in hand and stores in suitCount array
    for (int j = 0; j < CARD_IN_HAND; j++)
    {
        suitValue = playerHand[j].suit;
        suitCount[suitValue]++;
    }
 
    // Checks if value greater than 4 is in the array
    for (int j = 1; j <= MAX_SUIT; j++)
    {
        if (suitCount[j] >= 5)
        {
 
            return j;
        }
    }
    // if no flush
    return 0;
}
 
//  checks for the guven number of pairs, minPair variable looks for given number of different pairs
int pairCheck(card playerHand[], int minPair)
{
    //  pairCount set to zero
    // below is same as rankCount function till ..
    int pairCount = 0;
    int rankCount[14] = {
        0,
    };
 
    for (int i = 0; i < CARD_IN_HAND; i++)
    {
        rankCount[playerHand[i].rank]++;
    }
    // ...here
    // checks for counts that are = 2 and pairCount is incremeneted
    for (int i = 0; i <= 13; i++)
    {
        if (rankCount[i] == 2)
        {
            pairCount++;
        }
    }
    // if pairCount is greater than minPair(asked number of pairs) then function returns true
    if (pairCount >= minPair)
    {
        return 1;
    }
    return 0;
}
 
// checks for hand rankings in player hand
void handRankChecker(card player[][CARD_IN_HAND], int handRank[])
{
    card playerHand[CARD_IN_HAND];
    int suitValue = 0;
 
    // For every player
    for (int i = 0; i < NO_OF_PLAYERS; i++)
    {
        //for every hand of a player
        for (int j = 0; j < CARD_IN_HAND; j++)
        {
            // converts into 1D array for ease
            playerHand[j] = player[i][j];
        }
 
        //checks hand for flush
        suitValue = flushCheck(playerHand);
 
        // below hand ranking checking happens and accordingly handRanking type is incremented
        // royalFlush, straightFlush, flush is checked only if flushchcek returns suitValue-(suit type)
        if (suitValue > 0)
        {
            // royal flush check
            if (cardCheck(playerHand, ace, suitValue) == 1 && cardCheck(playerHand, king, suitValue) == 1 && cardCheck(playerHand, queen, suitValue) == 1 && cardCheck(playerHand, jack, suitValue) == 1 && cardCheck(playerHand, ten, suitValue) == 1)
            {
                handRank[royalFlush]++;
            }
            else if (straightCheck(playerHand, suitValue)) //straightFlush check
            {
                handRank[straightFlush]++;
            }
            else //flush check
            {
                handRank[flush]++;
            }
            break; //gets out of the loop once any of the flush is found
        }
        // suitValue is set to zero as its redundant now
        suitValue = 0;
 
        // rankCount is initialized
        int rankCount = rankRepeatCheck(playerHand);
 
        // fourOfaKind check
        if (rankCount == 4)
        {
            handRank[fourOfaKind]++;
        }
        else if (rankCount == 3 && pairCheck(playerHand, 1) == 1) //fullHouse Check
        {
            handRank[fullHouse]++;
        }
        else if (straightCheck(playerHand, suitValue) == 1) //straightCheck
        {
            handRank[straight]++;
        }
        else if (rankCount == 3) //checks for three of a kind
        {
            handRank[threeOfaKind]++;
        }
        else if (pairCheck(playerHand, 2) == 1) // two pair check
        {
            handRank[twoPair]++;
        }
        else if (rankCount == 2) // pair check
        {
            handRank[pair]++;
        }
        else // default high card
        {
            handRank[highCard]++;
        }
        break;
    }
    return;
}
 
// checks for handRank value and returns handRanking Name Accordingly as a string
char *handRankName(handRanks handRank)
{
    switch (handRank)
    {
    case royalFlush:
        return "Royal Flush    ";
        break;
    case straightFlush:
        return "Straight Flush ";
        break;
    case fourOfaKind:
        return "Four Of A Kind ";
        break;
    case fullHouse:
        return "Full House     ";
        break;
    case flush:
        return "Flush          ";
        break;
    case straight:
        return "Straight       ";
        break;
    case threeOfaKind:
        return "Three Of A Kind";
        break;
    case twoPair:
        return "Two Pair       ";
        break;
    case pair:
        return "One Pair       ";
        break;
    case highCard:
        return "High Card      ";
        break;
    default:
        return "\0";
    }
}
 
// Calculates probability of all combinations in handRAnkData Array and stores all necessary data in a file
void probabilityCalculator(int handRankData[], double probabilityData[])
{
    // FILE is opened
    FILE *fptr = fopen("ProbabilityData.txt", "w");
 
    // sum variables declared
    double sumOfProbability;
    int sumOfHandRanks;
 
    // Assigns all probability values to probabibiltyData, calculates all combinations sum, probabibilty sum and then writes it to a file.
    for (int i = 1; i <= 10; i++)
    {
        // probability is calculated and assigned
        probabilityData[i - 1] = handRankData[i] / NO_OF_ITERATIONS;
 
        //all probability sum is found
        sumOfProbability = sumOfProbability + probabilityData[i - 1];
 
        //all handRank sum is found
        sumOfHandRanks = sumOfHandRanks + handRankData[i - 1];
 
        // writes into a file (ProbabilityData.txt)
        fprintf(fptr, "\n%s\t%5.d\t%.10lf\n", handRankName(i), handRankData[i], probabilityData[i - 1]);
    }
    fprintf(fptr, "\n%s\t%5.d\t%.10lf\n", "Total          ", sumOfHandRanks, sumOfProbability);
    return;
}
 
// main
int main()
{
    // declaration of player, deck, handRankdata, probabilityData (all array items assigned 0)
    card deck[CARDS], player[NO_OF_PLAYERS][CARD_IN_HAND];
    // handRankData holds all handRanking Counts in randomly generated hands
    int handRankData[11] = {
        0,
    };
    // probabilityData holds all combination probability values
    double probabilityData[HAND_RANKS] = {
        0,
    };
 
    // call deckMaker
    deckMaker(deck);
 
    // random card generartion, calls shuffler, dealCards, handRankChecker
    for (int i = 0; i < NO_OF_ITERATIONS; i++)
    {
        shuffler(deck);
        dealCards(deck, player);
        handRankChecker(player, handRankData);
    }
 
    // Calculates probability of combinations
    probabilityCalculator(handRankData, probabilityData);
 
    //Execution Completed Message
    printf("\nDone!\nCHECK \"ProbabilityData.txt\" file in cwd\n");
 
    return 0;
}


// Output I Got: NO_OF_ITERATIONS - 100,000,000


// Royal Flush    	 4541	   0.0000454100

// Straight Flush 	34548	0.0003454800

// Four Of A Kind 	172252	0.0017225200

// Full House     	2560616	0.0256061600

// Flush          	2954916	0.0295491600

// Straight       	4194920	0.0419492000

// Three Of A Kind	4981350	0.0498135000

// Two Pair       	23174311	0.2317431100

// One Pair       	44242552	0.4424255200

// High Card      	17679994	0.1767999400

// Total          	82320010	1.0000000000



