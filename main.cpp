// PROGRAM 3
// CS 141
// System: Replit
// Author: MUHAMMAD MUZZAMMIL
// UIN: 661657007

#include <iostream> 
#include <fstream>
#include <vector>
#include <cassert> 
#include <cctype> 
#include <string>
#include <ctime>
using namespace std;


int promptMenu(){
  int option;
  cout << "\nSelect a menu option:" << endl;
  cout << "   1. To play Wordle Reload 3 letter play" << endl;
  cout << "   2. To play Wordle Reload 5 letter play" << endl;
  cout << "   3. Exit the program" << endl;
  cout << "Your choice --> ";
  cin >> option;
  cout << endl;
  return(option);
}

void loadWords(vector <string> & threeLetterWords, vector <string> & fiveLetterWords) {
  ifstream inStream;
  inStream.open( "wordlewords.txt");     
  assert( inStream.fail() == false );        
  fiveLetterWords.clear();
  threeLetterWords.clear();
  string word;                        
  while( inStream >> word) {
    if (word.length() == 3) {
      threeLetterWords.push_back(word);
    } else {
     fiveLetterWords.push_back(word);
    }
  }
  inStream.close();
}

bool iequals(const string& a, const string& b) {
  return std::equal(a.begin(), a.end(), b.begin(), b.end(),
    [](char a, char b) {
      return tolower(a) == tolower(b);
  });
}

bool binarySearch(string searchValue, vector<string> &words){
  bool playableWord = false;
  int low = 0;
  int high = words.size()-1;
  int mid;
  while(low <= high){
    mid = (low + high)/2;
    if (searchValue == words[mid])
    {
      playableWord = true;
      break;
    } else if(searchValue > words[mid]){
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  } 
  return playableWord;
}


string chooseRandomWord(vector <string> &words){  
  int max = words.size()-1;
  int index = rand() % ( max + 1);
  return words[index];
}


int playGame(int length, vector <string> &words) {
  int elapsedSeconds = 0;
  time_t startTime;
  int timeAllowed = 20;
  int maxAttempts = 4;
  if (length == 5) {
    timeAllowed = 40;
    maxAttempts = 6;
  }
  cout << "To get started, enter your first " << length <<" letter word." << endl;
  cout << "You have " << maxAttempts << " attempts to guess the random word." << endl;
  cout << "The timer will start after your first word entry." <<endl;
  cout << "Try to guess the word within " << timeAllowed << " seconds." <<endl;
  
  string word = chooseRandomWord(words);
  int tries = 1;
  bool guessed = false;
  string results;
  
  while (tries < maxAttempts + 1){
    
    string userWordInput;
    string userWord;
    
    while (true){
      cout << "\n\nPlease enter word -->  ";
      cin >> userWordInput;
      userWord = "";
      for (int i = 0; i < int(userWordInput.length()); i++) {
        userWord += tolower(userWordInput[i]);
      }

      if (int(userWordInput.length()) != length) {
        cout << "Invalid word entry - please enter a word that is " << length
       << " characters long." << endl;
        continue;
      }
      
      if (!binarySearch(userWord, words)) {
        cout << "Not a playable word, please select another word." << endl;
        continue;
      }
            
      break;
    }

    cout << "\n";    
    if (tries == 1) {
        startTime = time(NULL);
    } else {
      elapsedSeconds = difftime(time(NULL), startTime);  
    }
    
    if (elapsedSeconds > timeAllowed) {
      cout << "Your time has expired.  Try again." << endl;
      cout << " - You are " << (elapsedSeconds - timeAllowed) << " seconds over the " << timeAllowed << " second time limit.";
      return -1;
    }
   
    
    cout << "\n";
    for (int i = 0; i < int(userWord.length()); i++) {
      char userChar = userWord[i];
      char userCharUpper = toupper(userWord[i]);      
      
      if ( userChar == word[i]) {
        results += "[ ";
        results.push_back(userCharUpper);
        results += " ] ";
      } else if (word.find(userChar) != std::string::npos) {
        results += "[ ";
        results.push_back(userChar);
        results += " ] ";        
      } else {
        results += "[ * ] " ;
      }
    }
    results += "\n";
    cout << results << "\n";
    if (iequals(userWord, word)) {
      cout << "\nNice Work!  You guessed the correct word" << endl;
      cout << " - You completed the board in: " << elapsedSeconds << " seconds." << endl;
      cout << " - It took you " << tries << "/" << maxAttempts << " attempts." << endl;
      return elapsedSeconds;
    }
    tries++;
  }
  cout << "\n";
  if (!guessed) {
    cout << "\nMaximum amount of attempts have been reached. Try again." << endl;
    return -1;
  }
  return tries;
}

void gameOver(int wins, int longestStreak, int seconds) {
  cout << "Overall Stats:" << endl;
  cout << "- You guessed: " << wins << endl;
  cout << "- Your longest streak is: " << longestStreak << endl;
  if (wins == 0) {
    cout << "- Average word completion time: N/A" << endl;
  } else {
    cout << "- Average word completion time: " << (seconds/wins)<< endl;
  }
  cout << "Exiting program" << endl;
}

void start() {
  cout << "Program 3: Wordle Reload" << endl;
  cout << "CS 141, Spring 2022, UIC\n" << endl;
  cout << "The objective of this game is to guess the randomly selected" << endl;
  cout << "word within a given number of attempts. You can select either" << endl;
  cout << "a three or five word board." << endl;
  cout << "At the conlusion of the game, stats will be displayed." << endl;
  cout << "Indicators will be given if characters of the user entered" << endl;
  cout << "word are reflected in the guessed word." <<endl;
  cout << " - If the character is in the correct position, the character" << endl;
  cout << "will display as an uppercase value." << endl;
  cout << " - If the character is within the random word, the character" << endl;
  cout << "will display as a lowercase value." << endl;
  cout << " - If you enter a character that is not in the word, an asterisk '*'" << endl;
  cout << "will display.\n" << endl;
}

int main() {
  start();
  srand(1);
  vector<string> threeLetterWords;
  vector<string> fiveLetterWords;
  loadWords(threeLetterWords, fiveLetterWords);
  int guessedWords = 0;
  int timeTaken = 0;
  int totalTimeTaken = 0;
  int longestStreak = 0;
  int streak = 0;
  while(true) {
    int choice = promptMenu();
    if (choice == 3) {
      gameOver(guessedWords,longestStreak, totalTimeTaken);
      break;
    }  
    int wordLength = 3;
    if (choice == 2) {
      wordLength = 5;
      timeTaken = playGame(wordLength, fiveLetterWords);
    } else {
      timeTaken = playGame(wordLength, threeLetterWords);
    }
    
    if (timeTaken >= 0) {
      totalTimeTaken += timeTaken;
      guessedWords++;
      streak++;
      if (streak > longestStreak) {
        longestStreak = streak;
      }
    } else {
      streak = 0;
    }
  }
}