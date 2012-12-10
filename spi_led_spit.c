
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>

uint8_t makeFlag(uint8_t red, uint8_t green, uint8_t blue) {
  uint8_t flag = 0;

  flag = (red&0xC0)>>6;  // (0xff & 0xC0) >> 6 = 0b1111 1111 & 0b1100 0000 >> 6 = 0b1100 0000 >>6 = 0b0000 0011
	// flag = 0b0000 0011  at this point if red is 0xff
  flag = flag | ((green&0xC0)>>4); // 0b0000 0011 | ((0b0000 0000 & 0b1100 0000) >> 4) = 0b0000 0011 | ((0b0000 0000) >> 4) = 0b0000 0011
	// flag = 0b0000 0011 at this point if green is 0x00 and red is 0xff
  flag = flag | ((blue&0xC0)>>2); // same as last time... since blue is 0x00 also
	// flag = 0b0000 0011 at this point if green is 0x00 and red is 0xff
  return ~flag; // inversion! so 0b0000 0011 goes to 0b1111 1100  =  0xfc
}

int sendFrame(unsigned char *data) {
	return wiringPiSPIDataRW(0, data, 4);
}

int sendEmptyFrame() {
	uint8_t empty_data [4];
	empty_data[0] = 0;
	empty_data[1] = 0;
	empty_data[2] = 0;
	empty_data[3] = 0;
	return sendFrame(empty_data);
}

int sendColor(uint8_t red, uint8_t green, uint8_t blue) {
	uint8_t color_data [4];
	color_data[0] = makeFlag(red, green, blue);
	color_data[1] = blue;
	color_data[2] = green;
	color_data[3] = red; // red last!? Yeah, crazy, I know. deal with it.
	return sendFrame(color_data);
}

uint8_t parseRed(char* color) {
	char red_color[3];
	unsigned int to_ret;
	red_color[0] = color[0];
	red_color[1] = color[1];
	red_color[2] = 0;
	sscanf(red_color, "%x", & to_ret);
	return to_ret;
}
uint8_t parseGreen(char* color) {
	char green_color[3];
	unsigned int to_ret;
	green_color[0] = color[2];
	green_color[1] = color[3];
	green_color[2] = 0;
	sscanf(green_color, "%x", & to_ret);
	return to_ret;
}
uint8_t parseBlue(char* color) {
	char blue_color[3];
	unsigned int to_ret;
	blue_color[0] = color[4];
	blue_color[1] = color[5];
	blue_color[2] = 0;
	sscanf(blue_color, "%x", & to_ret);
	return to_ret;
}

int main (int argc, char* argv[]) {
	int i;
	int channel = 0;
	uint8_t red, green, blue;
	
	if (argc == 1) {
		printf("No colors given. Exiting... \n");
		return 1;
	}
	
	if (wiringPiSetup () == -1)
	{
		fprintf (stdout, "oops: %s\n", strerror (errno)) ;
		return 1 ;
	}

	if (wiringPiSPISetup (channel, 1000000) < 0) 
		fprintf (stderr, "SPI Setup failed: %s\n", strerror (errno));
		
	printf("Writing stdin colors to SPI channel 0\n");
	
	
	sendEmptyFrame();
	for (i=1; i < argc; i += 1) {
		red = parseRed(argv[i]);
		green = parseGreen(argv[i]);
		blue = parseBlue(argv[i]);
		printf("Setting pixel %i to: %i, %i, %i\n", i, red, green, blue);
		sendColor(red, green, blue);
	}
	sendEmptyFrame();
	
	printf("Colors written\n");
	
	return 0;
}
