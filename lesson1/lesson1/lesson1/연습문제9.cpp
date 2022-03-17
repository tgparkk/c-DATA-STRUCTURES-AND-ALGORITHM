#include <iostream>

struct node
{
	int data;
	node* left;
	node* right;
};

struct bst
{
	node* root = nullptr;

	node* find(int value)
	{
		return find_impl(root, value);
	}

private:
	node* find_impl(node* current, int value)
	{
		if (!current)
		{
			std::cout << std::endl;
			return NULL;
		}

		if (current->data == value)
		{
			std::cout << value << "��(��) ã�ҽ��ϴ�." << std::endl;
			return current;
		}

		if (value < current->data) // value ���� ���� ��� ���ʿ� �ִ� ���
		{
			std::cout << current->data << "���� �������� �̵�: ";
			return find_impl(current->left, value);
		}

		// value ���� ���� ��� �����ʿ� �ִ� ���
		std::cout << current->data << "���� ���������� �̵�: ";
		return find_impl(current->right, value);
	}

public:
	void insert(int value)
	{
		if (!root)
			root = new node{ value, NULL, NULL };
		else
			insert_impl(root, value);
	}

private:
	void insert_impl(node* current, int value)
	{
		if (value < current->data)
		{
			if (!current->left)
				current->left = new node{ value, NULL, NULL };
			else
				insert_impl(current->left, value);
		}
		else
		{
			if (!current->right)
				current->right = new node{ value, NULL, NULL };
			else
				insert_impl(current->right, value);
		}
	}

public:
	void inorder()
	{
		inorder_impl(root);
	}

private:
	void inorder_impl(node* start)
	{
		if (!start)
			return;

		inorder_impl(start->left);			// ���� ���� Ʈ�� �湮
		std::cout << start->data << " ";	// ���� ��� ���
		inorder_impl(start->right);			// ������ ���� Ʈ�� �湮
	}

public:
	node* successor(node* start)
	{
		auto current = start->right;
		while (current && current->left)
			current = current->left;
		return current;
	}

	void deleteValue(int value)
	{
		root = delete_impl(root, value);
	}

private:
	node* delete_impl(node* start, int value)
	{
		if (!start)
			return NULL;

		if (value < start->data)
			start->left = delete_impl(start->left, value);
		else if (value > start->data)
			start->right = delete_impl(start->right, value);
		else
		{
			if (!start->left) // �ڽ� ��尡 ���� ���ų�, ���� �ڽ� ��常 ���� ���
			{
				auto tmp = start->right;
				delete start;
				return tmp;
			}

			if (!start->right) // ������ �ڽ� ��常 ���� ���
			{
				auto tmp = start->left;
				delete start;
				return tmp;
			}

			// �ڽ� ��尡 �� �� �ִ� ���
			auto succNode = successor(start);
			start->data = succNode->data;

			// ������ ���� Ʈ������ �İ���(successor)�� ã�� ����
			start->right = delete_impl(start->right, succNode->data);
		}

		return start;
	}
};

int main()
{
	bst tree;
	tree.insert(12);
	tree.insert(10);
	tree.insert(20);
	tree.insert(8);
	tree.insert(11);
	tree.insert(15);
	tree.insert(28);
	tree.insert(4);
	tree.insert(2);
	tree.insert(12);

	std::cout << "���� ��ȸ: ";
	tree.inorder(); // BST�� ��� ���Ҹ� ������������ ����մϴ�.
	std::cout << std::endl;

	tree.deleteValue(12);
	std::cout << "12�� ������ �� ���� ��ȸ: ";
	tree.inorder(); // BST�� ��� ���Ҹ� ������������ ����մϴ�.
	std::cout << std::endl;

	if (tree.find(12))
		std::cout << "���� 12�� Ʈ���� �ֽ��ϴ�." << std::endl;
	else
		std::cout << "���� 12�� Ʈ���� �����ϴ�." << std::endl;
}