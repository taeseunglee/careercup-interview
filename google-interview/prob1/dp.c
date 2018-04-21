#include <stdio.h>
#include <stdlib.h>

int main()
{
  int width, height;
  scanf("%d %d", &width, &height);

#ifdef TD // 2D solution
  // __init__
  int **matrix = calloc(height, sizeof(int*));
  for (int r_i = 0; r_i < height; ++r_i)
    matrix[i] = calloc(width, sizeof(int));

  // __process__
  matrix[height-1][0] = 1;
  for (int c_i = 1; c_i < width; ++c_i)
    {
      int lower_right_dir = 0;
      for (int r_i = 0; r_i < height; ++r_i)
        {
          matrix[r_i][c_i] =
           ((r_i-1 != height) ? matrix[r_i][c_i+1] : 0)   // upper-right
                              + matrix[r_i][c_i-1]        // right
                              + lower_right_dir;          // lower-right
        }
    }

  // __print_result__
  printf("%d\n", matrix[height-1][width-1]);

#else // 1D solution
  // __init__
  int *mat_col = calloc(height, sizeof(int));

  // __process__
  mat_col[height-1] = 1;
  for (int c_i = 1; c_i < width; ++c_i)
    {
      int lower_right = 0;
      for (int r_i = 0; r_i < height; ++r_i)
        {
          int next_lower_right = mat_col[r_i];
          mat_col[r_i] += lower_right
            + ((r_i-1 != height) ? mat_col[r_i+1] : 0);
          lower_right = next_lower_right;
        }
    }

  // __print_result__
  printf("%d\n", mat_col[height-1]);
#endif
  return 0;
}
