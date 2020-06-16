#pragma once


#include <RawDataFrame.h>

#include <vector>
#include <memory>
#include <iostream>

namespace fct{
  
  class RawDataSet{
  public:
    RawDataSet(){};
    ~RawDataSet(){};

    void setPath(std::string path);
    virtual void readAll() = 0;
    void writeAll(std::string filepath);

    void debugPrintInfo();
    
  protected:
    std::string m_path;
    std::vector<std::unique_ptr<fct::RawDataFrame>> m_data;

    // Scanner manufacturer
    std::string m_manufacturer;           // "SIEMENS" or "GE"

    // Detector
    uint16_t m_detector_rows;
    uint16_t m_detector_channels;
    float m_detector_transverse_spacing;
    float m_detector_axial_spacing;
    std::string m_detector_shape;         // "CYLINDRICAL" "SPHERICAL" or "FLAT"

    // Scanner geometry
    float m_dist_source_to_detector;
    float m_dist_source_to_isocenter;
    std::vector<float> m_detector_central_element = {0.0,0.0};  // column/channel [0], row/row [1]

    std::string m_scan_type;              // AXIAL or HELICAL
    std::string m_projection_geometry;    // "FANBEAM"

    // Flying focal spot module
    std::string m_flying_focal_spot_mode;
    
    // Random stuff
    uint16_t m_projections_per_rotation;
    
  };
}