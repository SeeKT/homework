/*離散フーリエ変換を実行するプログラム*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 256

int main(void)
{
  FILE *f1,*f2,*f3,*fp_1,*fp_2,*fp_3,*fp_4,*fp_5,*fp_6;
  char *fname1="sinwave_4_2.txt";
  char *fname2="sinwave_5.txt";
  char *fname3="sinwave_6.txt";
  char line1[N][256];
  char line2[N][256];
  char line3[N][256];
  double f_1[N];
  double f_2[N];
  double f_3[N];
  int k,n;
  double theta;
  double Re1[N],Im1[N],Re2[N],Im2[N];
  double Re3[N],Im3[N];


  f1 = fopen(fname1,"r");
  if(f1==NULL){
    printf("%sファイルが開けません\n",fname1);
    return -1;
  }

  int cnt1=0;
  while(fgets(line1[cnt1],256,f1)!=NULL){
    sscanf(line1[cnt1],"%lf",&f_1[cnt1]);
    cnt1++;
  }
  fclose(f1);

  f2 = fopen(fname2,"r");
  if(f2==NULL){
    printf("%sファイルが開けません\n",fname2);
    return -1;
  }

  int cnt2=0;
  while(fgets(line2[cnt2],256,f2)!=NULL){
    sscanf(line2[cnt2],"%lf",&f_2[cnt2]);
    cnt2++;
  }
  fclose(f2);

  f3 = fopen(fname3,"r");
  if(f3==NULL){
    printf("%sファイルが開けません\n",fname3);
    return -1;
  }

  int cnt3=0;
  while(fgets(line3[cnt3],256,f3)!=NULL){
    sscanf(line3[cnt3],"%lf",&f_3[cnt3]);
    cnt3++;
  }
  fclose(f3);


  fp_1=fopen("fourier_sin4_re.txt","w");
  fp_2=fopen("fourier_sin4_im.txt","w");
  fp_3=fopen("fourier_sin5_re.txt","w");
  fp_4=fopen("fourier_sin5_im.txt","w");
  fp_5=fopen("fourier_sin6_re.txt","w");
  fp_6=fopen("fourier_sin6_im.txt","w");


  for(k=0;k<N;k++){
    for(n=0;n<N;n++){
      theta=-2*M_PI*k*n/N;
      Re1[k]+=f_1[n]*cos(theta);
      Im1[k]+=f_1[n]*sin(theta);
      Re2[k]+=f_2[n]*cos(theta);
      Im2[k]+=f_2[n]*sin(theta);
      Re3[k]+=f_3[n]*cos(theta);
      Im3[k]+=f_3[n]*sin(theta);
    }
    fprintf(fp_1,"%lf\n",Re1[k]);
    fprintf(fp_2,"%lf\n",Im1[k]);
    fprintf(fp_3,"%lf\n",Re2[k]);
    fprintf(fp_4,"%lf\n",Im2[k]);
    fprintf(fp_5,"%lf\n",Re3[k]);
    fprintf(fp_6,"%lf\n",Im3[k]);
  }

  fclose(fp_1);
  fclose(fp_2);
  fclose(fp_3);
  fclose(fp_4);
  fclose(fp_5);
  fclose(fp_6);

  return 0;
}
