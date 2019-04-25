/*
 * hierarchical_optimizer.cpp
 *
 *  Created on: Jan 11, 2019
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

//libraries
#include <Eigen/Eigen>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

//local
#include "../nonrigid_optimization/hierarchical/optimizer_with_telemetry.hpp"
#include "eigen_numpy.hpp"
#include "../math/typedefs.hpp"

namespace bp = boost::python;
namespace impl = nonrigid_optimization::hierarchical;
namespace eig = Eigen;
typedef impl::OptimizerWithTelemetry2d HierarchicalOptimizer2d;
typedef impl::OptimizerWithTelemetry3d HierarchicalOptimizer3d;

namespace python_export {
namespace hierarchical_optimizer {

math::Tensor3v3f test_function(){
	math::Tensor3v3f a(1, 2, 2);
	a.setValues( { { { math::Vector3f(1.0f, 2.0f, 3.0f), math::Vector3f(4.0f, 5.0f, 6.0f) },
			{ math::Vector3f(7.0f, 8.0f, 9.0f), math::Vector3f(10.0f, 11.0f, 12.0f) } } });
	return a;
}

void export_algorithms_2d() {
	{
		bp::def("test_function", test_function);
		bp::scope outer =
				bp::class_<HierarchicalOptimizer2d>("HierarchicalOptimizer2d",
						bp::init<bp::optional<
								bool, bool,
								int, float, int, float,
								float, float, eig::VectorXf,
								HierarchicalOptimizer2d::ResamplingStrategy,
								HierarchicalOptimizer2d::VerbosityParameters,
								HierarchicalOptimizer2d::LoggingParameters> >(
								bp::args("tikhonov_term_enabled",
										"gradient_kernel_enabled",

										"maximum_chunk_size",
										"rate",
										"maximum_iteration_count",
										"maximum_warp_update_threshold",

										"data_term_amplifier",
										"tikhonov_strength",
										"kernel",

										"resampling_strategy",

										"verbosity_parameters",
										"logging_parameters"
										)))
						.def("optimize", &HierarchicalOptimizer2d::optimize,
						"Find optimal warp to map given live SDF to given canonical SDF",
						bp::args("canonical_field", "live_field"))
						.def("get_per_level_convergence_reports",
						&HierarchicalOptimizer2d::get_per_level_convergence_reports)
						.def("get_per_level_iteration_data",
						&HierarchicalOptimizer2d::get_per_level_iteration_data)
						;
		bp::enum_<HierarchicalOptimizer2d::ResamplingStrategy>("ResamplingStrategy")
				.value("NEAREST_AND_AVERAGE", HierarchicalOptimizer2d::ResamplingStrategy::NEAREST_AND_AVERAGE)
				.value("LINEAR", HierarchicalOptimizer2d::ResamplingStrategy::LINEAR);
		bp::class_<HierarchicalOptimizer2d::VerbosityParameters>("VerbosityParameters",
				"Parameters that control verbosity to stdout. "
						"Assumes being used in an \"immutable\" manner, i.e. just a structure that holds values",
				bp::init<bp::optional<bool, bool, bool, bool, bool>>(
						bp::args(/*"self",*/
						"print_max_warp_update",
								"print_iteration_mean_tsdf_difference",
								"print_iteration_std_tsdf_difference",
								"print_iteration_data_energy",
								"print_iteration_tikhonov_energy")))
				.add_property("print_iteration_max_warp_update",
				&HierarchicalOptimizer2d::VerbosityParameters
				::print_iteration_max_warp_update)
				.add_property("print_iteration_mean_tsdf_difference",
				&HierarchicalOptimizer2d::VerbosityParameters
				::print_iteration_mean_tsdf_difference)
				.add_property("print_iteration_std_tsdf_difference",
				&HierarchicalOptimizer2d::VerbosityParameters
				::print_iteration_std_tsdf_difference)
				.add_property("print_iteration_data_energy",
				&HierarchicalOptimizer2d::VerbosityParameters
				::print_iteration_data_energy)
				.add_property("print_iteration_tikhonov_energy",
				&HierarchicalOptimizer2d::VerbosityParameters
				::print_iteration_tikhonov_energy)
				//============================================
				.add_property("print_per_iteration_info",
				&HierarchicalOptimizer2d::VerbosityParameters
				::print_per_iteration_info)
				.add_property("print_per_level_info",
				&HierarchicalOptimizer2d::VerbosityParameters
				::print_per_level_info)
				;

		bp::class_<HierarchicalOptimizer2d::LoggingParameters>("LoggingParameters",
				"Parameters that control what intermediate results are gathered during run",
				bp::init<bp::optional<bool, bool>>(
						bp::args(
								"collect_per_level_convergence_reports",
								"collect_per_level_iteration_data"
								)))
				.add_property("collect_per_level_convergence_reports",
				&HierarchicalOptimizer2d::LoggingParameters::collect_per_level_convergence_reports)
				.add_property("collect_per_level_iteration_data",
				&HierarchicalOptimizer2d::LoggingParameters::collect_per_level_iteration_data)
				;
	}
}

