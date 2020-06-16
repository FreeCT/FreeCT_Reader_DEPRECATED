#include <RawDataSet.h>
#include <DicomFrame.h>

namespace fct{  
  class DicomDataSet: public RawDataSet{
    virtual void readAll();
  };
}
