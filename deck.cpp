//
// Created by Thinkpad on 2020/6/19.
//
#define NDEBUG
#include "deck.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>

using namespace std;

// EFFECTS: constructs a "newly opened" deck of cards.  first the
// spades from 2-A, then the hearts, then the clubs, then the
// diamonds.  The first card dealt should be the 2 of Spades.
Deck::Deck(): deck{TWO, SPADES, THREE, SPADES, FOUR, SPADES, FIVE, SPADES,
                   SIX, SPADES, SEVEN, SPADES, EIGHT, SPADES, NINE, SPADES,
                   TEN, SPADES, JACK, SPADES, QUEEN, SPADES, KING, SPADES,
                   ACE, SPADES,
                   TWO, HEARTS, THREE, HEARTS, FOUR, HEARTS, FIVE, HEARTS,
                   SIX, HEARTS, SEVEN, HEARTS, EIGHT, HEARTS, NINE, HEARTS,
                   TEN, HEARTS, JACK, HEARTS, QUEEN, HEARTS, KING, HEARTS,
                   ACE, HEARTS,
                   TWO, CLUBS, THREE, CLUBS, FOUR, CLUBS, FIVE, CLUBS,
                   SIX, CLUBS, SEVEN, CLUBS, EIGHT, CLUBS, NINE, CLUBS,
                   TEN, CLUBS, JACK, CLUBS, QUEEN, CLUBS, KING, CLUBS,
                   ACE, CLUBS,
                   TWO, DIAMONDS, THREE, DIAMONDS, FOUR, DIAMONDS, FIVE, DIAMONDS,
                   SIX, DIAMONDS, SEVEN, DIAMONDS, EIGHT, DIAMONDS, NINE, DIAMONDS,
                   TEN, DIAMONDS, JACK, DIAMONDS, QUEEN, DIAMONDS, KING, DIAMONDS,
                   ACE, DIAMONDS,}, next(0)
{
    // Test
    assert(cout << SuitNames[deck[next].suit] << " " << SpotNames[deck[next].spot] << endl);
}



// EFFECTS: resets the deck to the state of a "newly opened" deck
// of cards:
void Deck::reset(){
    next = 0;
    for(int i = 0; i < DeckSize; i++) {
        // Generate the suits.
        if(i < 13){
            deck[i].suit = SPADES;
        }
        else if(i < 26){
            deck[i].suit = HEARTS;
        }
        else if(i < 39){
            deck[i].suit = CLUBS;
        }
        else{
            deck[i].suit = DIAMONDS;
        }

        // Generate the spots.
        switch(i % 13){
            case 0:
                deck[i].spot = TWO;
                break;
            case 1:
                deck[i].spot = THREE;
                break;
            case 2:
                deck[i].spot = FOUR;
                break;
            case 3:
                deck[i].spot = FIVE;
                break;
            case 4:
                deck[i].spot = SIX;
                break;
            case 5:
                deck[i].spot = SEVEN;
                break;
            case 6:
                deck[i].spot = EIGHT;
                break;
            case 7:
                deck[i].spot = NINE;
                break;
            case 8:
                deck[i].spot = TEN;
                break;
            case 9:
                deck[i].spot = JACK;
                break;
            case 10:
                deck[i].spot = QUEEN;
                break;
            case 11:
                deck[i].spot = KING;
                break;
            case 12:
                deck[i].spot = ACE;
                break;
            default:
                assert(1);
                break;
        }
    }
}

// REQUIRES: n is between 0 and 52, inclusive.

// MODIFIES: this

// EFFECTS: cut the deck into two segments: the first n cards,
// called the "left", and the rest called the "right".  Note that
// either right or left might be empty.  Then, rearrange the deck
// to be the first card of the right, then the first card of the
// left, the 2nd of right, the 2nd of left, and so on.  Once one
// side is exhausted, fill in the remainder of the deck with the
// cards remaining in the other side.  Finally, make the first
// card in this shuffled deck the next card to deal.  For example,
// shuffle(26) on a newly-reset() deck results in: 2-clubs,
// 2-spades, 3-clubs, 3-spades ... A-diamonds, A-hearts.
//
// Note: if shuffle is called on a deck that has already had some
// cards dealt, those cards should first be restored to the deck
// in the order in which they were dealt, preserving the most
// recent post-shuffled/post-reset state.
void Deck::shuffle(int n){
    Deck shuffle_l, shuffle_r;
    shuffle_l.next = 0;
    shuffle_r.next = 0;
    int l_num, r_num;
    l_num = 0;
    r_num = 0;
    next = 0;

    // Divide the deck into 2 parts.
    for(int i = 0; i < n; i++){
        shuffle_l.deck[i] = this->deck[i];
        l_num++;
    }
    for(int i = n; i < DeckSize; i++){
        shuffle_r.deck[i - n] = this->deck[i];
        r_num++;
    }
    int i = 0;

    // Merge them into one deck.
    while(i < DeckSize){
        if(shuffle_l.next < l_num && shuffle_r.next < r_num){
            this->deck[i] = shuffle_r.deck[shuffle_r.next];
            shuffle_r.next++;
            this->deck[i + 1] = shuffle_l.deck[shuffle_l.next];
            shuffle_l.next++;
            i += 2;
        }
        else if(shuffle_l.next == l_num){
            this->deck[i] = shuffle_r.deck[shuffle_r.next];
            shuffle_r.next++;
            i++;
        }
        else if(shuffle_r.next == r_num){
            this->deck[i] = shuffle_l.deck[shuffle_l.next];
            shuffle_l.next++;
            i++;
        }
    }

    /*cout << "---------------------------"  << endl;
    for(int a = 0; a < DeckSize; a++){
        cout << SuitNames[deck[a].suit] << " " << SpotNames[deck[a].spot] << endl;
    }*/
}

// MODIFIES: this
// EFFECTS: returns the next card to be dealt.  If no cards
// remain, throws an instance of DeckEmpty.s
Card Deck::deal(){
    try{
        if(next == DeckSize){
            // Debugs
            cerr << "Error: Move until the end of deck!";
            throw 1;
        }
    }
    catch(int n){
        exit(-1);
    }
    next++;
    return deck[next - 1];
}

// EFFECTS: returns the number of cards in the deck that have not
// been dealt since the last reset/shuffle.
int Deck::cardsLeft(){
    return DeckSize - next;
}
