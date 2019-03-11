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
#include "../nonrigid_optimization/hierarchical_optimizer2d.hpp"
#include "eigen_numpy.hpp"

namespace bp = boost::python;
namespace nro = nonrigid_optimization;

namespace python_export {
namespace hierarchical_optimizer {
void export_algorithms() {
	{
		bp::scope outer =
				bp::class_<nro::HierarchicalOptimizer2d>("HierarchicalOptimizer",
						bp::init<bp::optional<bool, bool,
								int, float, int, float, float, float, eig::VectorXf,
								nro::HierarchicalOptimizer2d::VerbosityParameters> >(
								bp::args("tikhonov_term_enabled",
										"gradient_kernel_enabled",

										"maximum_chunk_size",
										"rate",
										"maximum_iteration_count",
										"maximum_warp_update_threshold",

										"data_term_amplifier",
										"tikhonov_strength",
										"kernel",
										"verbosity_parameters")))
						.def("optimize", &nro::HierarchicalOptimizer2d::optimize,
						"Find optimal warp to map given live SDF to given canonical SDF",
						bp::args("canonical_field", "live_field"))
								;
		bp::class_<nro::HierarchicalOptimizer2d::VerbosityParameters>("VerbosityParameters",
				bp::init<bp::optional<bool, bool, bool>>(
						bp::args(/*"self",*/
								"print_max_warp_update",
								"print_iteration_data_energy",
								"print_iteration_tikhonov_energy")))
										.add_property("print_iteration_max_warp_update",
												&nro::HierarchicalOptimizer2d::VerbosityParameters
												::print_iteration_max_warp_update)
										.add_property("print_iteration_data_energy",
												&nro::HierarchicalOptimizer2d::VerbosityParameters
												::print_iteration_data_energy)
										.add_property("print_iteration_tikhonov_energy",
												&nro::HierarchicalOptimizer2d::VerbosityParameters
												::print_iteration_tikhonov_energy)
										.add_property("print_per_iteration_info",
												&nro::HierarchicalOptimizer2d::VerbosityParameters
												::print_per_iteration_info)
										.add_property("print_per_level_info",
												&nro::HierarchicalOptimizer2d::VerbosityParameters
												::print_per_level_info)
										;

	}
}
} // namespace hierarchical_optimizer
} // namespace python_export
