#include "alignchart.h"

AlignChart::AlignChart(std::string seq1, std::string seq2) {

	const int MATCH_COST = 1;
	const int MISMATCH_COST = -1;
	const int GAP_COST = -1;

	matrix.resize(seq2.size()+1, seq1.size()+1);

	int mod_buff;
	
	int from_top,
		 from_left,
		 from_diag;

	seq1 = ' ' + seq1;
	seq2 = ' ' + seq2;
	
	matrix[0][0] = 0;

	for (int i = 1; i < matrix.N_rows; i++) {
		matrix[i][0] = matrix[i-1][0] + GAP_COST;
	}
	for (int j = 1; j < matrix.N_cols; j++) {
		matrix[0][j] = matrix[0][j-1] + GAP_COST;
	}

	for (int i = 1; i < matrix.N_rows; i++) {
		for (int j = 1; j < matrix.N_cols; j++) {

			from_top = matrix[i-1][j] + GAP_COST;

			from_left = matrix[i][j-1] + GAP_COST;

			if (seq2[i] == seq1[j])
				mod_buff = MATCH_COST;
			else
				mod_buff = MISMATCH_COST;
			from_diag = matrix[i-1][j-1] + mod_buff;
			
			matrix[i][j] = std::max(std::max(from_top, from_left), from_diag);
		}
	}
}

Matrix<int> AlignChart::get_alignment_matrix() {
	return matrix;
}
