#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HEIGHT 8
#define WIDTH 8
#define M_AMOUNT 10

#define MASK 10

void init(int *stage);
void shuffle(int *stage);
void show_map(int *stage);

int  search_M(int *stage, int pos);
int  open_cell(int *stage, int pos);
int  input();

int main(void)
{
  int stage[HEIGHT*WIDTH];

  int i;

  init(stage);

  while(1){
    i = input();

    open_cell(stage, i);

    show_map(stage);
  }

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

    if(stage[i] >= MASK){
      printf("#");
    }else if(stage[i] == 1){
      printf("M");
    }else if(stage[i] == 0){
      risk = search_M(stage,i);
      if(risk){
        printf("%d",risk);
      }else{
        printf("-");
      }
    }
  }

  if(i%WIDTH == 0) puts("");
}

int search_M(int *stage, int pos)
{
  int i,j;
  int x,y;
  int ret = 0;

  x = pos % WIDTH;
  y = pos / WIDTH;

  for(i=-1; i<=1; i++){
    if(y+i < 0 || y+i >= HEIGHT) continue;
    for(j=-1; j<=1; j++){
      if(x+j < 0 || x+j >= WIDTH) continue;
      ret += stage[WIDTH*(y+i) + x+j] % MASK;
    }
  }

  return ret;
}

int open_cell(int *stage, int pos)
{
  if(stage[pos] >= MASK){
    stage[pos] -= MASK;
  }

  return stage[pos];
}

int input()
{
  int x, y;

  scanf("%d",&x);
  scanf("%d",&y);

  return y*WIDTH + x;
}
