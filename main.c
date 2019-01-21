#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Adaboost.h"


void main()
{
	//f1,adaboost
    float a1, b1;
    struct test{
        float st;
        float dst;
    }testData[14]={{5,0.5},\
               {5.5,0.9},\
               {3,1.1},\
               {2.5,1.4},\
               {5.5,1.2},\
               {5.6,1.6},\
               {6.1,1.1},\
               {7.5,1.5},\
               {5.7,1.6},\
               {7,2},\
               {6,0.9},\
               {8,1.15},\
                 {25,4},\
                 {8,3}};
    
    struct test *p;
    p = testData;
    float st;
    float dst;
    int i;
 	int result ;
    for(i=0;i<14;i++)
    {
        st=(p+i)->st;
        dst=(p+i)->dst;

        result =  f1Adaboost(st, dst);
	    printf("result is %d\n\n", result); 
    }
   

    for(count=0;count<8;count++)
    {
        for(iIters=0;iIters<K; iIters++)
        {
            distence[iIters] = sqrt(pow((testdata+count)->st - newCore[iIters].st,2)+\
                            pow((testdata+count)->dst-newCore[iIters].dst,2));
        }
        if(distence[0]>distence[1])
        {
            printf("test result: N \n");
        }
        else
        {
            printf("test result: Y \n");
        }
    }  
 
}
