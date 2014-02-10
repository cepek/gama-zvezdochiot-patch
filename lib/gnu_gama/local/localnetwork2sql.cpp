/*
    GNU Gama -- adjudstment of geodetic networks
    Copyright (C) 2010  Ales Cepek <cepek@gnu.org>,
                  2010 Jiri Novak <jiri.novak@petriny.net>,
                  2012, 2013, 2014 Ales Cepek <cepek@gnu.org>

    This file is part of the GNU Gama C++ library.

    This library is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  $
*/

#include "localnetwork2sql.h"
#include <gnu_gama/xml/gkfparser.h>
#include <gnu_gama/local/gamadata.h>
#include <sstream>

using namespace GNU_gama::local;

LocalNetwork2sql::LocalNetwork2sql(LocalNetwork& lnet)
  : localNetwork(lnet),
    points      (lnet.PD),
    observations(lnet.OD)
{
  setDelete(true);
}

void LocalNetwork2sql::readGkf(std::istream& istr)
{
  try
    {
      GKFparser gkf(points, observations);
      char c;
      int  n, finish = 0;
      std::string line;
      do
        {
          line = "";
          n     = 0;
          while (istr.get(c))
            {
              line += c;
              n++;
              if (c == '\n') break;
            }
          if (!istr) finish = 1;

          gkf.xml_parse(line.c_str(), n, finish);
        }
      while (!finish);

      // setting public data mambers from GKFparser
      localNetwork.apriori_m_0(gkf.m0_apr );
      localNetwork.conf_pr    (gkf.konf_pr);
      localNetwork.tol_abs    (gkf.tol_abs);

      localNetwork.update_constrained_coordinates(gkf.update_constr);

      if (gkf.typ_m0_apriorni)
        localNetwork.set_m_0_apriori();
      else
        localNetwork.set_m_0_aposteriori();

      localNetwork.description = gkf.description;
      localNetwork.epoch = gkf.epoch;
    }
  catch (...)
    {
      throw;
    }
}


