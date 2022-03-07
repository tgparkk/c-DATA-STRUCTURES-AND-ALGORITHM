#include <iostream>
#include <list>

int main()
{
	std::list<int> list1 = { 1, 2, 3, 4, 5 };
	list1.push_back(6);                   // {1, 2, 3, 4, 5, 6}

	// next(list1.begin()) : �� ó�� ���� ���� ��ġ
	list1.insert(next(list1.begin()), 0); // {1, 0, 2, 3, 4, 5, 6}
	list1.insert(list1.end(), 7);         // {1, 0, 2, 3, 4, 5, 6, 7}
	list1.pop_back();                     // {1, 0, 2, 3, 4, 5, 6}

	std::cout << "���� & ���� �� ����Ʈ: ";
	for (auto i : list1)
		std::cout << i << " ";
}