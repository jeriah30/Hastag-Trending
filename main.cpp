/*  Name: Jeriah Garcia
    Date: 10/27/24
    Brief Description: My code analyzes hashtag frequency across two input files "start" and an "end" file where a hashtag represents any type of whitespace. 
    I make sure to convert every letter of each hashtag to lowercase for string comparisons to see if the same hashtag is used again. I use a Hashtag class 
    to store each hashtag’s text, count of occurrences, and rank. For each file, my code increments the count if the hashtag already exists or creates a new 
    instance otherwise. After analyzing all the hashtags, my code assigns ranks to each hashtag based on frequency, using a custom comparison function that 
    prioritizes count in descending order and alphabetically. My code finds which hashtags had the largest increases and decreases in rank between the two files. 
    Also, my code identifies new hashtags in the end file that wasn't found in the start file. It then outputs the top 10 new hashtags by rank. However, It is 
    sorted alphabetically if ranks are the same. Thus, my code outputs the highest-ranking end file hashtag, the hashtags with the greatest ranking changes, and
    the top 10 new hashtags from the end file.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Hashtag.h"
using namespace std;

void toLowercase(string &charWord) {
    for (unsigned int i = 0; i < charWord.length(); i++) {
        charWord.at(i) = tolower(charWord.at(i));
    }
}

bool containsHashtag(const vector<Hashtag>& hashtags, const string& word, int& index) {
    for (unsigned int i = 0; i < hashtags.size(); i++) {
        if (hashtags.at(i).getWord() == word) {
            index = i;
            return true;
        }
    }
    return false;
}

void readFile(const string& fileName, vector<Hashtag>& hashtags) {
    ifstream inFS(fileName);
    string word;
    
    if (!inFS.is_open()) {                                    
        cout << "Could not open file." << endl;
        return;
    }
    
    while (inFS >> word) {
        toLowercase(word);
        
        int index;
        if (containsHashtag(hashtags, word, index)) {
            hashtags.at(index).IncrementCount();
        } 
        else {
            hashtags.push_back(Hashtag(word));
        }
    }
    inFS.close();
}
bool compareHashtags(const Hashtag& a, const Hashtag& b) {
    if (a.getCount() == b.getCount()) {
        return a.getWord() < b.getWord();
    }
    return a.getCount() > b.getCount();
}

void rankHashtags(vector<Hashtag>& hashtags) {
    sort(hashtags.begin(), hashtags.end(), compareHashtags);
    
    int currentRank = 1;
    for (unsigned int i = 0; i < hashtags.size(); i++) {
        if (i > 0 && hashtags.at(i).getCount() == hashtags.at(i-1).getCount()) {
            hashtags.at(i).setRank(currentRank);
        }
        else {
            currentRank++;
            hashtags.at(i).setRank(currentRank);
        }
    }
}

int findRank(const vector<Hashtag>& hashtags, const string& word) {
    for (unsigned int i = 0; i < hashtags.size(); i++) {
        if (hashtags.at(i).getWord() == word) {
            return hashtags.at(i).getRank();
        }
    }
    return -1; 
}

///////////////// Before submitting your code
// 1) uncomment this part since zyBooks use it.
int main(int argc, const char* argv[]) {
    if (argc != 3)
    {
        std::cout << "./project2 inputFile1 inputFile2" << std::endl;
        return EXIT_FAILURE;
    }
    string inputFileName1 = argv[1];
    string inputFileName2 = argv[2];
    ///////////////////// uncomment above befofre submitting on zyBooks /////////////////
//2) Comment the next 3 lines below
//int main(void) {
    //string inputFileName1 = "testfile0Start.txt";    //Do NOT change the name "inputFileName1" since used above
    //string inputFileName2 = "testfile0End.txt";    //Do NOT change the name "inputFileName2" since used above

    //Add your code //
    vector<Hashtag> hashtagStart, hashtagEnd;

    readFile(inputFileName1, hashtagStart);
    readFile(inputFileName2, hashtagEnd);

    rankHashtags(hashtagStart);
    rankHashtags(hashtagEnd);

    
    cout << "Hashtag with Rank 1 in the End file: " << hashtagEnd.at(0).getWord() << " with " << hashtagEnd.at(0).getCount() << " counts.\n";

    int maxIncrease = 0, maxDecrease = 0;
    string increaseWord, decreaseWord;

    for (unsigned int i = 0; i < hashtagEnd.size(); i++) {
        int startRank = findRank(hashtagStart, hashtagEnd.at(i).getWord());
        
        if (startRank != -1) { 
            int rankDiff = startRank - hashtagEnd.at(i).getRank();
        
            if (rankDiff > maxIncrease) {
                maxIncrease = rankDiff;
                increaseWord = hashtagEnd.at(i).getWord();
            }
            if (rankDiff < maxDecrease) {
                maxDecrease = rankDiff;
                decreaseWord = hashtagEnd.at(i).getWord();
            }
        }
    }

    cout << "Hashtag with Ranking increases the most: " << increaseWord << "(+" << maxIncrease << " in ranking)\n";
    cout << "Hashtag with Ranking decreases the most: " << decreaseWord << "(" << maxDecrease << " in ranking)\n";
    
    vector<Hashtag> newHashtags;
    for (unsigned int i = 0; i < hashtagEnd.size(); i++) {
        if (findRank(hashtagStart, hashtagEnd.at(i).getWord()) == -1) {
            newHashtags.push_back(hashtagEnd.at(i));
            if (newHashtags.size() >= 10) {
                break;
            }
        }
    }

    sort(newHashtags.begin(), newHashtags.end(), compareHashtags);

    cout << "New Hashtags (first 10 by ranking) in the End file:\n";
    for (unsigned int i = 0; i < newHashtags.size(); i++) {
        cout << newHashtags.at(i).getWord() << " (" << newHashtags.at(i).getCount() << "," << newHashtags.at(i).getRank() - 1 << ")\n";
    } 

   return 0;
}
