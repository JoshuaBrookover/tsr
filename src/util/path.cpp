#include "util/path.hpp"
#include <vector>
#include <iostream>
#include <unistd.h>
#include <limits.h>

std::string path::resolve(const std::string& path)
{
	return path::unixResolve(path);
}

std::string path::normalize(const std::string& path)
{
	return path::unixNormalize(path);
}

std::string path::join(const std::string& a, const std::string& b)
{
	return path::unixJoin(a, b);
}

std::string path::dirname(const std::string& path)
{
	return path::unixDirname(path);
}

bool path::isAbsolute(const std::string& path)
{
	return path::unixIsAbsolute(path);
}

std::string path::unixResolve(const std::string& path)
{
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		return path::unixJoin(cwd, path);
	} else {
		return path;
	}
}

std::string path::unixNormalize(const std::string& path)
{
	std::vector<std::string> dirs;
	std::string working;
	for (size_t i = 0; i < path.size(); ++i)
	{
		if (path[i] == '/') {
			if (working != "" || dirs.size() == 0)
			{
				dirs.push_back(working);
			}
			working = "";
		} else {
			working += path[i];
		}
	}
	dirs.push_back(working);
	for (size_t i = 0; i < dirs.size(); ++i)
	{
		if (dirs[i] == "..")
		{
			dirs.erase(dirs.begin() + i);
			dirs.erase(dirs.begin() + i - 1);
			i -= 2;
		}
		else if (dirs[i] == ".")
		{
			dirs.erase(dirs.begin() + i);
			i -= 1;
		}
	}
	working = "";
	for (size_t i = 0; i < dirs.size(); ++i)
	{
		working += dirs[i];
		if (i != dirs.size() - 1) {
			working += "/";
		}
	}
	return working;
}

std::string path::unixJoin(const std::string& a, const std::string& b)
{
	return unixNormalize(a + "/" + b);
}

std::string path::unixDirname(const std::string& path)
{
	std::vector<std::string> dirs;
	std::string working;
	for (size_t i = 0; i < path.size(); ++i)
	{
		if (path[i] == '/') {
			if (working != "" || dirs.size() == 0)
			{
				dirs.push_back(working);
			}
			working = "";
		} else {
			working += path[i];
		}
	}
	dirs.push_back(working);
	dirs.pop_back();
	working = "";
	for (size_t i = 0; i < dirs.size(); ++i)
	{
		working += dirs[i];
		if (i != dirs.size() - 1) {
			working += "/";
		}
	}
	return working;
	return path;
}

bool path::unixIsAbsolute(const std::string& path)
{
	return path.size() > 0 && path[0] == '/';
}
