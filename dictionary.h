#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <Windows.h>

#include "DATA.h"
#include "AVL_ADT.h"



class dictionary {
private:
	AvlTree<DATA, string> tree;

	int wordCount = 0;
public:
	void learnDict(const string&);
	void printDict();
	void searchDict();
	void printDetails();
	void saveDict();
	void loadDict();
	void learnMultDict();
	void delLowFreq();
	bool delDict();
	void quicksort(DATA arr[], int l, int r);
	vector<string> GetFileNamesInDirectory(string directory);
	vector<std::string> getAllFilesInDir(const std::string &dirPath, 	const std::vector<std::string> dirSkipList = { });
	string incrString(string);
	string trim(const string&);
};

void dictionary::learnDict(const string &fileN = "") {

	string fileName, phrase;
	string words[3] = {""};
	DATA myData;

	fileName = fileN;

	if (fileName == "") {
		cout << "Enter the file you want to read(file_name.txt): ";
		cin >> fileName;
	}

	ifstream myFile(fileName);
	while (myFile >> words[0]) {
		wordCount++;
		if (words[2] == "")  {
			myFile >> words[1];
			phrase = words[0] + " " + words[1];
			words[2] = words[1];
		}
		else {
			phrase = words[2] + " " + words[0];
			words[2] = words[0];
		}



		for (int i = 0; i < 2; i++) {
			if (words[i] != "") {
				words[i].erase(remove_if(words[i].begin(), words[i].end(), [](char c) { return !isalpha(c); } ), words[i].end());
				transform(words[i].begin(), words[i].end(), words[i].begin(), ::tolower);
				trim(words[i]);
//				if (words[i] != "") {
					if( tree.AVL_Retrieve(words[i], myData)) {
						tree.AVL_Retrieve(words[i], myData, true, fileName);
					}
					else {
						DATA data(words[i], fileName);
						tree.AVL_Insert(data);
						wordCount++;
					}
			}
		}

	for (size_t k = 0; k < min(10, int(freqPhrases.size())); k++) {
		tree.AVL_Insert(freqPhrases.front());
		cout <<  freqPhrases.front().key << endl;
		pop_heap(freqPhrases.begin(), freqPhrases.end());
		wordCount++;
	}
	freqPhrases.clear();
	cout << "Successfully learned dictionary from the file!" << endl << endl;
}

void dictionary::printDict() {
	cout << "Dictionary" << endl;
	tree.AVL_Print_Dict();
}

void dictionary::printDetails() {
	cout << "AVL Tree" << endl
			<< "Words count: " << wordCount <<  "!" << endl;
	tree.AVL_Print();
}

void dictionary::searchDict() {
	string sKey, bKey;
	cout << "Enter the search key: ";
	cin >> sKey;

	bKey = incrString(sKey);

	priority_queue<DATA> result;
	tree.searchDict(sKey, bKey, result);

//	Printing the result of the search query.
	cout << result.size() << " words found!" << endl;
	for (size_t i = 0; i < result.size() && i < 5; i++) {
		cout << result.top().key << setw(3) << "(" << result.top().frequency << ")" << endl;
		result.pop();
	}
}

void dictionary::delLowFreq() {


	//1. Create sorted linked list of the words in the order of frequency.
	//2. Delete the desired words.
	//3. Sort the words via alphabetical order.
	//4.
	//1. The words should be in the ascending order of the frequency.	Frequency
	//2. Delete the words with the desired frequency.					Frequency
	//3. Insert back the words to an AVL tree.							WORDS
}

void binarySearch(vector<DATA> list, int target, int i) {
	if (list[i/2].frequency > target)
		binarySearch(list, target, i/2);
	else
		binarySearch(list, target, 3/2 * i);
}

void dictionary::loadDict() {
	string word, fileName;
	DATA myData;
	int counter = 0;

	ifstream file;

	cout << "Enter the dictionary name to load: ";
	cin >> fileName;

	file.open(fileName);

	delDict();
	wordCount = 0;


		while(file >> word) {

			if (counter == 0 && word != ",")
				if (myData.key == "")
				{
					myData.key = word;
				}
				else
					myData.key = myData.key + " " + word;

			else if (counter == 1 && word != ",")
				myData.frequency = stoi(word);
			else if (counter == 2 && word != ";"){
				myData.index.push_back(word);
			}
			if (word == ",")
				counter++;

			if (word == ";") {
				tree.AVL_Insert(myData);
				myData.clear();
				counter = 0;
				wordCount++;
			}

		}

		cout << "Dictionary has been loaded!" << endl;
}

void dictionary::learnMultDict() {
	vector<string> vFileNames;
	vFileNames = GetFileNamesInDirectory("./filesToRead/*");
	for (size_t i = 0; i < vFileNames.size(); i++) {
		learnDict(vFileNames[i]);
	}
}

void dictionary::saveDict() {
	vector<DATA> dict;
	tree.save_dict(dict);
	string fileName;

	ofstream file;
	cout << "Enter the name for the dictionary: ";
	cin >> fileName;

	file.open(fileName);

	for (size_t i = 0; i < dict.size(); i++) {
		file << dict[i].key << " , " << dict[i].frequency << " , ";
		for (size_t j = 0; j < dict[i].index.size(); j++) {
			file << dict[i].index[j] << " ";
			if (j == dict[i].index.size() - 1)
				file << ";";
		}
		file << "\n";
	}

	file.close();
	cout << "Dictionary has been saved!" << endl;
}

string dictionary::incrString(string arg) {
	if (arg[arg.size()-1] == 'z') {
			arg = arg + "a";
	}
	else {
		arg[arg.size() - 1]++;
	}
	return arg;
}

string dictionary::trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

std::vector<std::string> dictionary::GetFileNamesInDirectory(std::string directory) {
	std::vector<std::string> files;
	WIN32_FIND_DATA fileData;
	HANDLE hFind;

	if ( !((hFind = FindFirstFile(directory.c_str(), &fileData)) == INVALID_HANDLE_VALUE) ) {
		while(FindNextFile(hFind, &fileData)) {
			if (fileData.cFileName != "..")
				files.push_back(fileData.cFileName);
		}
	}

	FindClose(hFind);
	return files;
}

bool dictionary::delDict() {
	tree.destroyTree();
	cout << "Dictionary has been deleted!" << endl;
	return true;
}

void dictionary::quicksort(DATA arr[], int l, int r)
{
    // Base case: No need to sort arrays of length <= 1
//    if (l >= r)
//    {
//        return;
//    }
//
//    // Choose pivot to be the last element in the subarray
//    int pivot = arr[r];
//
//    // Index indicating the "split" between elements smaller than pivot and
//    // elements greater than pivot
//    int cnt = l;
//
//    // Traverse through array from l to r
//    for (int i = l; i <= r; i++)
//    {
//        // If an element less than or equal to the pivot is found...
//        if (arr[i] <= pivot)
//        {
//            // Then swap arr[cnt] and arr[i] so that the smaller element arr[i]
//            // is to the left of all elements greater than pivot
////            swap(&arr[cnt], &arr[i]);
//
//            // Make sure to increment cnt so we can keep track of what to swap
//            // arr[i] with
//            cnt++;
//        }
//    }
//
//    // NOTE: cnt is currently at one plus the pivot's index
//    // (Hence, the cnt-2 when recursively sorting the left side of pivot)
//    quicksort(arr, l, cnt-2); // Recursively sort the left side of pivot
//    quicksort(arr, cnt, r);   // Recursively sort the right side of pivot
}

//int sortedArrayToBST(int arr[], int start, int end, vector<int>& result)
//{
//    /* Base Case */
//    if (start > end)
//        return NULL;
//    int rez;
//    /* Get the middle element
//       and make it root */
//    int mid = (start + end) / 2;
//    rez = arr[mid];
//    result.push_back(rez);
//    /* Recursively construct the
//       left subtree and make it
//       left child of root */
//    result.push_back(sortedArrayToBST(arr, start, mid - 1, result));
//
//    /* Recursively construct the
//       right subtree and make it
//       right child of root */
//    result.push_back(sortedArrayToBST(arr, mid + 1, end, result));
//
//    return rez;
//}


#endif
