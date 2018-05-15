#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HEIGHT 8
#define WIDTH 8
#define M_AMOUNT 8

#define MASK 10

void init(int *stage);
void shuffle(int *stage);
void show_map(int *stage);

int  search_M(int *stage, int x, int y);

int main(void)
{
  int stage[HEIGHT*WIDTH];

  init(stage);
}

void init(int *stage)
{
  int i;

	srand((unsigned)time(NULL));

  for(i = 0; i < HEIGHT*WIDTH; i++){
    stage[i] = MASK;
    if(i < M_AMOUNT) stage[i]++;
  }

  shuffle(stage);
  show_map(stage);
}

void shuffle(int *stage)
{
  int i,j;
  int tmp;
  
  for(i = 0; i < HEIGHT*WIDTH; i++){
    j = rand()%(HEIGHT*WIDTH);
    tmp = stage[i];
    stage[i] = stage[j];
    stage[j] = tmp;
  }
}

void show_map(int *stage)
{
  int i;
  int risk;

  for(i = 0; i < HEIGHT*WIDTH; i++){
    if(i%WIDTH == 0) puts("");
    if(stage[i]%MASK) printf("M");
    else {
      risk = search_M(stage,i%WIDTH,i/WIDTH);  
      if(risk) printf("%d",risk);
      else printf("-");
    }
  }
  if(i%WIDTH == 0) puts("");
}

int search_M(int *stage, int x, int y){
  int i,j;
  int ret = 0;

  --x;
  --y;

  for(i=0; i<3; i++){
    if(y+i < 0 || y+i >= HEIGHT) continue;
    for(j=0; j<3; j++){
      if(x+j < 0 || x+j >= WIDTH) continue;
      ret += stage[WIDTH*(y+i) + x+j] - MASK;
    }
  }

  return ret;
}
