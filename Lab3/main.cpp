#include <stdint.h>
#include <iostream>
using namespace std;

extern const uint8_t * const p_start_image0;
extern const uint8_t** image1;
const uint8_t * const p_start_image1 = &image1[0][0];
int main()
{
  cout << p_start_image1;
  return 0;
}
