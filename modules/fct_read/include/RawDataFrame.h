#pragma once

#include <eigen3/Eigen/Dense>

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
    
}