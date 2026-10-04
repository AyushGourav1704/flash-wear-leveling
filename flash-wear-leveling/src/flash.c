#include <stdio.h>
#include "../include/flash.h"

FlashBlock blocks[TOTAL_BLOCKS];

void flash_init(void)
{
    for (int i = 0; i < TOTAL_BLOCKS; i++)
    {
        blocks[i].block_id = i;
        blocks[i].write_count = 0;
        blocks[i].valid = 0;
    }
}

void flash_write(int block_id, const char *data)
{
    if (block_id < 0 || block_id >= TOTAL_BLOCKS)
    {
        printf("Invalid block!\n");
        return;
    }

    blocks[block_id].write_count++;
    blocks[block_id].valid = 1;

    printf("Data written to Block %d\n", block_id);
    
    FILE *fp = fopen("data/storage.txt", "a");

	if (fp != NULL)
	{
	    fprintf(fp, "Block %d: %s\n", block_id, data);
	    fclose(fp);
	}
}

void flash_show(void)
{
    printf("\n--- Block Status ---\n");

    for (int i = 0; i < TOTAL_BLOCKS; i++)
    {
        printf("Block %d | Writes: %d | Valid: %d\n",
               blocks[i].block_id,
               blocks[i].write_count,
               blocks[i].valid);
    }
}
