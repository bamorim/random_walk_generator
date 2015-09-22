#include<degree_dist_csv_formatter.hpp>
void DegreeDistCsvFormatter::format(const std::vector<uint_fast32_t>& distribution, std::ostream& out, bool include_headers){
  if(include_headers){
    out << "degree,count" <<std::endl;
  }

  uint_fast32_t i = 0;
  for( auto d : distribution) {
    if(d > 0){
      if(i > 0) out << std::endl;
      out << i << "," << d;
    }
    i++;
  }
}

void DegreeDistCsvFormatter::format(const std::vector<uint_fast32_t>& distribution, std::ostream& out){
  format(distribution, out, false);
}
