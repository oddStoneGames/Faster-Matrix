#include "ScalarMatrix.hpp"
#include <iostream>
#include <chrono>
#include <vector>

void ScalarMatrixBenchmark()
{
	std::vector<ScalarMatrix> matrices1, matrices2, results;

	for (int i = 1; i <= 200; i++)
	{
		matrices1.push_back(ScalarMatrix(i, i));
		matrices2.push_back(ScalarMatrix(i, i));
		results.push_back(ScalarMatrix(i, i));
		matrices1[i - 1].Randomize();
		matrices2[i - 1].Randomize();
	}

	// Perform Multiplication on 400 Matrices.
	auto startTime = std::chrono::high_resolution_clock::now();

	for (volatile int i = 0; i < 200; i++)
		results[i] = matrices1[i] * matrices2[i];

	auto endTime = std::chrono::high_resolution_clock::now();

	long long start = std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch().count();
	long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();
	float timeTaken = (float)(end - start) / 1000.0f;

	std::cout << "Time taken to multiply 400 1x1 to 200x200 scalar matrices is: " << timeTaken << " ms\n";

	// Perform Transpose on 400 Matrices.
	startTime = std::chrono::high_resolution_clock::now();

	for (volatile int i = 0; i < 200; i++)
	{
		matrices1[i].Transpose();
		matrices2[i].Transpose();
	}
	endTime = std::chrono::high_resolution_clock::now();

	start = std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch().count();
	end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();
	timeTaken = (float)(end - start) / 1000.0f;

	std::cout << "Time taken to transpose 400 1x1 to 200x200 scalar matrices is: " << timeTaken << " ms\n";

	// Perform Inverse on 400 Matrices.
	startTime = std::chrono::high_resolution_clock::now();

	for (volatile int i = 0; i < 10; i++)
	{
		matrices1[i].Inverse();
		matrices2[i].Inverse();
	}

	endTime = std::chrono::high_resolution_clock::now();

	start = std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch().count();
	end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();
	timeTaken = (float)(end - start) / 1000.0f;

	std::cout << "Time taken to inverse 20 1x1 to 9x9 scalar matrices is: " << timeTaken << " ms\n";

}

int main()
{
	ScalarMatrixBenchmark();
	return 0;
}