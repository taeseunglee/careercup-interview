#include <stdio.h>
#include <string.h>
#define MAX 100

void get_failure(const char * const pat, int *failure);
int modified_kmp(const char * const str, const char * const pat, const int * const failure);

int main()
{
  // __init__
  char str[MAX], pat[MAX];
  int failure[MAX];

#ifdef t1
  strcpy(str, "AGoogleInterviewIsAwesome");
  strcpy(pat, "IA");
#elif t2
  strcpy(str, "AGoogleIsAwesome");
  strcpy(pat, "IsA");
#else
  printf("Enter the String : ");
  scanf("%s", str);

  printf("Enter the Pattern : ");
  scanf("%s", pat);
#endif

  // __process__
  get_failure(pat, failure);
  unsigned int idx_first_occur = modified_kmp(str, pat, failure);

  // __print_result__
  printf("The Index in str of the first occurence of pat : %u\n",
         idx_first_occur);

  return 0;
}

void get_failure(const char * const pat, int *failure)
{
  failure[0] = 0;
  for (unsigned int i_p  = 1; pat[i_p]; ++i_p)
    {
      unsigned int idx_pre = failure[i_p];

      while (pat[i_p] != pat[idx_pre] && idx_pre > 0)
        idx_pre = failure[idx_pre];
      
      if (pat[i_p] == pat[idx_pre])
        failure[i_p] = failure[idx_pre]+1;
      else
        failure[i_p] = 0; 
    }
}

int modified_kmp(const char * const str, const char * const pat, const int * const failure)
{
  unsigned int len_p = strlen(pat),
      len_s = strlen(str);
  unsigned int i_p = -1, i_s = 0;

  while (i_p < len_p && i_s < len_s)
    {
      if (str[i_s] == pat[i_p])
        ++ i_s, ++ i_p;
      else // str[i_s] != pat[i_p]
        {
          if (i_p == 0)
            ++i_s;
          else
            i_p = failure[i_p];
        }
    }

  return ((i_p == len_p) ? i_s : -1);
}
