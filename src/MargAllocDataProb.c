/**********************************	This returns the probability of the allelic type given it is from a 	particular source.  For use with the generic function MargAllocZ()**********************************/#include <stdlib.h>#include <stdio.h>#include <math.h>#include "ECA_MemAlloc.h"#include "MCTypesEtc.h"#include "MathStatRand.h"#include "ranlib.h"#include "GFMCMC.h"#include "GFMCMC_DrawingUtilities.h"#include "NewHybrids.h"#include "MAZ4NewHybs.h"#include "ECA_MemAlloc.h" double MargAllocDataProb( MAZ_var_struct *Vars,int t,int j){	int l = t/2;  // locus subscript	int c = t%2;  // gene copy subscript	int i = Vars->Indiv;  // the individual subscript	hyb_chain *C = Vars->C;	int a = j;  // this will be the source		double TheProb;			if(YnotMissing(C,i,l) ) {  // if it is not missing the probability is the frequency in pop "j", which							 // we have changed to "a" to be like the rest of the program		TheProb = C->Lat->Theta[a][l][C->Lat->Ind[i]->Y[l][c]->v ]->v;	}	else {  // if data are missing then the prob is unity.  		TheProb = 1.0;	}		return(TheProb);	}    // allocates to the space that MargAllocZs needs to do its computations// and also for the Idx array that we must pass to MargAllocZs, and // for the output parameter as well.  These are all global vars.void AllocateToMargAllocStuff(int NumZs){	int i,j;		gBaumProbs = (double ***)ECA_CALLOC((size_t)NumZs,sizeof(double **));	for(i=0;i<NumZs;i++)  {		gBaumProbs[i] = (double **)ECA_CALLOC((size_t)(i+2),sizeof(double *));		for(j=0;j<i+2;j++)  {			gBaumProbs[i][j] = (double *)ECA_CALLOC(2,sizeof(double));		}	}		gBaumIdx = (int *)ECA_CALLOC((size_t)(NumZs), sizeof(int));	for(i=0; i<NumZs; i++)  {		gBaumIdx[i] = i;	}		gBaumZOutputParm = (int *)ECA_CALLOC((size_t)(NumZs), sizeof(int));} // this is called after MargAllocZ to put the z's from the Baum algorithm// back into the w field of the i-th individualvoid InsertZsToIndivs(int *Zs, hyb_chain *C, int i){	int t,l,c;		for(t=0; t<C->Dat->L*2; t++)  {		l = t/2;		c = t%2;				C->Lat->Ind[i]->W[l][c]->v = Zs[t];	}}      