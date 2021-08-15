#ifndef __NEON_COL_SWAP_H__
#define __NEON_COL_SWAP_H__
void c_color_swap1(uint8_t *p_img, const size_t buffer_size);
void c_color_swap2(uint8_t *p_img, const size_t buffer_size);
void neon_color_swap(uint8_t *p_img, const size_t buffer_size);
#endif
