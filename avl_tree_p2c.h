// William Yang
// Class AvlTree is a template container.
// Modified AvlTree class.
// Double rotation no longer calls 2 single rotation functions.

#ifndef AVL_TREE_P2C_H
#define AVL_TREE_P2C_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// Comparable getElement( x )			--> Return element x
// size_t numberOfNodes( )			--> Return number of nodes
// size_t internalPathLength( )			--> Return internal path length
// float averageDepth( )			--> Return average depth
// bool find( x )				--> Return true if x is found
// size_t getTotalRecursionCalls( )		--> Return total recursion calls for functions: find(), remove(), and findMin()
// void resetRecursionCounter( )		--> Reset total recursion calls counter to 0
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
public:
	/**
	 * Zero-parameter constructor.
	 */
	AvlTree() : root{ nullptr }
	{ }

	/**
	 * Copy constructor.
	 */
	AvlTree(const AvlTree& rhs) : root{ nullptr }
	{
		root = clone(rhs.root);
	}

	/**
	 * Move constructor.
	 */
	AvlTree(AvlTree&& rhs) : root{ rhs.root }
	{
		rhs.root = nullptr;
	}

	/**
	 * Destructor.
	 */
	~AvlTree()
	{
		makeEmpty();
	}

	/**
	 * Deep copy.
	 */
	AvlTree& operator=(const AvlTree& rhs)
	{
		AvlTree copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	/**
	 * Move.
	 */
	AvlTree& operator=(AvlTree&& rhs)
	{
		std::swap(root, rhs.root);

		return *this;
	}

	/**
	 * Find the smallest item in the tree.
	 * Throw UnderflowException if empty.
	 */
	const Comparable& findMin()
	{
		if (isEmpty())
			throw UnderflowException{ };
		return findMin(root)->element;
	}

	/**
	 * Find the largest item in the tree.
	 * Throw UnderflowException if empty.
	 */
	const Comparable& findMax()
	{
		if (isEmpty())
			throw UnderflowException{ };
		return findMax(root)->element;
	}

	/**
	 * Returns true if x is found in the tree.
	 */
	bool contains(const Comparable& x) const
	{
		return contains(x, root);
	}

	/**
	 * Test if the tree is logically empty.
	 * Return true if empty, false otherwise.
	 */
	bool isEmpty() const
	{
		return root == nullptr;
	}

	/**
	 * Print the tree contents in sorted order.
	 */
	void printTree() const
	{
		if (isEmpty())
			cout << "Empty tree" << endl;
		else
			printTree(root);
	}

	/**
	 * Make the tree logically empty.
	 */
	void makeEmpty()
	{
		makeEmpty(root);
	}

	/**
	 * Insert x into the tree; duplicates are ignored.
	 */
	void insert(const Comparable& x)
	{
		insert(x, root);
	}

	/**
	 * Insert x into the tree; duplicates are ignored.
	 */
	void insert(Comparable&& x)
	{
		insert(std::move(x), root);
	}

	/**
	 * Remove x from the tree. Return true if successful; else false.
	 */
	bool remove(const Comparable& x)
	{
		return remove(x, root);
	}

	/**
	 * Return x by reference from the tree.
	 * x can be mutated.
	 * Assumes contains functioned was utilized prior to use and that x exists.
	 */
	Comparable& getElement(const Comparable& x) const
	{
		return getElement(x, root);
	}

	/**
	 * Returns the number of nodes currently in the tree.
	 */
	size_t numberOfNodes() const
	{
		return numberOfNodes(root);
	}

	/**
	 * Returns the internal path length.
	 */
	size_t internalPathLength() const
	{
		return internalPathLength(root);
	}

	/**
	 * Returns the calculated average depth.
	 */
	float averageDepth() const
	{
		size_t number_of_nodes = numberOfNodes(root);
		if (number_of_nodes == 0)
			return 0;
		return (float)internalPathLength(root) / numberOfNodes(root);
	}

	/**
	 * Return true if x is found; else false.
	 */
	bool find(const Comparable& x)
	{
		return find(x, root);
	}

	/**
	 * Return total number of recursion calls of function: find(), findMin(), and remove().
	 */
	size_t getTotalRecursionCalls() const
	{
		return recursion_counter;
	}

	/**
	 * Reset total recursion calls.
	 */
	void resetRecursionCounter()
	{
		recursion_counter = 0;
	}

private:
	// Node class.
	struct AvlNode
	{
		Comparable element;
		AvlNode* left;
		AvlNode* right;
		int       height;

		AvlNode(const Comparable& ele, AvlNode* lt, AvlNode* rt, int h = 0)
			: element{ ele }, left{ lt }, right{ rt }, height{ h } { }

		AvlNode(Comparable&& ele, AvlNode* lt, AvlNode* rt, int h = 0)
			: element{ std::move(ele) }, left{ lt }, right{ rt }, height{ h } { }
	};

	// Root of tree.
	AvlNode* root;
	// Recursion counter.
	size_t recursion_counter = 0;

	/**
	 * Internal method to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void insert(const Comparable& x, AvlNode*& t)
	{
		if (t == nullptr)
			t = new AvlNode{ x, nullptr, nullptr };
		else if (x < t->element)
			insert(x, t->left);
		else if (t->element < x)
			insert(x, t->right);
		else
			t->element.Merge(x);

		balance(t);
	}

	/**
	 * Internal method to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void insert(Comparable&& x, AvlNode*& t)
	{
		if (t == nullptr)
			t = new AvlNode{ std::move(x), nullptr, nullptr };
		else if (x < t->element)
			insert(std::move(x), t->left);
		else if (t->element < x)
			insert(std::move(x), t->right);
		else
			t->element.Merge(std::move(x));

		balance(t);
	}

	/**
	 * Internal method to remove from a subtree.
	 * x is the item to remove.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 * Return true if removed; else false.
	 * Recursive remove() calls and findMin() calls are counted towards recursion counter.
	 */
	bool remove(const Comparable& x, AvlNode*& t)
	{
		if (t == nullptr)
			return false;   // Item not found; do nothing

		bool removed = false;

		if (x < t->element)
		{
			removed = remove(x, t->left);
			if (removed)
				recursion_counter++;
		}
		else if (t->element < x)
		{
			removed = remove(x, t->right);
			if (removed)
				recursion_counter++;
		}
		else if (t->left != nullptr && t->right != nullptr) // Two children
		{
			recursion_counter += 2;
			t->element = findMin(t->right)->element;
			removed = remove(t->element, t->right);
		}
		else
		{
			AvlNode* oldNode = t;
			t = (t->left != nullptr) ? t->left : t->right;
			delete oldNode;
			removed = true;
		}

		balance(t);
		return removed;
	}

	static const int ALLOWED_IMBALANCE = 1;

	// Assume t is balanced or within one of being balanced
	void balance(AvlNode*& t)
	{
		if (t == nullptr)
			return;

		if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) {
			if (height(t->left->left) >= height(t->left->right))
				rotateWithLeftChild(t);
			else
				doubleWithLeftChild(t);
		}
		else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) {
			if (height(t->right->right) >= height(t->right->left))
				rotateWithRightChild(t);
			else
				doubleWithRightChild(t);
		}
		t->height = max(height(t->left), height(t->right)) + 1;
	}

	/**
	 * Internal method to find the smallest item in a subtree t.
	 * Return node containing the smallest item.
	 * Counts recursive calls of findMin() towards recursion counter.
	 */
	AvlNode* findMin(AvlNode* t)
	{
		if (t == nullptr)
			return nullptr;
		if (t->left == nullptr)
			return t;
		recursion_counter++;
		return findMin(t->left);
	}

	/**
	 * Internal method to find the largest item in a subtree t.
	 * Return node containing the largest item.
	 */
	AvlNode* findMax(AvlNode* t)
	{
		if (t != nullptr)
			while (t->right != nullptr)
				t = t->right;
		return t;
	}

	/**
	 * Internal method to test if an item is in a subtree.
	 * x is item to search for.
	 * t is the node that roots the tree.
	 */
	bool contains(const Comparable& x, AvlNode* t) const
	{
		if (t == nullptr)
			return false;
		else if (x < t->element)
			return contains(x, t->left);
		else if (t->element < x)
			return contains(x, t->right);
		else
			return true;    // Match
	}
	/****** NONRECURSIVE VERSION*************************
		bool contains( const Comparable & x, AvlNode *t ) const
		{
			while( t != nullptr )
				if( x < t->element )
					t = t->left;
				else if( t->element < x )
					t = t->right;
				else
					return true;    // Match
			return false;   // No match
		}
	*****************************************************/

	/**
	 * Internal method to make subtree empty.
	 */
	void makeEmpty(AvlNode*& t)
	{
		if (t != nullptr)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	}

	/**
	 * Internal method to print a subtree rooted at t in sorted order.
	 */
	void printTree(AvlNode* t) const
	{
		if (t != nullptr)
		{
			printTree(t->left);
			cout << t->element << endl;
			printTree(t->right);
		}
	}

	/**
	 * Internal method to clone subtree.
	 */
	AvlNode* clone(AvlNode* t) const
	{
		if (t == nullptr)
			return nullptr;
		else
			return new AvlNode{ t->element, clone(t->left), clone(t->right), t->height };
	}

	// Avl manipulations
	/**
	 * Return the height of node t or -1 if nullptr.
	 */
	int height(AvlNode* t) const
	{
		return t == nullptr ? -1 : t->height;
	}

	/**
	 * Return the larger integer.
	 */
	int max(int lhs, int rhs) const
	{
		return lhs > rhs ? lhs : rhs;
	}

	/**
	 * Rotate binary tree node with left child.
	 * For AVL trees, this is a single rotation for case 1.
	 * Update heights, then set new root.
	 */
	void rotateWithLeftChild(AvlNode*& k2)
	{
		AvlNode* k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), k2->height) + 1;
		k2 = k1;
	}

	/**
	 * Rotate binary tree node with right child.
	 * For AVL trees, this is a single rotation for case 4.
	 * Update heights, then set new root.
	 */
	void rotateWithRightChild(AvlNode*& k1)
	{
		AvlNode* k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1->height = max(height(k1->left), height(k1->right)) + 1;
		k2->height = max(height(k2->right), k1->height) + 1;
		k1 = k2;
	}

	/**
	 * (MODIFIED)
	 * Double rotate binary tree node: first left child.
	 * with its right child; then node k3 with new left child.
	 * For AVL trees, this is a double rotation for case 2.
	 * Update heights, then set new root.
	 */
	void doubleWithLeftChild(AvlNode*& k3)
	{
		AvlNode* k1 = k3->left;
		AvlNode* k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k3->left = k2->right;
		k2->right = k3;
		k1->height = max(height(k1->left), height(k1->right)) + 1;
		k3->height = max(height(k3->left), height(k3->right)) + 1;
		k2->height = max(k1->height, k3->height) + 1;
		k3 = k2;
	}

	/**
	 * (MODIFIED)
	 * Double rotate binary tree node: first right child.
	 * with its left child; then node k1 with new right child.
	 * For AVL trees, this is a double rotation for case 3.
	 * Update heights, then set new root.
	 */
	void doubleWithRightChild(AvlNode*& k1)
	{
		AvlNode* k3 = k1->right;
		AvlNode* k2 = k3->left;
		k3->left = k2->right;
		k2->right = k3;
		k1->right = k2->left;
		k2->left = k1;
		k1->height = max(height(k1->left), height(k1->right)) + 1;
		k3->height = max(height(k3->left), height(k3->right)) + 1;
		k2->height = max(k1->height, k3->height) + 1;
		k1 = k2;
	}

	// End of avl manipulations

	/*
	 * Internal method to get x.
	 * Assumes element exists and that the contains functioned was utilized beforehand.
	 * If x is not found, throw an exception.
	 */
	Comparable& getElement(const Comparable& x, AvlNode* t) const
	{
		if (t == nullptr)
			throw ArrayIndexOutOfBoundsException{ };
		else if (x < t->element)
			return getElement(x, t->left);
		else if (t->element < x)
			return getElement(x, t->right);
		else
			return t->element;
	}

	/*
	 * Internal method to calculate the number of nodes.
	 * Return number of nodes in tree.
	 */
	size_t numberOfNodes(AvlNode* t) const
	{
		if (t == nullptr)
			return 0;
		size_t left_nodes = numberOfNodes(t->left);
		size_t right_nodes = numberOfNodes(t->right);
		return left_nodes + right_nodes + 1;
	}

	/*
	 * Internal method to calculate the internal path length.
	 * Return internal path length.
	 */
	size_t internalPathLength(AvlNode* t) const
	{
		if (t == nullptr)
			return 0;
		return internalPathLength(t->left) + internalPathLength(t->right) + numberOfNodes(t) - 1;
	}

	/*
	 * Internal method to find x.
	 * Returns true if found; else false.
	 * Counts recursive calls of find() towards recursion counter.
	 */
	bool find(const Comparable& x, AvlNode* t)
	{
		if (t == nullptr)
			return false;	// Not found
		else if (x < t->element)
		{
			recursion_counter++;
			return find(x, t->left);
		}
		else if (t->element < x)
		{
			recursion_counter++;
			return find(x, t->right);
		}
		else
			return true;	// Found
	}
};

#endif
