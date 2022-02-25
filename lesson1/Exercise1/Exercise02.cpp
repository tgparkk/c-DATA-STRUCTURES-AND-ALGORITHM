#include<array>
#include<iostream>
#include<type_traits>

template<typename ...Args>
auto build_array(Args&&... args)->std::array<typename std::common_type<Args...>::type, sizeof ...(args)>
{
	using commonType = typename std::common_type<Args...>::type;
	return { std::forward<commonType>((Args&&)args)... };
}

int main()
{
	auto data = build_array(1, 0u, 'a', 3.2f, false);

	// data2 �� �ϳ��� ����Ÿ������ ��ȯ�� �� �����Ƿ� ����
	// auto data2 = build_array(1, "packet");

	for (auto i : data)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
}