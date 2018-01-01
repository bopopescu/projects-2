#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mymalloc.h"

void double_check_memory(int **ptrs, int *dc, int nptrs, int fl_size)
{
  void *low, *l;
  void *high, *h;
  int *ip, i;
  int nbytes;
  int nfl;

  nbytes = 0;

  for (i = 0; i < nptrs; i++) {
    l = (void *) ptrs[i];
    l -= 8;
    ip = (int *) l;

    if (*ip != dc[i]) {
      printf("Error: pointer number %d the wrong size (%d instead of %d)\n", i, *ip, dc[i]);
      exit(1);
    }
    h = l + *ip;
    if (nbytes == 0 || l < low) low = l;
    if (nbytes == 0 || h > high) high = h;
    nbytes += *ip;
  }
    
  nfl = 0;
  for (l = free_list_begin(); l != NULL; l = free_list_next(l)) {
    ip = (int *) l;
    h = l + *ip;
    if (nbytes == 0 || l < low) low = l;
    if (nbytes == 0 || h > high) high = h;
    nbytes += *ip;
    nfl++;
  }

  if (nbytes != 8192) {
    printf("Error: Total bytes allocated and on the free list = %d, not 8192\n", nbytes);
    exit(0);
  }
    
  if (high - low != 8192) {
    printf("Error: Highest address (0x%x) minus lowest (0x%x) does not equal 8192\n", (int) high, (int) low);
    exit(0);
  }

  if (nfl != fl_size && fl_size != -1) {
    printf("Error: %d nodes on the free list -- should be %d\n", nfl, fl_size);
    exit(0);
  }
}


main()
{
  int *ptrs[25];
  int *free_ptrs[10];
  int dc[25];

  free_ptrs[0] = my_malloc(120);
  free_ptrs[4] = my_malloc(129);
  ptrs[2] = my_malloc(113); dc[2] = 128;
  free_ptrs[1] = my_malloc(123);
  free_ptrs[8] = my_malloc(123);
  free_ptrs[9] = my_malloc(149);
  ptrs[5] = my_malloc(114); dc[5] = 128;
  ptrs[1] = my_malloc(137); dc[1] = 152;
  free_ptrs[5] = my_malloc(132);
  ptrs[4] = my_malloc(151); dc[4] = 160;
  ptrs[9] = my_malloc(122); dc[9] = 136;
  ptrs[3] = my_malloc(120); dc[3] = 128;
  ptrs[8] = my_malloc(122); dc[8] = 136;
  ptrs[6] = my_malloc(123); dc[6] = 136;
  ptrs[0] = my_malloc(139); dc[0] = 152;
  free_ptrs[6] = my_malloc(151);
  ptrs[7] = my_malloc(131); dc[7] = 144;
  free_ptrs[3] = my_malloc(129);
  free_ptrs[2] = my_malloc(116);
  free_ptrs[7] = my_malloc(145);

  my_free(free_ptrs[5]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[1]);

  ptrs[13] = my_malloc(93); dc[13] = 104;
  ptrs[17] = my_malloc(88); dc[17] = 96;
  ptrs[20] = my_malloc(94); dc[20] = 104;
  ptrs[19] = my_malloc(89); dc[19] = 104;
  ptrs[15] = my_malloc(75); dc[15] = 88;
  ptrs[12] = my_malloc(73); dc[12] = 88;
  ptrs[24] = my_malloc(76); dc[24] = 88;
  ptrs[18] = my_malloc(85); dc[18] = 96;
  ptrs[10] = my_malloc(73); dc[10] = 88;
  ptrs[21] = my_malloc(81); dc[21] = 96;
  ptrs[22] = my_malloc(83); dc[22] = 96;
  ptrs[23] = my_malloc(79); dc[23] = 88;
  ptrs[16] = my_malloc(93); dc[16] = 104;
  ptrs[11] = my_malloc(74); dc[11] = 88;
  ptrs[14] = my_malloc(80); dc[14] = 88;

  double_check_memory(ptrs, dc, 25, 11);
  printf("Correct\n");
}
