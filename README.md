# Standalone-BIN-Image-Corrector
This is being completed as part of a project on data recovery from CDs.

## Acknowledgements

- EDC/ECC Checker - https://github.com/claunia/edccchk (License in source file)  
- Reed Solomon code library - https://github.com/mersinvald/Reed-Solomon (License in include folder)  

## Licensing

- Natalia Portillo's EDC/ECC Checker's license is included in the file edcchk.cpp (under /src/)
	- The license requires a declaration of changes made. Out of the original project, only the one file was included. The main function entry point has been commented out. Only the business code is being utilized. No alterations to that code have been made.

- Mike Lubinets' RS decoder library's license is included in the RS_LICENSE file (under /include/)
	- The license requires the inclusion of itself in the project utilizing a copy of the original project. Furthermore it is used as follows: Only the header file portions are included in this project (gf.hpp, poly.hpp, and rs.hpp). The source file utilizing the library (/src/rs_decoder.cpp) was made using information from the example in the original project.
	
- This program is released under the GPL v3 license as required and wished for by the copyright holders.

## Build

- Clone source code or download ZIP file and extract to a folder.

`git clone https://github.com/Danial-Ahari/Standalone-BIN-Image-Corrector.git`

- Enter folder and run make.

`make corrector`

## Usage

`corrector <input file> <output file>`

## Changelog

[CHANGELOG](CHANGELOG.md)
