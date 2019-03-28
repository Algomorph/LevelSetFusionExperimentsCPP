/*
 * collection_comparison.tpp
 *
 *  Created on: Mar 26, 2019
 *      Author: Gregory Kramida
 *   Copyright: 2019 Gregory Kramida
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#pragma once

//local
#include "typedefs.hpp"
#include "collection_comparison.hpp"

namespace math {

template<typename TReal>
bool almost_equal_relative(TReal a, TReal b, TReal epsilon = 3e-6) {
	const TReal absA = std::abs(a);
	const TReal absB = std::abs(b);
	const TReal diff = std::abs(a - b);

	if (a == b) { // shortcut, handles infinities
		return true;
	} else if (a == 0 || b == 0 || diff < std::numeric_limits<TReal>::denorm_min()) {
		// a or b is zero or both are extremely close to it
		// relative error is less meaningful here
		return diff < (epsilon * std::numeric_limits<TReal>::denorm_min());
	} else { // use relative error
		return diff / std::min((absA + absB), std::numeric_limits<TReal>::max()) < epsilon;
	}
}

template<typename TReal>
bool almost_equal_absolute(TReal a, TReal b, TReal epsilon = 3e-6) {
	return std::abs(a - b) < epsilon;
}

template<>
bool almost_equal<float>(float a, float b) {
	return almost_equal_absolute(a, b);
}

template<>
bool almost_equal<float, float>(float a, float b, float tolerance) {
	return almost_equal_absolute(a, b, tolerance);
}

template<>
bool almost_equal<float, double>(float a, float b, double tolerance) {
	return almost_equal_absolute(a, b, static_cast<float>(tolerance));
}

template<>
bool almost_equal<double, double>(double a, double b, double tolerance) {
	return almost_equal_absolute(a, b, tolerance);
}

template<>
bool almost_equal<math::Vector2f, float>(math::Vector2f a, math::Vector2f b, float tolerance) {
	return almost_equal_absolute(a.x, b.x, tolerance) && almost_equal_absolute(a.y, b.y, tolerance);
}

template<>
bool almost_equal<math::Vector2f, double>(math::Vector2f a, math::Vector2f b, double tolerance) {
	float tol_f = static_cast<float>(tolerance);
	return almost_equal_absolute(a.x, b.x, tol_f) && almost_equal_absolute(a.y, b.y, tol_f);
}

template<>
bool almost_equal<math::Matrix2f, float>(math::Matrix2f a, math::Matrix2f b, float tolerance) {
	return almost_equal_absolute(a.xy00, b.xy00, tolerance) && almost_equal_absolute(a.xy01, b.xy01, tolerance) &&
			almost_equal_absolute(a.xy10, b.xy10, tolerance) && almost_equal_absolute(a.xy11, b.xy11, tolerance);
}

template<>
bool almost_equal<math::Matrix2f, double>(math::Matrix2f a, math::Matrix2f b, double tolerance) {
	float tol_f = static_cast<float>(tolerance);
	return almost_equal_absolute(a.xy00, b.xy00, tol_f) && almost_equal_absolute(a.xy01, b.xy01, tol_f) &&
			almost_equal_absolute(a.xy10, b.xy10, tol_f) && almost_equal_absolute(a.xy11, b.xy11, tol_f);
}

template<>
bool almost_equal<math::Vector3f, float>(math::Vector3f a, math::Vector3f b, float tolerance) {
	return almost_equal_absolute(a.x, b.x, tolerance)
			&& almost_equal_absolute(a.y, b.y, tolerance)
			&& almost_equal_absolute(a.z, b.z, tolerance);
}

template<>
bool almost_equal<math::Vector3f, double>(math::Vector3f a, math::Vector3f b, double tolerance) {
	float tol_f = static_cast<float>(tolerance);
	return almost_equal_absolute(a.x, b.x, tol_f) && almost_equal_absolute(a.y, b.y, tol_f)
			&& almost_equal_absolute(a.z, b.z, tol_f);
}

template<typename TTensor, typename TReportFunction>
bool compare_tensor_dimensions(TTensor tensor_a, TTensor tensor_b, TReportFunction&& report_function) {
	for (int i_dim = 0; i_dim < TTensor::NumDimensions; i_dim++) {
		if (tensor_a.dimension(i_dim) != tensor_b.dimension(i_dim)) {
			std::forward<TReportFunction>(report_function)(tensor_a, tensor_b, i_dim);
			return false;
		}
	}
	return true;
}

template<typename TTensor>
bool compare_tensor_dimensions_silent(TTensor tensor_a, TTensor tensor_b) {
	return compare_tensor_dimensions(tensor_a, tensor_b,
			[](TTensor tensor_a, TTensor tensor_b, int i_dim) -> void {});
}

template<typename TTensor>
bool compare_tensor_dimensions_verbose(TTensor tensor_a, TTensor tensor_b) {
	return compare_tensor_dimensions(tensor_a, tensor_b,
			[](TTensor tensor_a, TTensor tensor_b, int i_dim) -> void {
				std::cout << "Tensor dimension " << i_dim << " (0-based) doesn't match. Tensor a dimension: "
				<< tensor_a.dimension(i_dim) << ". Corresponding tensor b dimension: " <<
				tensor_b.dimension(i_dim) << std::endl;
			});
}

template<typename TMatrix, typename TReportFunction>
bool compare_matrix_dimensions(TMatrix matrix_a, TMatrix matrix_b, TReportFunction&& report_function) {
	if (matrix_a.rows() != matrix_b.rows() || matrix_a.cols() != matrix_b.rows()) {
		std::forward<TReportFunction>(report_function)(matrix_a, matrix_b);
		std::cout << "Matrix dimensions don't match. Matrix a: " << matrix_a.cols() << " columns by " << matrix_a.rows()
				<< " rows, Matrix b: " << matrix_b.cols() << " columns by " << matrix_b.rows() << " rows."
				<< std::endl;
		return false;
	}
	return true;
}

template<typename TMatrix>
bool compare_matrix_dimensions_silent(TMatrix matrix_a, TMatrix matrix_b) {
	return compare_matrix_dimensions(matrix_a, matrix_b, [](TMatrix matrix_a, TMatrix matrix_b) -> void {});
}

template<typename TMatrix>
bool compare_matrix_dimensions_verbose(TMatrix matrix_a, TMatrix matrix_b) {
	return compare_matrix_dimensions(matrix_a, matrix_b, [](TMatrix matrix_a, TMatrix matrix_b) -> void {
		std::cout << "Matrix dimensions don't match. Matrix a: " << matrix_a.cols() << " columns by " << matrix_a.rows()
		<< " rows, Matrix b: " << matrix_b.cols() << " columns by " << matrix_b.rows() << " rows."
		<< std::endl;
	}
			);
}

template<typename TEigenContainer, typename TBaseElementType, typename LambdaCompareDimensions,
		typename LambdaPrintLocalError>
bool almost_equal_generic(TEigenContainer container_a, TEigenContainer container_b,
		LambdaCompareDimensions&& compare_dimensions,
		LambdaPrintLocalError&& print_local_error,
		TBaseElementType tolerance
		) {
	std::forward<LambdaCompareDimensions>(compare_dimensions)(container_a, container_b);
	for (Eigen::Index index = 0; index < container_a.size(); index++) {
		if (!almost_equal(container_a(index), container_b(index), tolerance)) {
			std::forward<LambdaPrintLocalError>(print_local_error)(container_a, container_b, index);
			return false;
		}
	}
	return true;
}

template<typename TMatrix, typename TBaseElementType>
bool matrix_almost_equal(TMatrix matrix_a, TMatrix matrix_b, TBaseElementType tolerance) {
	return almost_equal_generic(matrix_a, matrix_b, compare_matrix_dimensions_silent<TMatrix>,
			[](TMatrix a, TMatrix b, Eigen::Index index) -> void {}, tolerance);
}

template<typename TMatrix, typename TBaseElementType>
bool matrix_almost_equal_verbose(TMatrix matrix_a, TMatrix matrix_b, TBaseElementType tolerance) {
	return almost_equal_generic(matrix_a, matrix_b, compare_matrix_dimensions_verbose<TMatrix>,
			[](TMatrix matrix_a, TMatrix matrix_b, Eigen::Index index) -> void {
				long x = index / matrix_a.cols();
				long y = index % matrix_a.cols();
				std::cout << "Matrix entries are not within tolerance threshold of each other. "
				"First mismatch at row " << y << ", column " << x << ". " << "Values: "
				<< matrix_a(index) << " vs. " << matrix_b(index) << ", difference: "
				<< matrix_a(index) - matrix_b(index) << std::endl;
			},
			tolerance);
}

typedef Eigen::Tensor<float, 3> TenF3;

template<typename TTensor>
inline std::vector<int> unravel_index(TTensor container, Eigen::Index index) {
	std::vector<int> unraveled_index;
	long remainder = static_cast<long>(index);
	for (int i_dimension = 0; i_dimension < TTensor::NumDimensions; i_dimension++) {
		int dimension = container.dimension(i_dimension);
		long new_remainder = remainder / dimension;
		unraveled_index.push_back(remainder % dimension);
		remainder = new_remainder;
	}
	return unraveled_index;
}
template<typename TTensor, typename TBaseElementType>
bool tensor_almost_equal(TTensor container_a, TTensor container_b, TBaseElementType tolerance) {
	return almost_equal_generic(container_a, container_b, compare_tensor_dimensions_silent<TTensor>,
			[](TTensor container_a, TTensor container_b, Eigen::Index index)-> void {},
			tolerance
			);
}
template<typename TTensor, typename TBaseElementType>
bool tensor_almost_equal_verbose(TTensor container_a, TTensor container_b, TBaseElementType tolerance) {
	return almost_equal_generic(
			container_a, container_b, compare_tensor_dimensions_verbose<TTensor>,
			[](TTensor container_a, TTensor container_b, Eigen::Index index) -> void {
				std::vector<int> unraveled_index = unravel_index(container_a, index); // @suppress("Invalid arguments")
				const typename TTensor::Scalar& a = container_a(index);
				const typename TTensor::Scalar& b = container_b(index);
				std::cout << "Tensor elements do not match. First mismatch at linear index " << unraveled_index[0];
				for (size_t ix_index = 1; ix_index < unraveled_index.size(); ix_index++) {
					std::cout << ", " << unraveled_index[ix_index];
				}
				std::cout << ". Values: " << a << " vs. " << b << ". Absolute difference: " << (a-b) << "."
						<< std::endl;
			},
			tolerance);
}

} // namespace math
