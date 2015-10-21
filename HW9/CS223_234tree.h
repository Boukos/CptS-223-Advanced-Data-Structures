#pragma once
// Eric Chen 11381898

// Implement this class in this header file

#include <iostream>
#include <queue>
#include <stack>

using namespace std;

// Notes about template object:
// Whatever object is used as the template type for this class must implement the following:
// - Copy constructor
// - int GetKey() function
// - string ToString() function

template <typename T>
class CS223_234Tree
{
private:
	struct Node
	{
		// A, B and C are the actual data values in the node		
		T* A;
		T* B;
		T* C;

		// Child pointers
		Node *L, *M1, *M2, *R;

		// Constructor to initialize the node with one value. The other two value 
		// pointers will be set to null and all child pointers will be set to null. 
		// The pointer given as the parameter is directly copied to A.
		Node(T* valueForA)
		{
			A = valueForA;
			B = C = NULL;
			L = M1 = M2 = R = NULL;
		}

		// Constructor to initialize the node with one value and two child pointers.
		Node(T* valueForA, Node* leftChildOfA, Node* rightChildOfA)
		{
			A = valueForA;
			L = leftChildOfA;
			M1 = rightChildOfA;

			// Everything else is NULL
			B = C = NULL;
			M2 = R = NULL;
		}

		Node(T* aVal, T* bVal, T* cVal, Node* left, Node* m1, Node* m2, Node* right)
		{
			A = aVal;
			B = bVal;
			C = cVal;
			L = left;
			M1 = m1;
			M2 = m2;
			R = right;
		}

		bool ContainsKey(int key)
		{
			if (C && C->GetKey() == key) { return true; }
			if (B && B->GetKey() == key) { return true; }
			if (A->GetKey() == key) { return true; }
			return false;
		}

		void DeleteData()
		{
			if (A) { delete A; A = NULL; }
			if (B) { delete B; B = NULL; }
			if (C) { delete C; C = NULL; }
		}

		// Returns true if all three data-value pointers, A, B, and C, are non-null, 
		// false otherwise.
		bool IsFull()
		{
			return (A != NULL && B != NULL && C != NULL);
		}

		// Returns true if all 4 child pointers are null, implying that the node is a leaf
		bool IsLeaf()
		{
			return (NULL == L && NULL == M1 && NULL == M2 && NULL == R);
		}

		// Returns object with greatest key value within node
		T* GetGreatest()
		{
			if (C)
			{
				return C;
			}
			else if (B)
			{
				return B;
			}
			// else case would be a lonely node
		}

		T* GetLeast()
		{
			return A;
		}

		int ValueCount()
		{
			if (C) { return 3; }
			else if (B) { return 2; }
			else if (A) { return 1; }

			// Should never come here
			return 0;
		}

		// Helper function for actually deleting the node
		void DeletePart(T* deleteMe)
		{
			if (A == deleteMe)
			{
				delete A;
				A = B;
				B = C;
				C = NULL;

				L = M1;
				M1 = M2;
				M2 = R;
				R = NULL;
			}
			else if (B == deleteMe)
			{
				delete B;
				B = C;
				C = NULL;

				M2 = R;
				R = NULL;
			}
			else
			{
				delete C;
				C = NULL;
				R = NULL;
			}
		}

		// helper function to set to NULL
		void RemovePart(T* deleteMe)
		{
			if (A == deleteMe)
			{
				A = B;
				B = C;
				C = NULL;

				L = M1;
				M1 = M2;
				M2 = R;
				R = NULL;
			}
			else if (B == deleteMe)
			{
				B = C;
				C = NULL;

				M2 = R;
				R = NULL;
			}
			else
			{
				C = NULL;
				R = NULL;
			}
		}

		// Returns true if and only if there is only ONE data-value pointer
		bool IsAlone()
		{
			return (NULL == B);
		}
	};

	Node* m_root;

	void DeleteTree(Node* root)
	{
		if (root)
		{
			root->DeleteData();
			DeleteTree(root->L);
			DeleteTree(root->M1);
			DeleteTree(root->M2);
			DeleteTree(root->R);
			delete root;
		}
	}

	void Display(Node* n)
	{
		if (!n) { return; }

		// There will always be an A value with a subtree to left and right of it
		Display(n->L);
		string nodeAsString = n->A->ToString();
		cout << nodeAsString << endl;
		Display(n->M1);

		// There may or may not be a B and C value
		if (n->B)
		{
			nodeAsString = n->B->ToString();
			cout << nodeAsString << endl;
			Display(n->M2);

			if (n->C)
			{
				nodeAsString = n->C->ToString();
				cout << nodeAsString << endl;
				Display(n->R);
			}
		}
	}