void LocalNetwork2sql::write(std::ostream& ostr, std::string conf)
{
  config = conf;
  ostr.precision(17);

  ostr << "/* generated by LocalNetwork2sql, configuration: " + config + "\n"
       << " */\n"
       << "begin;\n\n";     // begin transaction

  if (getDelete())
    {
      ostr << "DELETE FROM gnu_gama_local_covmat         WHERE conf_id = " << cnfg() << ";\n"
           << "DELETE FROM gnu_gama_local_descriptions   WHERE conf_id = " << cnfg() << ";\n"
           << "DELETE FROM gnu_gama_local_points         WHERE conf_id = " << cnfg() << ";\n"
           << "DELETE FROM gnu_gama_local_obs            WHERE conf_id = " << cnfg() << ";\n"
           << "DELETE FROM gnu_gama_local_coordinates    WHERE conf_id = " << cnfg() << ";\n"
           << "DELETE FROM gnu_gama_local_vectors        WHERE conf_id = " << cnfg() << ";\n"
           << "DELETE FROM gnu_gama_local_clusters       WHERE conf_id = " << cnfg() << ";\n"
           << "DELETE FROM gnu_gama_local_configurations WHERE conf_id = " << cnfg() << ";\n\n";
    }

  std::string axes = "ne";
  switch(localNetwork.PD.local_coordinate_system)
  {
      case LocalCoordinateSystem::EN: axes = "'en', "; break;
      case LocalCoordinateSystem::NW: axes = "'nw', "; break;
      case LocalCoordinateSystem::SE: axes = "'se', "; break;
      case LocalCoordinateSystem::WS: axes = "'ws', "; break;
      case LocalCoordinateSystem::NE: axes = "'ne', "; break;
      case LocalCoordinateSystem::SW: axes = "'sw', "; break;
      case LocalCoordinateSystem::ES: axes = "'es', "; break;
      case LocalCoordinateSystem::WN: axes = "'wn', "; break;
      default:
             axes =  "'ne', "; //break;*/
  }

  {
    std::string algorithm;
    if (localNetwork.algorithm().empty())
      algorithm = "'gso', ";
    else
      algorithm = "'" + localNetwork.algorithm() + "', ";

    ostr <<  "insert into gnu_gama_local_configurations"
         <<  " (conf_id, conf_name, sigma_apr, conf_pr, tol_abs, sigma_act,"
         <<  " update_cc, axes_xy, angles, epoch, algorithm, ang_units,"
         <<  " latitude, ellipsoid) values ("
         <<  "(select new_id from (select coalesce(max(conf_id), 0)+1 as "
         <<  "new_id from gnu_gama_local_configurations)x),"
         <<  " '" + config +"', "
         <<  localNetwork.apriori_m_0() << ", "
         <<  localNetwork.conf_pr() << ", "
         <<  localNetwork.tol_abs() << ", "
         << (localNetwork.m_0_apriori()
             ? "'apriori'" : "'aposteriori'") << ", "
         << (localNetwork.update_constrained_coordinates()
             ? "'yes'" : "'no'") << ", "
         <<  axes
         << (localNetwork.PD.left_handed_angles()
             ? "'left-handed'" : "'right-handed'") << ", "
         <<  localNetwork.epoch << ", "
         << algorithm
         << (localNetwork.gons() ? 400 : 300) << ", "
         << "50, "    // latitude
         << "NULL"    // ellipsoid
         << ");\n";
  }

  /* <points-observations> atributes */
  // {
  //   double da = gkfparser->implicit_stdev_distance_a();
  //   double db = gkfparser->implicit_stdev_distance_b();
  //   double dc = gkfparser->implicit_stdev_distance_c();
  //   if (da + db != 0)
  //     {
  //    ostr << "insert into gnu_gama_local_atributes"
  //         << " (conf_id, atribute, tag, value) values ("
  //         << cnfg() << ", 'distance-stdev', 'points-observations', '" << da;
  //    if (db)
  //      ostr << " " << db << " " << dc;
  //    ostr << "');\n";
  //     }
  //
  //   if (double dir=gkfparser->implicit_stdev_direction())
  //     {
  //    ostr << "insert into gnu_gama_local_atributes (conf_id, atribute, tag, value) values ("
  //         << cnfg() << ", 'direction-stdev', 'points-observations', '" << dir << "');\n";
  //     }
  //
  //   if (double angle=gkfparser->implicit_stdev_angle())
  //     {
  //    ostr << "insert into gnu_gama_local_atributes (conf_id, atribute, tag, value) values ("
  //         << cnfg() << ", 'angle-stdev', 'points-observations', '" << angle << "');\n";
  //     }
  //
  //     if (double zangle=gkfparser->implicit_stdev_zangle())
  //     {
  //    ostr << "insert into gnu_gama_local_atributes (conf_id, atribute, tag, value) values ("
  //         << cnfg() << ", 'zenith-angle-stdev', 'points-observations', '" << zangle << "');\n";
  //     }
  // }


  /* <description> */
  if (!localNetwork.description.empty())
    {
      const int N = 1000;  // varchar('N') in gnu_gama_local_descriptions table;
      int indx = 0;
      while (indx*N < localNetwork.description.length())
        {
          const std::string& s = localNetwork.description.substr(indx*N, N);
          std::string description;
          for (std::string::const_iterator i=s.begin(); i!=s.end(); ++i)
            if (*i == '\'')
              description += "''";
            else
              description += *i;
          ostr << "insert into gnu_gama_local_descriptions"
               << " (conf_id, indx, text) values ("
               << cnfg() << ", " << (indx+1) << ", '" << description << "');\n";
          indx++;
        }
    }


  /* <points-observations><point /> */
  {
    using namespace GNU_gama::local;
    ostr << "\n";
    for (PointData::const_iterator i=points.begin(); i!=points.end(); ++i)
      {
        const PointID&    id = i->first;
        const LocalPoint& pt = i->second;

        std::string atr = "conf_id, id";
        std::ostringstream val;
        val.setf(std::ios_base::fixed, std::ios_base::floatfield);
        val.precision(17);
        val << cnfg() << ", '" << id << "'";

        if (pt.test_xy())
          {
            atr += ", x, y";
            val << ", " << pt.x() << ", " << pt.y();
          }

        if (pt.test_z())
          {
            atr += ", z";
            val << ", " << pt.z();
          }

        if (pt.active_xy())
          {
            atr += ", txy";
            if      (pt.fixed_xy()      )  val << ", 'fixed'";
            else if (pt.constrained_xy())  val << ", 'constrained'";
            else if (pt.free_xy()       )  val << ", 'adjusted'";
          }

        if (pt.active_z())
          {
            atr += ", tz";
            if      (pt.fixed_z()      )  val << ", 'fixed'";
            else if (pt.constrained_z())  val << ", 'constrained'";
            else if (pt.free_z()       )  val << ", 'adjusted'";
          }

        ostr << "insert into gnu_gama_local_points (" << atr << ") "
             << "values (" << val.str() << ");\n";
      }
  }


  /* clusters */
  {
    using namespace GNU_gama::local;

    int cluster = 1;
    for (GNU_gama::local::ObservationData::ClusterList::const_iterator
           i=observations.clusters.begin(); i!=observations.clusters.end(); ++i)
      {
        const Cluster* c = *i;
        if (const StandPoint* sp = dynamic_cast<const StandPoint*>(c))
          {
            /* xml <obs> atributes from, orientation and from_dh,
             * defined in gama-local.dtd, are ignored in database
             * schema (from_dh is not even implemented in class
             * StandPoint)
             */
            write_cluster(ostr, c, cluster, "obs");

            Index index = 1;
            for (ObservationList::const_iterator
                   b = c->observation_list.begin(),
                   e = c->observation_list.end();  b != e;  ++b)
              {
                // tag, from_id, to_id, to_id2, val, stdev, from_dh, to_dh, to_dh2, dist
                if      (const Distance*   m = dynamic_cast<const Distance*  >(*b))
                {
                  ostr << "insert into gnu_gama_local_obs "
                       << "(conf_id, ccluster, indx, tag, from_id, to_id, "
                       << "val, from_dh, to_dh, rejected) values ("
                       << cnfg() << ", " << cluster << ", "
                       << index++ << ", 'distance', '"
                       << m->from() << "', '" << m->to() << "', "
                       << m->value();
                  if (m->from_dh()) ostr << ", " << m->from_dh(); else ostr << ", null";
                  if (m->to_dh()  ) ostr << ", " << m->to_dh();   else ostr << ", null";
                  ostr << ", " << rejected(m) << ");\n";
                }
                else if (const Direction*  m = dynamic_cast<const Direction* >(*b))
                {
                  ostr << "insert into gnu_gama_local_obs "
                       << "(conf_id, ccluster, indx, tag, from_id, to_id, "
                       << "val, from_dh, to_dh, rejected) values ("
                       << cnfg() << ", " << cluster << ", "
                       << index++ << ", 'direction', '"
                       << m->from() << "', '" << m->to() << "', "
                       << m->value();
                  if (m->from_dh()) ostr << ", " << m->from_dh(); else ostr << ", null";
                  if (m->to_dh()  ) ostr << ", " << m->to_dh();   else ostr << ", null";
                  ostr  << ", " << rejected(m) << ");\n";
                }
                else if (const S_Distance* m = dynamic_cast<const S_Distance*>(*b))
                {
                  ostr << "insert into gnu_gama_local_obs "
                       << "(conf_id, ccluster, indx, tag, from_id, to_id, "
                       << "val, from_dh, to_dh, rejected) values ("
                       << cnfg() << ", " << cluster << ", "
                       << index++ << ", 's-distance', '"
                       << m->from() << "', '" << m->to() << "', "
                       << m->value();
                  if (m->from_dh()) ostr << ", " << m->from_dh(); else ostr << ", null";
                  if (m->to_dh()  ) ostr << ", " << m->to_dh();   else ostr << ", null";
                  ostr  << ", " << rejected(m) << ");\n";
                }
                else if (const Z_Angle*    m = dynamic_cast<const Z_Angle*   >(*b))
                {
                  ostr << "insert into gnu_gama_local_obs "
                       << "(conf_id, ccluster, indx, tag, from_id, to_id, "
                       << "val, from_dh, to_dh, rejected) values ("
                       << cnfg() << ", " << cluster << ", "
                       << index++ << ", 'z-angle', '"
                       << m->from() << "', '" << m->to() << "', "
                       << m->value();
                  if (m->from_dh()) ostr << ", " << m->from_dh(); else ostr << ", null";
                  if (m->to_dh()  ) ostr << ", " << m->to_dh();   else ostr << ", null";
                  ostr  << ", " << rejected(m) << ");\n";
                }
                else if (const Azimuth*    m = dynamic_cast<const Azimuth*   >(*b))
                {
                  ostr << "insert into gnu_gama_local_obs "
                       << "(conf_id, ccluster, indx, tag, from_id, to_id, "
                       << "val, from_dh, to_dh, rejected) values ("
                       << cnfg() << ", " << cluster << ", "
                       << index++ << ", 'azimuth', '"
                       << m->from() << "', '" << m->to() << "', "
                       << m->value();
                  if (m->from_dh()) ostr << ", " << m->from_dh(); else ostr << ", null";
                  if (m->to_dh()  ) ostr << ", " << m->to_dh();   else ostr << ", null";
                  ostr  << ", " << rejected(m) << ");\n";
                }
                else if (const Angle*      m = dynamic_cast<const Angle*     >(*b))
                  {
                    ostr << "insert into gnu_gama_local_obs "
                         << "(conf_id, ccluster, indx, tag, from_id, to_id, to_id2, "
                         << "val, from_dh, to_dh, to_dh2, rejected) values ("
                         << cnfg() << ", " << cluster << ", "
                         << index++ << ", 'angle', '"
                         << m->from() << "', '" << m->bs() << "', '" << m->fs() << "', "
                         << m->value();
                    if (m->from_dh()) ostr << ", " << m->from_dh(); else ostr << ", null";
                    if (m->bs_dh()  ) ostr << ", " << m->bs_dh();   else ostr << ", null";
                    if (m->fs_dh()  ) ostr << ", " << m->fs_dh();   else ostr << ", null";
                    ostr  << ", " << rejected(m) << ");\n";
                  }
                else if (const H_Diff*     m = dynamic_cast<const H_Diff*    >(*b))
                  {
                    ostr << "insert into gnu_gama_local_obs "
                         << "(conf_id, ccluster, indx, tag, from_id, to_id, "
                         << "val, dist, rejected) values (" << cnfg() << ", " << cluster << ", "
                         << index++ << ", 'dh', '"
                         << m->from() << "', '" << m->to() << "', "
                         << m->value() << ", ";
                    if (m->dist())
                      ostr << ", " << m->dist();
                    else
                      ostr << "null";
                    ostr << ", " << rejected(m) << ");\n";
                  }
                else
                  {
                  }
              }
          }
        else if (const HeightDifferences* sp = dynamic_cast<const HeightDifferences*>(c))
          {
            write_cluster(ostr, c, cluster, "height-differences");

            Index index = 1;
            for (ObservationList::const_iterator
                   b = c->observation_list.begin(),
                   e = c->observation_list.end();  b != e;  ++b)
              {
                const H_Diff* hd = dynamic_cast<const H_Diff*>(*b);
                ostr << "insert into gnu_gama_local_obs "
                     << "(conf_id, ccluster, indx, tag, from_id, to_id, "
                     << "val, dist, rejected) values (" << cnfg() << ", " << cluster << ", "
                     << index++ << ", 'dh', '"
                     << hd->from() << "', '" << hd->to() << "', "
                     << hd->value() << ", ";
                if (hd->dist())
                  ostr << hd->dist();
                else
                  ostr << "null";
                ostr << ", " << rejected(hd) << ");\n";
              }
          }
        else if (const Coordinates* sp = dynamic_cast<const Coordinates*>(c))
          {
            write_cluster(ostr, c, cluster, "coordinates");
            Index index = 1, inc;
            for (ObservationList::const_iterator
                   b = c->observation_list.begin(),
                   e = c->observation_list.end();  b != e;  ++b)
              {
                inc = 0;
                std::string        ats;
                std::ostringstream xyz;
                int                rejected_point = 0;
                xyz.precision(17);
                std::string pointid = (*b)->from().str();
                if (const X* xcoord = dynamic_cast<const X*>(*b))
                  {
                    inc++;
                    ats += ", x";
                    xyz << ", " << xcoord->value();
                    if (rejected(*b)) rejected_point = rejected(*b);
                    ObservationList::const_iterator t = b;
                    ++t;
                    if (t != e)
                      {
                        inc++;
                        ++b;
                        ats += ", y";
                        xyz << ", " << (*b)->value();
                        if (rejected(*b)) rejected_point = rejected(*b);
                        ++t;
                        if (t != e && dynamic_cast<const Z*>(*t)
                            && (*t)->from().str()==pointid)
                          {
                            inc++;
                            ++b;
                            ats += ", z";
                            xyz << ", " << (*b)->value();
                            if (rejected(*b)) rejected_point = rejected(*b);
                          }
                      }
                  }
                else if (const Z* zcoord = dynamic_cast<const Z*>(*b))
                  {
                    inc  = 1;
                    ats += ", z";
                    xyz << ", " << zcoord->value();
                    rejected_point = rejected(zcoord);
                  }
                ostr << "insert into gnu_gama_local_coordinates "
                     << "(conf_id, ccluster, indx, id" << ats
                     << ", rejected) "
                     << "values (" << cnfg() << ", " << cluster << ", "
                     << index << ", '" << pointid << "'"
                     << xyz.str() << ", " << rejected_point << ");\n";
                index += inc;
              }
          }
        else if (const Vectors* sp = dynamic_cast<const Vectors*>(c))
          {
            write_cluster(ostr, c, cluster, "vectors");
            Index index = 1, inc;
            for (ObservationList::const_iterator
                   b = c->observation_list.begin(),
                   e = c->observation_list.end();  b != e;  ++b)
              {
                const Xdiff* xd = dynamic_cast<const Xdiff*>(*b++);
                const Ydiff* yd = dynamic_cast<const Ydiff*>(*b++);
                const Zdiff* zd = dynamic_cast<const Zdiff*>(*b);
                int rejected_point = 0;
                if (rejected(xd)) rejected_point = rejected(xd);
                if (rejected(yd)) rejected_point = rejected(yd);
                if (rejected(zd)) rejected_point = rejected(zd);
                ostr << "insert into gnu_gama_local_vectors "
                     << "(conf_id, ccluster, indx, from_id, to_id, "
                     << "dx, dy, dz, from_dh, to_dh, rejected) values ("
                     << cnfg() << ", " << cluster << ", " << index << ", '"
                     << xd->from().str() << "', '" << xd->to().str() << "', "
                     << xd->value() << ", "
                     << yd->value() << ", "
                     << zd->value() << ", "
                     << " null, null"  // from_dh to_dh (are they really used?)
                     << ", " << rejected_point << ");\n";
                index += 3;
              }
          }
        else
          throw GNU_gama::local::Exception("gkf2sql --- unknown cluster type");

        cluster++;
      }
  }

  ostr << "\ncommit;\n";  // commit transaction
}


void LocalNetwork2sql::write_cluster(std::ostream& ostr, const Cluster* c,
                            int cluster, std::string tag)
{
  const GNU_gama::local::Observation::CovarianceMatrix& covmat = c->covariance_matrix;
  Index dim  = covmat.rows();
  Index band = covmat.bandWidth();

  ostr << "\ninsert into gnu_gama_local_clusters "
       << "(conf_id, ccluster, dim, band, tag) "
       << "values (" << cnfg() << ", "
       << cluster << ", " << dim << ", " << band << ", '" << tag
       << "');\n";

  for (Index i=1; i<=dim; i++)
    for (Index j=i; j<=i+band && j <= dim; j++)
      {
        ostr << "insert into gnu_gama_local_covmat "
             << "(conf_id, ccluster, rind, cind, val) "
             << "values (" << cnfg() << ", " << cluster
             << ", " << i << ", " << j << "," << covmat(i,j) << ");\n";
      }
}
