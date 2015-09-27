#include<iostream>
#include<cxxopts.hpp>
#include<random_walk_generator.hpp>
#include<graph.hpp>
#include<dist_csv_formatter.hpp>
#include<random>

void execute(
    uint_fast32_t seed,
    uint_fast32_t runs,
    uint_fast32_t steps,
    uint_fast32_t max_order,
    uint_fast32_t initial_order,
    std::ostream& degree_out
    ) {
  std::mt19937 mt(seed);
  auto stats = RandomWalkGenerator::accumulate_measure(&mt, runs, max_order, steps, initial_order);

  degree_out << "Degree Distribution:" << std::endl;
  DistCsvFormatter::format(
      stats.degree_distribution,
      degree_out,
      true); // Print CSV headers

  degree_out << std::endl
             << "Vertices Per Depth Distribution" << std::endl;

  DistCsvFormatter::format(
      stats.vertices_per_depth,
      degree_out,
      true); // Print CSV headers
}

int main(int argc, char** argv){
  cxxopts::Options options(argv[0]);

  options.add_options("")
    ("h,help", "prints the help message")
  ;

  options.add_options("params")
    ("s,steps", "steps taken on each addition", cxxopts::value<uint_fast32_t>()->default_value("1"))
    ("seed", "defaults to random", cxxopts::value<uint_fast32_t>())
    ("r,runs", "number of times to run randomly the generator", cxxopts::value<uint_fast32_t>()->default_value("1"))
    ("v,max-order", "[required] desired order (||V||)", cxxopts::value<uint_fast32_t>())
    ("k,initial-order", "order of the complete starting graph", cxxopts::value<uint_fast32_t>()->default_value("3"))
  ;

  options.parse(argc, argv);

  if(options.count("help") > 0) {
    std::cout << options.help({"", "params"}) << std::endl;
    return 0;
  }

  if(options.count("max-order") == 0){
    std::cout 
      << "Invalid usage." << std::endl
      << options.help({"", "params"}) << std::endl;
    return 1;
  }

  std::random_device rd;
  auto steps = options["steps"].as<uint_fast32_t>();
  auto initial_order = options["initial-order"].as<uint_fast32_t>();
  auto max_order = options["max-order"].as<uint_fast32_t>();
  auto seed = options["seed"].count() > 0 ? options["seed"].as<uint_fast32_t>() : rd();
  auto runs = options["runs"].as<uint_fast32_t>();

  // Fill the seeds vector with seeds

  std::cerr << "Running with params:" << std::endl
    << "  Seed: " << seed << std::endl
    << "  Steps: " << steps << std::endl
    << "  Max Order: " << max_order << std::endl
    << "  Initial Order: " << initial_order << std::endl << std::endl;

  execute(seed, runs, steps, max_order, initial_order, std::cout);

  return 0;
}
