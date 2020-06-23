#pragma once

#include <vector>
#include <memory>
#include <iostream>

#include <eigen3/Eigen/Dense>

#include <yaml-cpp/yaml.h>

// Require abstract methods to implement:
// Frame:
//    readFromFile(std::string filepath)
// DataSet:
//    readAll()

namespace fct{

  class RawDataFrame{
  public:

    int getRows();
    int getCols();
    float getDFCAngularPosition(){return m_dfc_angular_position;};
    float getDFCAxialPosition(){return m_dfc_axial_position;};
    float getDFCRadialPosition(){return m_dfc_radial_distance;};
    float getFFSAngularShift(){return m_ffs_angular_shift;};
    float getFFSAxialShift(){return m_ffs_axial_shift;};
    float getFFSRadialShift(){return m_ffs_radial_shift;};    
    std::string getFilepath(){return m_filepath;};
    
    virtual bool readFromFile(std::string filepath) = 0;

    // TODO: virtual readFromStream(std::ifstream fstream) = 0; // for if we have raw data stored as one file like many manufacturers

  protected:
    
    friend class RawDataSet;
    
    // Bare minimum support right now
    std::string m_filepath = "";
    Eigen::MatrixXf m_projection;
    
    uint16_t m_detector_channels;
    uint16_t m_detector_rows;
    
    // dfc is short for "detector focal center"
    float m_dfc_angular_position;
    float m_dfc_axial_position;
    float m_dfc_radial_distance;
    
    float m_ffs_angular_shift;
    float m_ffs_axial_shift;
    float m_ffs_radial_shift;
  };

  class RawDataSet{
  public:
    RawDataSet(){};
    ~RawDataSet(){};

    void setPath(std::string path);
    virtual void readAll() = 0;
    void writeAll(std::string filepath);

    void debugPrintInfo();

  protected:

    friend class RawDataFrame;

    friend void operator >> (const YAML::Node& node, RawDataSet& rds){
      rds.m_manufacturer                      = node["manufacturer"].as<std::string>();
      rds.m_detector_rows                     = node["detector_rows"].as<uint16_t>();
      rds.m_detector_channels                 = node["detector_channels"].as<uint16_t>();
      rds.m_detector_transverse_spacing       = node["detector_transverse_spacing"].as<float>();
      rds.m_detector_axial_spacing            = node["detector_axial_spacing"].as<float>();
      rds.m_detector_shape                    = node["detector_shape"].as<std::string>();

      rds.m_dist_source_to_detector           = node["distance_source_to_detector"].as<float>();
      rds.m_dist_source_to_isocenter          = node["distance_source_to_isocenter"].as<float>();
      rds.m_detector_central_row              = node["detector_central_row"].as<float>();
      rds.m_detector_central_channel          = node["detector_central_channel"].as<float>();
      rds.m_projection_geometry               = node["projection_geometry"].as<std::string>();

      rds.m_scan_type                         = node["scan_type"].as<std::string>();
      rds.m_projections_per_rotation          = node["projections_per_rotation"].as<uint16_t>();
      rds.m_flying_focal_spot_mode            = node["flying_focal_spot_mode"].as<std::string>();

      rds.m_total_num_projections             = node["total_num_projections"].as<uint16_t>();
    };

    std::string m_path;
    std::vector<std::unique_ptr<fct::RawDataFrame>> m_data;

    std::string m_manufacturer;           // "SIEMENS" or "GE"    
    uint16_t m_detector_rows;
    uint16_t m_detector_channels;
    float m_detector_transverse_spacing;
    float m_detector_axial_spacing;
    std::string m_detector_shape;         // "CYLINDRICAL" "SPHERICAL" or "FLAT"    
    float m_dist_source_to_detector;
    float m_dist_source_to_isocenter;
    float m_detector_central_row;
    float m_detector_central_channel;
    std::string m_scan_type;              // AXIAL or HELICAL
    std::string m_projection_geometry;    // "FANBEAM"
    std::string m_flying_focal_spot_mode;    
    uint16_t m_projections_per_rotation;
    uint16_t m_total_num_projections;

  };

}
