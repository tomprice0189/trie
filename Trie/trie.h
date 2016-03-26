#include <memory>
#include <string>
#include <unordered_map>

class Trie {

public:
	struct Node {
		using NodeMap = std::unordered_map <char, std::unique_ptr<Node>>;
		NodeMap node_map_;
		bool is_word;
		Node() : is_word(false) {}
	};

	Trie() : topNode(std::make_unique<Node>()) {}

	void addWord(const std::string& word) {
		auto currentNode = topNode.get();
		for (auto ch : word) {
			auto foundChar = currentNode->node_map_.find(ch);
			if (foundChar == currentNode->node_map_.end()) {
				auto insertRes = currentNode->node_map_.insert(
					std::make_pair(ch, std::make_unique<Node>()));
				if (!insertRes.second) {
					throw std::runtime_error("Could not add a new node");
				}
				else {
					currentNode = insertRes.first->second.get();
				}
			}
			else {
				currentNode = foundChar->second.get();
			}
		}
		currentNode->is_word = true;
	}

	bool isWordPresent(const std::string& word) {
		auto currentNode = topNode.get();
		for (auto ch : word) {
			auto foundChar = currentNode->node_map_.find(ch);
			if (foundChar == currentNode->node_map_.end()) {
				return false;
			}
			currentNode = foundChar->second.get();				
		}
		return currentNode->is_word;
	}

	using Words = std::vector<std::string>;

	Words prefixRecurse(Node* node, const std::string& word) {
		Words words;
		for (const auto&  ch : node->node_map_) {
			if (ch.second->is_word) {
				words.push_back(std::string(word) + ch.first);
			}			
			auto moreWords = prefixRecurse(ch.second.get(), std::string(word) + ch.first);
			words.insert(words.end(), moreWords.begin(), moreWords.end());
		}
		return words;
	}

	auto getPrefixes(const std::string& prefix) {		
		Words words;
		auto currentNode = topNode.get();
		for (auto ch : prefix) {
			auto foundChar = currentNode->node_map_.find(ch);
			if (foundChar == currentNode->node_map_.end()) {
				return words;
			}
			currentNode = foundChar->second.get();
		}

		if (currentNode->is_word) {
			words.push_back(prefix);
		}
		
		auto moreWords(prefixRecurse(currentNode, prefix));
		words.insert(words.end(), moreWords.begin(), moreWords.end());
		return words;
	}

private:
	std::unique_ptr<Node> topNode;
	
};