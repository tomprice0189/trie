

#include <iostream>
#include <iterator>

#include "trie.h"

int main() {
	Trie trie;

	trie.addWord("burnley");
	trie.addWord("dog");
	trie.addWord("cat");
	trie.addWord("catalyst");
	trie.addWord("canatalever");
	trie.addWord("crucifix");
	trie.addWord("frederick");
	trie.addWord("freedom");

	/*
	std::cout << "Does cat exist: " << std::boolalpha << trie.isWordPresent("cat") << "\n";
	std::cout << "Does cata exist: " << std::boolalpha << trie.isWordPresent("cata") << "\n";
	std::cout << "Does catalyst exist: " << std::boolalpha << trie.isWordPresent("catalyst") << "\n";
	*/

	while (true) {
		std::string prefix;
		std::cout << "#############################\nEnter your prefix to see if in dictionary: \n";
		std::getline(std::cin, prefix);
		if (prefix == "quit") {
			break;
		}

		auto prefixes(trie.getPrefixes(prefix));
		std::cout << "Found " << prefixes.size() << " potential matches in the dictionary:\n\n";
		std::copy(prefixes.begin(), prefixes.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
		std::cout << "\n";
	}
	return 0;
}