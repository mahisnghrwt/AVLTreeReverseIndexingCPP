#include <iostream>
#include <fstream>

#include "dictionary.h"

using namespace std;

int main() {
	int option;
	dictionary dict;
	do {
		cout 	<< "1. Learn Dictionary from text file." << endl
				<< "2. Print while Dictionary" << endl
				<< "3. Search for the word in the Dictionary" << endl
				<< "4. Print AVL Tree information" << endl
				<< "5. Save dictionary into a file" << endl
				<< "6. Load dictionary" << endl
				<< "7. Learn dictionary from multiple files" << endl
				<< "8. Delete low frequency words" << endl
				<< "9. Delete the dictionary" << endl
				<< "10. Exit" << endl;

		cin >> option;
		switch (option) {
			case 1: dict.learnDict();
				break;
			case 2: dict.printDict();
				break;
			case 3: dict.searchDict();
				break;
			case 4: dict.printDetails();
				break;
			case 5: dict.saveDict();
				break;
			case 6: dict.loadDict();
				break;
			case 7: dict.learnMultDict();
				break;
			case 8: dict.delLowFreq();
				break;
			case 9: dict.delDict();
		}
	} while(option != 10);
	cout << "Program has been terminated!" << endl;
}
