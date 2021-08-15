#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "android_arm_util.h"
#include "neon_col_swap.h"

#define C_COLOR_SWAP_1      0
#define C_COLOR_SWAP_2      0
#define NEON_COLOR_SWAP     1

#define ORI_INTER_DATA "/vendor/bin/data/icon_interleve.bin"
#define RES_INTER_DATA_1 "/vendor/bin/data/icon_interleve_swap_1.bin"                       // c_color_swap1
#define RES_INTER_DATA_2 "/vendor/bin/data/icon_interleve_swap_2.bin"                       // c_color_swap2
#define RES_INTER_DATA_NEON "/vendor/bin/data/icon_interleve_swap_neon.bin"                 // neon_color_swap

int main(int argc, char* argv[])
{
    FUNC_ENTRANCE_LOG;
    uint8_t *p_img = NULL;
    int read_size = 0;
    size_t fsize;
    FILE *file = fopen(ORI_INTER_DATA, "rb");

    if (!file)
    {
       ex_log(LOG_ERROR, "%s FILE %s doesn't exist", __func__, ORI_INTER_DATA);
       goto EXIT_MAIN;
    }
    
    fseek(file, 0L, SEEK_END);
    fsize = (size_t)ftell(file);
    ex_log(LOG_DEBUG, "%s FILE's size is %zu", __func__, fsize);
    fclose(file);
    file = NULL;

    file = fopen(ORI_INTER_DATA, "rb");
    if (!file)
    {
        ex_log(LOG_ERROR, "%s FILE %s reopen failed", __func__, ORI_INTER_DATA);
        goto EXIT_MAIN;
    }

    p_img = malloc(fsize);
    if (!p_img)
    {
        ex_log(LOG_ERROR, "%s allocates img buffer failed", __func__);
        goto EXIT_MAIN;
    }

    read_size = fread(p_img, 1, fsize, file);
    fclose(file);
    ex_log(LOG_DEBUG, "%s read_size is %d", __func__, read_size);

#if C_COLOR_SWAP_1
    ex_log(LOG_DEBUG, "%s enables C_COLOR_SWAP_1", __func__);
    c_color_swap1(p_img, read_size);

    file = fopen(RES_INTER_DATA_1, "wb");

    if (file)
    {
        ex_log(LOG_DEBUG, "%s writes swap_color_img %s", __func__, RES_INTER_DATA_1);
        fwrite(p_img, 1, read_size, file);
        fclose(file);
    } else
    {
        ex_log(LOG_ERROR, "%s opens %s failed", __func__, RES_INTER_DATA_1);
    }
#endif

#if C_COLOR_SWAP_2
    ex_log(LOG_DEBUG, "%s enables C_COLOR_SWAP_2", __func__);
    c_color_swap2(p_img, read_size);

    file = fopen(RES_INTER_DATA_2, "wb");

    if (file)
    {
        ex_log(LOG_DEBUG, "%s writes swap_color_img %s", __func__, RES_INTER_DATA_2);
        fwrite(p_img, 1, read_size, file);
        fclose(file);
    } else
    {
        ex_log(LOG_ERROR, "%s opens %s failed", __func__, RES_INTER_DATA_2);
    }
#endif

#ifdef NEON_COLOR_SWAP
    ex_log(LOG_DEBUG, "%s enbles NEON_COLOR_SWAP", __func__);
    neon_color_swap(p_img, read_size);

    file = fopen(RES_INTER_DATA_NEON, "wb");

    if (file)
    {
        ex_log(LOG_DEBUG, "%s writes swap_color_img %s", __func__, RES_INTER_DATA_NEON);
        fwrite(p_img, 1, read_size, file);
        fclose(file);
    } else
    {
        ex_log(LOG_ERROR, "%s opens %s failed", __func__, RES_INTER_DATA_NEON);
    }
#endif

EXIT_MAIN:
    if (p_img)
    {
        free(p_img);
    }
    FUNC_EXIT_LOG;
    return 0;
}
