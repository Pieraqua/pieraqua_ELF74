/**
*   @file images.h
*   @brief Arquivo com definições a serem utilizadas no Lab3.
*/

extern "C"{
extern const uint16_t width0;
extern const uint16_t height0;
extern const uint8_t * const p_start_image0;

extern const uint16_t width1;
extern const uint16_t height1;
extern const uint8_t **image1;

uint16_t EightBitHistogram(uint16_t width, uint16_t height, const uint8_t * const p_image, uint16_t *p_histogram);
}