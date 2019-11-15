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
	if (digit % 2)
		return false;
	return true;
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

// a Monte Carlo style test-validation to ensure results are within expected ranges
void monte_validation(
	vector<string> func(string val),
	int times = 100,
	int string_size = 10,
	bool digit = 1
	) {
	vector <int> scores;

	do {
		string test_string = randomString(string_size, digit);
		std::cout << "String being tested:\t" << test_string << std::endl;

		vector <string> results = func(test_string);

		string biggest = "";
		for (int i = 0; i < results.size(); ++i) {
			if (results[i].length() > biggest.length()) {
				biggest = results[i];
			}
		}

		cout << "The largest: " << biggest << "\t which is: " << biggest.length() << endl;
		scores.push_back(biggest.length());
		times--;
	} while (times > 0);

	cout << "Average score: " << vector_avg(scores) << endl;
}

// regex solution
vector<string> reg_solution(
	string base
) {
	vector<string> x;
	std::smatch matches;
	std::regex reg("(([02468][13579])+)");

	while (std::regex_search(base, matches, reg)) {
		x.push_back(matches.str(1));
		base = matches.suffix().str();
	}
	return x;
}


int main() {
	srand(time(NULL));

	monte_validation(reg_solution);

	return 0;
}