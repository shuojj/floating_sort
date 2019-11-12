#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>


/* #define PRINTVALUES */

void negpos(float *unjoined, float *joined, int n){
	int numpos=0; 
	int numneg=0;
	for (int i = 0; i < n; i++) {
		if (unjoined[i] >= 0){
			numpos+=1;

		}
		else {
			numneg+=1;
			
		}
	}
	int j=0;
	for (int i = n-1; i >= n-numneg; i--){
		joined[j] = unjoined[i];
		j++;
	}
	for (int i = 0; i < numpos; i++){
		joined[j] = unjoined[i];
		j++;
	}
}
void rsort(float *lst2, float *dst, int n){
  unsigned int group = 8;
  unsigned int buckets = 2 << group;
  unsigned int mask = buckets - 1;
  unsigned int cnt[buckets];
  unsigned int map[buckets];
  unsigned int *lst = (unsigned int*) lst2;

  for(unsigned int k = 0; k < 32; k += 8){
    
    memset(cnt, 0, sizeof(cnt));
    memset(map, 0, sizeof(map));
    

    for(unsigned i = 0; i < n; i++){
      cnt[(lst[i] >> k) & mask]++;
    }

    map[0] = 0;
    for(unsigned i = 1; i < buckets; i++){
      map[i] = map[i - 1] + cnt[i - 1];
    }

    for(unsigned i = 0; i < n; i++){
      dst[map[(lst[i] >> k) & mask]++] = lst2[i];
    }

    for(unsigned i = 0; i < n; i++){
      lst2[i] = dst[i];
    }
  }
  negpos(dst, lst2, n);
}

int main(int argc, char *argv[])
{
    int i, fd, ascending=1;
    double dvalue, total = 0;
    long ivalue;
    float *lst;  
    float *map;
    int n, filesize;

    fd = open(argv[1], O_RDWR);

    if (fd == -1) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    lseek(fd, 0, SEEK_END);
    filesize = lseek(fd, 0, SEEK_CUR) ;
    n = filesize >> 2;

    lst = mmap(0, filesize, PROT_WRITE, MAP_SHARED, fd, 0);
    float *tmp;
    tmp = malloc(sizeof(float)*n);
    
    if (lst == MAP_FAILED) {
        close(fd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }
    rsort(lst, tmp, n);
    for (int i = 0; i < n; i++){
      total+=lst[i];
    }
    printf("Total: %.2f\n", total);
    return 0;
}