	// Finds and returns the node containing the minimum value in the subtree.
	Node* FindMin(Node* root)
	{
		if (root->IsLeaf())
		{
			return root;
		}

		Node* n = root->L;
		while (n->L) { n = n->L; }
		return n;
	}

#if defined(DEBUG) || defined(_DEBUG)
	bool IsTreeValid(Node* n)
	{
		if (!n) { return true; }

		// First make sure that A is non-null. This should always be true for any 
		// node in the tree.
		if (!n->A)
		{
			cout << "DEBUG: Tree error: Value A in node is null!" << endl;
			return false;
		}

		// Now make sure A < B < C within the node. If C is null then we just 
		// need to verify that A < B and if B and C are NULL then it's ok.
		if (n->C)
		{
			// B must not be NULL in this case
			if (NULL == n->B)
			{
				cout << "DEBUG: Tree error: Value C in node is non-null but B is null!" << endl;
				return false;
			}

			if (n->C->GetKey() <= n->B->GetKey())
			{
				cout << "DEBUG: Tree error: Value C in node is <= B!" << endl;
				return false;
			}
		}
		else if (n->B)
		{
			if (n->B->GetKey() <= n->A->GetKey())
			{
				cout << "DEBUG: Tree error: Value B in node is <= A!" << endl;
				return false;
			}
		}

		// Next we make sure we have non-null child pointers where appropriate.
		if (!n->IsLeaf())
		{
			if (n->C)
			{
				if (NULL == n->R)
				{
					cout << "DEBUG: Tree error: R pointer in node is NULL but value C is not!" << endl;
					return false;
				}
			}
			if (n->B)
			{
				if (NULL == n->M2)
				{
					cout << "DEBUG: Tree error: M2 pointer in node is NULL but value B is not!" << endl;
					return false;
				}
			}
			if (NULL == n->M1)
			{
				cout << "DEBUG: Tree error: M1 pointer in node (key=";
				cout << n->A->GetKey() << ") is NULL!" << endl;
				return false;
			}
			if (NULL == n->L)
			{
				cout << "DEBUG: Tree error: L pointer in node is NULL!" << endl;
				return false;
			}
		}

		// For each value in the node, the left subtree should be all less and the right 
		// subtree all greater.
		T* vals[] = { n->A, n->B, n->C };
		Node* children[] = { n->L, n->M1, n->M1, n->M2, n->M2, n->R };
		for (int i = 0; i < 3; i++)
		{
			if (NULL == vals[i]) { break; }
			int key = vals[i]->GetKey();

			// Make sure all keys in left subtree are less
			stack<Node*> nodes;
			nodes.push(children[i / 2]);
			while (!nodes.empty())
			{
				Node* temp = nodes.top();
				nodes.pop();
				if (!temp) { continue; }

				if (temp->A->GetKey() >= key)
				{
					cout << "DEBUG ERROR: Node in left subtree of key=" << key;
					cout << " has a key of " << temp->A->GetKey() << ", which is";
					cout << "greater and thus improperly structured." << endl;
					return false;
				}
				if (temp->B && temp->B->GetKey() >= key)
				{
					cout << "DEBUG ERROR: Node in left subtree of key=" << key;
					cout << " has a key of " << temp->A->GetKey() << ", which is";
					cout << "greater and thus improperly structured." << endl;
					return false;
				}
				if (temp->C && temp->C->GetKey() >= key)
				{
					cout << "DEBUG ERROR: Node in left subtree of key=" << key;
					cout << " has a key of " << temp->A->GetKey() << ", which is";
					cout << "greater and thus improperly structured." << endl;
					return false;
				}

				// Push children
				nodes.push(temp->L);
				nodes.push(temp->M1);
				nodes.push(temp->M2);
				nodes.push(temp->R);
			}

			// TODO: Right subtree - implement it on your own if you need the 
			// extra error checking
		}

		// Recurse for all children
		return (IsTreeValid(n->L) && IsTreeValid(n->M1) &&
			IsTreeValid(n->M2) && IsTreeValid(n->R));
	}
#endif

public:
	CS223_234Tree(void)
	{
		m_root = NULL;
	}

