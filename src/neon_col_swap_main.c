#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "android_arm_util.h"

#define ORI_INTER_DATA "/vendor/bin/data/icon_interleve.bin"
#define RES_INTER_DATA "/vendor/bin/data/icon_interleve_swap.bin"

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
    ex_log(LOG_DEBUG, "%s read_size is %d", __func__, read_size);
    ex_log(LOG_DEBUG, "%s %d %d %d", __func__, *p_img, *(p_img+1), *(p_img+2));
    ex_log(LOG_DEBUG, "%s %d %d %d", __func__, *(p_img+17090), *(p_img+17091), *(p_img+17092));

EXIT_MAIN:
    if (p_img)
    {
        free(p_img);
    }
    FUNC_EXIT_LOG;
    return 0;
}
