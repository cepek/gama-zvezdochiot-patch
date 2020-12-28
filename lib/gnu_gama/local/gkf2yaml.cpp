
/* Gkf2yaml --- conversion from gkf to yaml input format
   Copyright (C) 2020 Ales Cepek <cepek@gnu.org>

   This file is part of the GNU Gama C++ library.

   Class Gkf2yaml is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Gkf2yaml is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GNU Gama.  If not, see <https://www.gnu.org/licenses/>.
*/


#include <regex>
#include <iomanip>
#include <gnu_gama/local/gkf2yaml.h>
#include <gnu_gama/local/observation.h>
#include <gnu_gama/xml/gkfparser.h>
#include <gnu_gama/gon2deg.h>

using namespace GNU_gama::local;

Gkf2yaml::Gkf2yaml(GNU_gama::local::GKFparser& gkfp, std::ostream& ostr)
  : gkfparser_(&gkfp), locnet_(gkfparser_->local_network()), ostream_(ostr)
{

}

void Gkf2yaml::run()
{
  description();
  defaults();
  points();
  observations();
}

void Gkf2yaml::description()
{
  // get rid of hardwired formating in gkf, underlines with ----------
  std::regex reg("\\s*------*\\s*");
  std::string desc = std::regex_replace(locnet_->description, reg, ",\n");

  ostream_ << "# generated by gama-local-gkf2yaml v. 0.90\n"
           << "#\n\n";

  if (desc.empty()) return;

  ostream_ << "description: >-\n";

  std::string word, line {"  "};
  std::istringstream istr(desc);
  while (istr >> word)
    {
      if (line.length() + word.length() > 65)
        {
          while (!line.empty() && isspace(line.back())) line.pop_back();
          ostream_ << line << "\n";
          line = "  ";
        }
      line += word + " ";
    }
  while (!line.empty() && isspace(line.back())) line.pop_back();
  ostream_ << line << "\n\n";
}

void Gkf2yaml::defaults()
{
  ostream_ << "defaults:\n";


  ostream_ << "  # <network>\n";
  std::string axes {};
  const auto& lcs = locnet_->PD.local_coordinate_system;
  if      (lcs == LocalCoordinateSystem::CS::NE) axes = "ne";
  else if (lcs == LocalCoordinateSystem::CS::SW) axes = "sw";
  else if (lcs == LocalCoordinateSystem::CS::ES) axes = "es";
  else if (lcs == LocalCoordinateSystem::CS::WN) axes = "wn";
  else if (lcs == LocalCoordinateSystem::CS::EN) axes = "en";
  else if (lcs == LocalCoordinateSystem::CS::NW) axes = "nw";
  else if (lcs == LocalCoordinateSystem::CS::SE) axes = "se";
  else if (lcs == LocalCoordinateSystem::CS::WS) axes = "ws";
  else axes = "ne";
  ostream_ << "  axes-xy:   " << axes << "\n";

  std::string angles
      = locnet_->PD.left_handed_angles() ? "left-handed" : "right-handed";
  ostream_ << "  angles:    " << angles << "\n";
  if (locnet_->has_epoch())
    ostream_ << "  epoch:     " << locnet_->epoch() << "\n";

  ostream_ << "\n";


  ostream_ << "  # <parameters />\n";
  ostream_ << "  sigma-apr: " << locnet_->apriori_m_0() << "\n";
  ostream_ << "  conf-pr:   " << locnet_->conf_pr() << "\n";
  ostream_ << "  tol-abs:   " << locnet_->tol_abs() << "\n";
  ostream_ << "  sigma-act: " <<(locnet_->m_0_aposteriori() ?
                                   "aposteriori" : "apriori") << "\n";
  if (locnet_->has_algorithm())
    ostream_ << "  algorithm: " << locnet_->algorithm() << "\n";
  // ........ "  language:  "    not available
  // ........ "  encoding:  "    not available
  ostream_ << "  angular:   " <<(locnet_->gons() ? 400 : 360) << "\n";
  //          "  latitude:  " << locnet_->latitude() << "\n";
  if (!locnet_->ellipsoid().empty())
    ostream_ << "  ellipsoid: " << locnet_->ellipsoid() << "\n";
  ostream_ << "\n";

  ostream_ << "  # <points-observations>\n";
  if (gkfparser_->implicit_stdev_distance_a() ||
      gkfparser_->implicit_stdev_distance_b()
      )
    ostream_ << "  distance-stdev:  "
             << gkfparser_->implicit_stdev_distance_a() << " "
             << gkfparser_->implicit_stdev_distance_b() << " "
             << gkfparser_->implicit_stdev_distance_c() << "\n";
  if (gkfparser_->implicit_stdev_direction())
    ostream_ << "  direction-stdev: "
             << gkfparser_->implicit_stdev_direction() << "\n";
  if (gkfparser_->implicit_stdev_angle())
    ostream_ << "  angle-stdev:     "
             << gkfparser_->implicit_stdev_angle() << "\n";
  if (gkfparser_->implicit_stdev_azimuth())
    ostream_ << "  azimuth-stdev: "
             << gkfparser_->implicit_stdev_azimuth() << "\n";
  if (gkfparser_->implicit_stdev_zangle())
    ostream_ << "  zenith-angle-stdev: "
             << gkfparser_->implicit_stdev_zangle() << "\n";
  ostream_ << "\n";
}

