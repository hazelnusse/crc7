When communicating to SD cards in SPI mode, a 6-byte command frame is used.
The first byte is the command index.  Bytes two through five are the argument.
The last byte is a CRC byte the is calculated on the first five bytes.  The CRC
polynomial is:

G(x) = x^7 + x^3 + x^0

The result of this CRC calculation goes in the upper 7 bits of the CRC byte.
The 0 bit of is set high.

This code shows what the CRC7 bytes are for a few commond SD commands.

You will need a gcc 4.7 or newer in order to build this with the current
Makefile, although it should be straightforward to modify to work with earlier
compilers or even with a C compiler.
