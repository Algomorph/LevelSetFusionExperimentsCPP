//  ================================================================
//  Created by Gregory Kramida on 10/11/18.
//  Copyright (c) 2018 Gregory Kramida
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at

//  http://www.apache.org/licenses/LICENSE-2.0

//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//  ================================================================
#pragma once
//stdlib

//libraries
#include <Eigen/Eigen>
#include <unsupported/Eigen/CXX11/Tensor>
#include <boost/python.hpp>

//local
#include "../math/typedefs.hpp"

namespace bp = boost::python;
namespace eig = Eigen;

namespace nonrigid_optimization {

//TODO: refactor everything "resampling" to "warping". Resampling refers to some completely different things from this in most contexts.
//TODO: break this up into multiple functions (as necessary, judge by usage) instead of passing behavior flags
eig::MatrixXf warp(math::MatrixXv2f& warp_field,
		const eig::MatrixXf& warped_live_field, const eig::MatrixXf& canonical_field,
		bool band_union_only = false, bool known_values_only = false,
		bool substitute_original = false, float truncation_float_threshold = 1e-6);
eig::MatrixXf warp_preserveing_vectors(math::MatrixXv2f& warp_field,
		const eig::MatrixXf& warped_live_field, const eig::MatrixXf& canonical_field,
		bool band_union_only = false, bool known_values_only = false,
		bool substitute_original = false, float truncation_float_threshold = 1e-6);

eig::MatrixXf warp(const eig::MatrixXf& scalar_field, math::MatrixXv2f& warp_field);
eig::Tensor3f warp(const eig::Tensor3f& scalar_field, math::Tensor3v3f& warp_field);

eig::MatrixXf warp_with_replacement(const eig::MatrixXf& scalar_field, math::MatrixXv2f& warp_field,
		float replacement_value);
eig::Tensor3f warp_with_replacement(const eig::Tensor3f& scalar_field, math::Tensor3v3f& warp_field,
		float replacement_value);

bp::object py_resample(const eig::MatrixXf& warped_live_field,
		const eig::MatrixXf& canonical_field, eig::MatrixXf warp_field_u,
		eig::MatrixXf warp_field_v, bool band_union_only = false, bool known_values_only = false,
		bool substitute_original = false, float truncation_float_threshold = 1e-6);

bp::object py_resample_warp_unchanged(const eig::MatrixXf& warped_live_field,
		const eig::MatrixXf& canonical_field, eig::MatrixXf warp_field_u,
		eig::MatrixXf warp_field_v, bool band_union_only = false, bool known_values_only = false,
		bool substitute_original = false, float truncation_float_threshold = 1e-6);

} // namespace nonrigid_optimization

