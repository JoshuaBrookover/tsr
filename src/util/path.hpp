#include <string>

namespace path
{
	std::string resolve(const std::string& path);
	std::string normalize(const std::string& path);
	std::string join(const std::string& a, const std::string& b);
	std::string dirname(const std::string& path);
	bool isAbsolute(const std::string& path);

	std::string unixResolve(const std::string& path);
	std::string unixNormalize(const std::string& path);
	std::string unixJoin(const std::string& a, const std::string& b);
	std::string unixDirname(const std::string& path);
	bool unixIsAbsolute(const std::string& path);

	// TODO: win32
}
