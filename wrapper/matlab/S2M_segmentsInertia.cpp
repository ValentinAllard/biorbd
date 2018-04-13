

void S2M_segmentsInertia( int nlhs, mxArray *plhs[],
				int nrhs, const mxArray*prhs[] ){
	// Verifier les arguments d'entrée
	checkNombreInputParametres(nrhs, 3, 3, "3 arguments are required where the 2nd is the handler on the model and 3rd is the Q");
	
	// Recevoir le model
	s2mMusculoSkeletalModel * model = convertMat2Ptr<s2mMusculoSkeletalModel>(prhs[1]);
    unsigned int nQ = model->nbQ(); /* Get the number of DoF */ /**** ATTENTION NDDL A ÉTÉ REMPLACÉ PAR NQ, SEGFAULT? ***/

	// Recevoir Q
    s2mGenCoord Q = *getParameterQ(prhs, 2, nQ).begin();
		
	// Update sur la cinématique (placer les segments)
	RigidBodyDynamics::UpdateKinematicsCustom(*model, &Q, NULL, NULL);

	/* Create a matrix for the return argument */
    const mwSize dims[3]={6,6, (mwSize)(nQ+1)};//model->nbBone()};
	plhs[0] = mxCreateNumericArray(3, dims, mxDOUBLE_CLASS, mxREAL);
	double *ia = mxGetPr(plhs[0]);

	// Remplir l'output
	unsigned int cmp = 0;
	for (std::vector<RigidBodyDynamics::Math::SpatialMatrix>::iterator ia_it = model->IA.begin(); ia_it != model->IA.end(); ++ia_it){
		for (unsigned int i = 0; i<36; ++i){
			ia[i+36*cmp] = (*ia_it)(i);
		}
		++cmp;
	}

	return;
}

void S2M_segmentsInertiaLocal( int nlhs, mxArray *plhs[],
                int nrhs, const mxArray*prhs[] ){
    // Verifier les arguments d'entree
    checkNombreInputParametres(nrhs, 2, 3, "2 arguments are required (+1 optional) where the 2nd is the handler on the model and optional third is the segment index");

    // Recevoir le model
    s2mMusculoSkeletalModel * model = convertMat2Ptr<s2mMusculoSkeletalModel>(prhs[1]);
    unsigned int nBones = model->nbBone(); /* Get the number of DoF */



    unsigned int idx;
    if (nrhs>2){
        idx = getInteger(prhs, 2, "index");
        if (idx<1){
            std::ostringstream msg;
            msg << "Segment index must be 1 or higher.";
            mexErrMsgIdAndTxt( "MATLAB:findnz:invalidInputType",msg.str().c_str());
        }
        else if  (idx>nBones){
            std::ostringstream msg;
            msg << "Segment index must not be higher than number of segment.";
            mexErrMsgIdAndTxt( "MATLAB:findnz:invalidInputType",msg.str().c_str());
        }

        /* Create a matrix for the return argument */
        const mwSize dims[2]={3,3};
        plhs[0] = mxCreateNumericArray(2, dims, mxDOUBLE_CLASS, mxREAL);
        double *ia = mxGetPr(plhs[0]);

        // Remplir l'output
        Eigen::Matrix3d Im =  model->bone(idx-1).caract().inertia(); // Mettre les masses dans la variable de sortie
        unsigned int cmp(0);
        for (unsigned int i = 0; i<3; ++i)
            for (unsigned int j = 0; j<3; ++j){
                ia[cmp] = Im(j,i);
                ++cmp;
            }
    }
    else{
        /* Create a matrix for the return argument */
        const mwSize dims[3]={3,3, (mwSize)(nBones)};
        plhs[0] = mxCreateNumericArray(3, dims, mxDOUBLE_CLASS, mxREAL);
        double *ia = mxGetPr(plhs[0]);

        // Remplir l'output
        unsigned int cmp (0);
        for (unsigned int idx=0; idx<nBones; ++idx){
            Eigen::Matrix3d Im =  model->bone(idx).caract().inertia(); // Mettre les masses dans la variable de sortie
            unsigned int cmp2(0);
            for (unsigned int i = 0; i<3; ++i)
                for (unsigned int j = 0; j<3; ++j){
                    ia[cmp2+9*cmp] = Im(j, i);
                    ++cmp2;
                }
            ++cmp;
        }


    }


    return;
}




