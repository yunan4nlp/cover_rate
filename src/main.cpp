#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;


void load_vocab(const char* file, map<string, long>& vocab);
void split_bychar(const string& str, vector<string>& vec, const char separator);
void rate(const map<string, long>& ngram, const map<string, long>& vocab, long cutoff);

int main(int argc, char* argv[]) {
	if (argc >= 3) {
		map<string, long> ngram;
		map<string, long> vocab;
		cout << "load ngram..." << endl;
		load_vocab(argv[1], ngram);
		cout << "load ngram ok" << endl;
		cout << "load vocab...." << endl;
		load_vocab(argv[2], vocab);
		cout << "load vocab ok" << endl;
		for (int idx = 0; idx < 100; idx++)
			rate(ngram, vocab, idx);
	}
	else
		cout << "no args" << endl;
	return 0;
}

void load_vocab(const char* file, map<string, long>& vocab) {
	ifstream in(file);
	if (in.is_open()) {
		string line;
		vector<string> info;
		long count;
		while (getline(in, line)) {
			split_bychar(line, info, ' ');
			count = atol(info[1].c_str());
			vocab[info[0]] = count;
		}
		in.close();
	}
	else
		cout << "vocab file don't exist" << endl;
}

void rate(const map<string, long>& ngram, const map<string, long>& vocab, long cutoff) {
	long all_count = 0;
	long find_count = 0;
	for (auto ngramit = ngram.begin(); ngramit != ngram.end(); ngramit++) {
		auto it = vocab.find(ngramit->first);
		if (it != vocab.end() && it->second >= cutoff)
			find_count += ngramit->second;
		all_count += ngramit->second;
	}
	cout << "find_count: " << find_count << ", all_count: " << all_count << endl;
	cout << "cutoff: " << cutoff << ", rate: " << (double)find_count / all_count << endl;
}

void split_bychar(const string& str, vector<string>& vec, const char separator = ' ') {
	//assert(vec.empty());
	vec.clear();
	string::size_type pos1 = 0, pos2 = 0;
	string word;
	while ((pos2 = str.find_first_of(separator, pos1)) != string::npos) {
		word = str.substr(pos1, pos2 - pos1);
		pos1 = pos2 + 1;
		if (!word.empty())
			vec.push_back(word);
	}
	word = str.substr(pos1);
	if (!word.empty())
		vec.push_back(word);
}