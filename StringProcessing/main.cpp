/**
    Matthew Vu
    String Processing Program
    Objective: To process string and change them into various sentence cases
    Sentence case: Hello world, rodney!
    Toggle case: hELLO wORLD
    Title case: Hello World
    sentence case with exceptions: Hello world, Rodney!

    Change Log 1 and 2 3/11-3/12:
    1. used hashmaps for vowels, nouns, and longest words
    2. checkForSentence function complete,
    3. added string/words into vectors
    4. found longest words
    5. found punctuation, vowels, consonants, num words, and more
    6. finished toggle, title, sentence, and exceptions cases
    7. Finished program.

    Plans:
    Add toggle, sentence/sentece with exceptions, and title case to program
    Learn to use hashmap for identifying vowels and consonants // DONE
    implement a way to find the longest word in a sentence, (2d vector?)

**/

#include <iostream>
#include <cstdlib> // c-string
#include <string>
#include <unordered_map> // maps for vowels, nouns
#include <fstream> // input streams
#include <vector>

using namespace std;


unordered_map<char, int> vowels = {{'a',1}, {'e',2}, {'i',3},{'o',4},{'u',5}
};
unordered_map<string, int> formalNouns = {{"I",1},{"Amy",2},{"Spain",3},{"Suzy",4},{"Billy",5},
    {"Fritos",6},{"Friday's",7},{"Hertford",8},{"Hereford",9},{"Hampshire",10}
};
unordered_map<string, int> longestWord;
vector<string> allWords;
vector<string> sentences;

