

struct hyp_record
  {
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
//      int micros;
      float wt;
      float amp_d;
//      int pol;
      float amp_v;
      float period;
  };

struct hyp_file
  {
              int n_rec;
              struct hyp_record rec[80];
  };


void hypdump(struct hyp_file *hyp, FILE *fo);
void hyrdump(struct hyp_file *hyp, FILE *fo);
int hypload (struct hyp_file *hyp, FILE *fi);
int hypline (struct hyp_record *r, char * line);

