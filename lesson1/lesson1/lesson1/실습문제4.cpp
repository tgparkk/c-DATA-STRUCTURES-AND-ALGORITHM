#include <iostream>
#include <vector>
#include <algorithm>

struct n_ary_node
{
	std::string name;
	bool is_dir;
	std::vector<n_ary_node*> children;
};

struct file_system
{
	using node = n_ary_node;
	using node_ptr = node*;

private:
	node_ptr root;
	node_ptr cwd;

public:
	file_system()
	{
		root = new node{ "/", true, {} };
		cwd = root; // ó������ ��Ʈ�� ���� ���丮�� ����
	}

	node_ptr find(const std::string& path)
	{
		if (path[0] == '/') // ���� ���
		{
			return find_impl(root, path.substr(1));
		}
		else // ��� ���
		{
			return find_impl(cwd, path);
		}
	}

private:
	node_ptr find_impl(node_ptr directory, const std::string& path)
	{
		if (path.empty())
			return directory;
		// find()
		// size_type find(const _Elem _Ch, const size_type _Off = 0)
		// string �� find �� _Ch �� ��ġ�� ����
		auto sep = path.find('/');
		
		// static const size_type npos = -1;
		std::string current_path = (sep == std::string::npos) ? path : path.substr(0, sep);
		std::string rest_path = (sep == std::string::npos) ? "" : path.substr(sep + 1);
		auto found = std::find_if(directory->children.begin(), directory->children.end(),
			[&](const node_ptr child) {
				return child->name == current_path;
			});
		if (found != directory->children.end())
		{
			return find_impl(*found, rest_path);
		}
		return NULL;
	}

public:
	bool add(const std::string& path, bool is_dir)
	{
		if (path[0] == '/')
		{
			// substr(size_type pos, size_type count = npos) : pos ��° ���� ���� count ���� ��ŭ�� ���ڿ� ����
			return add_impl(root, path.substr(1), is_dir);
		}
		else
		{
			return add_impl(cwd, path, is_dir);
		}
	}

private:
	bool add_impl(node_ptr directory, const std::string& path, bool is_dir)
	{
		if (not directory->is_dir)
		{
			std::cout << directory->name << "��(��) �����Դϴ�." << std::endl;
			return false;
		}

		auto sep = path.find('/');

		// path�� '/'�� ���� ���
		if (sep == std::string::npos)
		{
			auto found = std::find_if(directory->children.begin(), directory->children.end(), [&](const node_ptr child) {
				return child->name == path;
				});

			if (found != directory->children.end())
			{
				std::cout << directory->name << "�� �̹� " << path << " �̸��� ����/���丮�� �ֽ��ϴ�." << std::endl;
				return false;
			}

			directory->children.push_back(new node{ path, is_dir, {} });
			return true;
		}

		// path�� '/'�� �ִ� ���, ��, ���丮 �̸��� �����ϰ� �ִ� ���.
		std::string next_dir = path.substr(0, sep);
		auto found = std::find_if(directory->children.begin(), directory->children.end(), [&](const node_ptr child) {
			return child->name == next_dir && child->is_dir;
			});

		if (found != directory->children.end())
		{
			return add_impl(*found, path.substr(sep + 1), is_dir);
		}

		// path�� ���丮 �̸��� ���ԵǾ� ������, �ش� ���丮�� ���� ���.
		std::cout << directory->name << "�� " << next_dir << " �̸��� ���丮�� �����ϴ�." << std::endl;
		return false;
	}

public:
	bool change_dir(const std::string& path)
	{
		auto found = find(path);
		if (found && found->is_dir)
		{
			cwd = found;
			std::cout << "���� ���丮�� " << cwd->name << "�� �̵��մϴ�." << std::endl;
			return true;
		}

		std::cout << path << " ��θ� ã�� �� �����ϴ�." << std::endl;
		return false;
	}

public:
	void show_path(const std::string& path)
	{
		auto found = find(path);
		if (not found)
		{
			std::cout << path << " ��ΰ� �������� �ʽ��ϴ�." << std::endl;
			return;
		}

		if (found->is_dir)
		{
			for (auto child : found->children)
			{
				std::cout << (child->is_dir ? "d " : "- ") << child->name << std::endl;
			}
		}
		else
		{
			std::cout << "- " << found->name << std::endl;
		}
	}
};

int main()
{
	file_system fs;
	fs.add("usr", true);       // "/"�� usr ���丮 �߰�
	fs.add("etc", true);       // "/"�� etc ���丮 �߰�
	fs.add("var", true);       // "/"�� var ���丮 �߰�
	fs.add("tmp_file", false); // "/"�� tmp_file ���� �߰�

	std::cout << "\"/\"�� ����/���丮 ���:" << std::endl;
	fs.show_path("/");        // "/"�� ����/���丮 ��� ���

	std::cout << std::endl;
	fs.change_dir("usr");
	fs.add("gilbut", true);
	fs.add("gilbut/Downloads", true);
	fs.add("gilbut/Downloads/newFile.cpp", false);

	std::cout << "���� ���丮���� usr�� ����/���丮 ���: " << std::endl;
	fs.show_path("usr"); // ���� ���丮���� usr ���丮�� �����Ƿ� ���������� ������� ���մϴ�.

	std::cout << "\"/usr\"�� ����/���丮 ���:" << std::endl;
	fs.show_path("/usr");

	std::cout << "\"/usr/gilbut/Downloads\"�� ����/���丮 ���" << std::endl;
	fs.show_path("/usr/gilbut/Downloads");
}