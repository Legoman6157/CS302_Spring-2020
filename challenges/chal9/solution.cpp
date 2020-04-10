#include <iostream>

#include "alignchart.cpp"

int main(int argc, char* argv[]) {
	std::string seq1,
					seq2;

	std::cin >> seq2 >> seq1;

	AlignChart align_chart(seq1, seq2);

	Matrix<int> matrix = align_chart.get_alignment_matrix();

	seq1 = ' ' + seq1;
	seq2 = ' ' + seq2;

	std::cout << ' ';
	for (int i = 0; i < matrix.N_cols; i++)
		std::cout << std::setw(3) << std::right << seq1[i];	
	std::cout << std::endl;


	for (int i = 0; i < matrix.N_rows; i++) {
		std::cout << seq2[i];
		for (int j = 0; j < matrix.N_cols; j++)
			std::cout << std::setw(3) << std::right << matrix[i][j];
		std::cout << std::endl;
	}

	std::cout << matrix[matrix.N_rows-1][matrix.N_cols-1] << std::endl;
	return 0;
}
