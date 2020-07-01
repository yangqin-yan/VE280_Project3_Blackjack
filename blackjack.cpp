//
// Created by Thinkpad on 2020/7/1.
//

#include "player.h"
#include "deck.h"
#include "rand.h"
#include <iostream>

using namespace std;

static const int MINIMUM = 5; // minimum bet is 5.

// EFFECTS: shuffle the deck 7 times
// MODIFIES: deck.
// REQUIRES: the address of deck.
void deck_shuffle(Deck & d){
    for(int i = 0; i < 7; i++){
        int cut = get_cut();
        d.shuffle(cut);
        cout << "cut at " << cut << endl;
    }
    cout << "Shuffling the deck\n";
}

int main(int argc, char* argv[]){

    string str;
    Hand p_hand, d_hand;
    Player *player = nullptr;
    str = argv[1]; // input bankroll
    int bankroll = atoi(str.c_str());
    str = argv[2];
    int max_num_hands = atoi(str.c_str());
    str = argv[3];
    if(str == "simple"){
        player = get_Simple();
    }
    if(str == "counting"){
        player = get_Counting();
    }

    // First shuffle the deck.
    Deck d;
    deck_shuffle(d);

    int thishand = 0;

    if(bankroll >= MINIMUM){
        while(bankroll >= MINIMUM && thishand < max_num_hands){
            thishand++;
            cout << "Hand " << thishand << " bankroll " << bankroll << endl; // announce the hand
            // If fewer than 20 cards left, shuffle
            if(d.cardsLeft() < 20) {
                deck_shuffle(d);
            }

            // ask the player for a wager and announce it.
            int wager = player->bet(bankroll, MINIMUM);
            cout << "Player bets " << wager << endl;

            //Initialization
            p_hand.discardAll();
            d_hand.discardAll();

            // Deal four cards.
            Card deal,dealer_hand;
            deal = d.deal();
            p_hand.addCard(deal);
            player->expose(deal);
            cout << "Player dealt " << SpotNames[deal.spot] << " of "
            << SuitNames[deal.suit] << endl;

            dealer_hand = d.deal();
            d_hand.addCard(dealer_hand);
            player->expose(dealer_hand);
            cout << "Dealer dealt " << SpotNames[dealer_hand.spot] << " of "
                 << SuitNames[dealer_hand.suit] << endl;

            deal = d.deal();
            p_hand.addCard(deal);
            player->expose(deal);
            cout << "Player dealt " << SpotNames[deal.spot] << " of "
                 << SuitNames[deal.suit] << endl;

            deal = d.deal();
            d_hand.addCard(deal);

            // Judgement.
            if(p_hand.handValue().count == 21){
                bankroll += wager * 3 / 2;
                cout << "Player dealt natural 21\n";
            }
            else{
                while(player->draw(dealer_hand, p_hand)){
                    // draw strategy
                    deal = d.deal();
                    p_hand.addCard(deal);
                    player->expose(deal);
                }
                int player_count = p_hand.handValue().count;
                cout << "Player's total is " << player_count << endl;
                if(player_count > 21){
                    // bust case
                    bankroll -= wager;
                    cout << "Player busts\n";
                    continue;
                }
                else{
                    // play the dealer's hand.
                    while(d_hand.handValue().count < 17){
                        deal = d.deal();
                        d_hand.addCard(deal);
                    }
                    int dealer_count = d_hand.handValue().count;
                    cout << "Dealer's total is " << dealer_count << endl;
                    if(dealer_count > 21){
                        bankroll += wager;
                        cout << "Dealer busts\n";
                        continue;
                    }

                    if(player_count < dealer_count){
                        bankroll -= wager;
                        cout << "Dealer wins\n";
                        continue;
                    }
                    else if(player_count > dealer_count){
                        bankroll += wager;
                        cout << "Player wins\n";
                        continue;
                    }
                    else{
                        // equal case
                        cout << "Push\n";
                        continue;
                    }
                }
            }
        }
    }

    cout << "Player has " << bankroll
    << " after " << thishand << " hands\n";

    return 0;
}