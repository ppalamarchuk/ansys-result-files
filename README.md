# Ansys Result Files library
C++ library for reading binary result files, generated by the ANSYS simulation software. The library is built upon the binlib library provided by ANSYS and implemented in Fortran.
ARF library offers the flexibility to be utilized either as subroutines (essentially Fortran function calls) or through the implemented wrapper class. Both usage scenarios are available in the examples folder.

## Supported Extensions:
* .rst - A structural or coupled-field analysis
* .rth - A thermal analysis
* .rmg - A magnetic analysis
* .rfl - A FLOTRAN analysis (a legacy results file)

## Usage
Two ways to start use the library in C++ code:
### Download binaries
Download latest release: https://github.com/ppalamarchuk/ansys-result-files/releases/latest
### Build from source
Build ansys-result-files.sln solution. Recommended way is using Microsoft Visual Studio with "Intel® Fortran Compiler" extension installed.

## Acknowledgments:
This work was inspired by Matt Sutton's excellent series of articles:

* https://www.padtinc.com/2016/02/19/reading-ansys-mechanical-rst-c-cpp-part1/
* https://www.padtinc.com/2016/02/22/reading-ansys-mechanical-rst-c-cpp-part2/
* https://www.padtinc.com/2016/02/24/reading-ansys-mechanical-rst-c-cpp-part3/
