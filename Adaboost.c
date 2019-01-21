#include <stdio.h>
#include <math.h>

#define DATANUM 10
#define ITERATION 3

int f1Adaboost(float st, float dst)
{
	//D(w1,w2,.....wn)
    float fInitialDataWeigths[DATANUM]={0};
	float fOldDataWeigths[DATANUM]={0};
	float fNewDataWeigths[DATANUM]={0};
	float fDataWeigths1[DATANUM]={0};
	float fDataWeigths2[DATANUM]={0};
    
	//data  err/right  number 
	int ResultH1[DATANUM]={0};
	int ResultH2[DATANUM]={0};  
	int ErrH1[DATANUM]={0};
	int ErrH2[DATANUM]={0};
	int RightH1[DATANUM]={0};
	int RightH2[DATANUM]={0};
	int iErrNum1=0;
    int iErrNum2=0;
	int iRightNum1=0;
	int iRightNum2=0;
	
	int resultH1=0;
    int resultH2=0;
    
    //the calssifer's err
	float fErr1=0;
    float fErr2=0;
    float fMinErr=0; 
	int iMinErrNum=0;
	
	//classifer's weights
    float a1=0;
    float a2=0;	
	float ax=0;

    int i,j;
    int loop;
    
	//output    
    int ResultFinalL1=0;
    int ResultFinalL2=0;
    int ResultFinalSum=0;
		
	//trainning data structure
	struct TRAINING{
        float ST;
        float DST;
        int SLEEP;
    };
	struct TRAINING *p1,*p2;
	//data set
	//struct TRAINING TrainingData[36]={{1,0.2,1},{3,0.5,1},{5,0.6,1},\
                                      {2,0.8,1},{5,0.4,1},{4,0.9,1},\
                                     {1.3,1.2,1},{4,1.48,1},{5,1.3,1},\
                                      {1.8,1.3,1},{4.6,1.22,1},{5.8,1.33,1},\
                                     {1.8,1.6,1},{4,2,1},{5,4,1},\
                                      {3,2,1},{5,4,1},{4,1.8,1},\
                                     {6,0.2,1},{7,0.5,1},{8,0.9,1},\
                                      {7,0.8,1},{8,0.5,1},{9,0.7,1},\
                                     {6,1.2,-1},{8,1.3,-1},{9,1.4,-1},\
                                     {6,1.1,-1},{7,1.4,-1},{8,1.45,-1},\
                                     {6.5,1.6,-1},{8,3,-1},{10,4,-1},\
                                     {6.2,2,-1},{7,2,-1},{8,2.5,-1}};
									 
	struct TRAINING TrainingData[10]={{5,0.2,1},{3,1.6,1},{5,0.6,1},{7,0.8,1},\
                                     {6.2,0.6,1},{7,2,-1},{8,2.5,-1},\
										 {6.2,1.1,-1},{7.5,1.6,-1},{7,1.1,-1}};
	p1= TrainingData;
	p2= TrainingData;
	
	//sign 
	int sign(float fx)
	{
		int result;
		if(fx>=0)
		{
			result =1;
		}
		else
			result =-1;
		return  result;
	}
	
	//weak classifier1
	int H1(float x, float TH )
	{
		int result;
		if(x>TH)
			result =-1;
		else
			result = 1;
        return result;
	}
	
	//weak classifier2
	int H2(float x, float TH )
	{
		int result;
		if(x>TH)
			result =-1;
		else
			result = 1;
        return result;
	}
	
	
	//comp  clasifier output and initial data,  right or no
	int CompClassierDiff(int iInitialDataVal, int iClassierVal)
	{
		int result;
		if (iInitialDataVal!= iClassierVal)
		{
			result = 1;
		}
		else 
			result =0;
		
		return result;
	}
	
	//count number of err/right
	int CountErrRightNum(int Data[],int Num)
	{
		int CountNum=0;
		for(i=0;i<DATANUM;i++)
		{
			if(Data[i] !=0)
			{
				CountNum++;
			}
		}
		return CountNum;
	}
	
	//comp the minimum err value of classifers
	int CompMinErrValue(float err1, float err2)
	{
		int min;
		if(err1<=err2)
		{
			min =1;
		}
		else
		{
			min =2;
		}
        return min;
	}
	
	//two weak classifer' results
	for(i=0;i<DATANUM;i++)
	{
		ResultH1[i]= H1((p1+i)->ST, 6);
		ResultH2[i]= H2((p1+i)->DST, 1);
	}
	
	//find the number of right and err  to classifer's result
	for(i=0;i<DATANUM;i++)
	{
		//classifier1
		resultH1 =CompClassierDiff((p1+i)->SLEEP, ResultH1[i]);	
		if(resultH1==0)
		{
			RightH1[iRightNum1]=(i+1);
			iRightNum1++;
		}
		else if(1==resultH1)
        {
			ErrH1[iErrNum1]=(i+1);
			iErrNum1++;
		}
		//classifier2
		resultH2 =CompClassierDiff((p1+i)->SLEEP, ResultH2[i]);	
		if(resultH2==0)
		{
			RightH2[iRightNum2]=(i+1);
			iRightNum2++;
		}
		else if(1==resultH2)
		{
			ErrH2[iErrNum2]=(i+1);
			iErrNum2++;
		}
	}
	

	//initial  weights
	for(i=0;i<DATANUM;i++)
	{
		fInitialDataWeigths[i]=(float)1/DATANUM;
		fOldDataWeigths[i]= fInitialDataWeigths[i];
        fNewDataWeigths[i]= fInitialDataWeigths[i];
	}
		
	//Weights update
	void WeightsUpdate(float fNewWcs[],float fOldWcs[], float fErr,int ErrHx[],int ErrNumX, int DataNum)
	{
		int cnt1=0;
        int cnt2=0;
        int temp=0; 
        for(cnt1=0;cnt1<DataNum;cnt1++)
		{		
            fNewWcs[cnt1]=fOldWcs[cnt1]/2/(1-fErr);
        }  
        for(cnt2=0;cnt2<ErrNumX;cnt2++)
        {
            temp = ErrHx[cnt2];
            temp--;
            fNewWcs[temp]=fOldWcs[temp]/2/fErr;
        }	
	}

	//calc Claaifer's err
	float CalcNewClassifersErr(float fOldDataWeigths[],int ErrHx[], int ErrNumX)
	{
		float err=0;
		int ErrNum=0;
		int cnt=0;
		for(cnt=0;cnt<ErrNumX;cnt++)
		{
			ErrNum=ErrHx[cnt];
			ErrNum--;
			err+=fOldDataWeigths[ErrNum];
		}
		return err;
	}
	
	iErrNum1= CountErrRightNum(ErrH1,DATANUM);
    iErrNum2= CountErrRightNum(ErrH2,DATANUM);	
	
	//first iteration
    loop =ITERATION;	
	while(loop--)
	{
		//clac the err  of  H1/H2/H3
		fErr1 = CalcNewClassifersErr(fOldDataWeigths,ErrH1,iErrNum1);
		fErr2 = CalcNewClassifersErr(fOldDataWeigths,ErrH2,iErrNum2);
		//find the minimum number of  clasifiers
		iMinErrNum = CompMinErrValue(fErr1,fErr2);
		// wights update
		switch(iMinErrNum)
		{
			case 1:	
				ax= 0.5*log((1-fErr1)/fErr1);
				WeightsUpdate(fNewDataWeigths,fOldDataWeigths,fErr1,ErrH1,iErrNum1,DATANUM);
				break;
			case 2:
				ax= 0.5*log((1-fErr2)/fErr2);
				WeightsUpdate(fNewDataWeigths,fOldDataWeigths,fErr2,ErrH2,iErrNum2,DATANUM);
				break;
		
			default:
				break;
		}	

        if(loop == 1)
        {
            a1=ax;
            switch(iMinErrNum)
            {
                case 1:
                    ResultFinalL1=H1(st,6);
                break;
                case 2:
                    ResultFinalL1=H2(dst,1);
                break;
                
                default:
                break;
            }
            
        }
        else if(loop ==0)
        {
            a2=ax;
            switch(iMinErrNum)
            {
                case 1:
                    ResultFinalL2=H1(st,6);
                break;
                case 2:
                    ResultFinalL2=H2(dst,1);
                break;
                default:
                break;
            }
        }
        
		for(i=0;i<DATANUM;i++)
		{
			fOldDataWeigths[i]=fNewDataWeigths[i];
//			printf("fOldDataWeigths[%d]=%f\n",i, fOldDataWeigths[i]);	
		}
	}

	ResultFinalSum = sign(a1*ResultFinalL1+a2*ResultFinalL2);
//	printf("ResultSum= %d", ResultFinalSum);
	return ResultFinalSum;	
}
