/* ビットマップファイルを読み込み、二次元離散フーリエ変換、逆変換を用いて画像処理を行うプログラム */
#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 128
#define H 54 //54
#define M 32
// int main(void) {
 int main(int argc, char **argv){
 FILE *fp, *fo;
 unsigned char header[H];
 unsigned char img[N][N][3];
 unsigned char in[N][N];
 unsigned char in_2[N/2][N/2];
 double input[N][N];
 unsigned char out[N][N][3];
 unsigned char out_2[N/2][N/2][3];
 double H_re[N][N],H_im[N][N],X_re[N][N],X_im[N][N];
 double h_re[N][N],h_im[N][N],x_re[N][N],x_im[N][N];
 unsigned char rx_re[N][N],rx_im[N][N];
 int i,j,k,n1,n2,k1,k2;
 int height_original=N;	//元の画像の縦のサイズ
 int width_original =N;	//元の画像の横のサイズ
 int height;			//出力画像の縦のサイズ
 int width ;			//出力画像の横のサイズ
 double sq;
 double theta;
 /* ファイルから読む */
	if( argc != 2 ){
        fprintf( stderr, "Usage: ./a input.bmp \n" );
        exit(-1);
    }
    if( (fp = fopen(argv[1], "rb")) == NULL ){
        fprintf( stderr, "Cannot open %s\n", argv[1] );
        exit(-2);
    }
fread(header,1,H,fp); /* ヘッダ(54バイト)を読み込み */
fread(img,1, height_original * width_original * 3,fp); /* 残りはデータ(最下行から順に入る) */
fclose(fp);
	//入力画像をin[i][j]に格納
 	for (i=0;i<height_original;i++){//縦の長さ
 		for (j=0;j<width_original;j++){//横の長さ
 			in[i][j]  = ( img[i][j][0] + img[i][j][1] + img[i][j][2])/3;
      input[i][j]=(double)in[i][j];
      /*配列の初期化*/
      H_re[i][j]=0;
      H_im[i][j]=0;
      X_re[i][j]=0;
      X_im[i][j]=0;
      h_re[i][j]=0;
      h_im[i][j]=0;
      x_re[i][j]=0;
      x_im[i][j]=0;
 		}
 	}

  	/************************/
 	/*                      */
 	/*      画像処理        */
 	/*      ここから        */
 	/*                      */
 	/************************/
 	height=height_original;     //出力画像の縦の長さ
 	width = width_original;     //出力画像の横の長さ

  height/=2;
  width/=2;

  sq=N*N;


  for(i=0;i<height;i++){
    for(j=0;j<width;j++){
      in_2[i][j]=in[2*i][2*j];
    }
  }


/*行に対する１次元離散フーリエ変換*/
  for(k1=0;k1<N;k1++){
    for(n2=0;n2<width;n2++){
      for(n1=0;n1<height;n1++){
        theta=-2*M_PI*k1*n1/N;
        H_re[k1][n2]+=(double)input[n1][n2]*cos(theta);
        H_im[k1][n2]+=(double)input[n1][n2]*sin(theta);
      }
    }
  }
/*列に対する１次元離散フーリエ変換*/
  for(k2=0;k2<N;k2++){
    for(k1=0;k1<N;k1++){
      for(n2=0;n2<width;n2++){
        theta=-2*M_PI*k2*n2/N;
        X_re[k1][k2]+=H_re[k1][n2]*cos(theta)-H_im[k1][n2]*sin(theta);
        X_im[k1][k2]+=H_re[k1][n2]*sin(theta)+H_im[k1][n2]*cos(theta);
      }
    }
  }

  /************************/
  /*                      */
  /*      平滑化処理        */
  /*      ここから        */
  /*                      */
  /************************/
  for(i=0;i<M;i++){
    for(j=M;j<N-M;j++){
      X_re[i][j]=0;
      X_im[i][j]=0;
    }
  }
  for(i=M;i<N-M;i++){
    for(j=0;j<width;j++){
      X_re[i][j]=0;
      X_im[i][j]=0;
    }
  }
  for(i=N-M;i<N;i++){
    for(j=M;j<N-M;j++){
      X_re[i][j]=0;
      X_im[i][j]=0;
    }
  }
  /************************/
 	/*                      */
 	/* 	 平滑化処理ここまで 	*/
 	/*                      */
 	/************************/


/*行に対する１次元離散フーリエ逆変換*/
  for(n1=0;n1<height;n1++){
    for(k2=0;k2<N;k2++){
      for(k1=0;k1<N;k1++){
        theta=2*M_PI*k1*n1/height;
        h_re[n1][k2]+=X_re[k1][k2]*cos(theta)-X_im[k1][k2]*sin(theta);
        h_im[n1][k2]+=X_re[k1][k2]*sin(theta)+X_im[k1][k2]*cos(theta);
      }
    }
  }
/*列に対する１次元離散フーリエ変換*/
  for(n2=0;n2<width;n2++){
    for(n1=0;n1<height;n1++){
      for(k2=0;k2<N;k2++){
        theta=2*M_PI*k2*n2/width;
        x_re[n1][n2]+=(h_re[n1][k2]*cos(theta)-h_im[n1][k2]*sin(theta))/sq;
        x_im[n1][n2]+=(h_re[n1][k2]*sin(theta)+h_im[n1][k2]*cos(theta))/sq;
      }
    }
  }


  for (i=0;i<height;i++){
 		for (j=0;j<width;j++){
 			//***********************
 			//出力画像の作成(画像処理)
 			//***********************

      rx_im[i][j]=x_im[i][j];
      if(x_re[i][j]<0){
        rx_re[i][j]=0;
      }
      else if(rx_re[i][j]>255){
        rx_re[i][j]=255;
      }
      else{
        rx_re[i][j]=x_re[i][j];
      }
 			out[i][j][0] =  rx_re[i][j];		//出力

 			//***********************
 		}
 	}


  for(i=0;i<height;i++){
    for(j=0;j<width;j++){
      out_2[i][j][0]=in_2[i][j];
    }
  }


 	/*******************************************/
 	/* 出力のRGB成分を同じ値で記録(グレイ画像) */
 	/*******************************************/



#if 0
for (i=0;i<height;i++){//縦の長さ
  for (j=0;j<width;j++){//横の長さ
    out[i][j][1] = out[i][j][2] = out[i][j][0];
  }
}
  #endif

  for (i=0;i<height;i++){//縦の長さ
    for (j=0;j<width;j++){//横の長さ
      out_2[i][j][1] = out_2[i][j][2] = out_2[i][j][0];
    }
  }
	/************************/
 	/*                      */
 	/* 	 画像処理ここまで 	*/
 	/*                      */
 	/************************/
 	 /* 書き込みファイルを開く */
	fo=fopen("output_CZP_Reduction_2.bmp","wb");
  	char *BM;
  BM="BM";
  unsigned int tmp;
  unsigned int tmp2;
  unsigned int dsize;
  //ファイルヘッダ書き込み
  fwrite(BM, 1, sizeof(unsigned short),fo);	//'BM'ビットマップ形式
  dsize=H+height*width*3;
  fwrite(&dsize,1,sizeof(unsigned int),fo);	//ファイルサイズ
  tmp=0;
  fwrite(&tmp,1,sizeof(unsigned short),fo);	//予約領域(常に0)
  fwrite(&tmp,1,sizeof(unsigned short),fo);	//予約領域(常に0)
  dsize=H;
  fwrite(&dsize,1,sizeof(unsigned int),fo);	//ヘッダバイト数(54)
  //情報ヘッダ書き込み
  dsize=40;
  fwrite(&dsize,1,sizeof(unsigned int),fo);	//情報ヘッダバイト数(40)
  tmp2=width;
  fwrite(&tmp2,1,sizeof(unsigned int),fo);	//画像の幅(ピクセル数 4の倍数バイトでないとダメ)
  tmp2=height;
  fwrite(&tmp2,1,sizeof(unsigned int),fo);	//画像の高さ(ピクセル数)
  tmp=1;
  fwrite(&tmp,1,sizeof(unsigned short),fo);	//プレーン数(常に1)
  tmp=24;
  fwrite(&tmp,1,sizeof(unsigned short),fo);	//色ビット数(1, 4, 8, 16, 24, 32)
  dsize=0;
  fwrite(&dsize,1,sizeof(unsigned int),fo); 	//圧縮形式(0, 1, 2, 3)
  dsize=width*height*3;
  fwrite(&dsize,1,sizeof(unsigned int),fo); 	//画像データサイズ
  tmp2=0;
  fwrite(&tmp2,1,sizeof(unsigned int),fo);	//水平解像度(0でも良い)
  tmp2=0;
  fwrite(&tmp2,1,sizeof(unsigned int),fo);	//垂直解像度(0でもよい)
  dsize=0;
  fwrite(&dsize,1,sizeof(unsigned int),fo);	//格納パレット数(0で良い)
  dsize=0;
  fwrite(&dsize,1,sizeof(unsigned int),fo);	//重要色数(0で良い)
	//以降はデータの書き込み．B G R の順で，左下から右上に書き込まれる．
	//fwrite(out,1, height*width*3,fo);



  #if 0
  for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			fwrite(&out[i][j][1],1,sizeof(unsigned char),fo);
			fwrite(&out[i][j][1],1,sizeof(unsigned char),fo);
			fwrite(&out[i][j][1],1,sizeof(unsigned char),fo);
		}
	}


  #endif

  for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			fwrite(&out_2[i][j][1],1,sizeof(unsigned char),fo);
			fwrite(&out_2[i][j][1],1,sizeof(unsigned char),fo);
			fwrite(&out_2[i][j][1],1,sizeof(unsigned char),fo);
		}
	}




	fclose(fo);

 	return 0;
 }
