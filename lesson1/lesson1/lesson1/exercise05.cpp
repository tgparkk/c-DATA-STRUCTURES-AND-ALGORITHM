#include<iostream>
#include<algorithm>

struct singly_ll_node
{
	int data;
	singly_ll_node* next;
};

class singly_ll
{
public:
	using node = singly_ll_node; // singly_ll_node �� node �� ����
	using node_ptr = node*; // node* �� node_ptr �� ����

private:
	node_ptr head;

public:
	void push_front(int val)
	{
		auto new_node = new node{ val, NULL };
		//auto new_node = new node(val, NULL);

		if (head != NULL)
			new_node->next = head; // head, a, b ->   new_node , head, a, b
		head = new_node->next;
	}

	void pop_front()
	{
		auto first = head;
		if (head)
		{
			head = head->next;
			delete first;
		}
	}
};

