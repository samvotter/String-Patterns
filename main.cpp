#include <iostream>
#include <time.h>
#include <vector>
#include <regex>
using namespace std;

// generates a random character, either a-z or 0-9
char randomChar(bool digit = false) {
	if (!digit)
		return rand() % 26 + 97;
	else
		return rand() % 10 + 48;
}

// generates a random string of length "size" and either alpha or numeric
string randomString(int size, bool digit = false) {
	string random = "";
	for (int i = 0; i < size; i++) {
		random += randomChar(digit);
	}
	return random;
}
// returns true if a char is [0,2,4,6,8] else false
bool is_even(char digit) {
	digit = digit - '0';
	return digit % 2;
}

// manually pattern matching for a repeating series of "(10)*"
string read_one_zero(string base) {
	string temp = "";
	bool con = false;
	bool last_was;
	int i = 0;
	if (is_even(base[i])) {
		temp += base[i];
		last_was = true;
		con = true;
		i++;
	}
	else {
		return temp;
	}
	while (con && (i < base.length())) {
		if (is_even(base[i])) {
			if (last_was) {
				return temp;
			}
			else {
				temp += base[i];
				last_was = true;
				con = true;
				i++;
			}
		}
		else {
			if (last_was) {
				temp += base[i];
				last_was = false;
				con = true;
				i++;
			}
			else {
				return temp;
			}
		}
	}
	return temp;
}

// finds the average value of a vector of ints
double vector_avg(vector<int> scores) {
	double total = 0;
	double size = scores.size();
	for (int i = 0; i < size; i++) {
		total += scores[i];
	}
	return total / size;
}

// applies the manual pattern matching algoirthm to a given string
vector <string> largest_substring(string base) {
	vector<string> valid_substrings;
	int index = 0;
	int increment = 0;
	int base_size = base.length();
	do {
		string temp = "";
		temp += read_one_zero(base.substr(index));
		increment = temp.length();
		if (increment) {
			valid_substrings.push_back(temp);
			index += increment;
		}
		else {
			index++;
		}
	} while (index < base_size);
	return valid_substrings;
}


// insures validation parameters are correct
bool checkParameters(
	int times,
	int string_size
) {
	if (times <= 0) {
		cout << "Invalid times parameter. Must be a positive integer, got: " << times << endl;
		return false;
	}

	if (string_size <= 0) {
		cout << "Invalid times parameter. Must be a positive integer, got :" << string_size << endl;
		return false;
	}
	return true;
}


// scores the result for largest substring
int getScore(vector<string> results) {
	if (results.empty()) {
		cout << "There were no even-odd alternating substrings. " << endl;
		return 0;
	}
	string biggest = "";
	for (int i = 0; i < results.size(); ++i) {
		if (results[i].length() > biggest.length()) {
			biggest = results[i];
		}
	}
	cout << "The largest: " << biggest << "\t which has a length of: " << biggest.length() << endl;
	return biggest.length();
}


// a Monte Carlo style test-validation to ensure results are within expected ranges
void monte_validation(
	vector<string> func(string val),
	int times = 100,
	int string_size = 10,
	bool digit = true
) {
	if (!checkParameters(times, string_size)) {
		return;
	}

	vector <int> scores;

	do {
		string test_string = randomString(string_size, digit);
		cout << "String being tested:\t" << test_string << endl;

		vector <string> results = func(test_string);

		int score = getScore(results);
		scores.push_back(score);
		times--;
	} while (times > 0);

	cout << "Average score: " << vector_avg(scores) << endl;
}

// regex solution
vector<string> reg_solution(
	string base
) {
	vector<string> x;
	smatch matches;
	regex reg("(([02468][13579])+)");

	while (regex_search(base, matches, reg)) {
		x.push_back(matches.str(1));
		base = matches.suffix().str();
	}
	return x;
}


int main() {
	cout << "The goal of this algorithm is to identify the largest alternating even-odd substrings within a given string." << endl;

	srand(time(NULL));

	int number_of_tests = 200;
	int size_of_strings = 20;
	bool digit = true;

	/*
	possible solutions are regolution or largest_substring
	*/

	monte_validation(reg_solution, number_of_tests, size_of_strings, digit);

	return 0;
}