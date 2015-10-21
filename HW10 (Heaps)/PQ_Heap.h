// Eric Chen 11381898

#ifndef PQHEAPH
#define PQHEAPH

#include "PQBase.h"
#include <queue>
#include <vector>

using namespace std;

template <typename T>
class PQ_Heap : public PQBase<T>
{
private:
	// Declare the private member variables you need here.
	// Store the heap data in an array or a std::vector.
	struct Node
	{
	public:
		T* value;
		vector<int> children_indexes;

		Node()
		{
			value = nullptr;
			children_indexes.clear();
		}

		Node(T* toCopyAndAdd)
		{
			value = toCopyAndAdd;
			children_indexes.clear();
		}
	};

	T return_largest(vector<T> childs)
	{
		T temp = childs[0];
		for (int i = 0; i < childs.size(); i++)
		{
			if (childs[i] > temp)
			{
				temp = childs[i];
			}
		}
		return temp;
	}

	vector<Node *> heap;
	int order;

public:
	PQ_Heap(int k)
	{
		// Implement this constructor so that it stores k and uses it in 
		// the appropriate member functions to build a k-ary heap for 
		// the priorty queue.
		order = k;
	}

	// Implement the rest of this class

	~PQ_Heap()	// Destructor
	{
		heap.clear();
	}

	void Add(const T& toCopyAndAdd)
	{ 
		T* obj = new T(toCopyAndAdd);
		Node *new_node = new Node(obj);
		Node *temp;
		vector<int> tmpVec;

		unsigned int i, parent_index, comp_index, index, chIndex, iteration = 0; // m_top
		vector<Node *>::iterator it;
		it = heap.begin();
		double num;

		if (heap.empty())
		{
			heap.push_back(new_node);
			return;
		}

		heap.push_back(new_node); // Add new value to the bottom
		i = heap.size() - 1;

		num = (double)((i - 1) / order);
		parent_index = floor(num);

		while (parent_index >= 0)
		{
			if (*obj > *(heap[parent_index]->value)) // If object > parent
			{
				if (iteration < 1)
				{
					if ((heap[parent_index]->children_indexes).size() <= order)
					{
						(heap[parent_index]->children_indexes).push_back(i);
					}
					else
					{
						(heap[parent_index + 1]->children_indexes).push_back(i);
					}
				}
				tmpVec = heap[parent_index]->children_indexes;
				heap[parent_index]->children_indexes = heap[i]->children_indexes; // swap parent with new node

				temp = heap[parent_index];			// save parent

				heap[parent_index] = heap[i]; 		// swap new node and parent

				heap[i]->children_indexes = tmpVec; // swap old parent's children and new node's children

				heap[i] = temp; 					// new node is old parent's parent

				iteration++;						// iterate
				i = parent_index;

				if (i == 0)
				{
					break;
				}

				num = (double)((i - 1) / order);
				parent_index = floor(num);

				continue;
			}
			else // object <= parent
			{
				if (iteration < 1)
				{
					if ((heap[parent_index]->children_indexes).size() <= order)
					{
						(heap[parent_index]->children_indexes).push_back(i);
					}
					else
					{
						(heap[parent_index + 1]->children_indexes).push_back(i);
					}
				}
				break;
			}
		}
	}
	bool IsEmpty() const
	{
		if (heap.empty())
		{
			return true;
		}
		return false;
	}

	// Removes the max item from the PQ. Returns false if the queue is empty.
	bool RemoveMax(T& outputItem)
	{
		Node *temp, *tmp2;
		vector<int> tmpVec;

		unsigned int i, child_index, comp_index, index, chIndex, childCount = 0, j; // m_top
		T tempVal, largestChild;
		std::vector<Node *>::iterator it;
		vector<T> children;

		it = heap.begin();
		double num;

		if (heap.empty())
		{
			return false;
		}
		if (heap.size() > 1)
		{
			temp = heap[heap.size() - 1]; // save last element

			tmpVec = heap.front()->children_indexes;
			heap.front()->children_indexes = temp->children_indexes; // swap top with last element

			heap[heap.size() - 1] = heap.front();

			heap.front() = temp; 		// last element is now the top

			heap.front()->children_indexes = tmpVec; 		// top node's children now last element's children

			int number = floor(double((heap.size() - 2) / order));

			(heap[number]->children_indexes).pop_back(); 	// update parent's children

			outputItem = *((heap.back())->value);
			heap.pop_back();
		}
		else if (heap.size() == 1)
		{
			outputItem = *((heap.back())->value);
			heap.pop_back();
			return true;
		}
		else
		{
			return true;
		}

		temp = heap.front(); // Rebalance
		child_index = 1;
		i = 0;
		
		while (child_index < heap.size())
		{
			while (child_index >= ((i*order) + 1))
			{
				children.clear();
				childCount = 0;
				j = child_index;
				while (childCount < order && j < heap.size()) 		// Find the largest child
				{
					tempVal = *(heap[j]->value);
					children.push_back(tempVal);
					j++;
					childCount++;
				}

				largestChild = return_largest(children);

				j = child_index;
				while (j < child_index + (order-1)) 				// Find the largest child's index
				{
					if (*(heap[j]->value) == largestChild)
					{
						break;
					}
					j++;
				}

				child_index = j;
				if (*(temp->value) < *(heap[child_index]->value)) 	// If object is more than parent node
				{
					tmpVec = heap[child_index]->children_indexes;
					heap[child_index]->children_indexes = heap[i]->children_indexes; // Swap parent with child

					tmp2 = heap[child_index];

					heap[child_index] = heap[i]; 					// Child node is now the parent

					heap[i] = tmp2;									// Set old parent to child's child node

					i = child_index;

					heap[child_index]->children_indexes = tmpVec; 	// Swap old parent and child's child nodes

					child_index = (i*order) + 1;

					if ((heap[i]->children_indexes).empty())
					{
						return true;
					}
					continue;
				}
				else
				{
					return true;
				}
				child_index++;
				children.clear();
			}
		}
		return true;
	}
};

#endif