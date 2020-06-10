#include <iostream>

#include <boost/filesystem.hpp>
#include <fct_read.h>

void usage(){
  printf("freect_read -i /path/to/dicom_directory/ -o /path/to/output_directory/\n");
  printf("Copyright (C) John Hoffman 2020\n");
};

void error_out(std::string message){
  std::cout << message << std::endl;
  usage();
  exit(1);
}

int main(int argc, char ** argv){

  
  std::string input_dirpath = "";
  std::string output_dirpath = "";
  
  // Parse command line arguments
  if (argc<5){
    std::cout << "Not enough input arguments!" << std::endl;
    usage();
    exit(1);
  }
  
  for (int i=1;i<argc;i++){

    std::string arg(argv[i]);
      
    if (arg=="-i")
      input_dirpath = argv[++i];
      
    else if (arg=="-o")
      output_dirpath = argv[++i];

    // TODO: add support for output format
    else{
      std::string message = "Unrecognized option \"" + std::string(argv[i]) +  "\" requested";
      error_out(message);
    }
  }

  // Validate the required inputs were set
  if (input_dirpath==""){
    std::string message = "Input path must be set!";
    error_out(message);
  }
  if (output_dirpath==""){
    std::string message = "Output path must be set!";
    error_out(message);
  }


  // Ensure input and output directories exist
  if (!boost::filesystem::exists(input_dirpath)){
    std::cout << "Could not find input dirpath: " << input_dirpath << std::endl;
    exit(1);
  }

  if (!boost::filesystem::exists(output_dirpath)){
    std::cout << "Could not find output dirpath: " << output_dirpath << std::endl;
    exit(1);
  }
   
  std::cout << "Got input_path: " << input_dirpath << std::endl;
  std::cout << "Got output_path: " << output_dirpath << std::endl;


  // Get a full file list for the input directory
  std::vector<std::string> file_list;
  for(auto & p : boost::filesystem::directory_iterator(boost::filesystem::path(input_dirpath))){
    file_list.push_back(boost::filesystem::path(p).string());    
  }
  std::sort(file_list.begin(),file_list.end());
  


  
  
    
  return 0;
}