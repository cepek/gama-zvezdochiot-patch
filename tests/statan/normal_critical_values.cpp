/*
  GNU Gama C++ library tests/statan
  Copyright (C) 2018  Ales Cepek <cepek@gnu.org>

  This file is part of the GNU Gama C++ library
  
  GNU Gama is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  GNU Gama is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with GNU Gama.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <vector>
#include <cmath>
#include "gnu_gama/statan.h"

using namespace GNU_gama;
using namespace std;

/*
  Testing data generated from the Octave script:

  % normal distribution - critical values

  N = 1000;
  x = N-1:-1:N/2;

  c = norminv(x/N);

  printf('  std::vector<double> X = {\n');
  printf('    %6.3f,\n', x/N);
  printf('  };\n\n');

  printf('  std::vector<double> Y = {\n');
  printf('    %20.16f,\n', c);
  printf('  };\n\n');

*/

int main()
{
  std::vector<double> X = {
     0.999,
     0.998,
     0.997,
     0.996,
     0.995,
     0.994,
     0.993,
     0.992,
     0.991,
     0.990,
     0.989,
     0.988,
     0.987,
     0.986,
     0.985,
     0.984,
     0.983,
     0.982,
     0.981,
     0.980,
     0.979,
     0.978,
     0.977,
     0.976,
     0.975,
     0.974,
     0.973,
     0.972,
     0.971,
     0.970,
     0.969,
     0.968,
     0.967,
     0.966,
     0.965,
     0.964,
     0.963,
     0.962,
     0.961,
     0.960,
     0.959,
     0.958,
     0.957,
     0.956,
     0.955,
     0.954,
     0.953,
     0.952,
     0.951,
     0.950,
     0.949,
     0.948,
     0.947,
     0.946,
     0.945,
     0.944,
     0.943,
     0.942,
     0.941,
     0.940,
     0.939,
     0.938,
     0.937,
     0.936,
     0.935,
     0.934,
     0.933,
     0.932,
     0.931,
     0.930,
     0.929,
     0.928,
     0.927,
     0.926,
     0.925,
     0.924,
     0.923,
     0.922,
     0.921,
     0.920,
     0.919,
     0.918,
     0.917,
     0.916,
     0.915,
     0.914,
     0.913,
     0.912,
     0.911,
     0.910,
     0.909,
     0.908,
     0.907,
     0.906,
     0.905,
     0.904,
     0.903,
     0.902,
     0.901,
     0.900,
     0.899,
     0.898,
     0.897,
     0.896,
     0.895,
     0.894,
     0.893,
     0.892,
     0.891,
     0.890,
     0.889,
     0.888,
     0.887,
     0.886,
     0.885,
     0.884,
     0.883,
     0.882,
     0.881,
     0.880,
     0.879,
     0.878,
     0.877,
     0.876,
     0.875,
     0.874,
     0.873,
     0.872,
     0.871,
     0.870,
     0.869,
     0.868,
     0.867,
     0.866,
     0.865,
     0.864,
     0.863,
     0.862,
     0.861,
     0.860,
     0.859,
     0.858,
     0.857,
     0.856,
     0.855,
     0.854,
     0.853,
     0.852,
     0.851,
     0.850,
     0.849,
     0.848,
     0.847,
     0.846,
     0.845,
     0.844,
     0.843,
     0.842,
     0.841,
     0.840,
     0.839,
     0.838,
     0.837,
     0.836,
     0.835,
     0.834,
     0.833,
     0.832,
     0.831,
     0.830,
     0.829,
     0.828,
     0.827,
     0.826,
     0.825,
     0.824,
     0.823,
     0.822,
     0.821,
     0.820,
     0.819,
     0.818,
     0.817,
     0.816,
     0.815,
     0.814,
     0.813,
     0.812,
     0.811,
     0.810,
     0.809,
     0.808,
     0.807,
     0.806,
     0.805,
     0.804,
     0.803,
     0.802,
     0.801,
     0.800,
     0.799,
     0.798,
     0.797,
     0.796,
     0.795,
     0.794,
     0.793,
     0.792,
     0.791,
     0.790,
     0.789,
     0.788,
     0.787,
     0.786,
     0.785,
     0.784,
     0.783,
     0.782,
     0.781,
     0.780,
     0.779,
     0.778,
     0.777,
     0.776,
     0.775,
     0.774,
     0.773,
     0.772,
     0.771,
     0.770,
     0.769,
     0.768,
     0.767,
     0.766,
     0.765,
     0.764,
     0.763,
     0.762,
     0.761,
     0.760,
     0.759,
     0.758,
     0.757,
     0.756,
     0.755,
     0.754,
     0.753,
     0.752,
     0.751,
     0.750,
     0.749,
     0.748,
     0.747,
     0.746,
     0.745,
     0.744,
     0.743,
     0.742,
     0.741,
     0.740,
     0.739,
     0.738,
     0.737,
     0.736,
     0.735,
     0.734,
     0.733,
     0.732,
     0.731,
     0.730,
     0.729,
     0.728,
     0.727,
     0.726,
     0.725,
     0.724,
     0.723,
     0.722,
     0.721,
     0.720,
     0.719,
     0.718,
     0.717,
     0.716,
     0.715,
     0.714,
     0.713,
     0.712,
     0.711,
     0.710,
     0.709,
     0.708,
     0.707,
     0.706,
     0.705,
     0.704,
     0.703,
     0.702,
     0.701,
     0.700,
     0.699,
     0.698,
     0.697,
     0.696,
     0.695,
     0.694,
     0.693,
     0.692,
     0.691,
     0.690,
     0.689,
     0.688,
     0.687,
     0.686,
     0.685,
     0.684,
     0.683,
     0.682,
     0.681,
     0.680,
     0.679,
     0.678,
     0.677,
     0.676,
     0.675,
     0.674,
     0.673,
     0.672,
     0.671,
     0.670,
     0.669,
     0.668,
     0.667,
     0.666,
     0.665,
     0.664,
     0.663,
     0.662,
     0.661,
     0.660,
     0.659,
     0.658,
     0.657,
     0.656,
     0.655,
     0.654,
     0.653,
     0.652,
     0.651,
     0.650,
     0.649,
     0.648,
     0.647,
     0.646,
     0.645,
     0.644,
     0.643,
     0.642,
     0.641,
     0.640,
     0.639,
     0.638,
     0.637,
     0.636,
     0.635,
     0.634,
     0.633,
     0.632,
     0.631,
     0.630,
     0.629,
     0.628,
     0.627,
     0.626,
     0.625,
     0.624,
     0.623,
     0.622,
     0.621,
     0.620,
     0.619,
     0.618,
     0.617,
     0.616,
     0.615,
     0.614,
     0.613,
     0.612,
     0.611,
     0.610,
     0.609,
     0.608,
     0.607,
     0.606,
     0.605,
     0.604,
     0.603,
     0.602,
     0.601,
     0.600,
     0.599,
     0.598,
     0.597,
     0.596,
     0.595,
     0.594,
     0.593,
     0.592,
     0.591,
     0.590,
     0.589,
     0.588,
     0.587,
     0.586,
     0.585,
     0.584,
     0.583,
     0.582,
     0.581,
     0.580,
     0.579,
     0.578,
     0.577,
     0.576,
     0.575,
     0.574,
     0.573,
     0.572,
     0.571,
     0.570,
     0.569,
     0.568,
     0.567,
     0.566,
     0.565,
     0.564,
     0.563,
     0.562,
     0.561,
     0.560,
     0.559,
     0.558,
     0.557,
     0.556,
     0.555,
     0.554,
     0.553,
     0.552,
     0.551,
     0.550,
     0.549,
     0.548,
     0.547,
     0.546,
     0.545,
     0.544,
     0.543,
     0.542,
     0.541,
     0.540,
     0.539,
     0.538,
     0.537,
     0.536,
     0.535,
     0.534,
     0.533,
     0.532,
     0.531,
     0.530,
     0.529,
     0.528,
     0.527,
     0.526,
     0.525,
     0.524,
     0.523,
     0.522,
     0.521,
     0.520,
     0.519,
     0.518,
     0.517,
     0.516,
     0.515,
     0.514,
     0.513,
     0.512,
     0.511,
     0.510,
     0.509,
     0.508,
     0.507,
     0.506,
     0.505,
     0.504,
     0.503,
     0.502,
     0.501,
     0.500
  };

  std::vector<double> Y = {
      3.0902323061678074,
      2.8781617390954843,
      2.7477813854449940,
      2.6520698079021945,
      2.5758293035488999,
      2.5121443279304621,
      2.4572633902054379,
      2.4089155458154603,
      2.3656181268642920,
      2.3263478740408416,
      2.2903678778552683,
      2.2571292444862245,
      2.2262117693171746,
      2.1972863766410513,
      2.1700903775845597,
      2.1444106209118399,
      2.1200716897421512,
      2.0969274291643427,
      2.0748547343933090,
      2.0537489106318234,
      2.0335201492530510,
      2.0140908120181384,
      1.9953933101678243,
      1.9773684281819464,
      1.9599639845400545,
      1.9431337511050666,
      1.9268365732639108,
      1.9110356475491184,
      1.8956979239918386,
      1.8807936081512509,
      1.8662957434581067,
      1.8521798587690468,
      1.8384236692477771,
      1.8250068211464032,
      1.8119106729525973,
      1.7991181068379667,
      1.7866133654934699,
      1.7743819103449574,
      1.7624102978623895,
      1.7506860712521697,
      1.7391976652852517,
      1.7279343223884189,
      1.7168860184310402,
      1.7060433968889614,
      1.6953977102721360,
      1.6849407678719142,
      1.6746648890243250,
      1.6645628612027215,
      1.6546279023510775,
      1.6448536269514724,
      1.6352340153886498,
      1.6257633862332344,
      1.6164363711150216,
      1.6072478919002178,
      1.5981931399228171,
      1.5892675570513917,
      1.5804668183993613,
      1.5717868165098596,
      1.5632236468662757,
      1.5547735945968530,
      1.5464331222567473,
      1.5381988585840640,
      1.5300675881378289,
      1.5220362417358566,
      1.5141018876192844,
      1.5062617232782449,
      1.4985130678799756,
      1.4908533552466614,
      1.4832801273356211,
      1.4757910281791711,
      1.4683837982456605,
      1.4610562691869069,
      1.4538063589405752,
      1.4466320671589790,
      1.4395314709384566,
      1.4325027208258119,
      1.4255440370804520,
      1.4186537061727389,
      1.4118300775008088,
      1.4050715603096329,
      1.3983766207974957,
      1.3917437793963257,
      1.3851716082134358,
      1.3786587286232777,
      1.3722038089987261,
      1.3658055625722720,
      1.3594627454182584,
      1.3531741545480032,
      1.3469386261102798,
      1.3407550336902165,
      1.3346222867001931,
      1.3285393288568097,
      1.3225051367384357,
      1.3165187184182607,
      1.3105791121681289,
      1.3046853852287899,
      1.2988366326425054,
      1.2930319761442426,
      1.2872705631079420,
      1.2815515655446008,
      1.2758741791491299,
      1.2702376223931491,
      1.2646411356610803,
      1.2590839804270717,
      1.2535654384704511,
      1.2480848111275475,
      1.2426414185778818,
      1.2372345991628273,
      1.2318637087349833,
      1.2265281200366103,
      1.2212272221055693,
      1.2159604197073186,
      1.2107271327915976,
      1.2055267959725182,
      1.2003588580308591,
      1.1952227814374272,
      1.1901180418964235,
      1.1850441279078099,
      1.1800005403477292,
      1.1749867920660899,
      1.1700024075004789,
      1.1650469223056024,
      1.1601198829975194,
      1.1552208466119518,
      1.1503493803760083,
      1.1455050613926969,
      1.1406874763376225,
      1.1358962211673118,
      1.1311309008386337,
      1.1263911290388007,
      1.1216765279254890,
      1.1169867278766097,
      1.1123213672493115,
      1.1076800921478003,
      1.1030625561995979,
      1.0984684203398629,
      1.0938973526034375,
      1.0893490279242770,
      1.0848231279419569,
      1.0803193408149561,
      1.0758373610404317,
      1.0713768892802134,
      1.0669376321927657,
      1.0625193022708670,
      1.0581216176847770,
      1.0537443021306667,
      1.0493870846841045,
      1.0450496996583889,
      1.0407318864675446,
      1.0364333894937896,
      1.0321539579593064,
      1.0278933458021426,
      1.0236513115560881,
      1.0194276182343707,
      1.0152220332170279,
      1.0110343281418164,
      1.0068642787985225,
      1.0027116650265493,
      0.9985762706156595,
      0.9944578832097531,
      0.9903562942135747,
      0.9862712987022383,
      0.9822026953334700,
      0.9781502862624717,
      0.9741138770593093,
      0.9700932766287371,
      0.9660882971323732,
      0.9620987539131418,
      0.9581244654219025,
      0.9541652531461944,
      0.9502209415410154,
      0.9462913579615760,
      0.9423763325979505,
      0.9384756984115684,
      0.9345892910734801,
      0.9307169489043390,
      0.9268585128160436,
      0.9230138262549801,
      0.9191827351468197,
      0.9153650878428139,
      0.9115607350675407,
      0.9077695298680556,
      0.9039913275644014,
      0.9002259857014332,
      0.8964733640019161,
      0.8927333243208557,
      0.8890057306010245,
      0.8852904488296417,
      0.8815873469961750,
      0.8778962950512287,
      0.8742171648664837,
      0.8705498301956545,
      0.8668941666364381,
      0.8632500515934207,
      0.8596173642419118,
      0.8559959854926822,
      0.8523857979575752,
      0.8487866859159672,
      0.8451985352820502,
      0.8416212335729144,
      0.8380546698774067,
      0.8344987348257406,
      0.8309533205598379,
      0.8274183207043821,
      0.8238936303385577,
      0.8203791459684610,
      0.8168747655001636,
      0.8133803882134044,
      0.8098959147358979,
      0.8064212470182405,
      0.8029562883093937,
      0.7995009431327366,
      0.7960551172626628,
      0.7926187177017123,
      0.7891916526582224,
      0.7857738315244841,
      0.7823651648553873,
      0.7789655643475453,
      0.7755749428188844,
      0.7721932141886848,
      0.7688202934580622,
      0.7654560966908778,
      0.7621005409950669,
      0.7587535445043712,
      0.7554150263604693,
      0.7520849066954916,
      0.7487631066149089,
      0.7454495481807891,
      0.7421441543954096,
      0.7388468491852137,
      0.7355575573851107,
      0.7322762047230995,
      0.7290027178052184,
      0.7257370241008051,
      0.7224790519280627,
      0.7192287304399239,
      0.7159859896102051,
      0.7127507602200429,
      0.7095229738446084,
      0.7063025628400876,
      0.7030894603309285,
      0.6998836001973415,
      0.6966849170630507,
      0.6934933462832894,
      0.6903088239330341,
      0.6871312867954694,
      0.6839606723506824,
      0.6807969187645748,
      0.6776399648779957,
      0.6744897501960818,
      0.6713462148778052,
      0.6682092997257232,
      0.6650789461759234,
      0.6619550962881618,
      0.6588376927361878,
      0.6557266787982535,
      0.6526219983478011,
      0.6495235958443252,
      0.6464314163244075,
      0.6433454053929170,
      0.6402655092143741,
      0.6371916745044747,
      0.6341238485217700,
      0.6310619790594988,
      0.6280060144375696,
      0.6249559034946873,
      0.6219115955806241,
      0.6188730405486286,
      0.6158401887479719,
      0.6128129910166272,
      0.6097913986740799,
      0.6067753635142650,
      0.6037648377986297,
      0.6007597742493188,
      0.5977601260424785,
      0.5947658468016782,
      0.5917768905914464,
      0.5887932119109196,
      0.5858147656875989,
      0.5828415072712162,
      0.5798733924277045,
      0.5769103773332714,
      0.5739524185685732,
      0.5709994731129873,
      0.5680514983389827,
      0.5651084520065837,
      0.5621702922579263,
      0.5592369776119069,
      0.5563084669589181,
      0.5533847195556727,
      0.5504656950201126,
      0.5475513533264013,
      0.5446416547999989,
      0.5417365601128167,
      0.5388360302784502,
      0.5359400266474902,
      0.5330485109029088,
      0.5301614450555192,
      0.5272787914395084,
      0.5244005127080407,
      0.5215265718289320,
      0.5186569320803909,
      0.5157915570468274,
      0.5129304106147282,
      0.5100734569685947,
      0.5072206605869457,
      0.5043719862383814,
      0.5015273989777079,
      0.4986868641421220,
      0.4958503473474532,
      0.4930178144844647,
      0.4901892317152093,
      0.4873645654694408,
      0.4845437824410792,
      0.4817268495847304,
      0.4789137341122559,
      0.4761044034893952,
      0.4732988254324371,
      0.4704969679049416,
      0.4676987991145083,
      0.4649042875095946,
      0.4621134017763774,
      0.4593261108356632,
      0.4565423838398406,
      0.4537621901698796,
      0.4509854994323708,
      0.4482122814566094,
      0.4454425062917199,
      0.4426761442038215,
      0.4399131656732339,
      0.4371535413917224,
      0.4343972422597814,
      0.4316442393839562,
      0.4288945040742017,
      0.4261480078412783,
      0.4234047223941829,
      0.4206646196376157,
      0.4179276716694819,
      0.4151938507784269,
      0.4124631294414049,
      0.4097354803212812,
      0.4070108762644657,
      0.4042892902985789,
      0.4015706956301486,
      0.3988550656423368,
      0.3961423738926983,
      0.3934325941109665,
      0.3907257001968700,
      0.3880216662179771,
      0.3853204664075677,
      0.3826220751625341,
      0.3799264670413074,
      0.3772336167618116,
      0.3745434991994427,
      0.3718560893850748,
      0.3691713625030897,
      0.3664892938894337,
      0.3638098590296958,
      0.3611330335572123,
      0.3584587932511938,
      0.3557871140348753,
      0.3531179719736893,
      0.3504513432734613,
      0.3477872042786274,
      0.3451255314704724,
      0.3424663014653906,
      0.3398094910131668,
      0.3371550769952773,
      0.3345030364232123,
      0.3318533464368166,
      0.3292059843026511,
      0.3265609274123726,
      0.3239181532811330,
      0.3212776395459965,
      0.3186393639643752,
      0.3160033044124829,
      0.3133694388838060,
      0.3107377454875920,
      0.3081082024473549,
      0.3054807880993974,
      0.3028554808913491,
      0.3002322593807219,
      0.2976111022334799,
      0.2949919882226262,
      0.2923748962268042,
      0.2897598052289143,
      0.2871466943147454,
      0.2845355426716215,
      0.2819263295870614,
      0.2793190344474542,
      0.2767136367367469,
      0.2741101160351471,
      0.2715084520178386,
      0.2689086244537097,
      0.2663106132040949,
      0.2637143982215300,
      0.2611199595485181,
      0.2585272773163097,
      0.2559363317436934,
      0.2533471031357998,
      0.2507595718829160,
      0.2481737184593125,
      0.2455895234220808,
      0.2430069674099823,
      0.2404260311423079,
      0.2378466954177493,
      0.2352689411132796,
      0.2326927491830448,
      0.2301181006572656,
      0.2275449766411493,
      0.2249733583138114,
      0.2224032269272062,
      0.2198345638050686,
      0.2172673503418633,
      0.2147015680017444,
      0.2121371983175241,
      0.2095742228896491,
      0.2070126233851871,
      0.2044523815368208,
      0.2018934791418508,
      0.1993358980612068,
      0.1967796202184666,
      0.1942246275988833,
      0.1916709022484199,
      0.1891184262727924,
      0.1865671818365193,
      0.1840171511619794,
      0.1814683165284768,
      0.1789206602713119,
      0.1763741647808612,
      0.1738288125016623,
      0.1712845859315065,
      0.1687414676205379,
      0.1661994401703587,
      0.1636584862331412,
      0.1611185885107453,
      0.1585797297538434,
      0.1560418927610500,
      0.1535050603780572,
      0.1509692154967774,
      0.1484343410544899,
      0.1459004200329940,
      0.1433674354577668,
      0.1408353703971274,
      0.1383042079614047,
      0.1357739313021117,
      0.1332445236111240,
      0.1307159681198633,
      0.1281882480984856,
      0.1256613468550742,
      0.1231352477348367,
      0.1206099341193073,
      0.1180853894255530,
      0.1155615971053833,
      0.1130385406445652,
      0.1105162035620418,
      0.1079945694091542,
      0.1054736217688682,
      0.1029533442550040,
      0.1004337205114699,
      0.0979147342114995,
      0.0953963690568920,
      0.0928786087772565,
      0.0903614371292588,
      0.0878448378958718,
      0.0853287948856292,
      0.0828132919318813,
      0.0802983128920550,
      0.0777838416469152,
      0.0752698620998299,
      0.0727563581760375,
      0.0702433138219167,
      0.0677307130042592,
      0.0652185397095437,
      0.0627067779432138,
      0.0601954117289566,
      0.0576844251079842,
      0.0551738021383168,
      0.0526635268940684,
      0.0501535834647337,
      0.0476439559544766,
      0.0451346284814213,
      0.0426255851769444,
      0.0401168101849681,
      0.0376082876612559,
      0.0351000017727088,
      0.0325919366966631,
      0.0300840766201891,
      0.0275764057393917,
      0.0250689082587111,
      0.0225615683902247,
      0.0200543703529506,
      0.0175472983721508,
      0.0150403366786357,
      0.0125334695080693,
      0.0100266811002748,
      0.0075199556985405,
      0.0050132775489267,
      0.0025066308995718,
      0.0000000000000000
  };

  std::vector<double> T;
  for (double x : X) {
    T.push_back(Normal(x));
  }

  double max = 0, sum = 0, diff {};
  for (std::size_t i=0; i<T.size(); i++) {
    diff = T[i] + Y[i];  // see the sign of Normal(x) function values
    sum += diff;
    if (abs(diff) > abs(max)) max = diff;
  }
  sum /= T.size();

  cout << "Normal distribution - critical values\n" << endl;
  cout << "diff max = " << max << "  avg = " << sum << endl;

  return abs(max) < 1e-12 ? 0 : 1;
}