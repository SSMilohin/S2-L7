// Лабораторная работа №7 (2 семестр)
// 
// Возьмите за основу репозиторий mathutils и дополните в нем перегрузку для оператора умножения. Выполните перегрузку оператора вычитания. 
// Дополните класс методами для нахождения определителя матрицы размерами 2х2 и 3х3.Для других размеров предусмотрите сообщение «Операция не поддерживается».
// Дополните класс методом для нахождения обратной матрицы размером 2х2 и 3х3.Для остальных размеров предусмотрите сообщение «Операция не поддерживается».
// Дополните класс методами для нахождения транспонированной матрицы произвольного размера.
// Выполните проверку.
//

#include <iostream>

class Matrix {
public:
	Matrix(int n, int m)
	{
		m_n = n;
		m_m = m;
		m_mat = new int* [m_n];
		for (int i = 0; i < m_n; i++)
			m_mat[i] = new int[m_m];
	}

	Matrix(const Matrix& mat)
	{
		m_n = mat.m_n;
		m_m = mat.m_m;

		m_mat = new int* [m_n];
		for (int i = 0; i < m_n; i++)
			m_mat[i] = new int[m_m];

		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				m_mat[i][j] = mat.m_mat[i][j];
	}

	Matrix& operator=(const Matrix& mat)
	{
		m_n = mat.m_n;
		m_m = mat.m_m;

		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				m_mat[i][j] = mat.m_mat[i][j];

		return *this;
	}

	Matrix operator+(const Matrix& mat) {
		Matrix tmp(m_n, m_m);
		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
		return tmp;
	}

	Matrix operator+=(const Matrix& mat) {
		Matrix tmp(m_n, m_m);
		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
		return tmp;
	}

	Matrix operator*(const Matrix& mat) {
		Matrix tmp(m_n, m_m);
		for (int i = 0; i < m_n; i++) {
			for (int j = 0; j < mat.m_m; j++) {
				tmp.m_mat[i][j] = 0;
				for (int k = 0; k < m_m; k++)
					tmp.m_mat[i][j] += m_mat[i][k] * mat.m_mat[k][j];
			}
		}
		return tmp;
	}

	Matrix operator-(const Matrix& mat) {
		Matrix tmp(m_n, m_m);
		for (int i = 0; i < m_n; i++) {
			for (int j = 0; j < m_m; j++)
				tmp.m_mat[i][j] = m_mat[i][j] - mat.m_mat[i][j];
		}
		return tmp;
	}

	int determinant() {
		if (m_n != m_m || m_n > 3) {
			std::cout << "The operation is not supported." << std::endl;
			return -1;
		}
		if (m_n == 2) return m_mat[0][0] * m_mat[1][1] - m_mat[0][1] * m_mat[1][0];
		if (m_n == 3) return m_mat[0][0] * m_mat[1][1] * m_mat[2][2] 
						   + m_mat[0][1] * m_mat[1][2] * m_mat[2][0]
						   + m_mat[1][0] * m_mat[2][1] * m_mat[0][2] 
						   - m_mat[2][0] * m_mat[1][1] * m_mat[0][2] 
						   - m_mat[2][1] * m_mat[1][2] * m_mat[0][0] 
						   - m_mat[1][0] * m_mat[0][1] * m_mat[2][2];
		return -1;
	}

	Matrix transpose() {
		Matrix tr_mat(m_m, m_n);
		for (int i = 0; i < m_n; i++) {
			for (int j = 0; j < m_m; j++) {
				tr_mat.m_mat[i][j] = m_mat[j][i];
			}
		}
		return tr_mat;
	}

	Matrix inversion() {
		if (m_n != m_m) {
			std::cout << "This operation is only available for square matrixes." << std::endl;
			return *this;
		}
		if (m_n > 3) {
			std::cout << "The operation is not supported." << std::endl;
			return *this;
		}

		int det = determinant();
		if (det == 0) {
			std::cout << "Matrix has no inverse." << std::endl;
			return *this;
		}

		Matrix tmp(m_n, m_m);
		if (m_n == 2)
		{
			tmp.m_mat[0][0] = m_mat[1][1] / det;
			tmp.m_mat[0][1] = -m_mat[0][1] / det;
			tmp.m_mat[1][0] = -m_mat[1][0] / det;
			tmp.m_mat[1][1] = m_mat[0][0] / det;
			return tmp;
		}
		if (m_n == 3) {
			tmp.m_mat[0][0] = (m_mat[1][1] * m_mat[2][2] - m_mat[2][1] * m_mat[1][2]) / det;
			tmp.m_mat[1][0] = -(m_mat[1][0] * m_mat[2][2] - m_mat[2][0] * m_mat[1][2]) / det;
			tmp.m_mat[2][0] = (m_mat[1][0] * m_mat[2][1] - m_mat[2][0] * m_mat[1][1]) / det;
			tmp.m_mat[0][1] = -(m_mat[0][1] * m_mat[2][2] - m_mat[2][1] * m_mat[0][2]) / det;
			tmp.m_mat[1][1] = (m_mat[0][0] * m_mat[2][2] - m_mat[2][0] * m_mat[0][2]) / det;
			tmp.m_mat[2][1] = -(m_mat[0][0] * m_mat[2][1] - m_mat[2][0] * m_mat[0][1]) / det;
			tmp.m_mat[0][2] = (m_mat[0][1] * m_mat[1][2] - m_mat[1][1] * m_mat[0][2]) / det;
			tmp.m_mat[1][2] = -(m_mat[0][0] * m_mat[1][2] - m_mat[1][0] * m_mat[0][2]) / det;
			tmp.m_mat[2][2] = (m_mat[0][0] * m_mat[1][1] - m_mat[1][0] * m_mat[0][1]) / det;
			return tmp;
		}
	}

	~Matrix()
	{
		for (int i = 0; i < m_n; i++)
			delete[] m_mat[i];
		delete m_mat;
	}

	friend std::istream& operator>>(std::istream& os, Matrix& mat);
	friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);

private:
	int m_n, m_m;
	int n;
	int** m_mat;
};

std::istream& operator>>(std::istream& in, Matrix& mat)
{
	for (int i = 0; i < mat.m_n; i++)
		for (int j = 0; j < mat.m_m; j++)
			in >> mat.m_mat[i][j];
	return in;
}

std::ostream& operator<<(std::ostream& out, const Matrix& mat)
{
	out << "Matrix " << mat.m_n << "x" << mat.m_m << std::endl;
	for (int i = 0; i < mat.m_n; i++) {
		for (int j = 0; j < mat.m_m; j++)
			out << mat.m_mat[i][j] << " ";
		out << std::endl;
	}
	return out;
}

int main()
{
	Matrix A(2, 2);
	std::cin >> A;
	std::cout << A << std::endl;

	Matrix B(2, 2); 
	B = A + A;
	std::cout << B << std::endl;

	Matrix C(2, 2);
	C = A * A;
	std::cout << C << std::endl;
	
	std::cout << "matrix A (transpose):" << std::endl << A.transpose() << std::endl;
	std::cout << "det(A) = " << A.determinant() << std::endl;
	std::cout << "matrix A (inverse):" << std::endl << A.inversion() << std::endl;

	return 0;
}