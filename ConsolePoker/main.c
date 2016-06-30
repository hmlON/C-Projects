#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "poker.h"

int main(){
    Card dealerHand[5]; 
    Card playerHand[5];
    int exit = 0;

	while(exit == 0){
		
		system("cls");
		printf("Welcome to 5-card draw poker\n\n");
		
		//dealing cards to player and dealer
		srand(time(NULL));
		dealCards(playerHand);
		dealCards(dealerHand);
		
		//printing player cards
		printf("Your cards:\n");
		printHand(playerHand);
		
		//changig dealers cards
		int cardsChanged = changeDealerCards(dealerHand);
		printf("\nDealer changed %d cards\n", cardsChanged);
		
		//changing player cards
		printf("\nHow many cards you want to change? (0 to 5)\n> ");
		int numberOfCardsToChange;
		scanf("%d", &numberOfCardsToChange);
		if(numberOfCardsToChange == 5){
			dealCards(playerHand);
		} else {
			int i;
			for(i = 0; i < numberOfCardsToChange; i++){
				int cardNumber;
				printf("Enter number of card you want to change (1 to 5)\n> ");
				scanf("%d", &cardNumber);
				playerHand[cardNumber-1].rank = (rand() % 13) + 2;
				playerHand[cardNumber-1].suit = rand() % 4;
			}
		}
		
		//printing new player cards
		printf("\nYour new cards:\n");
		printHand(playerHand);
		
		//printing final dealer cards
		printf("\nDealer cards:\n");
		printHand(dealerHand);
		
		//printing who is winner
		if (findWinner(playerHand, dealerHand)){
        	printf("\nCongratulations!!! You Win!!!\n");
    	}
    	else
        	printf("\nYou lose...\n");
        	
        //asking to play again
        printf("\nDo you want to play again? (1 - yes, 2 - no)\n> ");
        int playAgain;
		scanf("%d", &playAgain);
		if(playAgain != 1){
        	exit = 1;
		}
		
	}

	return 0;
}
