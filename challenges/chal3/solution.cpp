#include <algorithm>		//tolower
#include <iostream>		//cin, cout, endl
#include <string>			//string
#include <unordered_map>//unordered_map
#include <utility>		//pair constructor
#include <vector>			//vector

//insert is just a convenience function.
//	Handles inserting into char_map, be it a new value or not
void insert(std::unordered_map<char, int> &char_map, char c) {
	if (char_map.find(c) != char_map.end())
		char_map[c]++;
	else
		char_map.insert(std::pair<char, int>(c, 1));
}//insert

//is_palindrome is where the determination of palindrome-ity occurs
bool is_palindrome(std::string str) {

	//Keeps the number of times a character occurs.
	std::unordered_map<char, int> char_map;

	//Buffer character to keep access to a minimum.
	char c;

	//Insert all alhabetical characters into the unordered_map
	for (int i = 0; i < str.size(); i++) {
		c = tolower(str[i]);
		if (c <= 'z' && c >= 'a')
			insert(char_map, c);
	}//for i < str.size()

	//Track the number of times a character occus an odd number of times.
	int odds = 0;

	//Count the number of times a character occus an odd number of times.
	for (std::unordered_map<char, int>::iterator it = char_map.begin(); it != char_map.end(); it++) {
		if (it->second % 2 == 1)
			odds++;
	}//for it != char_map.end();

	//If there is more than one character that occurs an odd number of times,
	//	it's not a palindrome permutation.
	if (odds > 1)
		return false;

	//Otherwise, it's a palindome permutation.
	return true;

}//is_palindrome

int main() {
	std::string str;
	//For all lines given from std::cin,
	while (std::getline(std::cin, str))
		
		//Check if palindrome permutation, and tell the user accordingly.
		if (is_palindrome(str))
			std::cout << str << " is a palindrome permutation." << std::endl;
		else
			std::cout << str << " isn't a palindrome permutation." << std::endl;
}//main