void Gkf2yaml::points()
{
  ostream_ << "points:\n";

  ostream_ << std::fixed;
  ostream_ << std::setprecision(5);

  for (auto point : locnet_->PD)
    {
      ostream_ << "  - id:  " << point.first << "\n";

      auto p = point.second;
      if (p.test_xy())
        {
          ostream_ << "    x:   " << p.x() << "\n";
          ostream_ << "    y:   " << p.y() << "\n";
        }

      if (p.test_z())
        {
          ostream_ << "    z:   " << p.z() << "\n";
        }

      std::string adj_xyz, fix_xyz;

      if(p.constrained_xy())
        adj_xyz += "XY";
      else if(p.free_xy())
        adj_xyz += "xy";

      if (p.fixed_xy())
        fix_xyz += "xy";


      if(p.constrained_z())
        adj_xyz += "Z";
      else if(p.free_z())
        adj_xyz += "z";

      if (p.fixed_z())
        fix_xyz += "z";

      if (!adj_xyz.empty()) ostream_ << "    adj: " <<  adj_xyz << "\n";
      if (!fix_xyz.empty()) ostream_ << "    fix: " <<  fix_xyz << "\n";
    }

  ostream_ << "\n";
}

void Gkf2yaml::observations()
{
  using namespace GNU_gama::local;

  ostream_ << "observations:\n";

  for (auto c : locnet_->OD.clusters)
    {
      if (StandPoint* s = dynamic_cast<StandPoint*>(c))
        {
          stand_point(s);
        }
      else if (HeightDifferences* h = dynamic_cast<HeightDifferences*>(c))
        {
          height_differences(h);
        }
      else if (Vectors* v = dynamic_cast<Vectors*>(c))
        {
          vectors(v);
        }
      else if (Coordinates* cords = dynamic_cast<Coordinates*>(c))
        {
          coordinates(cords);
        }
    }
}

void Gkf2yaml::stand_point(StandPoint* sp)
{
  ostream_ << "  - from: " << sp->station << "\n";
  ostream_ << "    obs:\n";

  bool obs_have_std = true;

  for (Observation* obs : sp->observation_list)
    {
      if (!obs->check_std_dev()) obs_have_std = false;
      stand_point_obs(obs);
    }

  const auto& cov = sp->activeCov();
  if (!obs_have_std || cov.bandWidth() >= 1)
    {
      cov_mat(cov, 6);
    }

}

void Gkf2yaml::stand_point_obs(Observation* obs)
{
  // if (!obs->active()) return;

  auto ostream_precision = ostream_.precision();

  // gama-local.xsd
  if (Direction* dir = dynamic_cast<Direction*>(obs))
    {
      ostream_ << "      - type:    direction\n";
      ostream_ << "        to:      " << dir->to() << "\n";
      ostream_ << "        val:     " << locnet_->angular_fmt(dir, 0, 6) << "\n";
    }
  else if (Distance* dis = dynamic_cast<Distance*>(obs))
    {
      ostream_.precision(10);      // practicall it means "infinity"
      ostream_ << "      - type:    distance\n";
      ostream_ << "        to:      " << dis->to() << "\n";
      ostream_ << "        val:     " << dis->value() << "\n";
    }
  else if (Angle* ang = dynamic_cast<Angle*>(obs))
    {
      ostream_ << "      - type:    angle\n";
      ostream_ << "        bs:      " << ang->bs() << "\n";
      ostream_ << "        fs:      " << ang->fs() << "\n";
      ostream_ << "        val:     " << locnet_->angular_fmt(ang, 0, 6) << "\n";
      if (double bh = ang->bs_dh()) ostream_
               << "        bs_dh:   " << bh << "\n";
      if (double fh = ang->fs_dh()) ostream_
               << "        fs_dh:   " << fh << "\n";
    }
  else if (S_Distance* sdi = dynamic_cast<S_Distance*>(obs))
    {
      ostream_.precision(10);
      ostream_ << "      - type:    s-distance\n";
      ostream_ << "        to:      " << sdi->to() << "\n";
      ostream_ << "        val:     " << sdi->value() << "\n";
    }
  else if (Z_Angle* zan = dynamic_cast<Z_Angle*>(obs))
    {
      ostream_ << "      - type:    z-angle\n";
      ostream_ << "        to:      " << zan->to() << "\n";
      ostream_ << "        val:     " << locnet_->angular_fmt(zan, 0, 6) << "\n";
    }
  else if (Azimuth* azi = dynamic_cast<Azimuth*>(obs))
    {
      ostream_ << "      - type:    azimuth\n";
      ostream_ << "        to:      " << azi->to() << "\n";
      ostream_ << "        val:     " << locnet_->angular_fmt(azi, 0, 6) << "\n";
    }

  // handle the case where <obs> does not define common from ID
  StandPoint* sp = dynamic_cast<StandPoint*>(obs->ptr_cluster());
  if (sp->station.str().empty())
      ostream_ << "        from:    " << obs->from() << "\n";

  if(obs->check_std_dev())
      ostream_ << "        stdev:   " << obs->stdDev() << "\n";


  ostream_.precision(ostream_precision);  // restore previous precition

  if (double fh = obs->from_dh())
      ostream_ << "        from_dh: " << fh << "\n";
  if (double th = obs->to_dh() )
      ostream_ << "        to_dh:   " << th << "\n";
 }

