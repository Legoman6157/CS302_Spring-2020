template <typename T>
class Matrix {
	private:
		T **matrix;

	public:
		int N_rows,
			 N_cols,
			 N;

		Matrix(int n_N_rows, int n_N_cols): N_rows(n_N_rows), N_cols(n_N_cols) {
			matrix = new T* [N_rows];

			for (int i = 0; i < N_rows; i++)
				matrix[i] = new T[N_cols];
		}//Matrix(int n_N_rows, int n_N_cols)

		~Matrix() {
			for (int i = 0; i < N_rows; i++)
				delete matrix[i];

			delete [] matrix;
		}//~Matrix

		void resize(int n_N_rows, int n_N_cols) {
			for (int i = 0; i < N_rows; i++)
				delete matrix[i];

			delete [] matrix;

			matrix = new T* [N_rows];

			for (int i = 0; i < N_rows; i++)
				matrix[i] = new T[N_cols];
		}//resize(int n_N_rows, int n_N_cols)

		T* operator[](int loc) {
			return matrix[loc];
		}//operator[](int loc)

};//Matrix class
