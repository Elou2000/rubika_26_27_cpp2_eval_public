#include "Huffman.h"
#include <iostream>


Huffman::~Huffman()
{
	DestroyTree(RootNode);
}

void Huffman::DestroyTree(Node* node)
{
	if (node == nullptr) return;

	DestroyTree(node->Left);
	DestroyTree(node->Right);

	delete(node);
}

bool Huffman::GenerateTree(const std::string& inputMessage)
{
	if (inputMessage.size() < 2) return false;
	
	GenerateNodeList(inputMessage);

	while (nodeList.size() >= 2)
	{
	
		auto values = GetLowestNode();

		Node* parentNode = new Node();
		parentNode->Frequency = values.first->Frequency + values.second->Frequency;
		parentNode->Left = values.first;
		parentNode->Right = values.second;

		nodeList.erase(std::remove(nodeList.begin(), nodeList.end(), values.first), nodeList.end());
		nodeList.erase(std::remove(nodeList.begin(), nodeList.end(), values.second), nodeList.end());
		nodeList.push_back(parentNode);

	}

	RootNode = nodeList[0];
	GenerateCodes(RootNode, "");
	return true;


}

void Huffman::GenerateNodeList(const std::string& message)
{
	std::unordered_map<char, int> charFrequency;
	nodeList.clear();

	for (auto charToken : message)
	{
		if (charFrequency.find(charToken) != charFrequency.end())
		{
			charFrequency[charToken]++;
		}
		else
		{
			charFrequency[charToken] = 1;
		}
	}

	for(auto& value : charFrequency)
	{
		Node*  newNode = new Node();
		newNode->Token = value.first;
		newNode->Frequency = (float)value.second / (float)message.size();

		nodeList.push_back(newNode);
	}

}

std::pair<Node*, Node*> Huffman::GetLowestNode()
{
	Node* lowest = nullptr;
	Node* secondLowest = nullptr;
	
	for (Node* node : nodeList)
	{
		if (lowest == nullptr || node->Frequency < lowest->Frequency)
		{
			secondLowest = lowest;
			lowest = node;
		}
		else if (secondLowest == nullptr || node->Frequency < secondLowest->Frequency)
		{
			secondLowest = node;
		}
	}

	return { lowest, secondLowest };
}

std::string Huffman::Encode(const std::string& message) const
{
	std::string returnString = "";

	for (auto charMessage : message)
	{
		auto it = codeTable.find(charMessage);
		if (it == codeTable.end()) continue;
		returnString += it->second;
	}

	return returnString;
}

std::string Huffman::Decode(const std::string& encodedMessage) const
{
	std::string returnString = "";
	if (RootNode == nullptr) return std::string();

	Node* currentNode = RootNode;
	
	if (currentNode->Left == nullptr && currentNode->Right == nullptr)
	{
		returnString += currentNode->Token;
		return returnString;
	}

	for (char currentChar : encodedMessage)
	{
		currentNode = (currentChar == '0') ? currentNode->Left : currentNode->Right;
		
		if (currentNode->Left == nullptr && currentNode->Right == nullptr)
		{
			returnString += currentNode->Token;
			currentNode = RootNode;
		}
	}
	
	return returnString;
}

void Huffman::GenerateCodes(const Node* node, const std::string& prefix)
{
	if (node == nullptr) return;

	if (node->Left == nullptr && node->Right == nullptr)
	{
		codeTable[node->Token] = prefix.empty() ? "0" : prefix;
	}

	GenerateCodes(node->Left, prefix + "0");
	GenerateCodes(node->Right, prefix + "1");

}


