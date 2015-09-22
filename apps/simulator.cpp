#include<iostream>
#include<cxxopts.hpp>
#include<random_walk_generator.hpp>
#include<graph.hpp>
#include<degree_dist_csv_formatter.hpp>
#include<random>

int main(int argc, char** argv){
  cxxopts::Options options(argv[0]);
  options.add_options()
    ("h,help", "prints the help message")
    ("s,steps", "defaults to 1", cxxopts::value<uint_fast32_t>())
    ("r,seed", "defaults to unix time", cxxopts::value<uint_fast32_t>())
    ("v,max-order", "[required] desired order (||V||)", cxxopts::value<uint_fast32_t>())
    ("k,initial-order", "order of the complete starting graph (defaults 3)", cxxopts::value<uint_fast32_t>())
    ("o,output", "If no argument is passed, prints to STDOUT", cxxopts::value<std::string>())
    ("degree-dist-image", "[NOT IMPLEMENTED] save the degree distribution histogram to file", cxxopts::value<std::string>())
    ("visits-dist-image", "[NOT IMPLEMENTED] save the visits distribution histogram to file", cxxopts::value<std::string>())
    ("depth-count-dist-image", "[NOT IMPLEMENTED] save the vertices per depth distribution histogram to file", cxxopts::value<std::string>())
  ;

  options.parse(argc, argv);

  if(options.count("help") > 0) {
    std::cout << options.help() << std::endl;
    return 0;
  }

  if(options.count("max-order") == 0){
    std::cout 
      << "Invalid usage." << std::endl
      << options.help() << std::endl;
    return 1;
  }

  std::random_device rd;

  auto seed = options.count("seed") > 0 ? options["seed"].as<uint_fast32_t>() : rd();
  auto steps = options.count("steps") > 0 ? options["steps"].as<uint_fast32_t>() : 1;
  auto max_order = options["max-order"].as<uint_fast32_t>();
  auto initial_order = options.count("initial_order") > 0 ? options["initial-order"].as<uint_fast32_t>() : 3;

  std::cout << "Running with params:" << std::endl
    << "Seed: " << seed << std::endl
    << "Steps: " << steps << std::endl
    << "Max Order: " << max_order << std::endl
    << "Initial Order: " << initial_order << std::endl << std::endl;

  Graph g = RandomWalkGenerator::run(seed, max_order, steps, initial_order);
  DegreeDistCsvFormatter::format(g.degree_distribution(), std::cout);

  return 0;
}
