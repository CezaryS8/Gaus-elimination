#include "gauss.h"
#include <math.h>
#include <stdio.h>
int eliminate(Matrix *mat, Matrix *b)
{
        double **A=mat->data;
        double **B=b->data;
        int w=mat->r;
        int k=mat->c;
        for(int i=0;i<k-1;i++)
        {
		for(int j=i+1;j<w;j++)
                {
                        if(A[i][i]!=0)
                        {
                                double q=A[j][i]/A[i][i];
                                for(int z=0;z<k;z++) A[j][z]-=q*A[i][z];
                                B[j][0]-=q*B[i][0];
                        }
                        else return 1;
                }

        }
        return 0;
}

