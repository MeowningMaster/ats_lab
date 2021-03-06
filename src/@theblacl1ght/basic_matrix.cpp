#pragma once
#include "basic_matrix.hpp"

size_t matrix::to_degrees_two(const size_t& number) {
	size_t d_two = 2;
	while (number > d_two) { d_two = d_two << 1; }
	return d_two;
}

template<typename T>
bool matrix::is_correct_multiply_sizes(
	const Matrix<T>& first, const Matrix<T>& second)
{
	if (first[0].size() != second.size()) {
		return false;
	}
	return true;
}

template<typename T>
bool matrix::is_correct_addition_sizes(
	const Matrix<T>& first, const Matrix<T>& second) 
{
	if (first.size() != second.size() || first[0].size() != second[0].size()) {
		false;
	}
	return true;
}

template<typename T>
void matrix::to_square_matrix(
	Matrix<T>& matrix, const size_t& size)
{
	matrix.resize(size);
	for (auto& r : matrix) {
		r.resize(size, 0);
	}
}

template<typename T>
Matrix<T> matrix::classic_multiply(
	const Matrix<T>& lhs, const Matrix<T>& rhs)
{
	if (!is_correct_multiply_sizes(lhs, rhs)) {
		throw std::runtime_error("");
	}

	Matrix<T> result(lhs.size());
	for (size_t i = 0; i < lhs.size(); ++i) {
		result[i].resize(rhs[0].size());
		for (size_t j = 0; j < rhs[0].size(); ++j) {
			for (size_t k = 0; k < lhs[0].size(); ++k) {
				result[i][j] += lhs[i][k] * rhs[k][j];
			}
		}
	}
	return result;
}

template<typename T>
Matrix<T> matrix::add_matrix(
	Matrix<T> lhs, const Matrix<T>& rhs)
{
	if (!is_correct_addition_sizes(lhs, rhs)) {
		throw std::runtime_error("");
	}

	for (size_t i = 0; i < lhs.size(); ++i) {
		for (size_t j = 0; j < lhs[0].size(); ++j) {
			lhs[i][j] += rhs[i][j];
		}
	}
	return lhs;
}

template<typename T>
Matrix<T> matrix::sub_matrix(
	Matrix<T> lhs, const Matrix<T>& rhs)
{
	if (!is_correct_addition_sizes(lhs, rhs)) {
		throw std::runtime_error("");
	}

	for (size_t i = 0; i < lhs.size(); ++i) {
		for (size_t j = 0; j < lhs[0].size(); ++j) {
			lhs[i][j] -= rhs[i][j];
		}
	}
	return lhs;
}
