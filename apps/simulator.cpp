#include<iostream>
#include<cxxopts.hpp>
#include<random_walk_generator.hpp>
#include<graph.hpp>
#include<dist_csv_formatter.hpp>
#include<random>
#include<string>
#include<fstream>
#include<functional>
#include<sys/stat.h>

bool file_exists(std::string fname){
  struct stat buffer;
  return (stat (fname.c_str(), &buffer) == 0);
}

std::string p_to_s(double p){
  std::ostringstream strs;
  strs << std::scientific << p;
  std::string str = strs.str();
  str.erase(std::remove(str.begin(), str.end(), '.'),str.end());
  return str;
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
    ("p,prob", "(this changes the behaviour to the 1-or-2 step mode) The walker takes one step with probability p and two steps with probability 1-p", cxxopts::value<double>()->default_value("-1.0"))
    ("selfloop", "enable selfloop on initial graph")
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
  auto prob = options["prob"].as<double>();
  auto selfloop = options["selfloop"].as<bool>();

  // Here we should swap the runner depending on which version of the runner we want to run
  std::mt19937 mt(seed);

  std::function<Graph(void)> runner;
  std::ostringstream filename;

  if(prob > 0) {
    runner = [&mt, max_order, prob, initial_order, selfloop](){
      return RandomWalkGenerator::run_one_or_two(&mt, max_order, prob, initial_order, selfloop);
    };

    filename << "p"  << p_to_s(prob);
    std::cerr << "Running 1-or-2 runner with params:" << std::endl
      << "  Seed: " << seed << std::endl
      << "  Prob: " << prob << std::endl
      << "  Max Order: " << max_order << std::endl
      << "  Initial Order: " << initial_order << std::endl << std::endl;
  } else {
    runner = [&mt, max_order,steps,initial_order,selfloop]() { 
      return RandomWalkGenerator::run(&mt, max_order, steps, initial_order, selfloop);
    };

    filename << "s"  << steps;
    std::cerr << "Running default runner with params:" << std::endl
      << "  Seed: " << seed << std::endl
      << "  Steps: " << steps << std::endl
      << "  Max Order: " << max_order << std::endl
      << "  Initial Order: " << initial_order << std::endl << std::endl;
  }
  
  filename
    << "_n" << max_order
    << "_k" << initial_order
    << "_r" << runs;

  if(selfloop)
    filename << "_sl";

  filename << "_" << seed;


  // Setting the out files
  std::string degree_fname = output_folder + "/" + filename.str() + ".degrees.csv";
  std::string depth_fname = output_folder + "/" + filename.str() + ".depths.csv";

  if(file_exists(depth_fname) && file_exists(degree_fname)){
    // Stop execution if both files already exists
    return 0;
  }

  // Do the actual run
  auto stats = RandomWalkGenerator::accumulate_measure(runner, runs, initial_order);

  // Save the measurements
  std::ofstream degree_out;
  degree_out.open(degree_fname);
  DistCsvFormatter::format(
      stats.degree_distribution,
      degree_out,
      true); // Print CSV headers

  std::ofstream depth_out;
  depth_out.open(depth_fname);
  DistCsvFormatter::format(
      stats.vertices_per_depth,
      depth_out,
      true); // Print CSV headers

  // Close the files
  degree_out.close();
  depth_out.close();

  return 0;
}
