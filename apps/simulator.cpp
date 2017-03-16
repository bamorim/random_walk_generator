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
  strs << p;
  std::string str = strs.str();
  str.erase(std::remove(str.begin(), str.end(), '.'),str.end());
  return str;
}

int main(int argc, char** argv){
  cxxopts::Options options(argv[0]);

  options.add_options("Steps")
    ("m,mode", "const | prob | log | pow | exp", cxxopts::value<std::string>()->default_value("const"))
    ("a,parama", "parameter a for step functions", cxxopts::value<double>()->default_value("1.0"))
    ("b,paramb", "parameter b for step functions", cxxopts::value<double>()->default_value("2.0"))
  ;

  options.add_options("Initial State")
    ("seed", "defaults to random", cxxopts::value<uint_fast32_t>())
    ("selfloop", "enable selfloop on initial graph")
    ("k,initial-order", "order of the complete starting graph", cxxopts::value<uint_fast32_t>()->default_value("3"))
  ;

  options.add_options("Other")
    ("r,runs", "number of times to run randomly the generator", cxxopts::value<uint_fast32_t>()->default_value("1"))
    ("n,max-order", "[required] desired order (||V||)", cxxopts::value<uint_fast32_t>())
    ("o,output", "folder to output the files", cxxopts::value<std::string>()->default_value("."))
    ("h,help", "prints the help message")
  ;

  // Catch exceptions here
  options.parse(argc, argv);

  std::function<void()> show_help = [options](){
    std::cout << "Steps can run in the following modes:" << std::endl
      << "const: S(n) = a; a > 0 (DEFAULT)" << std::endl
      << "prob: S(n) = 1 (with probability p) or 2 (with probability 1-p); 0 <= p <= 1" << std::endl
      << "log: S(n) = b*log_a(n); b > 0; a > 1" << std::endl
      << "pow: S(n) = b*n^a; b > 0; a >= 0" << std::endl
      << "exp: S(n) = b*a^n; b > 0; a >= 1" << std::endl << std::endl;

    std::cout << options.help({"Steps", "Initial State", "Other"}) << std::endl;
  };

  std::function<void(std::string)> error_with_help = [show_help](auto err) {
    std::cout << err << std::endl << std::endl;
    show_help();
  };

  if(options.count("help") > 0) {
    show_help();
    return 0;
  }

  if(options.count("max-order") == 0){
    error_with_help("Max order should be > 0.");
    return 1;
  }

  // Initial State options
  auto initial_order = options["initial-order"].as<uint_fast32_t>();
  auto selfloop = options["selfloop"].as<bool>();
  RandomWalkGenerator::InitialState initial_state = {initial_order, selfloop};

  std::random_device rd;
  auto seed = options["seed"].count() > 0 ? options["seed"].as<uint_fast32_t>() : rd();

  // Other options
  auto max_order = options["max-order"].as<uint_fast32_t>();
  auto runs = options["runs"].as<uint_fast32_t>();
  auto output_folder = options["output"].as<std::string>();

  // Steps options
  auto mode = options["mode"].as<std::string>();
  auto parama = options["parama"].as<double>();
  auto paramb = options["paramb"].as<double>();

  // Here we should swap the runner depending on which version of the runner we want to run
  std::mt19937 mt(seed);

  std::ostringstream filename;

  RandomWalkGenerator::StepFunction sf;
  
  // TODO: Add validations here

  filename << mode << "_a";

  if(mode == "const"){
    sf = RandomWalkGenerator::steps_const(round(parama));
    filename << round(parama);

  } else if (mode == "prob") {
    sf = RandomWalkGenerator::steps_prob(&mt, parama);
    filename << p_to_s(parama);

  } else if (mode == "log") {
    sf = RandomWalkGenerator::steps_log(parama,paramb);
    filename << p_to_s(parama) << "_b" << p_to_s(paramb);

  } else if (mode == "pow") {
    sf = RandomWalkGenerator::steps_pow(parama,paramb);
    filename << p_to_s(parama) << "_b" << p_to_s(paramb);

  } else if (mode == "exp") {
    sf = RandomWalkGenerator::steps_exp(parama,paramb);
    filename << p_to_s(parama) << "_b" << p_to_s(paramb);

  } else {
    error_with_help("Invalid step mode");
    return 1;
  }

  filename
    << "_n" << max_order
    << "_k" << initial_order
    << "_r" << runs;

  std::cerr << "Running on mode " << mode << " with params:" << std::endl
    << "  Seed: " << seed << std::endl
    << "  a: " << parama << std::endl
    << "  b: " << paramb << std::endl
    << "  Max Order: " << max_order << std::endl
    << "  Initial Order: " << initial_order << std::endl << std::endl;
  

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
  auto stats = RandomWalkGenerator::acc_run_and_measure(&mt, initial_state, sf, max_order, runs);

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
