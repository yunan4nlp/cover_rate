#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;


void load_ngram(const char* file, vector<string>& ngram);
void load_vocab(const char* file, map<string, long>& vocab);
void split_bychar(const string& str, vector<string>& vec, const char separator);
void rate(const vector<string>& ngram, const map<string, long>& vocab, long cutoff);

int main(int argc, char* argv[]) {
	if(argc > 3){
		vector<string> ngram;
		map<string, long> vocab;
		load_ngram(argv[1], ngram);
		load_vocab(argv[2], vocab);
		rate(ngram, vocab, 0);
	}
	else
		cout << "no args" << endl;
	return 0;
}

void load_ngram(const char* file, vector<string>& ngram) {
	ifstream in(file);
	if (in.is_open()) {
		string line;
		while (getline(in, line)) {
			ngram.push_back(line);
		}
		in.close();
	}
	else
		cout << "ngram file don't exist" << endl;
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

void rate(const vector<string>& ngram, const map<string, long>& vocab, long cutoff = 0) {
	int maxsize = ngram.size();
	int find_count = 0;
	for (int idx = 0; idx < maxsize; idx++) {
		 auto it = vocab.find(ngram[idx]);
		 if (it->second >= cutoff)
			 find_count++;
	}
	cout << "cutoff: " << cutoff << ", rate: " << (double)find_count / maxsize << endl;
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