#include "ScalarMatrix.hpp"

#include <cstdlib>

ScalarMatrix::ScalarMatrix(int rows, int columns)
	: m_Rows(rows), m_Columns(columns)
{
	AllocateSpace();
}

ScalarMatrix::ScalarMatrix() : m_Rows(0), m_Columns(0), m_Buffer(nullptr) { }

ScalarMatrix::ScalarMatrix(const ScalarMatrix& other)
	: m_Rows(other.m_Rows), m_Columns(other.m_Columns)
{
	AllocateSpace();

	for (int i = 0; i < m_Rows; ++i)
		for (int j = 0; j < m_Columns; ++j)
			m_Buffer[i][j] = other.m_Buffer[i][j];
}

ScalarMatrix& ScalarMatrix::operator=(const ScalarMatrix& other)
{
	if (this == &other)
		return *this;

	if (m_Rows != other.m_Rows || m_Columns != other.m_Columns) 
	{
		m_Buffer.release();

		m_Rows = other.m_Rows;
		m_Columns = other.m_Columns;
		AllocateSpace();
	}

	for (int i = 0; i < m_Rows; ++i)
		for (int j = 0; j < m_Columns; ++j)
			m_Buffer[i][j] = other.m_Buffer[i][j];

	return *this;
}

inline float& ScalarMatrix::operator()(int x, int y)
{
	return m_Buffer[x][y];
}

inline const float ScalarMatrix::operator()(int x, int y) const
{
	return m_Buffer[x][y];
}

ScalarMatrix& ScalarMatrix::operator+=(const ScalarMatrix& other)
{
	// This Operation can only be performed on matrices of equal dimensions.
	if (m_Rows != other.m_Rows || m_Columns != other.m_Columns)
		return *this;

	for (int i = 0; i < m_Rows; ++i)
		for (int j = 0; j < m_Columns; ++j)
			m_Buffer[i][j] += other.m_Buffer[i][j];

	return *this;
}

ScalarMatrix ScalarMatrix::operator+(const ScalarMatrix& other)
{
	// This Operation can only be performed on matrices of equal dimensions.
	if (m_Rows != other.m_Rows || m_Columns != other.m_Columns)
		return *this;

	ScalarMatrix res(*this);

	for (int i = 0; i < m_Rows; ++i)
		for (int j = 0; j < m_Columns; ++j)
			res.m_Buffer[i][j] += other.m_Buffer[i][j];

	return res;
}

ScalarMatrix& ScalarMatrix::operator-=(const ScalarMatrix& other)
{
	// This Operation can only be performed on matrices of equal dimensions.
	if (m_Rows != other.m_Rows || m_Columns != other.m_Columns)
		return *this;

	for (int i = 0; i < m_Rows; ++i)
		for (int j = 0; j < m_Columns; ++j)
			m_Buffer[i][j] -= other.m_Buffer[i][j];

	return *this;
}

ScalarMatrix ScalarMatrix::operator-(const ScalarMatrix& other)
{
	// This Operation can only be performed on matrices of equal dimensions.
	if (m_Rows != other.m_Rows || m_Columns != other.m_Columns)
		return *this;

	ScalarMatrix res(*this);

	for (int i = 0; i < m_Rows; ++i)
		for (int j = 0; j < m_Columns; ++j)
			res.m_Buffer[i][j] -= other.m_Buffer[i][j];

	return res;
}

ScalarMatrix& ScalarMatrix::operator*=(const ScalarMatrix& other)
{
	if (m_Columns != other.m_Rows) return *this;

	ScalarMatrix mult(m_Rows, other.m_Columns);

	// Multiplying matrix a and b and storing in array mult.
	for (int i = 0; i < m_Rows; ++i)
		for (int j = 0; j < other.m_Columns; ++j)
			for (int k = 0; k < m_Columns; ++k)
				mult.m_Buffer[i][j] += m_Buffer[i][k] * other.m_Buffer[k][j];
	
	return (*this = mult);
}

ScalarMatrix ScalarMatrix::operator*(const ScalarMatrix& other)
{
	if (m_Columns != other.m_Rows) return *this;

	ScalarMatrix mult(m_Rows, other.m_Columns);

	// Multiplying matrix a and b and storing in array mult.
	for (int i = 0; i < m_Rows; ++i)
		for (int j = 0; j < other.m_Columns; ++j)
			for (int k = 0; k < m_Columns; ++k)
				mult.m_Buffer[i][j] += m_Buffer[i][k] * other.m_Buffer[k][j];

	return mult;
}

ScalarMatrix& ScalarMatrix::operator*=(float value)
{
	for (int i = 0; i < m_Rows; ++i)
		for (int j = 0; j < m_Columns; ++j)
			m_Buffer[i][j] *= value;

	return *this;
}

ScalarMatrix ScalarMatrix::operator*(float value)
{
	ScalarMatrix res(*this);

	for (int i = 0; i < m_Rows; ++i)
		for (int j = 0; j < m_Columns; ++j)
			res.m_Buffer[i][j] *= value;

	return res;
}

ScalarMatrix& ScalarMatrix::operator/=(float value)
{
	for (int i = 0; i < m_Rows; ++i)
		for (int j = 0; j < m_Columns; ++j)
			m_Buffer[i][j] /= value;

	return *this;
}

ScalarMatrix ScalarMatrix::operator/(float value)
{
	ScalarMatrix res(*this);

	for (int i = 0; i < m_Rows; ++i)
		for (int j = 0; j < m_Columns; ++j)
			res.m_Buffer[i][j] /= value;

	return res;
}

void ScalarMatrix::Zero()
{
	for (int i = 0; i < m_Rows; ++i)
		for (int j = 0; j < m_Columns; ++j)
			m_Buffer[i][j] = 0.0f;
}

