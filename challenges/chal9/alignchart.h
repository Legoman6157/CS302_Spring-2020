#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include "matrix.h"

class AlignChart {
	private:
		Matrix<int> matrix;

	public:
		AlignChart(std::string seq1, std::string seq2);
		Matrix<int> get_alignment_matrix();
};
