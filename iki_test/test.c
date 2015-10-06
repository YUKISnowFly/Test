#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int k=0,i=0,j=0; //カウント

//セグメント幅　30*30
//レーダ　-300~300

void extraction(float inp[],int n,float seg[][2000]){
	//y座標の平均値を求める//
	float ave=0;
	
	for(k=1;k<=n;k++){
		//printf("%f ",inp[k-1]);
		if(k%3==1) ave=ave+inp[k];
		//if(k%3==0)printf("\n");
	}
	
	ave=ave/(n/3);
	printf("ave=%f\n",ave);
	
	
}







int main(void){
	clock_t start,end;
	FILE *fp;
	int n=0;
	float out[3];
	char *fname = "Result.csv";
	float *inp;
	int segNo=0,sx=-300,sz=300,hit=0;
	float seg[400][2000];

	start=clock();
	//初期化//
	for(k=0;k<400;k++){
		for(i=0;i<2000;i++){
			seg[k][i]=999;
		}
	}	
	
	//ファイル読み込み//
	fp = fopen(fname,"r");
	if(fp == NULL) {
		printf("error\n");
		return -1;
	}	
	
	
	while((fscanf(fp,"%f,%f,%f",&out[0],&out[1],
					&out[2])) != EOF){
		n++;
		//printf("%f,%f,%f\n",out[0],out[1],out[2]);
	}
	
	printf("%d\n",n*3);
	n=n*3;
	inp = (float *)malloc(sizeof(float)*n);
	if(inp == NULL){
		printf("error\n");
		return -1;
	}

	fseek(fp, 0L, SEEK_SET);	//fpポインタをファイルの先頭に
	k=0;
	while((fscanf(fp,"%f,%f,%f",&inp[k],&inp[k+1],
					&inp[k+2])) != EOF){
	//x,y,z(k,k+1,k+2)		
		//printf("%f,%f,%f\n",inp[k],inp[k+1],inp[k+2]);

	sx=-300;
	sz=300;
	hit=0;
	segNo=0;
	

//printf("inp[x]=%f,inp[y]=%f,inp[z]=%f\n",inp[k],inp[k+1],inp[k+2]);
		for(sz=300;sz>=-270;sz=sz-30){
		for(sx=-300;sx<=270;sx=sx+30){
			//printf("segNo=%d,sx=%d,sz=%d\n",segNo,sx,sz);
			if(inp[k]>=sx && inp[k]<sx+30 
				&& inp[k+2]<=sz && inp[k+2]>sz-30){
			while(1){
				if(seg[segNo][hit]==999){
					seg[segNo][hit]=inp[k+1];
	//printf("セグメント%d hit%d y=%f\n",segNo,hit,seg[segNo][hit]);
			
					hit=0;
					break;
				}
				hit++;
			}
			
			}
			segNo++;
			
		}
		}			

		

		k=k+3;

	
	}	
	fclose(fp);

	//ファイル読み込み終了//
	
	extraction(inp,n,seg);
	end=clock();
	printf("処理時間%f[s]\n",(double)(end-start)/CLOCKS_PER_SEC);
	return 0;	
}
