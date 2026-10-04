#ifndef FLASH_H
#define FLASH_H

#define TOTAL_BLOCKS 8
#define BLOCK_SIZE 100

typedef struct
{
    int block_id;
    int write_count;
    int valid;
} FlashBlock;

extern FlashBlock blocks[TOTAL_BLOCKS];

void flash_init(void);
void flash_write(int block_id, const char *data);
void flash_show(void);

#endif
