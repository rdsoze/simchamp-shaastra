#include <iostream.h>
#include <math.h>
#include <conio.h>

struct build
{
 int p,d,c,g,x,y,f;
};

int times[100]={0}, index, elapsed;

void swap(struct build *a, struct build *b)
{
 struct build *t;
 t->d = a->d; a->d = b->d; b->d = t->d;
 t->p = a->p; a->p = b->p; b->p = t->p;
 t->c = a->c; a->c = b->c; b->c = t->c;
 t->x = a->x; a->x = b->x; b->x = t->x;
 t->y = a->y; a->y = b->y; b->y = t->y;
 t->f = a->f; a->f = b->f; b->f = t->f;
}

void copy(struct build *a, struct build *b)
{
 a->d = b->d;
 a->p = b->p;
 a->c = b->c;
 a->x = b->x;
 a->y = b->y;
 a->f = b->f;
}

void fetch(struct build x[100], struct build y[100], int n)
{
 for(int i=1; i<n; i++)
   copy(&x[i-1], &y[i]);
}

int sort(struct build x[5][5], struct build y[100], int f = 0)
{
 int i,j,k=0;
 for(i=0;i<5;i++)
  for(j=0; j<5; j++)
   if(f==1 && i == 0 && j == 3)
    continue;
   else if(i!=2 || j!=2)
   {
    while(x[i][j].p > 2)
    {
     copy(&y[k], &x[i][j]);
     y[k].p = 2;
     x[i][j].p -=2;
     k++;
    }
    copy(&y[k],&x[i][j]);
    k++;
   }
 return k;  
}

int savefirst(int no , int max, int flag = 0)
{
 int s = 0, el = 0;
 while(no!=0 && el<=max)
 {
  el+=10;
  if(no >= 2) //Save a 2
  {  
   no -= 2;
   if(flag)
    cout<<"Saved (0,3)\n";
   s+=2;
  } 
  else //Save a 1
  {
   no -= 1;
   if(flag) 
    cout<<"Saved (0,3)\n";
   s+=1;  
  } 
 }
 elapsed+=el;
 return s;
}

void sub(struct build a[], int time, int n)
{
 for(int i =0; i<n; i++)
  a[i].d -= time;
}

int save(struct build a[], int n, int initial, int green, int max, int flag = 0)
{
 int elapsed = 0, saved=0, indi;
 sub(a,initial,n);

 for(int i=0; i<n && elapsed<max; i++)
 {
  if(a[i].d - a[i].c >= green && a[i].f)
  {
    saved+= a[i].p;
    if(flag)
	 cout<<"Saved ("<<a[i].x<<","<<a[i].y<<")\n";
    elapsed+= a[i].c;
    sub(a, a[i].c,n);
  }
 }
 ::elapsed+=elapsed;
 return saved;
}

