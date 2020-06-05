#ifndef DATA_H_
#define DATA_H_

#include <String>
#include <vector>

using namespace std;

struct DATA {
	string key;
	int frequency =1;
	vector<string> index;

	DATA() {};
	DATA(string k) {
		key = k;
		frequency = 1;
	}

	DATA (string k, string fName) {
		key = k;
		index.push_back(fName);
	}

	void clear() {
		key = "";
		frequency = 1;
		index.clear();
	}

	bool operator<(const DATA& right) const {
		return frequency < right.frequency;
	}

	bool operator==(const DATA&right) const {
		return key == right.key;
	}
};

#endif
