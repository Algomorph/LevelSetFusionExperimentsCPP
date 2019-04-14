//  ================================================================
//  Created by Gregory Kramida on 10/23/18.
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

#include <Eigen/Eigen>

#include "../../src/math/stacking.hpp"
#include "../src/math/typedefs.hpp"

namespace test_data {
namespace eig = Eigen;
static eig::MatrixXf field = [] {
	eig::MatrixXf field(16, 16);
	//@formatter:off
        field << 4.71329689e-03, -8.68739009e-01, -5.74181378e-01, -8.74342024e-01,
                4.57525730e-01, 2.99881458e-01, 9.47121620e-01, -8.15366149e-01,
                -8.39478970e-01, 1.19697332e-01, -5.41317701e-01, -2.85580277e-01,
                8.61226439e-01, -9.98036802e-01, -3.59104276e-02, -5.89095473e-01, // line 1

                2.97642708e-01, 6.22404814e-01, 3.57468247e-01, 3.66355896e-01,
                -6.26746297e-01, 5.17148972e-01, -7.25306869e-01, 8.91848445e-01,
                3.98869872e-01, -1.25052333e-02, -9.87516046e-02, -3.17590475e-01,
                -6.07606053e-01, -3.60752702e-01, -9.05864537e-01, -1.52506411e-01, // line 2

                -1.48031056e-01, 7.49697208e-01, -2.52435803e-02, 5.71540236e-01,
                7.48488545e-01, -6.32846236e-01, 7.84215569e-01, -1.13798618e-01,
                -6.29856586e-02, 5.54790497e-01, 2.11236954e-01, -5.22230506e-01,
                8.04714084e-01, -9.53254342e-01, 3.62226367e-01, -3.33150625e-01,   // line 3

                -9.17420745e-01, -6.83708012e-01, -2.45982051e-01, -2.01202095e-01,
                3.28054667e-01, 6.76548123e-01, -7.04806685e-01, 7.22823858e-01,
                8.16856503e-01, -6.73805416e-01, 2.92529821e-01, 5.80841541e-01,
                7.17144728e-01, 6.68222189e-01, 3.53856921e-01, 1.15608454e-01,     // line 4

                5.24113178e-02, -6.88337445e-01, -6.74110889e-01, -7.58959651e-01,
                4.02654052e-01, 7.07991242e-01, 6.60780668e-01, 1.70756459e-01,
               -7.94715583e-01, -5.25580168e-01, 7.51729131e-01, -4.11096573e-01,
                6.35050416e-01, 7.99569130e-01, 6.12377048e-01, 9.10849571e-02,     // line 5

                8.05941939e-01, -6.04516625e-01, -8.55662584e-01, -6.12542331e-01,
               -3.89738917e-01, 7.95977831e-01, -9.71067250e-01, 3.78547788e-01,
                3.16264510e-01, -2.35498309e-01, 6.58781409e-01, 1.97392941e-01,
               -3.99811864e-02, -3.09162676e-01, 2.05297947e-01, 1.20441318e-01,   // line 6

                7.97815323e-01, -1.32516503e-01, 6.76907063e-01, 7.39054203e-01,
                2.27817059e-01, 3.78660798e-01, 6.36429191e-01, 6.81392074e-01,
                2.19333410e-01, 8.28518510e-01, -4.81729388e-01, 6.75043225e-01,
                2.72091031e-01, -8.86008978e-01, 5.05375862e-02, 2.92044640e-01,     // line 7

               -1.60691679e-01, 7.42550254e-01, 8.13372612e-01, 9.51762438e-01,
               -7.98479438e-01, 8.01112175e-01, -3.03357542e-01, 1.58910632e-01,
               -6.07136846e-01, -3.63147557e-01, -9.78226840e-01, -4.29015875e-01,
               -5.63022912e-01, 2.95923233e-01, 8.15509677e-01, 2.48366833e-01,    // line 8

               -6.03294253e-01, 6.07662559e-01, 2.32673764e-01, 6.08038068e-01,
               -8.71697664e-02, -7.77666748e-01, 5.26712775e-01, 1.14489436e-01,
                8.72801185e-01, -4.65581059e-01, -5.35496950e-01, 8.20559740e-01,
                4.10578966e-01, 8.22712064e-01, -7.75927305e-03, 7.15556979e-01,     // line 9

               -1.48940861e-01, -9.09604311e-01, -5.94020247e-01, -4.10049736e-01,
                4.86408472e-02, 7.84370780e-01, -4.85069036e-01, -8.00256848e-01,
                8.44199538e-01, 3.75755429e-01, 7.68698454e-01, -9.69303548e-01,
                8.55000019e-01, 6.66101456e-01, -4.81275082e-01, 8.23024511e-02,    // line 10

                3.13036442e-01, -3.72296929e-01, -9.81959224e-01, -6.35781169e-01,
               -1.77023470e-01, -4.58278239e-01, 5.39610863e-01, -4.36231792e-01,
                4.20212150e-01, 7.56424665e-02, 3.95595193e-01, -7.69713461e-01,
                1.48281574e-01, 3.48860741e-01, 4.42541599e-01, -3.76082897e-01,     // line 11

               -5.95490456e-01, 9.78946686e-03, 8.41099024e-01, 9.37111974e-01,
               -6.50102437e-01, -8.39628816e-01, -4.31775808e-01, 5.68472743e-01,
               -4.54768360e-01, 2.35685825e-01, 7.02300429e-01, -4.35404897e-01,
               -6.03454947e-01, 7.61583209e-01, -5.23658752e-01, 2.65099168e-01,   // line 12

               -6.32248998e-01, -5.21010160e-02, 8.30814958e-01, -7.02030003e-01,
                8.90392065e-02, 4.82232690e-01, 4.25310493e-01, 8.33075643e-01,
               -6.96706295e-01, 1.81824207e-01, 2.37859845e-01, -3.69144559e-01,
               -2.49619722e-01, -8.47997665e-02, -9.62202311e-01, -5.38789988e-01, // line 13

                4.65139031e-01, -6.49003983e-02, 2.60427833e-01, 3.33787084e-01,
               -8.70978117e-01, -2.11835980e-01, -7.60375082e-01, 5.31809688e-01,
                5.37764192e-01, -6.75393105e-01, 1.81047916e-01, -1.67454600e-01,
               -1.22953296e-01, -7.63626695e-02, 3.13402534e-01, -3.98172259e-01,  // line 14

                1.03978276e-01, 2.68656969e-01, 8.81000161e-01, -2.27972269e-01,
                8.82237196e-01, -5.27557492e-01, -8.24825525e-01, -3.87512147e-01,
               -7.12337494e-01, -3.70885730e-01, -6.20220542e-01, 2.07332850e-01,
               -2.21788883e-04, -4.47846174e-01, 3.28795075e-01, 8.63388062e-01,   // line 15

                2.30687261e-01, 4.07925367e-01, -3.45132828e-01, -9.69689190e-01,
               -6.00292683e-02, 1.71350718e-01, 6.13288641e-01, -8.35009456e-01,
               -7.21962512e-01, 4.47731376e-01, -1.69224143e-01, 2.65484810e-01,
               -9.40007687e-01, -3.37775290e-01, -1.68722153e-01, -2.38238335e-01; // line 16
        //@formatter:on
	return field;
}();

static eig::MatrixXf expected_gradient_x = [] {
	eig::MatrixXf expected_gradient_x(16, 16);
	expected_gradient_x <<
	                    //@formatter:off
               -8.73452306e-01, -2.89447337e-01, -2.80150771e-03, 5.15853524e-01,
                5.87111712e-01, 2.44797945e-01, -5.57623804e-01, -8.93300295e-01,
                4.67531741e-01, 1.49080634e-01, -2.02638805e-01, 7.01272070e-01,
                -3.56228262e-01, -4.48568434e-01, 2.04470664e-01, -5.53185046e-01, // line 1

                3.24762106e-01, 2.99127698e-02, -1.28024459e-01, -4.92107272e-01,
                7.53965378e-02, -4.92802858e-02, 1.87349737e-01, 5.62088370e-01,
                -4.52176839e-01, -2.48810738e-01, -1.52542621e-01, -2.54427224e-01,
                -2.15811133e-02, -1.49129242e-01, 1.04123145e-01, 7.53358126e-01,  // line 2

                8.97728264e-01, 6.13937378e-02, -8.90784860e-02, 3.86866063e-01,
                -6.02193236e-01, 1.78635120e-02, 2.59523809e-01, -4.23600614e-01,
                3.34294558e-01, 1.37111306e-01, -5.38510501e-01, 2.96738565e-01,
                -2.15511918e-01, -2.21243858e-01, 3.10051858e-01, -6.95376992e-01, // line 3

                2.33712733e-01, 3.35719347e-01, 2.41252959e-01, 2.87018359e-01,
                4.38875109e-01, -5.16430676e-01, 2.31378675e-02, 7.60831594e-01,
                -6.98314667e-01, -2.62163341e-01, 6.27323508e-01, 2.12307453e-01,
                4.36903238e-02, -1.81643903e-01, -2.76306868e-01, -2.38248467e-01, // line 4

                -7.40748763e-01, -3.63261104e-01, -3.53111029e-02, 5.38382471e-01,
                7.33475447e-01, 1.29063308e-01, -2.68617392e-01, -7.27748156e-01,
                -3.48168314e-01, 7.73222327e-01, 5.72417974e-02, -5.83393574e-02,
                6.05332851e-01, -1.13366842e-02, -3.54242086e-01, -5.21292090e-01, // line 5

                -1.41045856e+00, -8.30802262e-01, -4.01285291e-03, 2.32961833e-01,
                7.04260111e-01, -2.90664166e-01, -2.08715022e-01, 6.43665910e-01,
                -3.07023048e-01, 1.71258450e-01, 2.16445625e-01, -3.49381298e-01,
                -2.53277808e-01, 1.22639567e-01, 2.14801997e-01, -8.48566294e-02,  // line 6

                -9.30331826e-01, -6.04541302e-02, 4.35785353e-01, -2.24545002e-01,
                -1.80196702e-01, 2.04306066e-01, 1.51365638e-01, -2.08547890e-01,
                7.35632181e-02, -3.50531399e-01, -7.67376423e-02, 3.76910210e-01,
                -7.80526102e-01, -1.10776722e-01, 5.89026809e-01, 2.41507053e-01,  // line 7

                9.03241932e-01, 4.87032145e-01, 1.04606092e-01, -8.05926025e-01,
                -7.53251314e-02, 2.47560948e-01, -3.21100771e-01, -1.51889652e-01,
                -2.61029094e-01, -1.85544997e-01, -3.29341590e-02, 2.07601964e-01,
                3.62469554e-01, 6.89266324e-01, -2.37782001e-02, -5.67142844e-01,  // line 8

                1.21095681e+00, 4.17984009e-01, 1.87754631e-04, -1.59921765e-01,
                -6.92852378e-01, 3.06941271e-01, 4.46078092e-01, 1.73044205e-01,
                -2.90035248e-01, -7.04149067e-01, 6.43070400e-01, 4.73037958e-01,
                1.07616186e-03, -2.09169120e-01, -5.35775423e-02, 7.23316252e-01,  // line 9

                -7.60663450e-01, -2.22539693e-01, 2.49777287e-01, 3.21330547e-01,
                5.97210288e-01, -2.66854942e-01, -7.92313814e-01, 6.64634287e-01,
                5.88006139e-01, -3.77505422e-02, -6.72529459e-01, 4.31507826e-02,
                8.17702532e-01, -6.68137550e-01, -2.91899502e-01, 5.63577533e-01,  // line 10

                -6.85333371e-01, -6.47497833e-01, -1.31742120e-01, 4.02467877e-01,
                8.87514651e-02, 3.58317167e-01, 1.10232234e-02, -5.96993566e-02,
                2.55937129e-01, -1.23084784e-02, -4.22677964e-01, -1.23656809e-01,
                5.59287071e-01, 1.47130013e-01, -3.62471819e-01, -8.18624496e-01,  // line 11

                6.05279922e-01, 7.18294740e-01, 4.63661253e-01, -7.45600700e-01,
                -8.88370395e-01, 1.09163314e-01, 7.04050779e-01, -1.14962757e-02,
                -1.66393459e-01, 5.78534365e-01, -3.35545361e-01, -6.52877688e-01,
                5.98494053e-01, 3.98980975e-02, -2.48242021e-01, 7.88757920e-01,   // line 12

                5.80147982e-01, 7.31531978e-01, -3.24964494e-01, -3.70887876e-01,
                5.92131376e-01, 1.68135643e-01, 1.75421476e-01, -5.61008394e-01,
                -3.25625718e-01, 4.67283070e-01, -2.75484383e-01, -2.43739784e-01,
                1.42172396e-01, -3.56291294e-01, -2.26995111e-01, 4.23412323e-01,  // line 13

                -5.30039430e-01, -1.02355599e-01, 1.99343741e-01, -5.65702975e-01,
                -2.72811532e-01, 5.53015172e-02, 3.71822834e-01, 6.49069667e-01,
                -6.03601396e-01, -1.78358138e-01, 2.53969252e-01, -1.52000606e-01,
                4.55459654e-02, 2.18177915e-01, -1.60904795e-01, -7.11574793e-01,  // line 14

                1.64678693e-01, 3.88510942e-01, -2.48314619e-01, 6.18517399e-04,
                -1.49792612e-01, -8.53531361e-01, 7.00226724e-02, 5.62440157e-02,
                8.31320882e-03, 4.60584760e-02, 2.89109290e-01, 3.09999377e-01,
                -3.27589512e-01, 1.64508432e-01, 6.55617118e-01, 5.34592986e-01,   // line 15

                1.77238107e-01, -2.87910044e-01, -6.88807249e-01, 1.42551780e-01,
                5.70519924e-01, 3.36658955e-01, -5.03180087e-01, -6.67625546e-01,
                6.41370416e-01, 2.76369184e-01, -9.11232829e-02, -3.85391772e-01,
                -3.01630050e-01, 3.85642767e-01, 4.97684777e-02, -6.95161819e-02;  // line 16
        //@formatter:on

	return expected_gradient_x;
}();

static eig::MatrixXf expected_gradient_y = [] {
	eig::MatrixXf expected_gradient_y(16, 16);
	expected_gradient_y <<
	                    //@formatter:off
                2.92929411e-01,1.49114382e+00,9.31649625e-01,1.24069786e+00,
                -1.08427203e+00,2.17267513e-01,-1.67242849e+00,1.70721459e+00,
                1.23834884e+00,-1.32202566e-01,4.42566097e-01,-3.20101976e-02,
                -1.46883249e+00,6.37284100e-01,-8.69954109e-01,4.36589062e-01,   // line 1

                -7.63721764e-02,8.09218109e-01,2.74468899e-01,7.22941160e-01,
                1.45481408e-01,-4.66363847e-01,-8.14530253e-02,3.50783765e-01,
                3.88246655e-01,2.17546582e-01,3.76277328e-01,-1.18325114e-01,
                -2.82561779e-02,2.23912299e-02,1.99068397e-01,1.27972424e-01,    // line 2

                -6.07531726e-01,-6.53056383e-01,-3.01725149e-01,-2.83778995e-01,
                4.77400482e-01,7.96995759e-02,1.02500916e-02,-8.45122933e-02,
                2.08993316e-01,-3.30650091e-01,1.95640713e-01,4.49216008e-01,
                6.62375391e-01,5.14487445e-01,6.29860759e-01,1.34057432e-01,     // line 3

                1.00221187e-01,-7.19017327e-01,-3.24433655e-01,-6.65249944e-01,
                -1.72917247e-01,6.70418739e-01,-6.17174506e-02,1.42277539e-01,
                -3.65864962e-01,-5.40185332e-01,2.70246089e-01,5.55669665e-02,
                -8.48318338e-02,8.76411736e-01,1.25075340e-01,2.12117791e-01,    // line 4

                8.61681342e-01,3.95956933e-02,-3.04840267e-01,-2.05670118e-01,
                -3.58896792e-01,5.97148538e-02,-1.33130282e-01,-1.72138035e-01,
                -2.50295997e-01,2.19153553e-01,1.83125794e-01,-1.91724300e-01,
                -3.78562957e-01,-4.88692433e-01,-7.42794871e-02,2.41643190e-03,  // line 5

                3.72702003e-01,2.77910471e-01,6.75508976e-01,7.49006927e-01,
                -8.74184966e-02,-1.64665222e-01,-1.21757388e-02,2.55317807e-01,
                5.07024527e-01,6.77049339e-01,-6.16729259e-01,5.43069899e-01,
                -1.81479692e-01,-8.42789054e-01,-2.80919731e-01,1.00479841e-01,  // line 6

                -4.83316809e-01,6.73533440e-01,8.34517598e-01,7.82152414e-01,
                -2.04370260e-01,2.56717205e-03,3.33854854e-01,-1.09818578e-01,
                -4.61700678e-01,-6.38246238e-02,-8.18504095e-01,-3.13204408e-01,
                -2.61520863e-01,3.02542955e-01,3.05105865e-01,6.39627576e-02,    // line 7

                -7.00554788e-01,3.70089531e-01,-2.22116649e-01,-6.55080676e-02,
                -1.57493412e-01,-5.78163743e-01,-5.48582077e-02,-2.83451319e-01,
                3.26733887e-01,-6.47049785e-01,-2.68837810e-02,7.27582574e-02,
                6.92439675e-02,8.54360521e-01,-2.91484296e-02,2.11756170e-01,    // line 8

                5.87540865e-03,-8.26077282e-01,-7.03696430e-01,-6.80906057e-01,
                4.23560143e-01,-8.37069750e-03,-9.08557475e-02,-4.79583740e-01,
                7.25668192e-01,3.69451493e-01,8.73462677e-01,-2.70143837e-01,
                7.09011436e-01,1.85089111e-01,-6.48392379e-01,-8.30321908e-02,   // line 9

                4.58165348e-01,-4.89979744e-01,-6.07316494e-01,-6.21909618e-01,
                -4.49268520e-02,1.59694254e-01,6.44904375e-03,-2.75360614e-01,
                -2.26294518e-01,2.70611763e-01,4.65546072e-01,-7.95136571e-01,
                -1.31148696e-01,-2.36925662e-01,2.25150436e-01,-5.45819938e-01,  // line 10

                -2.23274797e-01,4.59696889e-01,7.17559636e-01,6.73580885e-01,
                -3.49371642e-01,-8.11999798e-01,2.66466141e-02,6.84364796e-01,
                -6.49483919e-01,-7.00348020e-02,-3.31990123e-02,2.66949326e-01,
                -7.29227483e-01,4.77408767e-02,-2.11918354e-02,9.13983583e-02,   // line 11

                -4.72642720e-01,1.60097957e-01,9.06387091e-01,-3.31244171e-02,
                1.33031338e-01,4.70255464e-01,-5.71501851e-02,6.34653687e-01,
                -5.58459222e-01,5.30908704e-02,-7.88676739e-02,2.00284451e-01,
                -1.98950648e-01,-2.16830254e-01,-7.02371955e-01,-8.13535452e-02, // line 12

                5.30314744e-01,-3.73449326e-02,-2.90335596e-01,-3.01662445e-01,
                -1.10437840e-01,3.13896418e-01,-1.64299637e-01,-1.83315277e-02,
                4.96266276e-01,-4.55539465e-01,-2.60626256e-01,1.33975148e-01,
                2.40250826e-01,-4.18972939e-01,4.18530643e-01,-3.31635714e-01,   // line 13

                3.68113637e-01,1.60378993e-01,2.50926018e-02,2.37028867e-01,
                3.96598995e-01,-5.04895091e-01,-6.25068009e-01,-6.10293865e-01,
                -7.81559944e-03,-2.76354969e-01,-4.29040194e-01,2.88238704e-01,
                1.24698967e-01,-1.81523204e-01,6.45498693e-01,7.01089025e-01,    // line 14

                -1.17225885e-01,2.36412883e-01,-3.02780330e-01,-6.51738167e-01,
                4.05474424e-01,1.91593349e-01,6.86831832e-01,-6.83409572e-01,
                -6.29863381e-01,5.61562240e-01,-1.75136030e-01,2.16469705e-01,
                -4.08527195e-01,-1.30706310e-01,-2.41062343e-01,7.99669623e-02,  // line 15

                1.26708984e-01,1.39268398e-01,-1.22613299e+00,-7.41716921e-01,
                -9.42266464e-01,6.98908210e-01,1.43811417e+00,-4.47497308e-01,
                -9.62501764e-03,8.18617105e-01,4.50996399e-01,5.81519604e-02,
                -9.39785898e-01,1.10070884e-01,-4.97517228e-01,-1.10162640e+00;  // line 16
        //@formatter:on
	return expected_gradient_y;
}();

static math::MatrixXv2f vector_field = [] {
	math::MatrixXv2f field(4, 4);
	field << math::Vector2f(0.66137378f, 0.22941163f), math::Vector2f(-0.79364663f, -0.51078996f),
			math::Vector2f(0.31330802f, -0.62231087f), math::Vector2f(0.38155258f, 0.25911068f),

			math::Vector2f(-0.93761754f, 0.22711085f), math::Vector2f(-0.84484027f, 0.74134703f),
			math::Vector2f(-0.77734907f, 0.31051154f), math::Vector2f(0.05594392f, 0.62550403f),

			math::Vector2f(0.24144975f, -0.03810476f), math::Vector2f(-0.83927967f, 0.2171229f),
			math::Vector2f(0.3517115f, -0.34761186f), math::Vector2f(-0.3781738f, 0.4708583f),

			math::Vector2f(-0.60896495f, 0.32025099f), math::Vector2f(0.11699246f, -0.98680021f),
			math::Vector2f(-0.96371592f, -0.93434108f), math::Vector2f(0.42603218f, 0.76691092f);
	return field;
}();

static math::MatrixXv2f vector_field2 = []{
		math::MatrixXv2f vector_field(4,4);
		vector_field <<
		math::Vector2f(0.8562016f,0.876527f),
		math::Vector2f(0.8056713f,0.31369442f),
		math::Vector2f(0.28571403f,0.38419583f),
		math::Vector2f(0.86377007f,0.9078812f),

		math::Vector2f(0.12255816f,0.22223428f),
		math::Vector2f(0.4487159f,0.7280231f),
		math::Vector2f(0.61369246f,0.43351218f),
		math::Vector2f(0.3545089f,0.33867624f),

		math::Vector2f(0.5658683f,0.53506494f),
		math::Vector2f(0.69546276f,0.9331944f),
		math::Vector2f(0.05706289f,0.06915309f),
		math::Vector2f(0.5286004f,0.9154799f),

		math::Vector2f(0.98797816f,0.60008055f),
		math::Vector2f(0.07343615f,0.10326899f),
		math::Vector2f(0.28764063f,0.05625961f),
		math::Vector2f(0.32258928f,0.84611595f);
		return vector_field;
}();

static math::MatrixXm2f expected_vector_field_gradient = [] {
	math::MatrixXm2f gradient(4, 4);
	gradient <<
			math::Matrix2f(-1.4550204f, -1.5989913f,
	                       -0.7402016f, -0.00230078f),
			math::Matrix2f(-0.17403288f, -0.05119364f,
			               -0.42586124f, 1.252137f),
			math::Matrix2f(0.58759964f, -1.0906571f,
			               0.3849503f, 0.9328224f),
			math::Matrix2f(0.06824457f, -0.32560867f,
			               0.88142157f, 0.36639336f),

			math::Matrix2f(0.09277727f, -0.20996201f,
			               0.51423615f, -0.13375819f),
			math::Matrix2f(0.08013424f, -0.02281652f,
			               0.04170034f, 0.36395642f),
			math::Matrix2f(0.4503921f, 0.01920174f,
			               -0.0579215f, 0.1373495f),
			math::Matrix2f(0.833293f, -0.3798632f,
			               0.3149925f, 0.10587381f),

			math::Matrix2f(-1.0807294f, 0.1643263f,
			               0.25522766f, 0.04657007f),
			math::Matrix2f(0.05513087f, 0.48091638f,
			               -0.15475355f, -0.86407363f),
			math::Matrix2f(0.23055294f, -0.09318343f,
			               0.1268677f, -0.62242633f),
			math::Matrix2f(-0.7298853f, 0.18504412f,
			               0.8184702f, 0.07070345f),

			math::Matrix2f(0.7259574f, -0.8504147f,
			               -1.3070512f, 0.35835573f),
			math::Matrix2f(-0.17737548f, 0.9562721f,
			               -0.62729603f, -1.2039231f),
			math::Matrix2f(0.15451986f, -1.3154274f,
			               0.87685555f, -0.5867292f),
			math::Matrix2f(1.3897481f, 0.80420595f,
			               1.701252f, 0.29605263f);
	return gradient;
}();

}//namespace test_data
