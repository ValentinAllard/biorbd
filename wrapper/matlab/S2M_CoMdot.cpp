

void S2M_CoMdot( int nlhs, mxArray *plhs[],
				int nrhs, const mxArray*prhs[] ){
	// Verifier les arguments d'entrée
	checkNombreInputParametres(nrhs, 4, 4, "4 arguments are required where the 2nd is the handler on the model, 3rd is the Q and 4th is QDot");
	
	// Recevoir le model
	s2mMusculoSkeletalModel * model = convertMat2Ptr<s2mMusculoSkeletalModel>(prhs[1]);
    unsigned int nQ = model->nbQ(); /* Get the number of DoF */
    unsigned int nQdot = model->nbQdot(); /* Get the number of DoF */

	// Recevoir Q
    std::vector<s2mGenCoord> Q = getParameterQ(prhs, 2, nQ);
	// Recevoir Qdot
    std::vector<s2mGenCoord> QDot = getParameterQdot(prhs, 3, nQdot);
		
    // S'assurer que Q, Qdot et Qddot (et Forces s'il y a lieu) sont de la bonne dimension
    unsigned int nFrame(Q.size());
    if (QDot.size() != nFrame)
        mexErrMsgIdAndTxt( "MATLAB:dim:WrongDimension", "QDot must have the same number of frames than Q");

    /* Create a matrix for the return argument */
    mwSize dims[3];
    dims[0] = 3;
    dims[1] = 1;
    dims[2] = Q.size();
    plhs[0] = mxCreateNumericArray(3, dims, mxDOUBLE_CLASS, mxREAL);
    double *com_dot = mxGetPr(plhs[0]);

    // Trouver la vitesse du CoM
    for (unsigned int i=0; i<Q.size(); ++i){
        RBDM::Vector3d COMDot = model->CoMdot(*(Q.begin()+i),*(QDot.begin()+i));
        for (unsigned int j=0; j<3; ++j)
            com_dot[3*i+j] = COMDot(j);
    }

	return;
}
