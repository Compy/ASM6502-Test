#include <nes.h>
#include <unistd.h>

void write_string(char *str)
{
  // Set the locations on screen for the string
  *((unsigned char*)0x2006) = 0x31;
  *((unsigned char*)0x2006) = 0x42;

  while(*str) {
    *((unsigned char*)0x2007) = *str;
    str++;
  }
}

int main()
{
  // We need to wait for the processor to become ready.
  // When its ready, the vblank line will change state...
  waitvblank();

  // Lets set the color schemes up. First the background.
  // Set the write mode
  *((unsigned char*)0x2006) = 0x3F;
  // Address to put the color in
  *((unsigned char*)0x2006) = 0x00;
  // Palette value, blue for example
  *((unsigned char*)0x2007) = COLOR_BLACK;

  // Set the write mode again
  *((unsigned char*)0x2006) = 0x3F;
  // Set the destination address to the foreground byte
  *((unsigned char*)0x2006) = 0x03;
  // Set the color to be white
  *((unsigned char*)0x2007) = COLOR_BLACK;

  // Write a string to the screen buffer
  write_string("SE RULZ!");

  // Set the X offset
  *((unsigned char*)0x2005) = 0x00;
  // Set the Y offset
  *((unsigned char*)0x2005) = 0x00;
  // Enable the screen
  *((unsigned char*)0x2001) = 8;

  // Loop forever so that our game stays "on"
  while(1);

  // Because C is pedantic, make sure we have a return code... though
  // the 6502 doesn't care...
  return 0;
}
