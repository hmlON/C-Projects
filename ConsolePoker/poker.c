#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "poker.h"

void dealCards(Card* hand){
	int i, j;
	for(i = 0; i < 5; i++)
	{
		int isEqual = 1;
		while (isEqual == 1){
			isEqual = 0;
			hand[i].rank = (rand() % 13) + 2;
			hand[i].suit = rand() % 4;
			for(j = 0; j < i; j++){
				if((hand[i].rank == hand[j].rank)&&(hand[i].suit == hand[j].suit))
					isEqual = 1;
			}
		}
		
	}
}

void printHand(Card* hand){
	int i;
	for(i = 0; i < 5; i++)
	{
		char rankChar; 
		if (hand[i].rank == 10){
			rankChar = 'T';
		} else if (hand[i].rank == 11){
			rankChar = 'J';
		} else if (hand[i].rank == 12){
			rankChar = 'Q';
		} else if (hand[i].rank == 13){
			rankChar = 'K';
		} else if (hand[i].rank == 14){
			rankChar = 'A';
		} else {
			rankChar = hand[i].rank + 48;
		}
		
		char suitChar;
		if (hand[i].suit == 0){
			suitChar = 'S';
		} else if (hand[i].suit == 1){
			suitChar = 'H';
		} else if (hand[i].suit == 2){
			suitChar = 'D';
		} else{
			suitChar = 'C';
		}
		
		printf("%c%c ", rankChar, suitChar);
	}
	printf("\n");
}

int search(Card hand[],int n){
    int i;

    for (i=0;i<5;i++){
        if (hand[i].rank==n)
            return 1;
    }

    return 0;
}

int isStraight(Card hand[], int *type){
    int i,min;

    min=20;

    for (i=0;i<5;i++)
        if (hand[i].rank<min)
            min=hand[i].rank;

    if (search(hand,min+1))
        if (search(hand,min+2))
            if (search(hand,min+3))
                if (search(hand,min+4)){
                    *type = min+4;
                    return 1;
                }

    return 0;

}

int isStraightFlush(Card hand[]){
    int suit = hand[0].suit;
    int i;

    for (i=1;i<5;i++)
        if (hand[i].suit!=suit)
            return 0;

    return 1;
}

int isRoyal(Card hand[]){
    if (search(hand,14))
        return 1;
    return 0;
}

int isFour(Card hand[], int *type){
    if (hand[0].rank==hand[1].rank&&hand[1].rank==hand[2].rank&&hand[2].rank==hand[3].rank){
        *type = hand[0].rank;
        return 1;
    }
    if (hand[0].rank==hand[1].rank&&hand[1].rank==hand[2].rank&&hand[2].rank==hand[4].rank){
        *type = hand[0].rank;
        return 1;
    }
    if (hand[0].rank==hand[1].rank&&hand[1].rank==hand[3].rank&&hand[3].rank==hand[4].rank){
        *type = hand[0].rank;
        return 1;
    }
    if (hand[0].rank==hand[2].rank&&hand[2].rank==hand[3].rank&&hand[3].rank==hand[4].rank){
        *type = hand[0].rank;
        return 1;
    }
    if (hand[1].rank==hand[2].rank&&hand[2].rank==hand[3].rank&&hand[3].rank==hand[4].rank){
        *type = hand[1].rank;
        return 1;
    }
    return 0;
}

int isThree(Card hand[], int *type){
    if (hand[0].rank==hand[1].rank&&hand[1].rank==hand[2].rank){
        *type=hand[0].rank;
        return 1;
    }
    if (hand[0].rank==hand[1].rank&&hand[1].rank==hand[3].rank){
        *type=hand[0].rank;
        return 1;
    }
    if (hand[0].rank==hand[1].rank&&hand[1].rank==hand[4].rank){
        *type=hand[0].rank;
        return 1;
    }
    if (hand[0].rank==hand[3].rank&&hand[3].rank==hand[4].rank){
        *type=hand[0].rank;
        return 1;
    }
    if (hand[0].rank==hand[2].rank&&hand[2].rank==hand[3].rank){
        *type=hand[0].rank;
        return 1;
    }
    if (hand[0].rank==hand[2].rank&&hand[2].rank==hand[4].rank){
        *type=hand[0].rank;
        return 1;
    }
    if (hand[2].rank==hand[3].rank&&hand[3].rank==hand[4].rank){
        *type=hand[2].rank;
        return 1;
    }
    if (hand[1].rank==hand[2].rank&&hand[2].rank==hand[3].rank){
        *type=hand[1].rank;
        return 1;
    }
    if (hand[1].rank==hand[2].rank&&hand[2].rank==hand[4].rank){
        *type=hand[1].rank;
        return 1;
    }
    if (hand[1].rank==hand[3].rank&&hand[3].rank==hand[4].rank){
        *type=hand[1].rank;
        return 1;
    }

    return 0;
}

int isFull(Card hand[],int *type){
    int second;
    int i=0;
    while (hand[i].rank==*type)
        i++;
    second = hand[i].rank;

    for (i=i+1;i<5;i++){
        if (hand[i].rank!=*type&&hand[i].rank!=second)
            return 0;
    }
    return 1;
}

