#pragma once
#include <iostream>
#include <string> 

using namespace std;

typedef string ItemType;

struct WordNode
{
	ItemType m_data; 
	int count;
	WordNode *m_left;
	WordNode *m_right;
	//Constructor
	WordNode(ItemType w) :m_data(w), count(1), m_left(nullptr), m_right(nullptr) {}
};

class WordTree
{
private:
	WordNode *root;

	//Private helper functions
	void addNodePrivate(WordNode*, ItemType);
	const void printTreePrivate(WordNode*, ostream&) const;
	unsigned int getTotal(WordNode*, unsigned int)const;
	const void printTree(ostream&) const;
	void deleteTree(WordNode*);
	WordNode* createNode(ItemType);

public:
	// Default constructor 
	WordTree() : root(nullptr) { };

	// Destroys all the dynamically allocated memory
	// in the tree
	~WordTree();

	// copy constructor 
	WordTree(const WordTree& rhs);
	void copyTree(WordNode*&, const WordNode*);
	// assignment operator
	const WordTree& operator=(const WordTree& rhs);

	// Adds the given word to the tree if it is not
	// already in the tree OR increments the appropriate
	// counter if it is already there 
	void add(ItemType);

	// Returns the number of distinct words / nodes 
	unsigned int distinctWords() const;
	unsigned int CountNodes(WordNode*) const;

	// Returns the total number of words inserted,
	// including duplicate values 
	unsigned int totalWords() const;

	// Prints the words of the tree in alphabetical order,
	// and next to each word, the number of times each
	// word occurs in the text
	friend ostream& operator<<(ostream&, const WordTree& );
};
