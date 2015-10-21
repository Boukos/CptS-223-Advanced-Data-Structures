// Eric Chen 11381898

#ifndef PQLLH
#define PQLLH

#include "PQBase.h"

template <typename T>
class PQ_LinkedList : public PQBase < T >
{
	// Implement this class - maintain a sorted linked-list internally where 
	// the list is always sorted in descending order and therefore the 
	// max is always accessible and removable in constant time.
private:
	struct Node
	{
	public:
		T *value;
		Node *next;
		Node *previous;

		Node()
		{
			value = NULL;
			next = nullptr;
			previous = nullptr;
		}

		Node(T *new_val)
		{
			value = new_val;
			next = nullptr;
			previous = nullptr;
		}

	};


	T* GetMin()
	{
		Node *temp = m_front;
		while (temp->next)
		{
			temp = temp->next;
		}
		return temp->value;
	}

	T* Front()
	{
		return m_front;
	}

	Node *m_front;
	// Implement this class - maintain a sorted linked-list internally where 
	// the list is always sorted in descending order and therefore the 
	// max is always accessible and removable in constant time.
public:
	PQ_LinkedList()
	{
		m_front = nullptr;
	}

	~PQ_LinkedList()
	{
		delete m_front;
	}


	// Adds an item to the PQ
	void Add(const T& toCopyAndAdd)
	{
		T* obj = new T(toCopyAndAdd);
		Node *new_node = new Node(obj);
		Node *temp = m_front;

		if (m_front == nullptr) 		// Front
		{
			m_front = new Node(obj);
			return;
		}

		while (temp != nullptr) 		// Until end
		{
			if (*obj > *(temp->value)) 	// If > current
			{
				if (temp == m_front) 	// Current node == front
				{
					new_node->next = m_front;
					m_front->previous = new_node;
					m_front = new_node;
					break;
				}
				else 					// Current node != front
				{
					temp->previous->next = new_node;
					new_node->previous = temp->previous;
					temp->previous = new_node;
					new_node->next = temp;
					break;
				}
			}
			else 						// If < current
			{
				if (temp->next == nullptr) // Current node == front
				{
					temp->next = new_node;
					new_node->previous = temp;
					break;
				}
				else 					// Current node != front
				{
					temp = temp->next;
					continue;
				}
			}
		}
	}

	bool IsEmpty() const
	{
		if (m_front == nullptr) // Front
		{
			return true;
		}
		return false;
	}

	// Removes the max item from the PQ. Returns false if the queue is empty
	bool RemoveMax(T& outputItem)
	{
		Node *temp = m_front->next;
		if (m_front == nullptr)
		{
			return false;
		}
		if (m_front->next == nullptr)
		{
			outputItem = *(m_front->value);
			m_front = nullptr;

			return true;
		}
		outputItem = *(m_front->value);
		temp->previous = nullptr;
		delete m_front;
		m_front = temp;

		return true;
	}
};
#endif