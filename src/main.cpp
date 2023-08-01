// CD BIN File Corrector
// Danial Ahari, mentored by Dr. Jacob Hauenstein
// The University of Alabama in Huntsville
// Summer 2023
//*************************************************************
// This project is a component of a Summer 2023 RCEU conducted
// at the University of Alabama in Huntsville.
//
// The code contained in edcchk.cpp is based on Natalia
// Portillo's code that can be found at 
// https://github.com/claunia/edccchk
// The licensing information is contained within that file.
//
// The code in header files related to rs decoding and the
// code used instructionally to generate rs_decoder.cpp was made
// by Mike Lubinets and can be found here:
// https://github.com/mersinvald/Reed-Solomon
//
// Many thanks are given to the people that contributed to
// projects used here. Without you, none of this would have
// been possible.


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <cassert>
#include <map>
#include <cstdint>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int8_t ecmify(uint8_t* sector);
void eccedc_init(void);
int rsDecode(uint8_t* Buf);

int main(int argc, char* argv[]) {
	// Open files and seek to get size.
	FILE *file = fopen(argv[1], "rb");
	FILE *newFile = fopen(argv[2], "wb");
	fseek(file, 0, SEEK_END);
	int numOfSectors = ftell(file)/2352;
	fseek(file, 0, SEEK_SET);
	
	// Start up ECC/EDC checker.
	eccedc_init();
	
	for(int i = 0; i < numOfSectors; i++) { // For every sector...
		// Load the sector into a buffer.
		uint8_t * Buf = (uint8_t*)malloc(sizeof(uint8_t)*2352);
		
		// Check if it's a goos sector.
		fread(Buf, 1, 2352, file);
		int resultEC = ecmify(Buf);
		if(resultEC != 0) { // If it's damaged, do a repair.
			rsDecode(Buf);
		}
		if(ecmify(Buf)) { // If we failed to fix it.
			printf("Failed to fix.\n");
		} else if (resultEC) { // If we fixed it.
			printf("Successfully fixed!\n");
		}
		// Write the sector into the new file.
		fwrite(Buf, 1, 2352, newFile);
		free(Buf);
	}
}
