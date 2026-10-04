#ifndef WEAR_LEVELING_H
#define WEAR_LEVELING_H

int find_least_used_block(void);
void wear_leveling_write(const char *data);

#endif