void Gkf2yaml::height_differences(HeightDifferences * hdifs)
{
  std::string indent = std::string(8, ' ');
  bool diag_cov = hdifs->activeCov().bandWidth() == 0;

  ostream_ << "  - height-differences:\n";

  for (Observation* obs : hdifs->observation_list)
    if (H_Diff* hd = dynamic_cast<H_Diff*>(obs))
      {
        ostream_ << "    - dh:\n";
        ostream_ << indent << "from:  " << hd->from()  << "\n";
        ostream_ << indent << "to:    " << hd->to()    << "\n";
        ostream_ << indent << "val:   " << hd->value() << "\n";
        if (diag_cov)
          {
            if (hd->dist() > 0)
              ostream_ << indent << "dist:  " << hd->dist()   << "\n";
            else
              ostream_ << indent << "stdev: " << hd->stdDev() << "\n";
          }
      }

  if(!diag_cov) cov_mat(hdifs->activeCov(), 4);
}

void Gkf2yaml::vectors(Vectors* v)
{
  std::string indent = std::string(8, ' ');
  ostream_ << "  - vectors:\n";

  for (Observation* obs : v->observation_list)
    if (Xdiff* dx = dynamic_cast<Xdiff*>(obs))
      {
        ostream_ << "    - vec:\n";
        ostream_ << indent << "from: " << dx->from()  << "\n"
                 << indent << "to:   " << dx->to()    << "\n"
                 << indent << "dx:   " << dx->value() << "\n";
      }
    else if (Ydiff* dy = dynamic_cast<Ydiff*>(obs))
      {
        ostream_ << indent << "dy:   " << dy->value() << "\n";
      }
    else if (Zdiff* dz = dynamic_cast<Zdiff*>(obs))
      {
        ostream_ << indent << "dz:   " << dz->value() << "\n";
      }

  cov_mat(v->activeCov(), 4);
}

void Gkf2yaml::coordinates(Coordinates * cords)
{
  const std::string indent = std::string(8, ' ');
  ostream_ << "  - coordinates:\n";

  // obs is std::list<Observation*>::iterator
  for (auto obs = cords->observation_list.begin();
                  obs != cords->observation_list.end(); obs++)
    {
      if (X* x = dynamic_cast<X*>(*obs))
        {
          ostream_ << "    - id: " << x->from()  << "\n";
          ostream_ << "      x:  " << x->value() << "\n";

          Y* y = dynamic_cast<Y*>(*++obs);
          ostream_ << "      y:  " << y->value() << "\n";

          auto tmp = obs;
          if (++tmp != cords->observation_list.end())
            {
              if (Z* z = dynamic_cast<Z*>(*tmp))
                {
                  ostream_ << "      z:  " << z->value() << "\n";
                  obs++;
                }
            }
        }
      else if (Z* z = dynamic_cast<Z*>(*obs))
        {
          ostream_ << "    - id: " << z->from()  << "\n";
          ostream_ << "      z:  " << z->value() << "\n";
        }
    }

  cov_mat(cords->activeCov(), 4);
}

void Gkf2yaml::cov_mat(const GNU_gama::local::Observation::CovarianceMatrix& cov,
                       std::string::size_type indent)
{
  std::string isp(indent, ' ');
  ostream_ << isp << "- cov-mat:\n"
           << isp << "    dim:  " << cov.dim() << "\n"
           << isp << "    band: " << cov.bandWidth() << "\n"
           << isp << "    upper-part:\n";

  std::string ispelements = isp + std::string(6, ' ');
  for (int row=1; row<=cov.dim(); row++)
    {
      ostream_ << ispelements;
      for (int col=row; col <= row+cov.bandWidth() && col <= cov.dim(); col++)
        {
          ostream_ << cov(row,col) << " ";
        }
      ostream_ << "\n";
    }
}
