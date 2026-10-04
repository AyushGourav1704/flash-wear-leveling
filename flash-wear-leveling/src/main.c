#include <stdio.h>
#include "../include/flash.h"
#include "../include/wear_leveling.h"

int main(void)
{
    int choice;
    char data[100];

    flash_init();

    while (1)
    {
        printf("\n===== FLASH WEAR-LEVELING SIMULATOR =====\n");
        printf("1. Write Data\n");
        printf("2. Show Block Status\n");
        printf("3. Exit\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter data: ");
                scanf("%99s", data);

                wear_leveling_write(data);
                break;

            case 2:
                flash_show();
                break;

            case 3:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