void showFlow(string str)
{
    cout << str << endl;
}
void line()
{
    cout << "-----------------------------\n";
}
// find the consonants, punctuation and vowels
int findVowelAndPunc(int &numVowel, int &numPunct, char sentenceChar)
{
    //iterate through the vowels unordered map and if it finds it then increment the num of vowels
    for(auto vowel: vowels)
    {
        if(tolower(sentenceChar) == vowel.first)
        {
            numVowel++;
        }
    }
    // after going through all the possible vowels check if the char is equal to a punctuation
    if(sentenceChar == '\'' || sentenceChar == '!' || sentenceChar == '.' || sentenceChar == '?' || sentenceChar == ',' || sentenceChar == '-')
    {
        numPunct++;
    }
}
// lowercase first letter in every word, then uppercase every other character
void toggleCase()
{
    int firstIndex = 0;
    cout << "Toggle Case: " << endl;
    for(int i = 0; i < sentences.size(); i++)
    {
        sentences[i][firstIndex] = tolower(sentences[i][firstIndex]);
        cout << sentences[i][firstIndex];
        for(int j = 1; j < sentences[i].size(); j++) // starts from the second characte
        {
            sentences[i][j] = toupper(sentences[i][j]); // capitalizing every other letter than the first
            cout << sentences[i][j];
        }
        cout << " ";
    }
    cout << endl;
}
// capitialize the first word in the sentence and that's it
void sentenceCase()
{
    int firstIndex = 0, secondIndex = 1;
    cout << "Sentence Case: " << endl;
    // change the very first element into a uppercase
    sentences[firstIndex][firstIndex] = toupper(sentences[firstIndex][firstIndex]);
    cout << sentences[firstIndex] << " ";  // outputs it
    // loops through the sentence's starting from the second word and outputs characters
    for(int i = secondIndex; i < sentences.size(); i++)
    {
        for(int j = firstIndex; j < sentences[i].size(); j++)
        {
            cout << static_cast<char>(tolower(sentences[i][j])); // change all other letters to lower case
        }
        cout << " ";
    }
    cout << endl;
}
// It should capitalize the first letter in every word.
void titleCase()
{
    // showFlow("I am at title Case");
    int firstLetIndex = 0;
    cout << "Title case: " << endl;
    for(int i = 0; i < sentences.size(); i++)
    {
        sentences[i][firstLetIndex] = toupper(sentences[i][firstLetIndex]);
        cout << sentences[i] << " ";
    }
    cout << endl;
}
// outputs Sentence case with proper nouns capitalized
void sentenceCaseException()
{
    cout << "Sentence case with exceptions: " << endl;
    int size = sentences.size(), firstIndex = 0;
    for(int i = 0; i < size; i++)
    {
        for(auto formalNoun: formalNouns)
        {
            if(formalNoun.first == sentences[i])
            {
                sentences[i][firstIndex] = toupper(sentences[i][firstIndex]);
            }
        }
        cout << sentences[i] << " ";
    }
    cout << endl;
}
void displayLongestWord()
{
    for(auto longest: longestWord)
    {
        cout << "Longest word in sentence is: " << longest.first << " with " << longest.second << " characters.\n";
    }
    longestWord.erase(longestWord.begin()); // gets rid of the key pair within the map to make rooom for the next sentence
}
// will store the longest word and the number of characters it has into a map, or replace it after it finds a larger word.
void storeLongestWord(int numChar, int currWordPos)
{
    // if the map is empty store the a key pair and it's length
    if(longestWord.empty())
    {
        longestWord.insert(make_pair(sentences[currWordPos], numChar));
        return;
    }
    // now in the second iteration, compare the value within in the map, and see if it's character values are less than the values in the current word
    for(auto longest: longestWord)
    {
        if(longest.second <= numChar) // compare charCount
        {
            longestWord.erase(longestWord.begin()); // erases the value inside the map
            longestWord.insert(make_pair(sentences[currWordPos], numChar)); // adds new value to map
        }
    }

}
// will display the words, chars, vowels, consonants, and the sentence
void displaySentence()
{
    int countWords = 0, countChar = 0, countVowels = 0, countConsonants = 0,
    countPunct = 0, countLongestChar = 0;;

    line();
    cout << "Displaying sentence:\n";
    for(int i = 0; i < sentences.size(); i++)
    {worww
        countLongestChar = 0; // resets the current longest character to 0, in preparation for the next word
        for(int j = 0; j < sentences[i].size(); j++)
        {
            countChar++;
            countLongestChar++;
            findVowelAndPunc(countVowels, countPunct, sentences[i][j]); // find the vowel and punctuations if any in the char
            cout << sentences[i][j];
        }
        storeLongestWord(countLongestChar, i); // store the longest word into map, if not just returns nothing
        countWords++; // increment num word
        cout << " ";
    }
    cout << "\n";
    // if i've correctly found all the character, vowels, and punctuation and I can simply subtract them from each other
    // to find the num of consonants
    countConsonants = countChar - countVowels - countPunct;
    countChar = countChar += (countWords-1); // this will include the spaces between each word as character in the string
    cout << "Total # of words in the sentence is: " << countWords << endl;
    cout << "Total # of characters in the sentence is: " << countChar << endl;
    cout << "Total # of vowels in the sentence is: " << countVowels << endl;
    cout << "Total # of consonants in the sentence is: " << countConsonants << endl;
    cout << "Total # of punctuation symbol in the sentence is: " << countPunct << endl;
    displayLongestWord();
}
void displayWords()
{
    for(int i = 0; i < allWords.size(); i++)
    {
        cout << allWords[i] << ' ';
    }
}
// Check if there is a period in the word, meaning it's the end of the sentence. Passes in the curr position in allWords vector
bool checkForSentence(int currWordPos)
{
    int length = allWords[currWordPos].size()-1;
    // cout << "length of word is: " << length << endl;
    if(allWords[currWordPos][length] == '.' || allWords[currWordPos][length] == '?' || allWords[currWordPos][length] == '!')
    {
      //  cout << "found the end of sentence: " << allWords[currWordPos] << endl << endl;
        return true;
    }
 //   cout << "end of sentence not found\n";
    return false;

}
// finds a sentence and then processes it, DOES FOR ALL SENTENCES
void findAllSentence()
{
    string word;
    for(int currWordPos = 0; currWordPos < allWords.size(); currWordPos++)   // iterates through all the words
    {
        word = allWords[currWordPos]; // sets a string word equal to current word
        sentences.push_back(word); // add the word to the sentences vect
        if(checkForSentence(currWordPos) == true)   // now check if the word has a punctuation mark that indicates the end of a sentence
        {
            displaySentence();
            sentenceCase();
            sentenceCaseException();
            titleCase();
            toggleCase();
            sentences.erase(sentences.begin(),sentences.end()); // gets rid of the old sentence in the vector in prep for the new one
        }
    }
}
// opens file and reads in the word
void readFile()
{
    ifstream finput; // stream for gathering file input
    string fileName, word; // word is used as a  temp variable

    cout << "What file do you want to open?" << endl;
    cin >> fileName;
    finput.open(fileName.c_str());
    if(!finput)   // checks if file could be opened or not
    {
        cout << "File could not be opened\n";
        readFile(); // calls function recursively to ask for file name again
    }
    else
    {
        cout << "File successfully opened\n\n";
        while(finput >> word)   // reads in all the words in the input into a vector of strings
        {
            allWords.push_back(word);
        }
        cout << "Successfully read in words\n\n";
        // used to display if all words are read in, debug code
        // displayWords();
        finput.close();
    }
}
// main function
int main()
{
    readFile();
    findAllSentence();
    return 0;
}