int isPair(Card hand[],int *type){
    int i,j;

    for (i=0;i<4;i++)
        for (j=i+1;j<5;j++)
            if (hand[i].rank==hand[j].rank){
                *type=hand[i].rank;
                return 1;
            }

    return 0;
}

int isTwoPairs(Card hand[], int *type, int *secondType){
    int i,j;

    for (i=0;i<4;i++)
        for (j=i+1;j<5;j++)
            if (hand[i].rank==hand[j].rank&&hand[i].rank!=*type){
                if (hand[i].rank<*type){
                    *secondType=hand[i].rank;
                    return 1;
                }
                else{
                    *secondType=*type;
                    *type=hand[i].rank;
                    return 1;
                }

            }

    return 0;
}

int findHighDouble(Card hand[],int *type, int *secondType, int *highCard){
    int i;

    for (i=0;i<5;i++)
        if (hand[i].rank!=(*type)&&hand[i].rank!=(*secondType)){
            *highCard = hand[i].rank;
            return 1;
        }

    return 0;
}

int findHighSimple(Card hand[],int *type, int *highCard){
    int i;
    int max = 0;

    for (i=0;i<5;i++)
        if (hand[i].rank!=*type&&hand[i].rank>max){
            max = hand[i].rank;
        }

    *highCard = max;
    return 1;
}

int findHigh(Card hand[], int *highCard){
    int i;
    int max = 0;

    for (i=0;i<5;i++)
        if (hand[i].rank>max)
            max = hand[i].rank;

    *highCard = max;
    return 1;
}

int isFlush(Card hand[],int *highCard){
    int i;
    int suit;

    suit = hand[0].suit;

    for (i=1;i<5;i++)
        if (hand[i].suit!=suit)
            return 0;

    return 1;
}

int getPoints(Card hand[], int *type, int *highCard,int *secondType){
    if (isFour(hand, type))
        return 8;
    if (isThree(hand,type)){
        if (isFull(hand,type))
            return 7;
        else
            return 4;
    }

    if (isStraight(hand,type)){
        if(isStraightFlush(hand)){
            if (isRoyal(hand))
                return 10;
            else
                return 9;
        }
        return 5;
    }

    if (isFlush(hand,highCard))
        return 6;

    if (isPair(hand,type)){
        if (isTwoPairs(hand,type,secondType)){
            findHighDouble(hand,type,secondType,highCard);
            return 3;
        }
        else{
            findHighSimple(hand,type,highCard);
            return 2;
        }
    }

    findHigh(hand,highCard);
    return 1;

}

int findWinner(Card hand1[], Card hand2[]){
    int points1,points2;
    int type1, highCard1,type2,highCard2;
    int secondType1,secondType2;

    points1 = getPoints(hand1,&type1,&highCard1,&secondType1);
    points2 = getPoints(hand2,&type2,&highCard2,&secondType2);

    //printf("points1 = %d points2 = %d\n",points1,points2);

    if (points1>points2)
        return 1;
    else if (points2>points1)
        return 0;
    else{
        if (points1==1){
            if (highCard1>highCard2)
                return 1;
            else
                return 0;
        }
        if (points1==2){
            if (type1>type2)
                return 1;
            else if (type2>type1)
                return 0;
            else{
                if (highCard1>highCard2)
                    return 1;
                else
                    return 0;
            }
        }
        if (points1==3){
            if (type1>type2)
                return 1;
            else if (type2>type1)
                return 0;
            else {
                if (secondType1>secondType2)
                    return 1;
                else if(secondType2>secondType1)
                    return 0;
                else{
                    if (highCard1>highCard2)
                        return 1;
                    else
                        return 0;
                }
            }
        }
        if (points1==4){
            if (type1>type2)
                return 1;
            else
                return 0;
        }
        if (points1==5){
            if (type1>type2)
                return 1;
            else
                return 0;
        }
        if (points1==9){
            if (type1>type2)
                return 1;
            else
                return 0;
        }
        if (points1==6){
            if (highCard1>highCard2)
                return 1;
            else
                return 0;
        }
    }

    return 2;
}

int changeDealerCards(Card* hand){
	int type;
	//if dealer great card combimnations dont chage cards
	if (isRoyal(hand)||isStraightFlush(hand)||isFull(hand, &type)||isFour(hand, &type)||isFlush(hand, &type)||isStraight(hand, &type)){
		return 0;
	} else if (isThree(hand, &type)){
		hand[1].rank = (rand() % 13) + 2;
		hand[1].suit = rand() % 4;
		hand[3].rank = (rand() % 13) + 2;
		hand[3].suit = rand() % 4;
		return 2;
	} else {
		hand[1].rank = (rand() % 13) + 2;
		hand[1].suit = rand() % 4;
		hand[3].rank = (rand() % 13) + 2;
		hand[3].suit = rand() % 4;
		hand[0].rank = (rand() % 13) + 2;
		hand[0].suit = rand() % 4;
		return 3;
	}
}

