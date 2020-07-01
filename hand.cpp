//
// Created by Thinkpad on 2020/6/21.
//
#include "hand.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>

using namespace std;

Hand::Hand():
curValue{0, false}{
}
// EFFECTS: establishes an empty blackjack hand.

void Hand::discardAll(){
    curValue.count = 0;
    curValue.soft = true;
}
// MODIFIES: this
// EFFECTS: discards any cards presently held, restoring the state
// of the hand to that of an empty blackjack hand.

void Hand::addCard(Card c){
    // jack queen king case
    if(c.spot == JACK || c.spot == QUEEN || c.spot == KING){
        curValue.count += 10;
    }
    // ace case
    else if(c.spot == ACE){
        // ace = 14 is too large.
        if(curValue.count + 11 > 21){
            curValue.count++;
        }
        else{
            curValue.soft = true;
            curValue.count += 11;
        }
    }
    else{
        curValue.count += c.spot;
    }

    // Overflow because of soft ace.
    if(curValue.soft && curValue.count > 21){
        curValue.soft = false;
        curValue.count -= 10;
    }
}
// MODIFIES: this
// EFFECTS: adds the card "c" to those presently held.

HandValue Hand::handValue() const{
    return curValue;
}
// EFFECTS: returns the present value of the blackjack hand.  The
// count field is the highest blackjack total possible without
// going over 21.  The soft field should be true if and only if at
// least one ACE is present, and its value is counted as 11 rather
// than 1.  If the hand is over 21, any value over 21 may be returned.
//
// Note: the const qualifier at the end of handValue means that
// you are not allowed to change any member variables inside
// handValue. Adding this prevents the accidental change by you.
