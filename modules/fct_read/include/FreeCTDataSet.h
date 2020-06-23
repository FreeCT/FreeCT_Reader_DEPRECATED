#include <RawDataSet.h>

namespace fct{
  
  class FreeCTFrame: public RawDataFrame{
    virtual bool readFromFile(std::string filepath);
  };
  
  class FreeCTDataSet: public RawDataSet{
    virtual void readAll();
  };
  
}
