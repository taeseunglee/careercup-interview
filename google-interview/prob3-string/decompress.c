#include <stdio.h>
#include <string.h>

#define MAX 1000

struct packet {
  char sub_str[MAX];
  int idx;
  int rep;
  int length;
};

// return idx after } or 
struct packet decompress_string (const char * const str, int idx);

int main()
{
  char *dstr[] = {
      "abc",
      "a(b){3}",
      "a(b(c){2}){2}d",
      "((x){3}(y){2}z){2}"
  };

  int T = sizeof(dstr) / sizeof(char*);
  for (int t_i = 0; t_i < T; ++t_i)
    {
      printf("Test %d : %s\n", t_i, dstr[t_i]);
      struct packet res = decompress_string(dstr[t_i], 0);
      printf("T%d : %s\n", t_i, res.sub_str);
    }

  return 0;
}

struct packet decompress_string (const char * const str, int idx)
{
  struct packet res;
  unsigned int len_s = strlen(str);
  int idx_sub = 0;
  while (idx < len_s)
    {
      if (str[idx] == '(') // in
        {
          struct packet ret = decompress_string(str, idx+1);
          idx = ret.idx;
          for (int i_r = 0; i_r < ret.rep; ++i_r, idx_sub += ret.length)
            strcpy(res.sub_str+idx_sub, ret.sub_str);
        }
      else if (str[idx] == ')' && str[idx+1] == '{') // escape
        {
          idx += 2;
          res.rep = 0;
          while (str[idx] != '}')
            res.rep = res.rep*10 + (str[idx++]-'0');

          res.idx = idx+1;
          res.sub_str[idx_sub] = '\0';
          res.length = idx_sub;
          return res;
        }
      else
        {
          res.sub_str[idx_sub++] = str[idx++];
        }
    }

  res.sub_str[idx_sub] = '\0';
  return res;
}
