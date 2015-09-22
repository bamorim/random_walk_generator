#include<iostream>
#include<cxxopts.hpp>
#include<random_walk_generator.hpp>
#include<graph.hpp>
#include<degree_dist_csv_formatter.hpp>
#include<random>

void execute(
    uint_fast32_t seed,
    uint_fast32_t steps,
    uint_fast32_t max_order,
    uint_fast32_t initial_order,
    std::ostream& out
    ) {
  Graph g = RandomWalkGenerator::run(seed, max_order, steps, initial_order);
  DegreeDistCsvFormatter::format(
      g.degree_distribution(),
      out,
      true); // Print CSV headers
}

int main(int argc, char** argv){
  cxxopts::Options options(argv[0]);

  options.add_options("")
    ("h,help", "prints the help message")
  ;

  options.add_options("params")
    ("s,steps", "steps taken on each addition", cxxopts::value<uint_fast32_t>()->default_value("1"))
    ("r,seed", "defaults to random", cxxopts::value<uint_fast32_t>())
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
  auto seed = options.count("seed") > 0 ? options["seed"].as<uint_fast32_t>() : rd();

  auto steps = options["steps"].as<uint_fast32_t>();
  auto initial_order = options["initial-order"].as<uint_fast32_t>();
  auto max_order = options["max-order"].as<uint_fast32_t>();

  std::cerr << "Running with params:" << std::endl
    << "Seed: " << seed << std::endl
    << "Steps: " << steps << std::endl
    << "Max Order: " << max_order << std::endl
    << "Initial Order: " << initial_order << std::endl << std::endl;

  execute(seed, steps, max_order, initial_order, std::cout);

  return 0;
}
