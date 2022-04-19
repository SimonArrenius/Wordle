#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>

#define BACKGROUND(color, text) "\033[3;42;" << static_cast<int>(color) << "m" << text << "\033[0m"
#define FOREGROUND(color, text) "\x1B[" << static_cast<int>(color) << "m" << text << "\033[0m"


using namespace std;

enum class BackgroundColor : int {
	Red = 41,
	Green = 42,
	Yellow = 43,
	Grey = 100,
	BrightRed = 101,
	BrightGreen = 102,
	BrightYellow = 103
	
};

enum class ForegroundColor : int {
	Red = 31,
	Green = 32,
	Yellow = 33,
	BrightRed = 91,
	BrightGreen = 92,
	BrightYellow = 93
};



int main() 
{
	string word;
	string line;

	srand(time(NULL));

	char again;
	
	bool playing = true;


	vector <string> dictionary;
	ifstream file("words.txt");

	bool dWord = false;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			
			dictionary.push_back(line);
		}
		file.close();
	}
	

	cout << "Wordle\n" << endl;
	do
	{
		int tries = 6;
		string guess{""};

		word = dictionary[rand() % dictionary.size()];
		//Cheat mode
		//cout << "The right word is: " << BACKGROUND(BackgroundColor::Green, word) << endl;

		while (playing && tries > 0)
		{
			dWord = false;
				cout << "\nStart guessing:\n\n" << endl;
				cin >> guess;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore();
				}

				for (int i = 0; i < guess.size(); i++)
				{
					guess[i] = toupper(guess[i]);
				}
				for (int i = 0; i < dictionary.size() - 1; i++)
				{
					if (guess == dictionary[i])
					{
						dWord = true;
					}
				}
				if (dWord == false)
				{
						cout << "Word does not exist..";
				}
				else if (dWord == true)
				{
					tries--;
				if (guess == word)
				{
					stringstream sstream;
					for (size_t i = 0; i < guess.length(); i++)
					{
						sstream << BACKGROUND(BackgroundColor::Green, guess[i]);
					}
					guess = sstream.str();
					cout << guess;
					playing = false;
				}
				else if (find(dictionary.begin(), dictionary.end(), word) != dictionary.end()) // feedback: you already searched dictionary once,
																							// when set dWord value, seems unnecessary to do it again.
				{
					stringstream sstream;
					for (size_t i = 0; i < guess.length(); i++)
					{
						if (guess[i] == word[i])
						{
							sstream << BACKGROUND(BackgroundColor::Green, guess[i]);
						}
						else if (find(word.begin(), word.end(), guess[i]) != word.end())
						{
							sstream << BACKGROUND(BackgroundColor::Yellow, guess[i]);
						}
						else
						{
							sstream << BACKGROUND(BackgroundColor::Grey, guess[i]);
						}

					}
					guess = sstream.str();
					cout << guess;
					cout << " num of tries left " << tries;
				}
			}
		}
		if (tries <= 0 && playing)
		{
			cout << "\nYou lost the right word is " << word << endl;
		}
		else
		{
			cout << FOREGROUND(ForegroundColor::Green, "\n\nYOU GOT IT!\n\n");
		}
		while (true)
		{
			cout << "\nAnother round? Press R and then Enter to play again.\n";
			cin >> again;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore();
			}
			else
			{
				if (toupper(again) == 'R')
				{
					playing = true;
				}
				break;
			}
		}
	} while (toupper(again) == 'R');
}

//todo Foreground on victory