#ifndef SCALARMATRIX_H
#define SCALARMATRIX_H

#include <iostream>
#include <memory>

class ScalarMatrix
{
public:
ScalarMatrix(int, int);
ScalarMatrix();
ScalarMatrix(const ScalarMatrix&);
ScalarMatrix& operator=(const ScalarMatrix&);
~ScalarMatrix() {}

inline float& operator()(int, int);
inline const float operator()(int, int) const;

ScalarMatrix& operator+=(const ScalarMatrix&);
ScalarMatrix  operator+(const ScalarMatrix&);

ScalarMatrix& operator-=(const ScalarMatrix&);
ScalarMatrix  operator-(const ScalarMatrix&);

ScalarMatrix& operator*=(const ScalarMatrix&);
ScalarMatrix  operator*(const ScalarMatrix&);

ScalarMatrix& operator*=(float);
ScalarMatrix  operator*(float);

ScalarMatrix& operator/=(float);
ScalarMatrix  operator/(float);

float Determinant(const ScalarMatrix&, size_t) const;

void Zero();
void Randomize(int max = 1024);

ScalarMatrix Transpose() const;
ScalarMatrix& Transpose();

void Cofactor(const ScalarMatrix&, ScalarMatrix&, size_t, size_t, size_t) const;
ScalarMatrix Adjoint() const;
ScalarMatrix Inverse() const;

static ScalarMatrix CreateIdentity(size_t size);

friend std::istream& operator>>(std::istream&, ScalarMatrix&);
friend std::ostream& operator<<(std::ostream&, const ScalarMatrix&);

private:
size_t m_Rows, m_Columns;
std::unique_ptr<std::unique_ptr<float[]>[]> m_Buffer;

void AllocateSpace();
};

#endif // !SCALARMATRIX_H