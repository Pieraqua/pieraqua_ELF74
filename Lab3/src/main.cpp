#include <stdint.h>
#include <iostream>
using namespace std;
#include <images.h>

extern "C" uint16_t EightBitHistogram(uint16_t width, uint16_t height, uint8_t const *p_image, uint16_t *p_histogram);

int main()
{
  uint16_t histogram[256];
  int pixels = EightBitHistogram(width1, height1, &image1[0][0], histogram);
  cout << pixels << endl;
  for (int i = 0; i < 255; i++){
    cout << histogram[i] << endl;}
  return 0;
}