void main()
{
 int i,j,k, sd, su;
 struct build up[5][5] = {{{3,250,-1,0},{5,400,-1,0},{2,200,-1,0},{3,400,-1,0},{2,300,-1,0}},{{1,300,-1,0},{4,400,-1,0},{2,200,-1,0},{3,300,-1,0},{5,350,-1,0}},{{5,500,-1,0},{4,450,-1,0},{0,0,0,1},{3,350,-1,0},{2,400,-1,0}},{{3,200,-1,0},{2,250,-1,0},{3,350,-1,0},{2,350,-1,0},{4,250,-1,0}},{{4,400,-1,0},{3,300,-1,0},{5,450,-1,0},{1,200,-1,0},{5,500,-1,0}}};
 
 struct build down[5][5] = {{{2,50,-1,0},{2,50,-1,0},{1,20,-1,0},{5,40,-1,0},{0,0,-1,0}},{{3,100,-1,0},{4,75,-1,0},{2,75,-1,0},{3,30,-1,0},{1,20,-1,0}},{{4,150,-1,0},{5,150,-1,0},{0,0,0,1},{3,200,-1,0},{2,50,-1,0}},{{4,150,-1,0},{5,200,-1,0},{2,150,-1,0},{4,150,-1,0},{3,100,-1,0}},{{3,200,-1,0},{5,250,-1,0},{2,300,-1,0},{4,150,-1,0},{4,200,-1,0}}};
 
 struct build sorted[100] = {0},trials[100] = {0}, sorted_d[100] = {0},trials_d[100] = {0};
 
 clrscr();

 for(i=0; i<5;i++)
  for(j=0; j<5; j++)
  {
   up[i][j].g = down[i][j].g = 0;
   up[i][j].c = down[i][j].c = 2*(abs(i-2)*10 + abs(j-2)*5);
   up[i][j].x = down[i][j].x = i; up[i][j].y = down[i][j].y = j;
   up[i][j].f = down[i][j].f = 1;
  }
 
 su = sort(up,sorted);
 sd = sort(down,sorted_d,1);

 clrscr();
 //for top section : Earliest Deadline First
 for(i=0;i<su; i++)
  for(j=0; j<su-1; j++)
   {
    if(sorted[j].d > sorted[j+1].d)
     swap(&sorted[j], &sorted[j+1]);

    if(sorted[j].d == sorted[j+1].d)
    {
     if(sorted[j].c > sorted[j+1].c)
      swap(&sorted[j], &sorted[j+1]);

     if(sorted[j].c == sorted[j+1].c)
       if(sorted[j].p < sorted[j+1].p)
	swap(&sorted[j], &sorted[j+1]);
    }
   }

  //for bottom section : Earliest Computation Time First
  for(i=0;i<sd; i++)
   for(j=0; j<sd-1; j++)
   {
    if(sorted_d[j].c > sorted_d[j+1].c)
     swap(&sorted_d[j], &sorted_d[j+1]);

    if(sorted_d[j].c == sorted_d[j+1].c)
    {
     if(sorted_d[j].d > sorted_d[j+1].d)
      swap(&sorted_d[j], &sorted_d[j+1]);

     if(sorted_d[j].d == sorted_d[j+1].d)
       if(sorted_d[j].p < sorted_d[j+1].p)
	swap(&sorted_d[j], &sorted_d[j+1]);
    }
   }
 clrscr();

 int top = -1, bottom = 0, max = 0, adj=0, max_condn, tadj = 0;
 for(i=0; i<20; i++)
 {
  elapsed = top = bottom = adj = 0;
  fetch(trials,sorted, su);
  fetch(trials_d, sorted_d, sd);
  adj = savefirst(down[0][3].p, i*10);
  tadj = elapsed;
  if(elapsed+30 < i*10)
  {
   elapsed+=30;
   bottom = save(trials_d, sd, elapsed , 30, i*10-(tadj+30));
  } 
  if(elapsed < 60)
  {
   elapsed+=80; //Going to top Green Room
   top = save(trials, su, elapsed , 80 , 6000-elapsed);
  }
  else
  {
   elapsed+=60; //Going to top Green Room
   top = save(trials, su, elapsed , 80 , 6000-elapsed);
  }  
  times[i]+=top+bottom+adj;
  if(times[i] > max)
  {
   max=times[i];
   max_condn = i;
  }
 }
 
 cout<<"\nMax Saved Were : "<<times[max_condn]<<"\n";
 fetch(trials,sorted, su);
 fetch(trials_d, sorted_d, sd);
 elapsed = top = bottom = adj = 0;
 
 cout<<"Bottom : \n";
 adj = savefirst(down[0][3].p, max_condn*10,1);
 tadj = elapsed;
 if(elapsed+30 < max_condn*10)
 {
  elapsed+=30;
  bottom = save(trials_d, sd, elapsed , 30, max_condn*10-(tadj+30),1);
 } 
  
 cout<<"\nTop :\n";
 if(elapsed < 60)
 {
  elapsed+=80;
  top = save(trials, su, elapsed , 80 , 6000-elapsed,1);
 }
 else
 {
  elapsed+=60;
  top = save(trials, su, elapsed , 80 , 6000-elapsed,1);
 }
 //Transport Session
 while(elapsed<=3000 && top)
 {
  top-=2;
  elapsed+=80; 
 }
 while(elapsed<=6000 && top)
 {
  top-=2;
  elapsed+=90;
 }
 while(elapsed<=6000 && bottom)
 {
  bottom-=2;
  elapsed+=30;
 }
 
 cout<<"\nTotal Time Taken : "<<elapsed;
 getch();
}