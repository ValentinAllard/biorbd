void S2M_nRoot( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray*prhs[] ){
	
	// Verifier les arguments d'entrée
	checkNombreInputParametres(nrhs, 2, 2, "2 arguments are required where the 2nd is the handler on the model");
	s2mMusculoSkeletalModel * model = convertMat2Ptr<s2mMusculoSkeletalModel>(prhs[1]);
					  
	/* Create a matrix for the return argument */ 
	plhs[0] = mxCreateDoubleMatrix( 1, 1, mxREAL); 
	double *nRoot = mxGetPr(plhs[0]);
        
	// Get nombre de dof sur le segment racine
	*nRoot = model->nbRoot();
	
	return;
}