#if !defined( __STDIO_H)
#include <stdio.h>
#endif // __STDIO_H

//#if !defined( __STRING_H)
#include <string.h>
//#endif // __STRING_H

#if !defined( __STDLIB_H)
#include <stdlib.h>
#endif // __STDLIB_H

#include "hypfile.h"


void hypdump(struct hyp_file * hyp, FILE *fo) {
int irec;
struct hyp_record *r;

  for (irec=0;irec<hyp->n_rec;irec++) {
    r=&hyp->rec[irec];

    fprintf(fo,
   "%-5s %s 99 %02d %02d %02d %02d %02d %02d %03d 000 %1d %12.6e  0 %12.6e %12.6e\n",
       r->sta,
       r->phase,
       r->year, 
       r->month, 
       r->day, 
       r->hour, 
       r->minute, 
       r->isec, 
       r->msec, 
 (int) r->wt, 
       r->amp_d, 
       r->amp_v,
       r->period);
       }
}

void hyrdump(struct hyp_file * hyp, FILE *fo) {
int irec;
struct hyp_record *r;

  for (irec=0;irec<hyp->n_rec;irec++) {
    r=&hyp->rec[irec];

    fprintf(fo,
   "%-5s %s 99 %02d %02d %02d %02d %02d %02d %03d 000 %4.0f %12.6e  0 %12.6e %12.6e\n",
       r->sta,
       r->phase,
       r->year, 
       r->month, 
       r->day, 
       r->hour, 
       r->minute, 
       r->isec, 
       r->msec, 
       r->wt, 
       r->amp_d, 
       r->amp_v,
       r->period);
       }
}


int hypline (struct hyp_record *r, char * line) {

  char sta[6];
  char phase[4];
  int ichan;
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int isec;
  int msec;
  int micros;
  float wt;
  float amp_d;
  int pol;
  float amp_v;
  float period;

  sscanf(line," %[^ ] %[^ ] %d %d %d %d %d %d %d %d %d %f %f %d %f %f\n",
       sta, phase,
       &ichan,
       &year, &month, &day,
       &hour, &minute, &isec,
       &msec, &micros,
       &wt,
       &amp_d, &pol, &amp_v, &period);

  strcpy(r->sta,sta);
  strcpy(r->phase,phase);
  r->year=year; 
  r->month=month;
  r->day=day; 
  r->hour=hour; 
  r->minute=minute; 
  r->isec=isec; 
  r->msec=msec; 
  r->wt=wt; 
  r->amp_d=amp_d; 
  r->amp_v=amp_v;
  r->period=period;

return(0);
}

int hypload (struct hyp_file *hyp, FILE *fi) {

char line[90];
int irec = 0;

  irec = 0;
  while (fgets (line, 85, fi) != NULL) {
//     fprintf(stdout,"%s", line);
     hypline(&hyp->rec[irec],line);
     irec++;
  }
  hyp->n_rec=irec;
return(0);
} 
