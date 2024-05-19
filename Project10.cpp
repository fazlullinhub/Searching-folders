#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

using namespace std;

void searchAndReplace(const string& folderPath, const string& searchWord, const string& replaceWord, bool removeWord) {
	int matches = 0;
	for (const auto& entry : filesystem::recursive_directory_iterator(folderPath)) {
		if (!entry.is_regular_file()) {
			continue;
		}

		string filePath = entry.path().string();

		ifstream inputFile(filePath);
		ofstream outputFile(filePath + ".tmp");

		string line;
		while (getline(inputFile, line)) {
			size_t pos = line.find(searchWord);
			if (pos != string::npos) {
				matches++;
				if (removeWord) {
					line.erase(pos, searchWord.length());
				}
				else {
					line.replace(pos, searchWord.length(), replaceWord);
				}
			}
			outputFile << line << endl;
		}

		inputFile.close();
		outputFile.close();

		filesystem::rename(filePath + ".tmp", filePath);
	}

	if (matches == 0) {
		cout << "No matches found" << endl;
	}
	else {
		cout << "Total matches found" << matches << endl;
	}
}

int main() {
	string folderPath, searchWord, replaceWord;
	bool removeWord = false;

	cout << "Enter way to path: ";
	getline(cin, folderPath);

	cout << "Enter word for search: ";
	getline(cin, searchWord);

	cout << "Do you want to delete word you're looking for? (y/n): ";
	char choice;
	cin >> choice;

	if (choice == 'y' || choice == 'Y') {
		removeWord = true;
	}
	else {
		cout << "Enter word for replacement: ";
		cin >> replaceWord;
	}

	searchAndReplace(folderPath, searchWord, replaceWord, removeWord);

	return 0;
}