void export_algorithms_3d() {
	{
		bp::scope outer =
				bp::class_<HierarchicalOptimizer3d>("HierarchicalOptimizer3d",
						bp::init<bp::optional<
								bool, bool,
								int, float, int, float,
								float, float, eig::VectorXf,
								HierarchicalOptimizer3d::ResamplingStrategy,
								HierarchicalOptimizer3d::VerbosityParameters,
								HierarchicalOptimizer3d::LoggingParameters> >(
								bp::args("tikhonov_term_enabled",
										"gradient_kernel_enabled",

										"maximum_chunk_size",
										"rate",
										"maximum_iteration_count",
										"maximum_warp_update_threshold",

										"data_term_amplifier",
										"tikhonov_strength",
										"kernel",

										"resampling_strategy",

										"verbosity_parameters",
										"logging_parameters"
										)))
						.def("optimize", &HierarchicalOptimizer3d::optimize,
						"Find optimal warp to map given live SDF to given canonical SDF",
						bp::args("canonical_field", "live_field"))
						.def("get_per_level_convergence_reports",
						&HierarchicalOptimizer3d::get_per_level_convergence_reports)
						.def("get_per_level_iteration_data",
						&HierarchicalOptimizer3d::get_per_level_iteration_data)
						;
		bp::enum_<HierarchicalOptimizer3d::ResamplingStrategy>("ResamplingStrategy")
				.value("NEAREST_AND_AVERAGE", HierarchicalOptimizer3d::ResamplingStrategy::NEAREST_AND_AVERAGE)
				.value("LINEAR", HierarchicalOptimizer3d::ResamplingStrategy::LINEAR);
		bp::class_<HierarchicalOptimizer3d::VerbosityParameters>("VerbosityParameters",
				"Parameters that control verbosity to stdout. "
						"Assumes being used in an \"immutable\" manner, i.e. just a structure that holds values",
				bp::init<bp::optional<bool, bool, bool, bool, bool>>(
						bp::args(/*"self",*/
						"print_max_warp_update",
								"print_iteration_mean_tsdf_difference",
								"print_iteration_std_tsdf_difference",
								"print_iteration_data_energy",
								"print_iteration_tikhonov_energy")))
				.add_property("print_iteration_max_warp_update",
				&HierarchicalOptimizer3d::VerbosityParameters
				::print_iteration_max_warp_update)
				.add_property("print_iteration_mean_tsdf_difference",
				&HierarchicalOptimizer3d::VerbosityParameters
				::print_iteration_mean_tsdf_difference)
				.add_property("print_iteration_std_tsdf_difference",
				&HierarchicalOptimizer3d::VerbosityParameters
				::print_iteration_std_tsdf_difference)
				.add_property("print_iteration_data_energy",
				&HierarchicalOptimizer3d::VerbosityParameters
				::print_iteration_data_energy)
				.add_property("print_iteration_tikhonov_energy",
				&HierarchicalOptimizer3d::VerbosityParameters
				::print_iteration_tikhonov_energy)
				//============================================
				.add_property("print_per_iteration_info",
				&HierarchicalOptimizer3d::VerbosityParameters
				::print_per_iteration_info)
				.add_property("print_per_level_info",
				&HierarchicalOptimizer3d::VerbosityParameters
				::print_per_level_info)
				;

		bp::class_<HierarchicalOptimizer3d::LoggingParameters>("LoggingParameters",
				"Parameters that control what intermediate results are gathered during run",
				bp::init<bp::optional<bool, bool>>(
						bp::args(
								"collect_per_level_convergence_reports",
								"collect_per_level_iteration_data"
								)))
				.add_property("collect_per_level_convergence_reports",
				&HierarchicalOptimizer3d::LoggingParameters::collect_per_level_convergence_reports)
				.add_property("collect_per_level_iteration_data",
				&HierarchicalOptimizer3d::LoggingParameters::collect_per_level_iteration_data)
				;
	}
}

} // namespace hierarchical_optimizer
} // namespace python_export
