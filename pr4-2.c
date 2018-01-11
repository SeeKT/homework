/*逆フーリエ変換を実行するプログラム*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 256
#define M 64

int main(void)
{
  FILE *f1,*f2,*f3,*f4,*f5,*f6,*fp_1,*fp_2,*fp_3,*fp_4;
  char *fname1="fourier1_1.txt";
  char *fname2="fourier1_2.txt";
  char *fname3="fourier2_1.txt";
  char *fname4="fourier2_2.txt";
  char *fname5="fourier_lena_re.txt";
  char *fname6="fourier_lena_im.txt";
  double f1_1[N];
  double f1_2[N];
  double f2_1[N];
  double f2_2[N];
  double f3_1[N];
  double f3_2[N];
  int k,n;
  double theta;
	double Re1[N],Im1[N],Re2[N],Im2[N],Re3[N],Im3[N];
  char line1[N][256];
  char line2[N][256];
  char line3[N][256];
  char line4[N][256];
  char line5[N][256];
  char line6[N][256];

  f1 = fopen(fname1,"r");
  if(f1==NULL){
    printf("%sファイルが開けません\n",fname1);
    return -1;
  }

  int cnt1=0;
  while(fgets(line1[cnt1],256,f1)!=NULL){
    sscanf(line1[cnt1],"%lf",&f1_1[cnt1]);
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
    sscanf(line2[cnt2],"%lf",&f1_2[cnt2]);
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
    sscanf(line3[cnt3],"%lf",&f2_1[cnt3]);
    cnt3++;
  }
  fclose(f3);

  f4 = fopen(fname4,"r");
  if(f4==NULL){
    printf("%sファイルが開けません\n",fname4);
    return -1;
  }

  int cnt4=0;
  while(fgets(line4[cnt4],256,f4)!=NULL){
    sscanf(line4[cnt4],"%lf",&f2_2[cnt4]);
    cnt4++;
  }
  fclose(f4);

  f5 = fopen(fname5,"r");
  if(f5==NULL){
    printf("%sファイルが開けません\n",fname5);
    return -1;
  }

  int cnt5=0;
  while(fgets(line5[cnt5],256,f5)!=NULL){
    sscanf(line5[cnt5],"%lf",&f3_1[cnt5]);
    cnt5++;
  }
  fclose(f5);

  f6 = fopen(fname6,"r");
  if(f6==NULL){
    printf("%sファイルが開けません\n",fname6);
    return -1;
  }

  int cnt6=0;
  while(fgets(line6[cnt6],256,f6)!=NULL){
    sscanf(line6[cnt6],"%lf",&f3_2[cnt6]);
    cnt6++;
  }
  fclose(f6);

  for(k=M;k<N-M;k++){
    f3_1[k]=0;
    f3_2[k]=0;
  }

  fp_1=fopen("rfourier1.txt","w");
  fp_2=fopen("rfourier2.txt","w");
  fp_3=fopen("rfourier_lena_re_64.txt","w");
  fp_4=fopen("rfourier_lena_im_64.txt","w");

  for(n=0;n<N;n++){
    for(k=0;k<N;k++){
      theta=2*M_PI*k*n/N;
			Re1[n]+=f1_1[k]*cos(theta)-f1_2[k]*sin(theta);
      Im1[n]+=f1_1[k]*sin(theta)+f1_2[k]*cos(theta);
      Re2[n]+=f2_1[k]*cos(theta)-f2_2[k]*sin(theta);
      Im2[n]+=f2_1[k]*sin(theta)+f2_2[k]*cos(theta);
      Re3[n]+=f3_1[k]*cos(theta)-f3_2[k]*sin(theta);
      Im3[n]+=f3_1[k]*sin(theta)+f3_2[k]*cos(theta);
    }
		Re1[n]/=N;
		Im1[n]/=N;
		Re2[n]/=N;
		Im2[n]/=N;
    Re3[n]/=N;
    Im3[n]/=N;
		fprintf(fp_1,"%f %f\n",Re1[n],Im1[n]);
		fprintf(fp_2,"%f %f\n",Re2[n],Im2[n]);
    fprintf(fp_3,"%f\n",Re3[n]);
    fprintf(fp_4,"%f\n",Im3[n]);
  }

  fclose(fp_1);
  fclose(fp_2);
  fclose(fp_3);

  return 0;
}