void ScalarMatrix::Randomize(int max)
{
	for (int i = 0; i < m_Rows; ++i)
		for (int j = 0; j < m_Columns; ++j)
			m_Buffer[i][j] = std::rand() % max;
}

ScalarMatrix ScalarMatrix::Transpose() const
{
	ScalarMatrix transpose(m_Columns, m_Rows);
	for (int i = 0; i < m_Rows; ++i) {
		for (int j = 0; j < m_Columns; ++j) {
			transpose.m_Buffer[j][i] = m_Buffer[i][j];
		}
	}
	return transpose;
}

ScalarMatrix& ScalarMatrix::Transpose()
{
	ScalarMatrix transpose(m_Columns, m_Rows);
	for (int i = 0; i < m_Rows; ++i)
		for (int j = 0; j < m_Columns; ++j)
			transpose.m_Buffer[j][i] = m_Buffer[i][j];

	return (*this = transpose);
}

void ScalarMatrix::Cofactor(const ScalarMatrix& source, ScalarMatrix& cofactor, size_t p, size_t q, size_t n) const
{
	// This operation is applicable only on square matrices.
	if (source.m_Rows != source.m_Columns || cofactor.m_Rows != source.m_Rows || cofactor.m_Columns != source.m_Columns ) 
		return;

	int i = 0, j = 0;

	// Looping for each element of the matrix
	for (int row = 0; row < n; row++) 
	{
		for (int col = 0; col < n; col++)
		{
			//  Copying into cofactor matrix only those
			//  element which are not in given row and
			//  column
			if (row != p && col != q) 
			{
				cofactor.m_Buffer[i][j++] = source.m_Buffer[row][col];

				// Row is filled, so increase row index and
				// reset col index
				if (j == n - 1)
				{
					j = 0;
					i++;
				}
			}
		}
	}

	return;
}

float ScalarMatrix::Determinant(const ScalarMatrix& a, size_t n) const
{
	// This operation is applicable only on square matrices.
	if (a.m_Rows != a.m_Columns) return 0.0f;

	float det = 0.0f;

	//  Base case : if matrix contains single element
	if (n == 1)
		return a.m_Buffer[0][0];

	ScalarMatrix cofactors(a.m_Rows, a.m_Columns); // To store cofactors

	int sign = 1; // To store sign multiplier

	// Iterate for each element of first row
	for (int f = 0; f < n; f++)
	{
		// Getting Cofactor of a[0][f]
		Cofactor(a, cofactors, 0, f, n);

		det += sign * a.m_Buffer[0][f] * Determinant(a, n - 1);

		// terms are to be added with alternate sign
		sign = -sign;
	}

	return det;
}

ScalarMatrix ScalarMatrix::Adjoint() const
{
	// This operation is applicable only on square matrices.
	if (m_Rows != m_Columns) return *this;

	ScalarMatrix adjoint(m_Rows, m_Columns);

	if (m_Rows == 1)
	{
		adjoint.m_Buffer[0][0] = 1;
		return adjoint;
	}

	int sign = 1;
	ScalarMatrix cofactors(m_Rows, m_Columns);

	for (int i = 0; i < m_Rows; i++) 
	{
		for (int j = 0; j < m_Columns; j++)
		{
			// Get cofactor of (*this)[i][j]
			Cofactor(*this, cofactors, i, j, m_Rows);

			// sign of adj[j][i] positive if sum of row
			// and column indexes is even.
			sign = ((i + j) % 2 == 0) ? 1 : -1;

			// Interchanging rows and columns to get the
			// transpose of the cofactor matrix
			adjoint.m_Buffer[j][i] = (sign) * (Determinant(cofactors, m_Rows - 1));
		}
	}

	return adjoint;
}

ScalarMatrix ScalarMatrix::Inverse() const
{
	// This operation is applicable only on square matrices.
	if (m_Rows != m_Columns) return *this;

	// Find determinant of (*this)[][]
	float det = Determinant(*this, m_Rows);

	// There is no inverse for Singular Matrix.
	if (det == 0) return *this;

	// Find adjoint.
	ScalarMatrix adjoint(m_Rows, m_Columns);
	adjoint = Adjoint();

	ScalarMatrix inverse(m_Rows, m_Columns);

	// Find Inverse using formula "inverse(A) =
	// adjoint(A)/determinant(A)"
	for (int i = 0; i < m_Rows; i++)
		for (int j = 0; j < m_Columns; j++)
			inverse.m_Buffer[i][j] = adjoint.m_Buffer[i][j] / det;

	return inverse;
}

ScalarMatrix ScalarMatrix::CreateIdentity(size_t size)
{
	ScalarMatrix identity(size, size);
	for (int i = 0; i < identity.m_Rows; ++i)
		for (int j = 0; j < identity.m_Columns; ++j)
			identity.m_Buffer[i][j] = (i == j) ? 1 : 0;

	return identity;
}

void ScalarMatrix::AllocateSpace()
{
	m_Buffer = std::make_unique<std::unique_ptr<float[]>[]>(m_Rows);
	for (int i = 0; i < m_Rows; i++)
		m_Buffer[i] = std::make_unique<float[]>(m_Columns);
}

std::istream& operator>>(std::istream& is, ScalarMatrix& m)
{
	for (int i = 0; i < m.m_Rows; ++i) 
		for (int j = 0; j < m.m_Columns; ++j)
			is >> m.m_Buffer[i][j];

	return is;
}

std::ostream& operator<<(std::ostream& os, const ScalarMatrix& m)
{
	for (int i = 0; i < m.m_Rows; ++i) 
	{
		os << m.m_Buffer[i][0];
		for (int j = 1; j < m.m_Columns; ++j)
			os << " " << m.m_Buffer[i][j];
		os << std::endl;
	}

	return os;
}