cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
set(PROJECT_NAME fct_read)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-pthread -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -g")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Ensure we have boost on the system
FIND_PACKAGE(Boost COMPONENTS system filesystem REQUIRED)
IF (Boost_FOUND)
  message("FOUND BOOST!")
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
  ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

#FIND_PACKAGE(GDCM REQUIRED)
#IF(GDCM_FOUND)
#  INCLUDE(${GDCM_USE_FILE})
#  SET(GDCM_LIBRARIES 
#    gdcmCommon)
#ELSE(GDCM_FOUND)
#  MESSAGE(FATAL_ERROR "Cannot find GDCM, did you set GDCM_DIR?")
#ENDIF(GDCM_FOUND)


FIND_PACKAGE(DCMTK)
if (DCMTK_FOUND)
  message("FOUND DCMTK!")
ELSE(DCMTK_FOUND)
  MESSAGE(FATAL_ERROR "Cannot find DCMTK, are you sure you've installed it?")
ENDIF(DCMTK_FOUND)

find_package(yaml-cpp REQUIRED)
if (yaml-cpp_FOUND)
  message("Found yaml-cpp.  Assuming it's installed on library search path.")
ELSE(yaml-cpp_FOUND)
endif(yaml-cpp_FOUND)

#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

#DCMTK_INCLUDE_DIRS  - Directories to include to use DCMTK
#DCMTK_LIBRARIES     - Files to link against to use DCMTK
#DCMTK_FOUND         - If false, don't try to use DCMTK
#DCMTK_DIR  

#FIND_PACKAGE(GDCM REQUIRED)
#IF(GDCM_FOUND)
#  INCLUDE(${GDCM_USE_FILE})
#  SET(GDCM_LIBRARIES 
#    gdcmcharls
#    gdcmCommon
#    gdcmDICT
#    gdcmDSED)
#    #gdcmexpat
#    #gdcmgetopt
#    #gdcmIOD
#    #gdcmjpeg12
#    #gdcmjpeg16
#    #gdcmjpeg8
#    #gdcmMEXD
#    #gdcmMSFF
#    #gdcmopenjpeg
#    #gdcmzlib
#    #socketxx
#    #vtkgdcm
#    #Rpcrt4)
#ELSE(GDCM_FOUND)
#  MESSAGE(FATAL_ERROR "Cannot find GDCM, did you set GDCM_DIR?")
#ENDIF(GDCM_FOUND)

# Add the 3rd Party libraries to be build (GDCM for DICOM reading)
#set(3RDPARTYDIR 3rdParty)
#
#set(GDCM_BUILD_TESTING OFF CACHE BOOL "GDCM Setting: Disable test suite")
#set(GDCM_BUILD_SHARED_LIBS ON CACHE BOOL "GDCM Setting: Build shared libs")
#set(GDCM_BUILD_DOCBOOK_MANPAGES OFF CACHE BOOL "GDCM Setting: Disable building man pages ")
#add_subdirectory(${3RDPARTYDIR}/gdcm-gdcm/)

set(INCLUDE_DIRS modules/fct_read/include/ ${DCMTK_INCLUDE_DIRS})

add_subdirectory(modules)
add_subdirectory(applications)
