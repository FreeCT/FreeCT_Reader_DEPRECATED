
#include <fstream>
#include <DicomFrame.h>
#include <set>
#include <chrono>

using namespace std::chrono;
class Timer{


public:
  Timer(){};
  ~Timer(){};
  void tic(){
    m_start = high_resolution_clock::now();
  };
  void toc(){
    m_stop = high_resolution_clock::now();
    std::cout << duration_cast<std::chrono::microseconds>(m_stop-m_start).count() << std::endl;;
  };

private:

  high_resolution_clock::time_point m_start;
  high_resolution_clock::time_point m_stop;
  
};

namespace fct{
  
  bool DicomFrame::readFromFile(std::string filepath){

    auto error_with_message = [](std::string message){
                                std::cout << " ERROR: " << message << std::endl;
                                exit(1);
                              };
    
    m_filepath = filepath;

    // Load the file
    DcmFileFormat fileformat;
    OFCondition status = fileformat.loadFile(m_filepath.c_str());

    if (!status.good())
      error_with_message("Could not read the file " + m_filepath);
    else{

      // Grab the frame dataset
      DcmDataset * ds = fileformat.getDataset();
      OFCondition status;

      // Get frame metadata
      status = ds->findAndGetFloat32(DcmTagKey(0x7031,0x1001),m_dfc_angular_position);
      if (!status.good())
        error_with_message("Could not find tube angle field (0x7031,0x1001 \"DetectorFocalCenterAngularPosition\") in file: " + m_filepath);
      
      status = ds->findAndGetFloat32(DcmTagKey(0x7031,0x1002),m_dfc_axial_position);
      if (!status.good())
        error_with_message("Could not find table position field in file: " + m_filepath);

      status = ds->findAndGetFloat32(DcmTagKey(0x7031,0x1003),m_dfc_radial_distance);
      if (!status.good())
        error_with_message("Could not find tube angle field (0x7031,0x1001 \"DetectorFocalCenterAngularPosition\") in file: " + m_filepath);
      
      status = ds->findAndGetUint16(DcmTagKey(0x7029,0x1010),m_detector_rows);
      if (!status.good())
        error_with_message("Could not find detector rows field in file: " + m_filepath);
      
      ds->findAndGetUint16(DcmTagKey(0x7029,0x1011),m_detector_channels);
      if (!status.good())
        error_with_message("Could not find detector channels field in file: " + m_filepath);
      
      // Get the pixel data
      double rescale_slope     = 0.0;
      double rescale_intercept = 0.0;
      status = ds->findAndGetFloat64(DcmTagKey(0x0028,0x1052),rescale_intercept);
      if (!status.good())
        error_with_message("Could not read rescale intercept in file: " + m_filepath);
        
      status = ds->findAndGetFloat64(DcmTagKey(0x0028,0x1053),rescale_slope);
      if (!status.good())
        error_with_message("Could not read rescale slope in file: " + m_filepath);

      uint16_t rows;
      uint16_t cols;
      status = ds->findAndGetUint16(DcmTagKey(0x0028,0x0010),rows);
      if (!status.good())
        error_with_message("Could not read number of image rows in file: " + m_filepath);
      
      status = ds->findAndGetUint16(DcmTagKey(0x0028,0x0011),cols);
      if (!status.good())
        error_with_message("Could not read number of image cols in file: " + m_filepath);

      status = ds->findAndGetFloat32(DcmTagKey(0x7033,0x100B),m_ffs_angular_shift);
      if (!status.good())
        error_with_message("Could not read ffs_angular_shift in file: " + m_filepath);
      
      status = ds->findAndGetFloat32(DcmTagKey(0x7033,0x100C),m_ffs_axial_shift);
      if (!status.good())
        error_with_message("Could not read ffs_axial_shift in file: " + m_filepath);
      
      status = ds->findAndGetFloat32(DcmTagKey(0x7033,0x100D),m_ffs_radial_shift);
      if (!status.good())
        error_with_message("Could not read ffs_radial_shift in file: " + m_filepath);
      
      const uint16_t * raw_pixel_data = NULL;
      unsigned long count;
      ds->findAndGetUint16Array(DcmTagKey(0x7fe0,0x0010),raw_pixel_data,&count,false);

      // Convert the pixel data into an row-major Eigen matrix
      // Note: m_projection is always row major, where rows correspond to detector rows
      uint16_t * tmp_ptr = (uint16_t *)raw_pixel_data;
      
      if (rows == m_detector_rows){
        Eigen::Map<Eigen::Matrix<uint16_t,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>> tmp_map(tmp_ptr,m_detector_rows,m_detector_channels);
        m_projection = (float)rescale_slope*tmp_map.cast<float>() + (float)rescale_intercept * Eigen::MatrixXf::Ones(m_detector_rows,m_detector_channels);  
      }
      else if (rows == m_detector_channels){
        Eigen::Map<Eigen::Matrix<uint16_t,Eigen::Dynamic,Eigen::Dynamic,Eigen::ColMajor>> tmp_map(tmp_ptr,m_detector_rows,m_detector_channels);
        m_projection = (float)rescale_slope*tmp_map.cast<float>() + (float)rescale_intercept * Eigen::MatrixXf::Ones(m_detector_rows,m_detector_channels);  
      }
      else{
        error_with_message("Rows/Cols does not match DetectorRows or DetectorChannels. Cannot read file!");
      }
      
    }

    return true;
  };
}
