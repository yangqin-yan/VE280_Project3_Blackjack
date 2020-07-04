#include"player.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>

using namespace std;

class Simple_Player : public Player{
public:
    Simple_Player(): count(0){};
    int bet(unsigned int bankroll,
            unsigned int minimum) override;
    bool draw(Card dealer,             // Dealer's "up card"
                      const Hand &player) override;
    void expose(Card c)override{};
    void shuffled()override{};
protected:
    int count;
};

class Counting_Player : public Simple_Player{
public:
    void expose(Card c) override;
    void shuffled() override;
};

int Simple_Player::bet(unsigned int bankroll,
                unsigned int minimum){
    if(bankroll >= minimum){
        if(count >= 2 && bankroll >= 2 * minimum){ // strategy of the counting player
            return 2 * minimum;
        }
        else{
            return minimum;
        }
    }

    return 0;
}
// REQUIRES: bankroll >= minimum
// EFFECTS: returns the player's bet, between minimum and bankroll
// inclusive

bool Simple_Player::draw(Card dealer,             // Dealer's "up card"
                  const Hand &player) // Player's current hand
{
    // First set of rules.
    if(!player.handValue().soft){
        if(player.handValue().count <= 11){
            return true;
        }
        else if(player.handValue().count == 12 && (dealer.spot != FOUR &&
        dealer.spot != FIVE && dealer.spot != SIX)){
            return true;
        }
        else if(player.handValue().count <= 16 && dealer.spot >= SEVEN){
            return true;
        }
        // 17 or greater
        return false;
    }
    // Soft count
    else{
        if(player.handValue().count <= 17){
            return true;
        }
        else if(player.handValue().count == 18 && (dealer.spot != TWO &&
                                                   dealer.spot != SEVEN && dealer.spot != EIGHT)){
            return true;
        }
        // 19 or greater.
        return false;
    }
}
// EFFECTS: returns true if the player wishes to be dealt another
// card, false otherwise.

void Counting_Player::expose(Card c){
    // subtracts one
    if(c.spot == TEN || c.spot == JACK || c.spot == QUEEN || c.spot == KING || c.spot == ACE){
        count--;
    }
    // adds one
    if(c.spot == TWO || c.spot == THREE || c.spot == FOUR || c.spot == FIVE || c.spot == SIX){
        count++;
    }
}
// EFFECTS: allows the player to "see" the newly-exposed card c.
// For example, each card that is dealt "face up" is expose()d.
// Likewise, if the dealer must show his "hole card", it is also
// expose()d.  Note: not all cards dealt are expose()d---if the
// player goes over 21 or is dealt a natural 21, the dealer need
// not expose his hole card.

void Counting_Player::shuffled(){
    // reset to 0
    count = 0;
}
// EFFECTS: tells the player that the deck has been re-shuffled.


// Declare instances of simple player and counting player.
static Simple_Player p1;
static Counting_Player p2;

Player *get_Simple(){
    return & p1;
}
// EFFECTS: returns a pointer to a "simple player", as defined by the
// project specification

Player *get_Counting(){
    return & p2;
}
// EFFECTS: returns a pointer to a "counting player", as defined by
// the project specification.

