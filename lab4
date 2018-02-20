#include <stdio.h>

#define MAX_MEMORY_SIZE 100

int parse_args(int argc, char **argv) {
  int t_size;
  if (argc == 2 && t_size = atoi(argv[1])) {
    return t_size;
  }
  fprintf(stderr, "Incorrect number of arguments. Argument should be the page table size\n");
  exit(-1);
}

int in_memory(int page, int *p_table, int t_size) {
  for (int i = 0; i < t_size; i++) {
    if (p_table[i] == page) {
      return i;
    }
  }
  return -2;
}

int main(int argc, char **argv) {
  int table_size = parse_args(argc, argv);
  int p_req, p_table_ind = 0, miss_rate = 0, reqs = 0;
  int *p_table = (int *) malloc(sizeof(int)*MAX_MEMORY_SIZE);
  char *input = NULL;
  ssize_ bytes;
  size_t input_allocated = 0;
   
  while ((bytes = getline(&input, &input_allocated, stdin)) != EOF) {
    p_req = atoi(input);
    if (!in_memory(p_req, p_table, table_size)) {
      printf("Page number %d caused a page fault\n", p_req);
      miss_rate++;
      if (p_table_ind < table_size) {
	p_table[p_table_ind++] = p_req;
      } else {
	// TODO implement page replacement algorithm
      }
  }
  printf("Hit rate = %d\n", reqs - miss_rate);
  free(input);
  free(p_table);
  return 0;
}

// cat tstfile | ./example 10