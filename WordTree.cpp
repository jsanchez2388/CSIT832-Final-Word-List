#include "wordtree.h"

WordTree::WordTree(const WordTree & rhs)
{
	copyTree(root, rhs.root); //Call helper function to copy the tree
}

void WordTree::copyTree(WordNode*& copy, const WordNode* og)
{
	if (og == nullptr) //if root of original tree is null
	{
		copy = nullptr;	//set root of new tree to null
	}
	else
	{
		copy = new WordNode(og->m_data);	//Create new WordNode and copy data
		copy->count = og->count;	//Copy Count
		if (og->m_left != nullptr)
		{
			copyTree(copy->m_left, og->m_left);	//Recursive call for left pointer

		}
		if (og->m_right != nullptr)
		{
			copyTree(copy->m_right, og->m_right); //Recursive call for right pointer
		}
	}
}

const WordTree& WordTree::operator=(const WordTree & rhs)
{
	if (&rhs == this) //if right and left side are equal
	{
		return *this;
	}
	deleteTree(root); //Delete the tree
	copyTree(root, rhs.root); //Copy new values
	return *this;
}

void WordTree::add(ItemType v)
{
	addNodePrivate(root, v); //Call helper function
}

void WordTree::addNodePrivate(WordNode* r, ItemType v)
{
	if (root == nullptr)	//If tree is empty
	{
		root = createNode(v); //Create a new node and point root to it
	}
	else if (v.compare(r->m_data) < 0)	//If tree not empty, and value passed is less than value of node
	{
		if (r->m_left != nullptr)	//If there is a left node 
		{
			addNodePrivate(r->m_left, v);	//Recursive call to function, passing same value and left pointer 
		}
		else
		{
			r->m_left = createNode(v);	//If there is not a left node, create one
		}
	}
	else if (v.compare(r->m_data) > 0)	//If tree not empty, and value pass is greater than value of node
	{
		if (r->m_right != nullptr)	//If there is a right node
		{
			addNodePrivate(r->m_right, v);	//Recurvise vall to function, passing same value and right pointer
		}
		else
		{
			r->m_right = createNode(v);	//If there is not a right node, create one
		}
	}
	else	//If value passed is equal to value of node, update count
	{
		r->count += 1;
	}
}

WordNode * WordTree::createNode(ItemType v)
{
	WordNode* temp = new WordNode(v);
	return temp;
}

unsigned int WordTree::CountNodes(WordNode* r) const
{
	//Pre-order traversal to count nodes
	unsigned int count = 1; 
	if (r->m_left != nullptr) {
		count += CountNodes(r->m_left);
	}
	if (r->m_right != nullptr) {
		count += CountNodes(r->m_right);
	}
	return count;
}

unsigned int WordTree::distinctWords() const
{
	if (root == nullptr)
	{
		return 0;	//If root is null, tree is empty. 
	}
	return CountNodes(root); //Call helper function and return value
}


unsigned int WordTree::totalWords() const
{
	unsigned int tCount = 0;	//Variable used to store count
	return getTotal(root, tCount);	//Call helper function and return value
}

unsigned int WordTree::getTotal(WordNode* r, unsigned int c) const
{
	//Pre-order traversal to add up total words
	if (r == nullptr)
	{
		return 0;
	}
	c = r->count;
	if (r->m_left != nullptr) {
		c += getTotal(r->m_left, c);
	}
	if (r->m_right != nullptr) {
		c += getTotal(r->m_right, c);
	}
	return c;
}

ostream & operator<<(ostream & out, const WordTree & rhs)
{
	rhs.printTree(out);	//Call helper function
	return out;
}

const void WordTree::printTree(ostream& outFile) const
{
	printTreePrivate(root, outFile); //Call private helper function
}

const void WordTree::printTreePrivate(WordNode* r, ostream& out) const
{
	if (r != nullptr)	//If node not null
	{
		if (r->m_left != nullptr)	//If left node not null
		{
			printTreePrivate(r->m_left, out);	//Recursive call to print out left node
		}
		out << r->m_data << " " << r->count << " ";	//print out node value
		if (r->m_right != nullptr)	//If right node not null
		{
			printTreePrivate(r->m_right, out);	//Recursive call to print out left node
		}
	}
}

WordTree::~WordTree()
{
	deleteTree(root); //Call helper function
}

void WordTree::deleteTree(WordNode *r)
{
	//Post-Order traversal to delete tree
	if (r == nullptr)	//If tree is empty just return
	{
		return;
	}
	deleteTree(r->m_left);	//Recursive call to delete left node 
	deleteTree(r->m_right);	//Recursive call to delete right node
	delete r;	//Delete node
}