#include <DicomDataSet.h>
#include <DicomFrame.h>
#include <iostream>

#include <boost/filesystem.hpp>

#include <memory>
#include <iostream>

namespace fct{
  void DicomDataSet::readAll(){    

    std::cout << "Reading DICOM dataset from: " << m_path << std::endl;

    // We add the requisite entries to the dictionary
    // This is NOT the preferred way to do it, however DCMTK and the
    // existing, MATLAB-derived LDCT DICOM dictionary do not make it
    // especially friendly to do it any other way.  Because we are looking
    // for a solution that works "out-of-the-box," on both linux and windows,
    // this is the best approach at this time.  If someone else knows better
    // we can switch to that approach.
    DcmDataDictionary& dict = dcmDataDict.wrlock();    
    dict.addEntry(new DcmDictEntry(0x7029,0x0010,DcmEVR::EVR_LO,"DetectorSystemArrangementModule"     ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7029,0x1010,DcmEVR::EVR_US,"NumberofDetectorRows"                ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7029,0x1011,DcmEVR::EVR_US,"NumberofDetectorColumns"             ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7029,0x1002,DcmEVR::EVR_FL,"DetectorElementTransverseSpacing"    ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7029,0x1006,DcmEVR::EVR_FL,"DetectorElementAxialSpacing"         ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7029,0x100B,DcmEVR::EVR_CS,"DetectorShape"                       ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7031,0x0010,DcmEVR::EVR_LO,"DetectorDynamicsModule"              ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7031,0x1001,DcmEVR::EVR_FL,"DetectorFocalCenterAngularPosition"  ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7031,0x1002,DcmEVR::EVR_FL,"DetectorFocalCenterAxialPosition"    ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7031,0x1003,DcmEVR::EVR_FL,"DetectorFocalCenterRadialDistance"   ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7031,0x1031,DcmEVR::EVR_FL,"ConstantRadialDistance"              ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7033,0x0010,DcmEVR::EVR_LO,"SourceDynamicsModule"                ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7033,0x100B,DcmEVR::EVR_FL,"SourceAngularPositionShift"          ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7033,0x100C,DcmEVR::EVR_FL,"SourceAxialPositionShift"            ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7033,0x100D,DcmEVR::EVR_FL,"SourceRadialDistanceShift"           ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7033,0x100E,DcmEVR::EVR_CS,"FlyingFocalSpotMode"                 ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7033,0x1013,DcmEVR::EVR_US,"NumberofSourceAngularSteps"          ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7033,0x1061,DcmEVR::EVR_US,"NumberofSpectra"                     ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7033,0x1063,DcmEVR::EVR_US,"SpectrumIndex"                       ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7033,0x1067,DcmEVR::EVR_FL,"Timestamp"                           ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7037,0x0010,DcmEVR::EVR_LO,"ProjectionDataDefinitions"           ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7037,0x1009,DcmEVR::EVR_CS,"TypeofProjectionData"                ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7037,0x100A,DcmEVR::EVR_CS,"TypeofProjectionGeometry"            ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7039,0x0010,DcmEVR::EVR_LO,"PreprocessingFlagsModule"            ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7039,0x1003,DcmEVR::EVR_CS,"BeamHardeningCorrectionFlag"         ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7039,0x1004,DcmEVR::EVR_CS,"GainCorrectionFlag"                  ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7039,0x1005,DcmEVR::EVR_CS,"DarkFieldCorrectionFlag"             ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7039,0x1006,DcmEVR::EVR_CS,"FlatFieldCorrectionFlag"             ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7039,0x1007,DcmEVR::EVR_CS,"BadPixelCorrectionFlag"              ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7039,0x1008,DcmEVR::EVR_CS,"ScatterCorrectionFlag"               ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7039,0x1009,DcmEVR::EVR_CS,"LogFlag"                             ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7041,0x0010,DcmEVR::EVR_LO,"WaterAttenuationModule"              ,1,1,NULL,false,NULL));
    dict.addEntry(new DcmDictEntry(0x7041,0x1001,DcmEVR::EVR_DS,"WaterAttenuationCoefficient"         ,1,1,NULL,false,NULL));
    //new DcmDictEntry(0x7031,0x1033,DcmEVR::EVR_FL,"DetectorCentralElement	1-n	PrivateTag
    //new DcmDictEntry(0x7033,0x1065,DcmEVR::EVR_FL,"PhotonStatistics	1-n	PrivateTag
    dcmDataDict.unlock();

    // Get a full file list for the input directory, sort by file name
    std::vector<std::string> file_list;
    for(auto & p : boost::filesystem::directory_iterator(boost::filesystem::path(m_path))){
      file_list.push_back(boost::filesystem::path(p).string());    
    }
    std::sort(file_list.begin(),file_list.end());

    // Read the first file to extract scanner- and scan-level information
    auto check_status = [](OFCondition status,std::string message){
                          if (!status.good())
                            std::cout << "ERROR: " <<  message << std::endl;
                        };

    DcmFileFormat fileformat;
    OFCondition status = fileformat.loadFile(file_list[0].c_str());

    if (!status.good())
      std::cout << "Could not read the file " + file_list[0] << std::endl;
    else{

      // Grab the frame dataset
      DcmDataset * ds = fileformat.getDataset();
      OFCondition status;
      if (!status.good()){
        std::cout << "Could not read file for scanner/scan information extraction" << std::endl;
        exit(1);
      }
      else{

        OFString tmp_string;
        
        status = ds->findAndGetOFString(DcmTagKey(0x0008,0x0070),tmp_string);
        m_manufacturer = tmp_string.c_str();
        check_status(status,"Failed to get manufacturer (non-fatal)");

        status = ds->findAndGetUint16(DcmTagKey(0x7029,0x1010),m_detector_rows);
        check_status(status,"Failed to get detector_rows (likely fatal)");
        
        status = ds->findAndGetUint16(DcmTagKey(0x7029,0x1011),m_detector_channels);
        check_status(status,"Failed to get detector_channels (likely fatal)");

        status = ds->findAndGetFloat32(DcmTagKey(0x7029,0x1002),m_detector_transverse_spacing);
        check_status(status,"Failed to get detector_transverse_spacing (fatal for reconstruction)");

        status = ds->findAndGetFloat32(DcmTagKey(0x7029,0x1006),m_detector_axial_spacing);
        check_status(status,"Failed to get detector_channels (fatal for reconstruction)");

        status = ds->findAndGetOFString(DcmTagKey(0x7029,0x100B),tmp_string);
        m_detector_shape = tmp_string.c_str();
        check_status(status,"Failed to get detector_shape (fatal for reconstruction)");

        status = ds->findAndGetFloat32(DcmTagKey(0x7031,0x1003),m_dist_source_to_isocenter);
        check_status(status,"Failed to get dist_source_to_isocenter (fatal for reconstruction)");

        status = ds->findAndGetFloat32(DcmTagKey(0x7031,0x1031),m_dist_source_to_detector);
        check_status(status,"Failed to get dist_source_to_detector (fatal for reconstruction)");

        status = ds->findAndGetOFString(DcmTagKey(0x7033,0x100E),tmp_string);
        m_flying_focal_spot_mode = tmp_string.c_str();
        check_status(status,"Failed to get flying_focal_spot_mode (fatal for reconstruction)");

        status = ds->findAndGetUint16(DcmTagKey(0x7033,0x1013),m_projections_per_rotation);
        check_status(status,"Failed to get projections_per_rotation (fatal for reconstruction)");

        status = ds->findAndGetOFString(DcmTagKey(0x7037,0x1009),tmp_string);
        m_scan_type = tmp_string.c_str();
        check_status(status,"Failed to get scan_type (axial or helical, fatal for reconstruction)");

        status = ds->findAndGetOFString(DcmTagKey(0x7037,0x100A),tmp_string);
        m_projection_geometry = tmp_string.c_str();
        check_status(status,"Failed to get projection geometry (likely fatal for reconstruction)");
        
      }
    }
    
    // Read the raw data file(s), again using runtime polymorphism
    // so that in any subsequent

    printf("Reading %05zu/%05zu",(size_t)0,file_list.size());
    int count  = 0;
    for (auto f: file_list){
      printf("\b\b\b\b\b\b\b\b\b\b\b");
      printf("%05zu/%05zu",(size_t)count,file_list.size()); fflush(stdout);
      
      std::unique_ptr<fct::RawDataFrame> rdf = std::make_unique<fct::DicomFrame>();
      bool success = rdf->readFromFile(f);
      if (success)
        m_data.push_back(std::move(rdf));
     
      count++;
    }
    std::cout << std::endl;
  };
}

