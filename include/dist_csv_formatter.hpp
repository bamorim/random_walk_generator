#include<vector>
#include<ostream>
#pragma once

namespace DistCsvFormatter {
  void format(const std::vector<uint_fast32_t>&, std::ostream&);
  void format(const std::vector<uint_fast32_t>&, std::ostream&, bool);
}
