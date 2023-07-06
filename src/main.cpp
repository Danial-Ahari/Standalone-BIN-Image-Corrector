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
	FILE *file = fopen(argv[1], "rb");
	FILE *newFile = fopen(argv[2], "wb");
	fseek(file, 0, SEEK_END);
	int numOfSectors = ftell(file)/2352;
	fseek(file, 0, SEEK_SET);
	eccedc_init();
	for(int i = 0; i < numOfSectors; i++) {
		uint8_t * Buf = (uint8_t*)malloc(sizeof(uint8_t)*2352);
		fread(Buf, 1, 2352, file);
		int resultEC = ecmify(Buf);
		if(resultEC != 0) {
			rsDecode(Buf);
		}
		fwrite(Buf, 1, 2352, newFile);
		free(Buf);
	}
}
