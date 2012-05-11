#include <iostream>
#include <cstdint>

uint8_t CRCTable[256];
 
void GenerateCRCTable()
{
  int i, j;
  uint8_t CRCPoly = 0x89;  // the value of our CRC-7 polynomial
 
  // generate a table value for all 256 possible byte values
  for (i = 0; i < 256; ++i) {
    CRCTable[i] = (i & 0x80) ? i ^ CRCPoly : i;
    for (j = 1; j < 8; ++j) {
        CRCTable[i] <<= 1;
        if (CRCTable[i] & 0x80)
            CRCTable[i] ^= CRCPoly;
    }
  }
}
 
// adds a message byte to the current CRC-7 to get a the new CRC-7
uint8_t CRCAdd(uint8_t CRC, uint8_t message_byte)
{
    return CRCTable[(CRC << 1) ^ message_byte];
}
 
// returns the CRC-7 for a message of "length" bytes
uint8_t getCRC(uint8_t message[], int length)
{
  int i;
  uint8_t CRC = 0;

  for (i = 0; i < length; ++i)
    CRC = CRCAdd(CRC, message[i]);

  return CRC;
}

int main()
{
  // This is CMD8(0x1AA) from the SD card spec for probing acceptable operating
  // voltages
  uint8_t data[6] = {0x48, 0, 0, 1, 0xAA, 0};
  GenerateCRCTable();
  data[5] = ((getCRC(data, 5) << 1) | 1);
  std::cout << std::hex << "0x" << (int) data[5] << std::endl;
  std::cout << std::dec << (int) data[5] << std::endl;
}
