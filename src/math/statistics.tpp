/*
 * statistics.tpp
 *
 *  Created on: Apr 9, 2019
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

//stdlib
#include <atomic>

//local
#include "statistics.hpp"
#include "stacking.hpp"
#include "vector_operations.hpp"
#include "../traversal/field_traversal_cpu.hpp"
#include "../traversal/index_raveling.hpp"
#include "../error_handling/throw_assert.hpp"

namespace math {

template<typename Scalar>

struct ValueAndCoordinates2d {
	ValueAndCoordinates2d() = default;
	ValueAndCoordinates2d(Scalar squared_norm, math::Vector2i coordinates) :
			value(squared_norm), coordinates(coordinates) {
	}
	Scalar value = 0.0f;
	math::Vector2i coordinates = math::Vector2i(0);
};

template<typename Scalar>
struct ValueAndCoordinates3d {
	ValueAndCoordinates3d() = default;
	ValueAndCoordinates3d(Scalar squared_norm, math::Vector3i coordinates) :
			value(squared_norm), coordinates(coordinates) {
	}
	Scalar value = 0.0f;
	math::Vector3i coordinates = math::Vector3i(0);
};

template<typename Scalar>
void locate_max_norm(typename Scalar::Scalar& max_norm, math::Vector2i& coordinates,
		const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor>& vector_field) {
	typename Scalar::Scalar max_squared_norm = 0;
	coordinates = math::Vector2i(0);
	int column_count = static_cast<int>(vector_field.cols());

	for (eig::Index i_element = 0; i_element < vector_field.size(); i_element++) {
		typename Scalar::Scalar squared_length = math::squared_norm(vector_field(i_element)); // @suppress("Function cannot be resolved")
		if (squared_length > max_squared_norm) {
			max_squared_norm = squared_length;
			coordinates.x = i_element / column_count;
			coordinates.y = i_element % column_count;
		}
	}
	max_norm = std::sqrt(max_squared_norm);
}

template<typename Scalar>
void locate_max_norm(typename Scalar::Scalar& max_norm, math::Vector3i& coordinates,
		const Eigen::Tensor<Scalar, 3, Eigen::ColMajor>& vector_field) {
	int matrix_size = static_cast<int>(vector_field.size());
	int y_stride = vector_field.dimension(0);
	int z_stride = y_stride * vector_field.dimension(1);

	std::atomic<ValueAndCoordinates3d<typename Scalar::Scalar>> max_norm_and_coordinate { { 0.0f, math::Vector3i(0) } };

#pragma omp parallel for
	for (int i_element = 0; i_element < matrix_size; i_element++) {
		int x, y, z;
		traversal::unravel_3d_index(x, y, z, i_element, y_stride, z_stride);
		ValueAndCoordinates3d<typename Scalar::Scalar> last_max_norm = max_norm_and_coordinate.load(); // @suppress("Invalid arguments")
		ValueAndCoordinates3d<typename Scalar::Scalar> new_norm;
		do {
			new_norm = last_max_norm;
			new_norm.value = math::squared_norm(vector_field(i_element)); // @suppress("Function cannot be resolved")
			new_norm.coordinates = math::Vector3i(x, y, z);
		} while (new_norm.value > last_max_norm.value &&
				!max_norm_and_coordinate.compare_exchange_strong(last_max_norm, new_norm));
	}
	ValueAndCoordinates3d<typename Scalar::Scalar> last_max_norm = max_norm_and_coordinate.load(); // @suppress("Invalid arguments")
	max_norm = std::sqrt(last_max_norm.value);
	coordinates = last_max_norm.coordinates;
}

template<typename Scalar>
void locate_min_norm(typename Scalar::Scalar& min_norm, math::Vector2i& coordinates,
		const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor>& vector_field) {
	int column_count = static_cast<int>(vector_field.cols());

	ValueAndCoordinates2d<typename Scalar::Scalar> initial_norm_and_coordinates;
	initial_norm_and_coordinates.value = std::numeric_limits<typename Scalar::Scalar>::max();
	std::atomic<ValueAndCoordinates2d<typename Scalar::Scalar>> squared_norm_and_coordinates(initial_norm_and_coordinates);

#pragma omp parallel for
	for (eig::Index i_element = 0; i_element < vector_field.size(); i_element++) {
		float squared_length = math::squared_norm(vector_field(i_element)); // @suppress("Function cannot be resolved")
		ValueAndCoordinates2d<typename Scalar::Scalar> last_best = squared_norm_and_coordinates.load(); // @suppress("Invalid arguments")
		ValueAndCoordinates2d<typename Scalar::Scalar> new_best;
		do {
			new_best = last_best;
			new_best.value = squared_length;
			new_best.coordinates.x = i_element / column_count;
			new_best.coordinates.y = i_element % column_count;
		} while (new_best.value < last_best.value
				&& !squared_norm_and_coordinates.compare_exchange_strong(last_best, new_best));
	}
	ValueAndCoordinates2d<typename Scalar::Scalar> last_best = squared_norm_and_coordinates.load(); // @suppress("Invalid arguments")
	min_norm = std::sqrt(last_best.value);
	coordinates = last_best.coordinates;
}

template<typename Scalar>
void locate_min_norm(typename Scalar::Scalar& min_norm, math::Vector3i& coordinates,
		const Eigen::Tensor<Scalar, 3, Eigen::ColMajor>& vector_field) {
	int matrix_size = static_cast<int>(vector_field.size());
	int y_stride = vector_field.dimension(0);
	int z_stride = y_stride * vector_field.dimension(1);

	std::atomic<ValueAndCoordinates3d<typename Scalar::Scalar>>
	min_norm_and_coordinates { { std::numeric_limits<typename Scalar::Scalar>::max(), math::Vector3i(0) } };

#pragma omp parallel for
	for (int i_element = 0; i_element < matrix_size; i_element++) {
		int x, y, z;
		traversal::unravel_3d_index(x, y, z, i_element, y_stride, z_stride);
		ValueAndCoordinates3d<typename Scalar::Scalar> last_min_norm = min_norm_and_coordinates.load();
		ValueAndCoordinates3d<typename Scalar::Scalar> new_norm;
		do {
			new_norm = last_min_norm;
			new_norm.value = math::squared_norm(vector_field(i_element)); // @suppress("Function cannot be resolved")
			new_norm.coordinates = math::Vector3i(x, y, z);
		} while (new_norm.value < last_min_norm.value &&
				!min_norm_and_coordinates.compare_exchange_strong(last_min_norm, new_norm));
	}
	ValueAndCoordinates3d<typename Scalar::Scalar> last_max_norm = min_norm_and_coordinates.load();
	min_norm = std::sqrt(last_max_norm.value);
	coordinates = math::Vector3i(last_max_norm.coordinates.x, last_max_norm.coordinates.y, last_max_norm.coordinates.z);
}

template<typename Scalar>
void locate_maximum(Scalar& maximum, math::Vector2i& coordinates,
		const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor>& scalar_field){
	maximum = scalar_field.maxCoeff(&coordinates.y, &coordinates.x);
}

template<typename Scalar>
void locate_maximum(Scalar& maximum, math::Vector3i& coordinates,
		const Eigen::Tensor<Scalar, 3, Eigen::ColMajor>& scalar_field) {
	int matrix_size = static_cast<int>(scalar_field.size());
	int y_stride = scalar_field.dimension(0);
	int z_stride = y_stride * scalar_field.dimension(1);

	std::atomic<ValueAndCoordinates3d<Scalar>> max_norm_and_coordinate { { 0.0f, math::Vector3i(0) } };

#pragma omp parallel for
	for (int i_element = 0; i_element < matrix_size; i_element++) {
		int x, y, z;
		traversal::unravel_3d_index(x, y, z, i_element, y_stride, z_stride);
		ValueAndCoordinates3d<Scalar> last_max_norm = max_norm_and_coordinate.load(); // @suppress("Invalid arguments")
		ValueAndCoordinates3d<Scalar> new_norm;
		do {
			new_norm = last_max_norm;
			new_norm.value = scalar_field(i_element);
			new_norm.coordinates = math::Vector3i(x, y, z);
		} while (new_norm.value > last_max_norm.value &&
				!max_norm_and_coordinate.compare_exchange_strong(last_max_norm, new_norm));
	}
	ValueAndCoordinates3d<Scalar> last_max_norm = max_norm_and_coordinate.load();
	maximum = last_max_norm.value;
	coordinates = last_max_norm.coordinates;
}

template<typename Container, typename OutType>
static inline
OutType max_norm_aux(const Container& vector_field) {
	std::atomic<OutType> max_norm_container(0);

#pragma omp parallel for
	for (eig::Index i_element = 0; i_element < vector_field.size(); i_element++) {
		float squared_length = math::squared_norm(vector_field(i_element)); // @suppress("Function cannot be resolved")
		float max_squared_norm = max_norm_container.load();
		while (squared_length > max_squared_norm
				&& !max_norm_container.compare_exchange_weak(max_squared_norm, squared_length));
	}
	return std::sqrt(max_norm_container.load());
}

template<typename Scalar>
typename Scalar::Scalar max_norm(const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor>& vector_field) {
	return max_norm_aux<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor>, typename Scalar::Scalar >(vector_field);
}

template<typename Scalar>
typename Scalar::Scalar max_norm(const Eigen::Tensor<Scalar, 3, Eigen::ColMajor>& vector_field) {
	return max_norm_aux<Eigen::Tensor<Scalar, 3, Eigen::ColMajor>, typename Scalar::Scalar >(vector_field);
}

template<typename Container, typename OutType>
static inline
OutType min_norm_aux(const Container& vector_field) {
	std::atomic<OutType> min_norm_container(std::numeric_limits<OutType>::max());
#pragma omp parallel for
	for (eig::Index i_element = 0; i_element < vector_field.size(); i_element++) {
		OutType squared_length = math::squared_norm(vector_field(i_element)); // @suppress("Function cannot be resolved")
		OutType min_squared_norm = min_norm_container.load();
		while (squared_length < min_squared_norm
				&& !min_norm_container.compare_exchange_weak(min_squared_norm, squared_length))
			;
	}
	return std::sqrt(min_norm_container.load());
}

template<typename Scalar>
typename Scalar::Scalar min_norm(const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor>& vector_field) {
	return min_norm_aux<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor>, typename Scalar::Scalar >(vector_field);
}

template<typename Scalar>
typename Scalar::Scalar min_norm(const Eigen::Tensor<Scalar, 3, Eigen::ColMajor>& vector_field) {
	return min_norm_aux<Eigen::Tensor<Scalar, 3, Eigen::ColMajor>, typename Scalar::Scalar >(vector_field);
}


template<typename Scalar>
static inline
Scalar mean(const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor>& field){
	return field.mean();
}

template<typename Scalar>
static inline
Scalar mean(const Eigen::Tensor<Scalar, 3, Eigen::ColMajor>& field){
	return static_cast<Eigen::Tensor<Scalar,0,Eigen::ColMajor>>(field.mean())(0);
}

template<typename Scalar>
static inline
Scalar std(const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor>& field){
	Scalar mean = math::mean(field);
	Scalar count = static_cast<Scalar>(field.size()) ;
	Scalar std_dev = std::sqrt((field.array() - mean).square().sum() / count);
	return std_dev;
}

template<typename Scalar>
static inline
Scalar std(const Eigen::Tensor<Scalar, 3, Eigen::ColMajor>& field){
	Scalar mean = math::mean(field);
	Scalar count = static_cast<Scalar>(field.size()) ;
	Scalar std_dev = std::sqrt(
			static_cast<Eigen::Tensor<Scalar, 0, Eigen::ColMajor>>((field - field.constant(mean)).square().sum())(0) /
			count);
	return std_dev;
}


} //namespace math

