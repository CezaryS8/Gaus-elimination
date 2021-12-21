#include "backsubst.h"
int  backsubst(Matrix *x, Matrix *mat, Matrix *b)
{
        double **A=mat->data;
        double **B=b->data;
        double **ans=x->data;
        int w=mat->r;
        int k=mat->c;
        int pom=0, i, j;

        if(w != b->r || b->c != 1 || w != k)
                return 2;
        for(i=w-1;i>=0;i--)
        {
                double sum=0;
                int pom1=0;
                for(j=k-1;j>k-1-pom;j--)
                {
                        sum+=A[i][j]*ans[pom1][0];
                        pom1++;
                }
                if(A[i][j]==0) return 1;
                ans[pom][0]=(B[i][0]-sum)/(A[i][j]);
                pom++;
        }
      	for (int low = 0, high = w - 1; low < high; low++, high--)
      	{
        	double temp = x->data[low][0];
       		x->data[low][0] = x->data[high][0];
        	x->data[high][0] = temp;
      	}
        return 0;
}


