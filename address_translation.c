#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int vas_mb = atoi(argv[1]);
    int page_kb = atoi(argv[2]);
    int vaddr = atoi(argv[3]);

    long vas_bytes = vas_mb * 1024 * 1024;
    long page_bytes = page_kb * 1024;

    int num_pages = vas_bytes / page_bytes;

    int page_number = vaddr / page_bytes;
    int offset = vaddr % page_bytes;

    if(page_number >= num_pages)
    {
        printf("Page table miss!\n");
        return 0;
    }

    int page_table[num_pages];

    for(int i = 0; i < num_pages; i++)
        page_table[i] = i;

    int frame_number = page_table[page_number];

    printf("<%d, %d>\n", frame_number, offset);

    return 0;
}