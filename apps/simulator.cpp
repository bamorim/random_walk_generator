#include<iostream>
#include<cxxopts.hpp>
#include<random_walk_generator.hpp>
#include<graph.hpp>
#include<dist_csv_formatter.hpp>
#include<random>
#include<string>
#include<fstream>

void execute(
    uint_fast32_t seed,
    uint_fast32_t runs,
    uint_fast32_t steps,
    uint_fast32_t max_order,
    uint_fast32_t initial_order,
    std::ostream& degree_out,
    std::ostream& depth_out
    ) {
  std::mt19937 mt(seed);
  auto stats = RandomWalkGenerator::accumulate_measure(&mt, runs, max_order, steps, initial_order);

  DistCsvFormatter::format(
      stats.degree_distribution,
      degree_out,
      true); // Print CSV headers

  DistCsvFormatter::format(
      stats.vertices_per_depth,
      depth_out,
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
    ("n,max-order", "[required] desired order (||V||)", cxxopts::value<uint_fast32_t>())
    ("k,initial-order", "order of the complete starting graph", cxxopts::value<uint_fast32_t>()->default_value("3"))
    ("o,output", "folder to output the files", cxxopts::value<std::string>()->default_value("."))
  ;

  // Catch exceptions here
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
  auto output_folder = options["output"].as<std::string>();
  
  std::ostringstream filename;
  filename
    << seed
    << "_s" << steps
    << "_n" << max_order
    << "_k" << initial_order
    << "_r" << runs;

  // Catch exceptions here
  std::ofstream degree_dist_file;
  degree_dist_file.open(output_folder + "/" + filename.str() + ".degrees.csv");

  std::ofstream depth_dist_file;
  depth_dist_file.open(output_folder + "/" + filename.str() + ".depths.csv");

  std::cerr << "Running with params:" << std::endl
    << "  Seed: " << seed << std::endl
    << "  Steps: " << steps << std::endl
    << "  Max Order: " << max_order << std::endl
    << "  Initial Order: " << initial_order << std::endl << std::endl;

  execute(seed, runs, steps, max_order, initial_order, degree_dist_file, depth_dist_file);

  degree_dist_file.close();
  depth_dist_file.close();

  return 0;
}
