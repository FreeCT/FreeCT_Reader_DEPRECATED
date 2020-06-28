# FreeCT_Reader

**NOTE:  No further updates or changes will be made to this repository.  I am currently in the process of migrating the entirety of the FreeCT project into one project: https://github.com/FreeCT/FreeCT.   This should simplify building and installing in every single way, however in the mean time there are going to be some growing pains and the project will be non-functional.  If you have any questions or comments please reach out to johnmarianhoffman@gmail.com.**

FreeCT_Reader is the reader library used by the FreeCT software package.  It is capable of reading binary data files and DICOM formatted raw data files.  It is also available for external use in other software packages undert the GNU LGPL v2.1.

We are particularly interested in targeting the "Low Dose CT Image and Projection Data" data set provided by the Mayo Clinic, which can be found at https://wiki.cancerimagingarchive.net/pages/viewpage.action?pageId=52758026.  Developement is ongoing and issues and features reported or requested via the GitHub issues page (https://github.com/FreeCT/FreeCT_Reader/issues) will be addressed as quickly as possible.

## How to Build

We use CMake to build the FreeCT Reader libraries.  We follow the "standard" CMake build pattern of:

``` bash
$ git clone https://github.com/FreeCT/FreeCT_Reader/
$ cd FreeCT_Reader
$ mkdir build && cd build
$ cmake ../
$ make
```

We also love and recommend Ninja (https://ninja-build.org/) in which case change the last two lines of the above to
```
$ cmake -GNinja ../
$ ninja
```

If you're using Windows (Visual Studio), select "File > Open > CMake " and select CMakeLists.txt.  (We really recommend Linux though!)

## Under Development
* A FreeCT_Reader executable to extract DICOM raw data into either images , *.mat files, or binary files
* Improved abstraction of CT Raw data (across the entire FreeCT project)

## Final Thoughts
Since the "Low Dose CT and Projection Data" data set referenced above has finally been released, we will do our best to ensure compatibility and ease-of-use.  Please keep in mind that "we" (at least insofar as programming is concerned :) ) is only one person at this point, and these things can take time.  I hope that you will find FreeCT useful and please provide any and all feedback via the GitHub Issues.

John Hoffman ("FreeCT Developers") 
2020/05/11 
johnmarianhoffman@gmail.com
