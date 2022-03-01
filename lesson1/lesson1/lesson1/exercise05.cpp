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
	using node = singly_ll_node; // singly_ll_node 를 node 로 정의
	using node_ptr = node*; // node* 를 node_ptr 로 정의

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

