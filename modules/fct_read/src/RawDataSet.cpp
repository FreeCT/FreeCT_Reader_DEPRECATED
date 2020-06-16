#include <RawDataSet.h>

#include <blosc.h>
#include <yaml-cpp/yaml.h>

#include <cstring>
#include <fstream>

#include <boost/filesystem.hpp>

namespace fct{
  void RawDataSet::setPath(std::string path){
    m_path = path;
  }

  void RawDataSet::debugPrintInfo(){
    std::cout << "Base class path: "<<  m_path << std::endl;
    std::cout << "Base data vector size: "<<  m_data.size() << std::endl;

    std::cout << "Derived class filepaths: " << std::endl;
    for (auto &p: m_data){
      std::cout << p->getFilepath() << std::endl;
    }
  }

  void RawDataSet::writeAll(std::string dirpath){

    // Emit YAML metadata and save to disk
    YAML::Emitter ye;
    ye << YAML::BeginMap;

    ye << YAML::Comment("FREECT READER OUTPUT FOR: " + m_path) << YAML::Newline << YAML::Newline;
    ye << YAML::Comment("DETECTOR");
    ye << YAML::Key << "manufacturer" << YAML::Value << m_manufacturer;
    ye << YAML::Key << "detector_rows" << YAML::Value << m_detector_rows;
    ye << YAML::Key << "detector_channels" << YAML::Value << m_detector_channels;
    ye << YAML::Key << "detector_transverse_spacing" << YAML::Value << m_detector_transverse_spacing;
    ye << YAML::Key << "detector_axial_spacing" << YAML::Value << m_detector_axial_spacing;
    ye << YAML::Key << "detector_shape" << YAML::Value << m_detector_shape;
    
    ye << YAML::Newline << YAML::Newline;
    ye << YAML::Comment("SCANNER GEOMETRY");
    ye << YAML::Key << "distance_source_to_detector" << YAML::Value << m_dist_source_to_detector;
    ye << YAML::Key << "distance_source_to_isocenter" << YAML::Value << m_dist_source_to_isocenter;
    ye << YAML::Key << "detector_central_element" << YAML::Flow << m_detector_central_element;
    ye << YAML::Key << "projection_geometry" << YAML::Value << m_projection_geometry;
    
    ye << YAML::Newline << YAML::Newline;
    ye << YAML::Comment("SCAN");
    ye << YAML::Key << "scan_type" <<  YAML::Value << m_scan_type;
    ye << YAML::Key << "projections_per_rotation" <<  YAML::Value << m_projections_per_rotation;
    ye << YAML::Key << "flying_focal_spot_mode" <<  YAML::Value << m_flying_focal_spot_mode;
   
    ye << YAML::EndMap;

    std::ofstream ofs_meta(dirpath + "/" + "meta.yaml");
    ofs_meta << ye.c_str() << std::endl;
    
    std::ofstream ofs_source_positions(dirpath + "/" + "source_positions.dat");
    for (auto &f: m_data){
      ofs_source_positions << f->getDFCAngularPosition() + f->getFFSAngularShift() << ",";
      ofs_source_positions << f->getDFCAxialPosition() + f->getFFSAxialShift() << ",";
      ofs_source_positions << f->getDFCRadialPosition() + f->getFFSRadialShift() << std::endl;
    }

    // Write the raw projection data to a binary file
    std::ofstream out(dirpath + "/" + "projections.dat", std::ios::out | std::ios::binary | std::ios::trunc);
    for (auto &f: m_data)
      out.write((char*)f->m_projection.data(),m_detector_rows*m_detector_channels*sizeof(float));
    
  }
}