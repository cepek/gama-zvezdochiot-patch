#ifndef GNU_gama___gama_ellipsoids__header_file_h
#define GNU_gama___gama_ellipsoids__header_file_h

#include <gnu_gama/ellipsoid.h>

// This file was generated by GNU Gama (program ellipsoids_xml) from 
// http://www.gnu.org/software/gama/xml/ellipsoids.xml revision 0.10

namespace GNU_gama {

enum gama_ellipsoid {

ellipsoid_unknown,
ellipsoid_airy,		// 6377563.396   6356256.910
ellipsoid_airy_mod,		// 6377340.189   6356034.446
ellipsoid_apl1965,		// 6378137   298.25
ellipsoid_andrae1876,		// 6377104.43   300.0
ellipsoid_australian,		// 6378160   298.25
ellipsoid_bessel,		// 6377397.15508   6356078.96290
ellipsoid_bessel_nam,		// 6377483.865   299.1528128
ellipsoid_clarke1858a,		// 6378361   6356685
ellipsoid_clarke1858b,		// 6378558   6355810
ellipsoid_clarke1866,		// 6378206.4   6356583.8
ellipsoid_clarke1880,		// 6378316   6356582
ellipsoid_clarke1880m,		// 6378249.145   293.4663
ellipsoid_cpm1799,		// 6375738.7   334.29
ellipsoid_delambre,		// 6376428   311.5
ellipsoid_engelis,		// 6378136.05   298.2566
ellipsoid_everest1830,		// 6377276.345   300.8017
ellipsoid_everest1848,		// 6377304.063   300.8017
ellipsoid_everest1856,		// 6377301.243   300.8017
ellipsoid_everest1869,		// 6377295.664   300.8017
ellipsoid_everest_ss,		// 6377298.556   300.8017
ellipsoid_fisher1960,		// 6378166   298.3
ellipsoid_fisher1960m,		// 6378155   298.3
ellipsoid_fischer1968,		// 6378150   298.3
ellipsoid_grs67,		// 6378160   298.2471674270
ellipsoid_grs80,		// 6378137   298.257222101
ellipsoid_hayford,		// 6378388   297
ellipsoid_helmert,		// 6378200   298.3
ellipsoid_hough,		// 6378270   297
ellipsoid_iau76,		// 6378140   298.257
ellipsoid_international,		// 6378388   297
ellipsoid_kaula,		// 6378163   298.24
ellipsoid_krassovski,		// 6378245   298.3
ellipsoid_lerch,		// 6378139   298.257
ellipsoid_mprts,		// 6397300   191.0
ellipsoid_mercury,		// 6378166   298.3
ellipsoid_merit,		// 6378137   298.257
ellipsoid_new_intl,		// 6378157.5   6356772.2
ellipsoid_nwl1965,		// 6378145   298.25
ellipsoid_plessis,		// 6376523   6355863
ellipsoid_se_asia,		// 6378155   6356773.3205
ellipsoid_sgs85,		// 6378136   298.257
ellipsoid_schott,		// 6378157   304.5
ellipsoid_sa1969,		// 6378160   298.25
ellipsoid_walbeck,		// 6376896   6355834.8467
ellipsoid_wgs60,		// 6378165   298.3
ellipsoid_wgs66,		// 6378145   298.25
ellipsoid_wgs72,		// 6378135   298.26
ellipsoid_wgs84		// 6378137   298.257223563

};

extern const char * const gama_ellipsoid_caption[];

gama_ellipsoid ellipsoid(const char*);
int            set(Ellipsoid*, gama_ellipsoid);

}

#endif
