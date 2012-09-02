//////////////////////////////////////////////////
//wc.cpp
//Word Count program.
//Written by Brian Beckett
//http://www.worthlesscheese.com
//This program is provided free of charge.  Feel free to modify it and distribute it, but please let me know first
//If this program has been useful to you in any way, then I'd love to hear from you!
//e-mail: brian {at} worthlesscheese {dot} com
//////////////////////////////////////////////////

#include <cstdio>
#include <iostream>
using namespace std;

void displayHelp(); //Declare the function.

int main( int argc, const char* argv[] ) {

	//Variables for processing argv.
	bool linesb = false;
	bool wordsb = false;
	bool charsb = false;
	bool charsOtherb = false;
	
	//Processing argv for commands.
	for (int i = 0; i < argc; i++) {
		if (argv[i][0]== '-') {
			
			if (argv[i][1] == 'l') {
				linesb = true;
			} else if (argv[i][1] == 'w') {
				wordsb = true;
			} else if (argv[i][1] == 'c') {
				charsb = true;
			} else if (argv[i][1] == 'n') {
				charsOtherb = true;
			} else {
				displayHelp();
				return 0;
			}	
		}
	}

	//Loading the file.
	//cout << argc << '\n';
	FILE * myfile = fopen(argv[1], "r");
	if (myfile == NULL) {
		cout << "Error while opening file\n\n";
		displayHelp();
		return 0;
	}
	
	//Variables.
	char c;
	int lines = 0;		//Number of lines
	int choo = 0;		//Number of characters, not counting \n
	int chNoSpace = 0;	//Number of characters, not counting \n or whitespace
	int words = 0;		//Number of words
	bool startNewWord = false;
	
	//Go through the file.
	while(true) {
		c = getc(myfile);
		if (c == EOF) { //Is it the end of the file?
			words++; //A word has ended
			break;
		} else if (c == '\n') { //Is it a newline?
			lines++; //it is a newline
			//Problem: Is it a new word as well?
			startNewWord = true;
		} else if (c == ' ' || c == '	') { //Is it whitespace?
			//It is the start of a new word...?
			startNewWord = true;
			choo++; //it is a character
		} else { //Not any of the above?
			choo++; //it is a character
			chNoSpace++; //it is a character (not counting whitespace)
			if (startNewWord == true) {
				words++;
				startNewWord = false;
			}
		}
	}
	
	//Display results.
	if (linesb == 1) {
		cout << lines;
	} else if (wordsb == 1) {
		cout << words;
	} else if (charsb == 1) {
		cout << choo;
	} else if (charsOtherb == 1) {
		cout << chNoSpace;
	} else {
		cout << "Number of lines in file: " << lines << '\n';
		cout << "Number of words in file: " << words << '\n';
		cout << "Number of characters in file: " << choo << '\n';
		cout << "     Not counting whitespace: " << chNoSpace << '\n';
	}
}

void displayHelp() {
		cout << "\nValid options are:\n\n-w for number of words\n-l for number of lines\n-c for number of characters (including whitespace)\n-n for number of characters (not including whitespace)\n-anything else (e.g. -h) to show this help message\n\n";
		cout << "Format:\n wc.exe filename [optional command]\n\nIt won't work if you don't put the filename first\nOnly one optional command can be used at a time\n\n";
		cout << "This version of Word Count was written by Brian Beckett in 2008.\nVisit the author at www.worthlesscheese.com\n";
	}
