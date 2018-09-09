#include <toh.hpp>
#include <fstream>
#include <iostream>
#include <vector>

void usage(char* name)
{
	std::cerr << name << " [options] <input> <output>" << std::endl;
	std::cerr << "  Options:" << std::endl;
	std::cerr << "    -null            - Add a null character to the end of the buffer" << std::endl;
	std::cerr << "    -variable <name> - Name of the variable in the generated header" << std::endl;
}

int main(int argc, char** argv)
{
	toh::Options options;
	std::string input, output;
	for (int i = 1; i < argc; ++i)
	{
		if (std::string(argv[i]) == "-null")
		{
			options.null = true;
		}
		else if (std::string(argv[i]) == "-variable")
		{
			if (i != argc - 1)
			{
				options.variable = argv[i + 1];
				++i;
			}
			else
			{
				usage(argv[0]);
				return 1;
			}
		}
		else if (input != "" && output != "")
		{
			usage(argv[0]);
			return 1;
		}
		else if (input == "")
		{
			input = argv[i];
		}
		else
		{
			output = argv[i];
		}
	}
	if (input == "" || output == "")
	{
		usage(argv[0]);
		return 1;
	}

	std::ifstream file(input, std::ios::binary | std::ios::ate);
	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << input << std::endl;
		return -1;
	}
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);
	std::vector<char> buffer(size);
	if (!file.read(buffer.data(), size))
	{
		std::cerr << "Failed to read file: " << input << std::endl;
		return -1;
	}

	std::string result = toh::convert(buffer.data(), buffer.size(), options);
	std::ofstream outfile(output);
	if (!outfile.is_open())
	{
		std::cerr << "Failed to open file: " << output << std::endl;
		return -1;
	}
	outfile << result;
	outfile.close();
	return 0;
}
