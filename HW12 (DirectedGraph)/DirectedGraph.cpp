// Cpt S 223 - Directed Graph Homework
// DirectedGraph.cpp
// Eric Chen 11381898

#include "DirectedGraph.h"
#include <iostream>
#include <limits>	// For infinity redefinition

#define INFINITY numeric_limits<unsigned int>::max()

DirectedGraph::DirectedGraph()
{
	// No initialization needed
}

DirectedGraph::~DirectedGraph()
{
	// Free all nodes and edges
	for (vector<Node*>::size_type i = 0; i < m_nodes.size(); i++)
	{
		delete m_nodes[i];
	}
	m_nodes.clear();
	for (vector<Edge*>::size_type i = 0; i < m_edges.size(); i++)
	{
		delete m_edges[i];
	}
	m_edges.clear();

	// Make sure the node map is cleared too
	NameNode_map.clear();
}

bool DirectedGraph::AddNode(const string& nodeName, const string& nodeData)
{
	// You must implement this function

	if (NodeExists(nodeName))	// Duplicate
	{
		return false;
	}

	Node* newNode_ptr = new Node(nodeName, nodeData);
	if (!newNode_ptr)
	{
		return false;
	}

	m_nodes.push_back(newNode_ptr);
	NameNode_map[nodeName] = newNode_ptr;
	return true;
}

// Adds an edge to the graph that starts at the source node, 
// and goes to the target node.
// If the graph already contains an edge going from the specified 
// source to target node then false is returned and no modification 
// occurs.
// If either or both of the two nodes don't exist in the graph then 
// false is returned and no modification occurs.
// Otherwise the edge will be added. Note that an edge from N1 (source) 
// to N2 (target) is different than an edge from N2 (source) to N1 (target).
bool DirectedGraph::AddEdge(const string& sourceNodeName, const string& targetNodeName)
{
	// You must implement this function
	// Check if both nodes exist
	if (!NodeExists(sourceNodeName)||!NodeExists(targetNodeName)) 
	{
		return false;
	}

	int sourceIndex = getNodeIndex(sourceNodeName);
	int targetIndex = getNodeIndex(targetNodeName);

	// Edge already exists
	if (EdgeExists(sourceIndex, targetIndex))
	{
		return false;
	}

	// Find indices of source and target nodes and allocate a new edge
	Edge* newEdge_ptr = new Edge(sourceIndex, targetIndex);
	if (!newEdge_ptr)
	{
		return false;
	}

	m_edges.push_back(newEdge_ptr);

	// Out of source, into target
	m_nodes[sourceIndex]->Out.push_back(newEdge_ptr);
	m_nodes[targetIndex]->In.push_back(newEdge_ptr);

	return true;
}

int DirectedGraph::getNodeIndex(const string& nodeName) const
{
	// Get the index of the node
	for (vector<Node*>::size_type i = 0; i < m_nodes.size(); i++)
	{
		if ( m_nodes[i]->Name == nodeName )
		{
			return i;
		}
	}
	return -1;
}

// Gets the degree of the node with the specified name. -1 is returned 
// if no such node exists in the graph.
int DirectedGraph::GetDegree(const string& nodeName)
{
	// You must implement this function

	Node* node_ptr = NameNode_map[nodeName];

	return node_ptr->In.size() + node_ptr->Out.size(); // Degree of a node = sum of edges going to + edges coming out
}

