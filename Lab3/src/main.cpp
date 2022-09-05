#include <stdint.h>
#include <iostream>
using namespace std;

extern const uint8_t * const p_start_image0;
extern const uint8_t** image1;
const uint8_t * const p_start_image1 = &image1[0][0];
#define WIDTH  160
#define HEIGHT 120

extern "C" uint16_t EightBitHistogram(uint16_t width, uint16_t height, uint8_t const *p_image, uint16_t *p_histogram);

int main()
{
  uint16_t *histogram = (uint16_t*)malloc(256*sizeof(uint16_t));
  int width = WIDTH;
  int height = HEIGHT;
  int pixels = EightBitHistogram(width, height, p_start_image1, histogram);
  cout << pixels << endl;
  return 0;
}
