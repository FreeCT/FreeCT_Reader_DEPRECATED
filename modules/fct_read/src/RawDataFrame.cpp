#include <RawDataFrame.h>

namespace fct{

  int RawDataFrame::getRows(){
    return m_detector_rows;
  };
  
  int RawDataFrame::getCols(){
    return m_detector_channels;
  };

}







