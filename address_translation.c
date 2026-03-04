/*Simulate the address translation in the paging scheme as follows: The program receives
three command line arguments in the order
    ● size of the virtual address space (in megabytes)
    ● page size (in kilobytes)
    ● a virtual address (in decimal notation)
The output should be the physical address corresponding to the virtual address in <frame
number, offset> format. You may assume that the page table is implemented as an array
indexed by page numbers. (NB: If the page table has no index for the page number
determined from the virtual address, you may just declare a page table miss!)
*/

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