// Gets the shortest path from the specified start to end nodes. If no path exists 
// from the start to end nodes then false is returned and the traversalList object 
// is not modified. Otherwise the traversalList is filled with strings representing 
// the sequence of nodes for the shortest path from start to end. These strings 
// will be the node names if nodeDataInsteadOfName is false, otherwise they will be 
// the node data values (which are strings).
bool DirectedGraph::GetShortestPath(const string& startNode, const string& endNode, 
									bool nodeDataInsteadOfName, vector<string>& traversalList)
{
	// You must implement this function

	struct MetaNode
	{
		Node* Node_ptr;
		unsigned int Distance;

		MetaNode(Node* n_ptr)
		{
			Node_ptr = n_ptr;
			Distance = INFINITY;
		}

	};

	vector<MetaNode*> unvisited_pq;		// Keep track of visited nodes
	vector<MetaNode*> meta_nodes; 		// Parallel to m_nodes
	meta_nodes.resize(m_nodes.size());

	MetaNode* start_ptr = NULL;
	MetaNode* end_ptr = NULL;
	MetaNode* cur_ptr = NULL;

	for (vector<Node*>::size_type i = 0; i < m_nodes.size(); i++)
	{
		MetaNode* newMetaNode = new MetaNode(m_nodes[i]);

		if (m_nodes[i]->Name == startNode)
		{
			newMetaNode->Distance = 0;
			start_ptr = newMetaNode;
			meta_nodes[i] = newMetaNode;
			continue;
		}
		else if (m_nodes[i]->Name == endNode)
		{
			end_ptr = newMetaNode;
		}

		unvisited_pq.push_back(newMetaNode);
		meta_nodes[i] = newMetaNode;
	}
	unvisited_pq.push_back(start_ptr);

	while (true)
	{
		cur_ptr = unvisited_pq.back();

		for (vector<Edge*>::size_type i = 0; i < cur_ptr->Node_ptr->Out.size(); i++)
		{
			MetaNode* neighbor_ptr = meta_nodes[cur_ptr->Node_ptr->Out[i]->targetI];

			if (neighbor_ptr->Distance == INFINITY) 				// Calculate distances of unvisited neighbors
			{
				if (cur_ptr->Distance + 1 < neighbor_ptr->Distance)	// Weight = 1
				{
					neighbor_ptr->Distance = cur_ptr->Distance + 1;
				}
			}
		}

		for (unsigned int i = 0; i < unvisited_pq.size(); i++)
		{
			MetaNode* tmp = unvisited_pq[i];						
			int j = i;								

			while (j >= 1 && tmp->Distance > unvisited_pq[j - 1]->Distance)
			{
				unvisited_pq[j] = unvisited_pq[j - 1];						
				j--;										
			}
			unvisited_pq[j] = tmp;	
		}

		// Unvisited -> visited, remove from list
		unvisited_pq.pop_back();

		if (end_ptr->Distance != INFINITY)	// Visited
		{
			break;
		}
		else if (unvisited_pq.back()->Distance == INFINITY)
		{
			return false;
		}
	} 
	// Path exist

	cur_ptr = end_ptr;
	traversalList.resize(end_ptr->Distance + 1); // A->B->C, end_ptr->Distance = 2 + 1 = 3 Nodes

	if (nodeDataInsteadOfName) { traversalList[end_ptr->Distance] = end_ptr->Node_ptr->Data; }
	else { traversalList[end_ptr->Distance] = end_ptr->Node_ptr->Name; }

	for (vector<string>::size_type dist = end_ptr->Distance - 1; dist > 0; dist--)
	{
		for (vector<Edge*>::size_type j = 0; j < cur_ptr->Node_ptr->In.size(); j++)	// Node's distance < dist
		{
			MetaNode* neighbor_ptr = meta_nodes[cur_ptr->Node_ptr->In[j]->srcI];

			if (neighbor_ptr->Distance == dist)
			{
				if (nodeDataInsteadOfName)
				{
					traversalList[dist] = neighbor_ptr->Node_ptr->Data;
				}
				else
				{
					traversalList[dist] = neighbor_ptr->Node_ptr->Name;
				}

				cur_ptr = neighbor_ptr;
				break;
			}

		}
	}

	if (nodeDataInsteadOfName)
	{
		traversalList[0] = start_ptr->Node_ptr->Data;
	}
	else
	{
		traversalList[0] = start_ptr->Node_ptr->Name;
	}

	return true;
}

// Returns true if the node exists in the graph, else false.
bool DirectedGraph::NodeExists(const string& nodeName)
{
	// You must implement this function

	if (NameNode_map[nodeName])
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Checks if edge exists, returns false if it doesn't.
bool DirectedGraph::EdgeExists(int sourceIndex, int targetIndex)
{
	for (vector<Edge*>::size_type i = 0; i < m_edges.size(); i++)
	{
		if (m_edges[i]->srcI == sourceIndex && m_edges[i]->targetI == targetIndex)
		{
			return true;
		}
	}
	return false;
}