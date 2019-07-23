#ifndef S2MSTATICOPTIMIZATIONIPOPTLINEARIZED_H
#define S2MSTATICOPTIMIZATIONIPOPTLINEARIZED_H

#include <IpIpoptApplication.hpp>
#include "IpTNLP.hpp"
#include "biorbdConfig.h"
#include "s2mGenCoord.h"
#include "s2mMusculoSkeletalModel.h"
#include "s2mMuscles.h"
#include "s2mVector.h"
#include "s2mStaticOptimizationIpopt.h"

#include <Eigen/Dense>


    
class BIORBD_API s2mStaticOptimizationIpoptLinearized : public s2mStaticOptimizationIpopt
{
    public:
        s2mStaticOptimizationIpoptLinearized(
                s2mMusculoSkeletalModel &model,
                const s2mGenCoord           &Q,
                const s2mGenCoord           &Qdot,
                const s2mTau                &tauTarget,
                const s2mVector             &activationInit,
                bool                        useResidual = true,
                unsigned int                p = 2,
                int                         verbose = 0,
                double                eps = 1e-15
        );

        virtual ~s2mStaticOptimizationIpoptLinearized();

        /** Method to return the constraint residuals */
        virtual bool eval_g(
           Ipopt::Index         n,
           const Ipopt::Number* x,
           bool          new_x,
           Ipopt::Index         m,
           Ipopt::Number*       g
           );

        /** Method to return:
         *   1) The structure of the jacobian (if "values" is NULL)
         *   2) The values of the jacobian (if "values" is not NULL)
         */
        virtual bool eval_jac_g(
           Ipopt::Index         n,
           const Ipopt::Number* x,
           bool                 new_x,
           Ipopt::Index         m,
           Ipopt::Index         nele_jac,
           Ipopt::Index*        iRow,
           Ipopt::Index*        jCol,
           Ipopt::Number*       values
           );

    protected:
        s2mMatrix m_jacobian;
        void prepareJacobian();

    private:

};
#endif // S2MSTATICOPTIMIZATIONIPOPTLINEARIZED_H