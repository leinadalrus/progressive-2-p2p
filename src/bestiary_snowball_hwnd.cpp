#include "../inc/stemfile_buffer_file_throughput.hpp"

int main(void)
{
  struct sb_stemmer *stemmer;
  FILE *file_input;
  FILE *file_output;
  stem(stemmer, file_input, file_output);
}