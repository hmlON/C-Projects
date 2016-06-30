#ifndef POKER_
#define POKER_

struct card{
    int suit;
    int rank;
};

typedef struct card Card;

void dealCards(Card* hand);

void printHand(Card* hand);

int search(Card hand[],int n);

int isStraight(Card hand[], int *type);

int isStraightFlush(Card hand[]);

int isRoyal(Card hand[]);

int isFour(Card hand[], int *type);

int isThree(Card hand[], int *type);

int isFull(Card hand[],int *type);

int isPair(Card hand[],int *type);

int isTwoPairs(Card hand[], int *type, int *secondType);

int findHighDouble(Card hand[],int *type, int *secondType, int *highCard);

int findHighSimple(Card hand[],int *type, int *highCard);

int findHigh(Card hand[], int *highCard);

int isFlush(Card hand[],int *highCard);

int getPoints(Card hand[], int *type, int *highCard,int *secondType);

int findWinner(Card hand1[], Card hand2[]);

int changeDealerCards(Card* hand);

#endif // POKER_