	virtual ~CS223_234Tree(void)
	{
		DeleteTree(m_root);
		m_root = NULL;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// Splits a full node by placing A and C in seperate nodes and fuses B into the parent node
	int Split(Node* splitMe, Node* parent)
	{
		T* midObj = splitMe->B;				// for 3 node
		int midVal = midObj->GetKey();		// save middle value
		splitMe->B = NULL;					// remove

		Node* rightSplit = new Node(splitMe->C);	// Splits the remaining 3-node up into 2 2-nodes
		splitMe->C = NULL;
		rightSplit->L = splitMe->M2;
		splitMe->M2 = NULL;
		rightSplit->M1 = splitMe->R;
		splitMe->R = NULL;

		Node* leftSplit = splitMe;

		if (splitMe == m_root){ 			// if root node
			m_root = new Node(midObj);		// set middle value to new root 2 node
			m_root->L = leftSplit;
			m_root->M1 = rightSplit;
		}
		else								// else push middle object up 
		{
			Merge(parent, midObj);
			if (midObj == parent->A){
				parent->L = leftSplit;
				parent->M1 = rightSplit;
			}
			else if (midObj == parent->B){
				parent->M1 = leftSplit;
				parent->M2 = rightSplit;
			}
			else {// if parent->C
				parent->M2 = leftSplit;
				parent->R = rightSplit;
			}
		}

		return midVal;
	}

	// Merges an object into a host node.
	bool Merge(Node* host, T* newObject)
	{
		int val = newObject->GetKey();

		if (host->A->GetKey() > val)				// A
		{
			host->C = host->B;						// shift values & pointers
			host->B = host->A;
			host->A = newObject;
			host->R = host->M2;
			host->M2 = host->M1;
			host->M1 = host->L;
		}
		else if (host->B && host->B->GetKey() < val)// C
		{
			host->C = newObject;					// empty, no shift
		}
		else										// B
		{
			host->C = host->B;						// shift values & pointers
			host->B = newObject;
			host->R = host->M2;
		}

		return true;
	}

	// Return the left child of the key within node n
	Node* GetLeftChild(Node* n, int key)
	{
		T* val[] = { n->A, n->B, n->C };
		Node* child[] = { n->L, n->M1, n->M2 };

		for (int i = 0; i < 3; i++)
		{
			if (val[i] && val[i]->GetKey() == key)
			{
				return child[i];
			}
		}

		return NULL;
	}

	// Return the right child of the key within node n
	Node* GetRightChild(Node* n, int key)
	{
		T* val[] = { n->A, n->B, n->C };
		Node* child[] = { n->M1, n->M2, n->R };

		for (int i = 0; i < 3; i++)
		{
			if (val[i] && val[i]->GetKey() == key)
			{
				return child[i];
			}
		}

		return NULL;
	}

	bool Add(T& toCopyAndAdd)
	{
		// You must implement this function for part 1 of this homework assignment
		// Do not allow duplicates in the tree
		// Return false if value already exists in tree or allocation of needed memory fails
		// Return true if addition succeeds
		// Don't forget the rules for splitting nodes

		int Val = toCopyAndAdd.GetKey();

		if (Find(Val))
		{
			return false;					// Return false if value already exists in tree
		}

		T* newObject = new T(toCopyAndAdd);	// Copy it

		if (!newObject)						// Return false if allocation of needed memory fails
		{
			return false;
		}

		if (!m_root)						// Empty
		{
			m_root = new Node(newObject);	// Only node
			return true;
		}

		Node* n = m_root;					// From root
		Node* parent = NULL;

		while (true)
		{
			if (n->IsFull())				// Full
			{
				int midVal = Split(n, parent);

				if (!parent)
				{
					parent = m_root;
				}

				if (midVal > Val)
				{
					n = GetLeftChild(parent, midVal);
				}
				else { n = GetRightChild(parent, midVal); }
			}
			else if (!n->IsLeaf())					// Not leaf
			{
				parent = n;

				if (n->A->GetKey() > Val) 				// A > val -> L
				{
					n = n->L;
				}
				else if (n->B && n->B->GetKey() < Val)	// B < val -> M2
				{
					n = n->M2;
				}

				else
				{
					n = n->M1;
				}
			}
			else		// Leaf
			{
				return Merge(n, newObject);		// Insert value into node
			}
		}
	}

	void Display(ostream& outstream)
	{
		if (!m_root)
		{
			outstream << "(tree is empty)";
		}
		Display(m_root);
	}

	void DisplayLevelKeys(ostream& outstream)
	{
		if (!m_root)
		{
			outstream << "(tree is empty, no levels to display)";
			return;
		}

		struct NodeLevel
		{
			Node* node;
			int level;
			NodeLevel(Node* n, int l) { node = n; level = l; }
		};

		queue<NodeLevel> nodes;
		nodes.push(NodeLevel(m_root, 0));
		int maxLevel = 0;
		while (!nodes.empty())
		{
			NodeLevel nl = nodes.front();
			nodes.pop();
			Node* n = nl.node;
			if (nl.level > maxLevel)
			{
				outstream << endl;
				maxLevel = nl.level;
			}

			outstream << "< " << n->A->GetKey() << " ";
			if (n->B) { outstream << n->B->GetKey() << " "; }
			if (n->C) { outstream << n->C->GetKey() << " "; }
			outstream << ">";

			// Enqueue children
			if (n->L) { nodes.push(NodeLevel(n->L, nl.level + 1)); }
			if (n->M1) { nodes.push(NodeLevel(n->M1, nl.level + 1)); }
			if (n->M2) { nodes.push(NodeLevel(n->M2, nl.level + 1)); }
			if (n->R) { nodes.push(NodeLevel(n->R, nl.level + 1)); }
		}
		outstream << endl;
	}

	T* Find(int key)
	{
		// You must implement this function to return the value for the object 
		// with the associated key. Return NULL if no such object exists in 
		// the tree.

		if (!m_root)
		{
			return NULL;
		}

		Node* n = m_root;

		while (n)			// Finds the key
		{
			T* val[] = { n->A, n->B, n->C, NULL };
			Node* child[] = { n->L, n->M1, n->M2, n->R };

			for (int i = 0; i <= 3; i++)
			{
				if (val[i])
				{
					int value = val[i]->GetKey();

					if (value == key)
					{
						return val[i];
					}
					else if (value > key)
					{
						n = child[i];
						break;
					}
				}
				else
				{
					n = child[i];
					break;
				}
			}
		}

		return NULL;		// No such object exists in the tree
	}

	T* GetMin()
	{
		if (!m_root)
		{
			return NULL;
		}
		Node* n = FindMin(m_root);
		return n->A;
	}

	// Rotates with right or left 3 node or 4 node sibling. Parent key becomes a 3 node
	void Rotate(Node* lonelyNode, Node* siblingNode, Node* parentNode, T* parentObj)
	{
		if (parentObj->GetKey() > lonelyNode->A->GetKey())	// Right
		{
			T* smallestSiblingObj = siblingNode->GetLeast();

			Merge(lonelyNode, parentObj);

			if (parentNode->C && parentNode->C == parentObj)
			{
				parentNode->C = smallestSiblingObj;
			}
			else if (parentNode->B && parentNode->B == parentObj)
			{
				parentNode->B = smallestSiblingObj;
			}
			else
			{
				parentNode->A = smallestSiblingObj;
			}

			lonelyNode->M2 = siblingNode->L;
			siblingNode->RemovePart(smallestSiblingObj);
		}
		else												// Left
		{
			T* largestSiblingObj = siblingNode->GetGreatest();

			Merge(lonelyNode, parentObj);

			if (parentNode->A == parentObj)
			{
				parentNode->A = largestSiblingObj;
			}
			else if (parentNode->B && parentNode->B == parentObj)
			{
				parentNode->B = largestSiblingObj;
			}
			else
			{
				parentNode->C = largestSiblingObj;
			}

			if (siblingNode->IsFull())
			{
				lonelyNode->L = siblingNode->R;
			}
			else
			{
				lonelyNode->L = siblingNode->M2;
			};

			siblingNode->RemovePart(largestSiblingObj);
		}
	}

	// Fuses the leftChild, parentObj, and rightChild into a single node. leftChild holds parentObj, rightChild and rightChild is deleted
	void Fuse(Node* leftChild, Node* rightChild, Node* parentNode, T* parentObj)
	{
		// If the parent: 3-node or 4-node, parentObj=leftChild
		Merge(leftChild, parentObj);
		if (parentNode->A == parentObj)
		{
			parentNode->M1 = parentNode->L;
		}
		parentNode->RemovePart(parentObj);

		// transfer rightChild to leftChild
		Merge(leftChild, rightChild->A);
		leftChild->M2 = rightChild->L;
		leftChild->R = rightChild->M1;
		rightChild->A = NULL;

		delete rightChild;
		rightChild = NULL;

		// If the parent: 2-node and sibling: 2-node | No A
		if (parentNode == m_root)
		{
			m_root = leftChild;
			parentNode->DeleteData();

			delete parentNode;
			parentNode = NULL;
		}
	}

#if defined(DEBUG) || defined(_DEBUG)
	bool IsTreeValid()
	{
		return IsTreeValid(m_root);
	}
#endif

	// n is alone, so we try to steal from parent, left, and right siblings. else: n fuses with root.
	void Steal(Node* n, Node* parent)
	{
		T* parentObjL = NULL;
		Node* leftSibling = NULL;

		// Case 3: Steal from parent
		if (parent->M1 == n)
		{
			parentObjL = parent->A;
			leftSibling = parent->L;
		}
		else if (parent->M2 == n)
		{
			parentObjL = parent->B;
			leftSibling = parent->M1;
		}
		else if (parent->R == n)
		{
			parentObjL = parent->C;
			leftSibling = parent->M2;
		}

		// Case 1: Steal from left sibling
		if (leftSibling && !leftSibling->IsAlone())	// rotate left and parent
		{
			Rotate(n, leftSibling, parent, parentObjL);
			return;
		}

		T* parentObjR = NULL;
		Node* rightSibling = NULL;

		// Case 3: Steal from parent
		if (parent->L == n)
		{
			parentObjR = parent->A;
			rightSibling = parent->M1;
		}
		else if (parent->M1 == n)
		{
			parentObjR = parent->B;
			rightSibling = parent->M2;
		}
		else if (parent->M2 == n)
		{
			parentObjR = parent->C;
			rightSibling = parent->R;
		}

		// Case 2: Steal from right sibling
		if (rightSibling && !rightSibling->IsAlone())
		{
			Rotate(n, rightSibling, parent, parentObjR);
			return;
		}

		// Case 4: Fuse root
		else
		{
			if (leftSibling)	// with left
			{
				Fuse(leftSibling, n, parent, parentObjL);
			}
			else 				// right
			{
				Fuse(n, rightSibling, parent, parentObjR);
			}
			return;
		}
	}

	// For interior nodes
	void ReplaceAndDelete(T* removeMe, T* nextHighestObj)
	{
		Node* toRemove = m_root;
		Node* parent = NULL;

		int key = removeMe->GetKey();

		// Loop until key is contained within n
		while (!toRemove->ContainsKey(key))
		{
			T* val[] = {toRemove->A, toRemove->B, toRemove->C, NULL};
			Node* child[] = {toRemove->L, toRemove->M1, toRemove->M2, toRemove->R};

			for (int i = 0; i <= 3; i++)
			{
				if (val[i])
				{
					int value = val[i]->GetKey();

					if (value == key)
					{
						break;
					}
					else if (value > key)
					{
						parent = toRemove;
						toRemove = child[i];
						break;
					}
				}
				else
				{
					parent = toRemove;
					toRemove = child[i];
					break;
				}
			}
		}

		//Repalce nextHighest
		if (toRemove->A == removeMe)
		{
			toRemove->A=nextHighestObj;
		}
		else if (toRemove->B == removeMe)
		{
			toRemove->B=nextHighestObj;
		}
		else
		{
			toRemove->C=nextHighestObj;
		}

		delete removeMe;
		removeMe = NULL;
	}

	bool Remove(int key)
	{
		if (!m_root) { return false; }

		// Implement the rest of this function for part 2 of this homework assignment.
		// (Don't worry about it and leave it as is for part 1).
		// Return false if the value is not present in the tree
		// Don't forget the rules for fusing nodes

		T* removeMe = Find(key);

		if (!removeMe)	// check first
		{
			return false;
		}
		Node* toRemove = m_root;
		Node* parent = NULL;

		while (!toRemove->ContainsKey(key))		// key is in n
		{
			T* val[] = {toRemove->A, toRemove->B, toRemove->C, NULL};
			Node* child[] = {toRemove->L, toRemove->M1, toRemove->M2, toRemove->R};

			for (int i = 0; i <= 3; i++)
			{
				if (val[i])
				{
					int value = val[i]->GetKey();
					if (value == key)
					{
						break;
					}
					else if (value > key)
					{
						parent = toRemove;
						toRemove = child[i];
						break;
					}
				}
				else
				{
					parent = toRemove;
					toRemove = child[i];
					break;
				}
			}

			// Nodes on the path to key must be alone
			if (toRemove->IsAlone())
			{
				Node* old_root = m_root;
				Steal(toRemove, parent);		// steal from parent

				if (m_root != old_root)
				{
					toRemove = m_root;
					parent = NULL;
				}
				else
				{
					toRemove = parent;
					parent = NULL;
				}
			}
		}

		if (toRemove->IsLeaf())	// IsLeaf
		{
			toRemove->DeletePart(removeMe);		// toRemove is removeMe
			removeMe = NULL;
		}
		else
		{
			Node* nextHighestNode = FindMin(GetRightChild(toRemove, key));
			T* nextHighestObj = new T(*(nextHighestNode->A));

			Remove(nextHighestObj->GetKey());
			ReplaceAndDelete(removeMe, nextHighestObj);
		}

		return true;
	}
};