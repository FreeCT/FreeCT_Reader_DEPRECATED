#include <FreeCTDataSet.h>

#include <boost/filesystem.hpp>
#include <yaml-cpp/yaml.h>

namespace fct{

  bool FreeCTFrame::readFromFile(std::string filepath){
    std::cout << "Fart knockers" << std::endl;
    return true;
  }

  void FreeCTDataSet::readAll(){

    std::string meta_filepath = m_path + "/" + "meta.yaml";
    std::string source_filepath = m_path + "/" + "source_positions.dat";
    std::string projections_filepath = m_path + "/" + "projections.dat";

    // Ensure the necessary files exist
    if (!boost::filesystem::exists(meta_filepath)){
      std::cout << "ERROR: Could not find metadata filepath " + meta_filepath << std::endl;
      exit(1);
    }
    if (!boost::filesystem::exists(source_filepath)){
      std::cout << "ERROR: Could not find source positions filepath " + source_filepath << std::endl;
      exit(1);
    }
    if (!boost::filesystem::exists(projections_filepath)){
      std::cout << "ERROR: Could not find projection data filepath " + projections_filepath << std::endl;
      exit(1);
    }

    // Read and parse the meta.yaml file
    std::ifstream fin(meta_filepath);
    YAML::Parser parser(fin);
    
    YAML::Node doc;

    //for(YAML::Iterator it=doc.begin();it!=doc.end();++it) {
    //  std::string key, value;
    //  it.first() >> key;
    //  it.second() >> value;
    //  std::cout << "Key: " << key << ", value: " << value << std::endl;
    //}
    
    //while(parser.GetNextDocument(doc)) {
    //  // ...
    //}

    //YAML::Node metadata = YAML::LoadFile(meta_filepath);
    //parse_item();
 
  }
}