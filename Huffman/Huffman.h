#pragma once

#include <string>
#include <vector>
#include <unordered_map>

// Feel free to add anything you need

struct Node
{
	char Token;
	float Frequency;

	Node* Left;
	Node* Right;
};

class Huffman
{
public:

	~Huffman();
	void DestroyTree(Node* node);

	bool GenerateTree(const std::string& inputMessage);

	void GenerateNodeList(const std::string& message);
	std::pair<Node*, Node*> GetLowestNode();

	std::string Encode(const std::string& message) const;

	std::string Decode(const std::string& encodedMessage) const;

private:
	Node* RootNode;

	std::unordered_map<char, std::string> codeTable;
	void GenerateCodes(const Node* node, const std::string& prefix);
	std::vector<Node*> nodeList;
};