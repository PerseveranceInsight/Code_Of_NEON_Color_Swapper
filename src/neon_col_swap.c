#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <arm_neon.h> 

#include "neon_col_swap.h"
#include "android_arm_util.h"

#define R1_MASK 0xFF000000
#define B0_MASK 0x00FF0000
#define G0_MASK 0x0000FF00
#define R0_MASK 0x000000FF

void c_color_swap1(uint8_t *p_img, const size_t buffer_size)
{
    FUNC_ENTRANCE_LOG;
    int i = 0;
    uint8_t pixel_channel_con = 0;
    unsigned int num_pixel = buffer_size/3; // R,G,B
    unsigned int pixel_contains = 0, pixel_swap_contains = 0;
    uint8_t *p_r_pixel = NULL;
    uint8_t *p_g_pixel = NULL;
    uint8_t *p_b_pixel = NULL;
    uint32_t *p_pixel = NULL;

    for (i = 0; i<num_pixel-1;i++)
    {
        p_pixel = (uint32_t*)(p_img + i*3);
        pixel_contains = *p_pixel;
        pixel_swap_contains = (pixel_contains&R0_MASK)<<16;
        pixel_swap_contains |= (pixel_contains&B0_MASK)>>16;
        pixel_swap_contains |= (pixel_contains&G0_MASK);
        pixel_swap_contains |= (pixel_contains&R1_MASK);
        *p_pixel = pixel_swap_contains;
    }

    p_r_pixel = (uint8_t*)p_img + buffer_size - 3;
    p_b_pixel = (uint8_t*)p_img + buffer_size - 1;
    pixel_channel_con = *p_r_pixel;
    *p_r_pixel = *p_b_pixel;
    *p_b_pixel = pixel_channel_con;

    FUNC_EXIT_LOG;
}

void c_color_swap2(uint8_t *p_img, const size_t buffer_size)
{
    FUNC_ENTRANCE_LOG;
    int i = 0;
    uint8_t pixel_channel_con = 0;
    unsigned int num_pixel = buffer_size/3; // R,G,B
    uint8_t *p_r_pixel = NULL;
    uint8_t *p_b_pixel = NULL;
    uint32_t *p_pixel = NULL;

    for (i = 3612; i<3613; i++)
    {
        p_pixel = (uint32_t*)(p_img + i*3);
        p_r_pixel = p_img + i*3;
        p_b_pixel = p_img + i*3 + 2;
        pixel_channel_con = *p_r_pixel;
        *p_r_pixel = *p_b_pixel;
        *p_b_pixel = pixel_channel_con;
    }

    FUNC_EXIT_LOG;
}

void neon_color_swap(uint8_t *p_img, const size_t buffer_size)
{
    // vld3q_u8
    // vreinterpretq_u32_u8
    // vst1q_u8
    // vst3q_u8
    FUNC_ENTRANCE_LOG;
    int i = 0;
    int num_iteration = buffer_size / (sizeof(uint8_t)*16*3);
    ex_log(LOG_DEBUG, "%s num_iteration %d", __func__, num_iteration);
    uint32_t *p_pixel_arr;
    uint8x16_t pixel_con_ch;
    uint8x16x3_t pixel_con_3q;

    for (i=0; i<num_iteration; i++)
    {
        p_pixel_arr = (uint32_t*)(p_img + i*sizeof(uint8_t)*16*3);
        pixel_con_3q = vld3q_u8((uint8_t*)p_pixel_arr);
        pixel_con_ch = pixel_con_3q.val[0];
        pixel_con_3q.val[0] = pixel_con_3q.val[2];
        pixel_con_3q.val[2] = pixel_con_ch;
        vst3q_u8((uint8_t*)p_pixel_arr, pixel_con_3q);
    }

    FUNC_EXIT_LOG;
}
