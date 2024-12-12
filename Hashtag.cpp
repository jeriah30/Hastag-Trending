#include "Hashtag.h"
#include <iostream>

Hashtag::Hashtag(string word) {
    this -> word = word;
    Count = 1;
    Rank = -1;
}

Hashtag::Hashtag(string word, int Count) {
    this -> word = word;
    this -> Count = Count;
    Rank = -1;
}

void Hashtag::setRank(int rank) {
    Rank = rank;
}

void Hashtag::IncrementCount() {
    Count++;
}

int Hashtag::getRank() const {
    return Rank;
}

int Hashtag::getCount() const {
    return Count;
}

string Hashtag::getWord() const {
    return word;
}

bool Hashtag::operator<(const Hashtag& rhs) const {
    if (Count == rhs.Count) {
        return word < rhs.word;
    }
    return Count > rhs.Count; 
}