#include <fstream>

int main(int argc, char* argv[]) {
	std::ofstream o_f("temp.txt");

	if (argc != 2)
		return 0;

	o_f << argv[1];

	return 0;
}
