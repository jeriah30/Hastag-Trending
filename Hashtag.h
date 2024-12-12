#ifndef HASHTAGH
#define HASHTAGH

#include <string>
using namespace std;

class Hashtag {
private:
	string word;		// The hashtag itself
	int Count;			// Number of occurrences in the file
	int Rank;			// Rank 

public:
	Hashtag(string word);
	Hashtag(string word, int Count);

	// Getter and setter functions for hashtag word, counts, and ranks
	string getWord() const;
	int getCount() const;
	int getRank() const;

	void setRank(int rank);
	void IncrementCount(); //to increment Count

	// Overloaded < operator for Hashtag objects
	bool operator<(const Hashtag& rhs) const;
};

#endif