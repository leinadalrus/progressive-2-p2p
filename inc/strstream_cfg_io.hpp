#ifndef STRSTREAM_CFG_IO_HPP
#define STRSTREAM_CFG_IO_HPP

#include "../inc/finger_table.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>

void rfile(std::istream &is)
{
  if(!is.eof())
    exit(1);

  std::string parsed = {};
  std::getline(is, parsed);
  if (!is)
    exit(1);

  std::istringstream iss(parsed);
}

void sentry_survey_span()
{
  std::ifstream ifs("data/startnodes_4_keys.cfg");
  
  if (!ifs.good())
    exit(1);
  
  rfile(ifs);
}

#endif // STRSTREAM_CFG_IO_HPP