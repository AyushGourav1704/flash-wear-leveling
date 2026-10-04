#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "../include/flash.h"
#include "../include/wear_leveling.h"

extern FlashBlock blocks[TOTAL_BLOCKS];

int find_least_used_block(void)
{
    int min = blocks[0].write_count;
    int index = 0;

    for (int i = 1; i < TOTAL_BLOCKS; i++)
    {
        if (blocks[i].write_count < min)
        {
            min = blocks[i].write_count;
            index = i;
        }
    }

    return index;
}

void wear_leveling_write(const char *data)
{
    int block;
    int fd;

    /* Find the least-used block */
    block = find_least_used_block();

    printf("Wear leveling selected Block %d\n", block);

    /* Open Linux device driver */
    fd = open("/dev/flash_wl", O_WRONLY);

    if (fd >= 0)
    {
        /* Send data to the Linux device driver */
        write(fd, data, strlen(data));

        close(fd);

        printf("Data sent to Linux device driver\n");
    }
    else
    {
        printf("Could not open Linux device driver\n");
    }

    /* Write data to simulated flash */
    flash_write(block, data);
}
