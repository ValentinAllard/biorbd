/* File : biorbd.i */
%module biorbd
%{
#include "s2mMusculoSkeletalModel.h"

#include <boost/numeric/odeint.hpp>
#include <Eigen/Dense>
#include <rbdl/rbdl.h>

#include "s2mRead.h"
#include "s2mJoints.h"
#include "s2mJoint.h"

#include "s2mGenCoord.h"
#include "s2mTau.h"

#include "s2mBone.h"
#include "s2mBoneMesh.h"
#include "s2mIMU.h"

#include "s2mMatrix.h"
#include "s2mNodeWrap.h"
#include "s2mNodeBone.h"
#include "s2mNodeMuscle.h"
#include "s2mTime.h"

#include "s2mKalmanReconsIMU.h"
#include "s2mKalmanReconsMarkers.h"

#include "s2mMuscleStateDynamics.h"
#include "s2mMuscleHillType.h"
#include "s2mMuscleHillTypeThelen.h"
#include "s2mMuscleHillTypeSimple.h"
#include "s2mMuscleHillTypeThelenFatigable.h"
#include "s2mMuscleFatigueState.h"
#include "s2mMuscleFatigueDynamicState.h"
#include "s2mMuscleFatigueDynamicStateXia.h"
#include "s2mGroupeMusculaire.h"
#include "s2mStaticOptimization.h"
%}
%include exception.i
%include <std_shared_ptr.i>

%exception {
    try {
        $action
    } catch(const std::exception& e) {
        SWIG_exception(SWIG_RuntimeError, e.what());
    } catch(...) {
        SWIG_exception(SWIG_RuntimeError, "Unknown exception");
    }
}

/* Instantiate standard library */
%include <std_vector.i>
%include <std_string.i>

// Instantiate templates
namespace std {
    %template(VecS2mNode) std::vector<s2mNode>;
    %template(MatS2mNode) std::vector<std::vector<s2mNode>>;
    %template(VecS2mNodeBone) std::vector<s2mNodeBone>;
    %template(MatS2mNodeBone) std::vector<std::vector<s2mNodeBone>>;
    %template(VecS2mAttitude) std::vector<s2mAttitude>;
    %template(MatS2mAttitude) std::vector<std::vector<s2mAttitude>>;

    %template(VecS2mVector) std::vector<s2mVector>;
    %template(MatS2mVector) std::vector<std::vector<s2mVector>>;
    %template(VecS2mTau) std::vector<s2mTau>;
    %template(MatS2mTau) std::vector<std::vector<s2mTau>>;
    %template(VecS2mGenCoord) std::vector<s2mGenCoord>;
    %template(MatS2mGenCoord) std::vector<std::vector<s2mGenCoord>>;

    %template(SharedS2mMuscle) std::shared_ptr<s2mMuscle>;
    %template(VecS2mMuscleStateDynamics) std::vector<s2mMuscleStateDynamics>;
    %template(MatS2mMuscleStateDynamics) std::vector<std::vector<s2mMuscleStateDynamics>>;
    %template(VecS2mNodeMuscle) std::vector<s2mNodeMuscle>;
    %template(MatS2mNodeMuscle) std::vector<std::vector<s2mNodeMuscle>>;

    %template(SharedS2mMuscleFatigueState) std::shared_ptr<s2mMuscleFatigueState>;
}

// Exposing some useful functions
%extend s2mMusculoSkeletalModel{
    s2mTau InverseDynamics(const s2mGenCoord &Q, const s2mGenCoord &QDot, const s2mGenCoord &QDDot) {
        s2mTau Tau(*self);
        RigidBodyDynamics::InverseDynamics(*self, Q, QDot, QDDot, Tau);
        return QDDot;
    }

    s2mGenCoord ForwardDynamics(const s2mGenCoord &Q, const s2mGenCoord &QDot, const s2mTau &Tau) {
        s2mGenCoord QDDot(*self);
        RigidBodyDynamics::ForwardDynamics(*self, Q, QDot, Tau, QDDot);
        return QDDot;
    }

    s2mGenCoord ForwardDynamicsLagrangian(const s2mGenCoord &Q, const s2mGenCoord &QDot, const s2mTau &Tau) {
        s2mGenCoord QDDot(*self);
        RigidBodyDynamics::ForwardDynamicsLagrangian(*self, Q, QDot, Tau, QDDot);
        return QDDot;
    }

    s2mGenCoord ForwardDynamicsConstraintsDirect(const s2mGenCoord &Q, const s2mGenCoord &QDot, const s2mTau &Tau, s2mContacts& CS) {
        s2mGenCoord QDDot(*self);
        RigidBodyDynamics::ForwardDynamicsConstraintsDirect(*self, Q, QDot, Tau, CS, QDDot);
        return QDDot;
    }
    s2mGenCoord ForwardDynamicsConstraintsDirect(const s2mGenCoord &Q, const s2mGenCoord &QDot, const s2mTau &Tau) {
        s2mGenCoord QDDot(*self);
        s2mContacts& CS = self->getConstraints_nonConst();
        RigidBodyDynamics::ForwardDynamicsConstraintsDirect(*self, Q, QDot, Tau, CS, QDDot);
        return QDDot;
    }

    s2mTau muscularJointTorque(const std::vector<s2mMuscleStateDynamics> &state, const s2mGenCoord &Q, const s2mGenCoord &QDot){
        return self->muscularJointTorque(*self, state, true, &Q, &QDot);
    }

    static s2mString getMuscleType(const std::shared_ptr<s2mMuscle> m){
        return m->type();
    }
}

// extension of muscle casting
%extend s2mMuscleHillType{
    static s2mMuscleHillType& getRef(std::shared_ptr<s2mMuscle> m)
    {
        return *(std::dynamic_pointer_cast<s2mMuscleHillType>(m));
    }
}
%extend s2mMuscleHillTypeThelen{
    static s2mMuscleHillTypeThelen& getRef(std::shared_ptr<s2mMuscle> m)
    {
        return *(std::dynamic_pointer_cast<s2mMuscleHillTypeThelen>(m));
    }
}
%extend s2mMuscleHillTypeThelenFatigable{
    static s2mMuscleHillTypeThelenFatigable& getRef(std::shared_ptr<s2mMuscle> m)
    {
        return *(std::dynamic_pointer_cast<s2mMuscleHillTypeThelenFatigable>(m));
    }
}
%extend s2mMuscleHillTypeSimple{
    static s2mMuscleHillTypeSimple& getRef(std::shared_ptr<s2mMuscle> m)
    {
        return *(std::dynamic_pointer_cast<s2mMuscleHillTypeSimple>(m));
    }
}

// extension of muscle fatigueState casting
%extend s2mMuscleFatigueState{
    static s2mMuscleFatigueState& getRef(std::shared_ptr<s2mMuscleFatigueState> s)
    {
        return *s;
    }
}
%extend s2mMuscleFatigueDynamicStateXia{
    static s2mMuscleFatigueDynamicStateXia& getRef(std::shared_ptr<s2mMuscleFatigueState> s)
    {
        return *(std::dynamic_pointer_cast<s2mMuscleFatigueDynamicStateXia>(s));
    }
}


/* Includes all neceressary files from the API */
%include "../include/biorbdConfig.h"
//%include "s2mOptions.h"

%include "../include/s2mVector.h"
%include "../include/s2mGenCoord.h"
%include "../include/s2mTau.h"
%include "../include/s2mMatrix.h"
%include "../include/s2mAttitude.h"
//%include "s2mNodeAttitude.h"
//%include "s2mQuaternion.h"
//%include "s2mNode.h"
%include "../include/s2mMarkers.h"

//%include "s2mPatch.h"
//%include "s2mTime.h"
//%include "s2mTimer.h"
//%include "s2mBenchmark.h"
//%include "../include/s2mString.h"
%apply std::string { s2mString };
//%include "s2mEquation.h"
//%include "s2mIfStream.h"
//%include "s2mError.h"
%include "../include/s2mPath.h"
%include "../include/s2mRead.h"
//%include "s2mIntegrator.h"

%include "../include/s2mJoints.h"
//%include "s2mJoint.h"
%include "../include/s2mContacts.h"

//%include "s2mActuator.h"
//%include "s2mActuatorConstant.h"
//%include "s2mActuatorGauss3p.h"
//%include "s2mActuatorGauss6p.h"
//%include "s2mActuatorLinear.h"
//%include "s2mActuators.h"

%include "../include/s2mNode.h"
%include "../include/s2mNodeBone.h"
//%include "s2mBone.h"
//%include "s2mBoneCaracteristics.h"
//%include "s2mBoneMesh.h"

%include "../include/s2mNodeMuscle.h"
%include "../include/s2mMuscleCompound.h"
%include "../include/s2mMuscle.h"
%include "../include/s2mMuscleFatigable.h"
%include "../include/s2mMuscleHillType.h"
%include "../include/s2mMuscleHillTypeThelen.h"
%include "../include/s2mMuscleHillTypeThelenFatigable.h"
%include "../include/s2mMuscleHillTypeSimple.h"
%include "../include/s2mMuscles.h"
%include "../include/s2mGroupeMusculaire.h"
%include "../include/s2mMuscleCaracteristics.h"

%include "../include/s2mMuscleFatigueParam.h"
%include "../include/s2mMuscleFatigueState.h"
%include "../include/s2mMuscleFatigueDynamicState.h"
%include "../include/s2mMuscleFatigueDynamicStateXia.h"
//%include "s2mMuscleForce.h"
//%include "s2mMuscleForceFromInsertion.h"
//%include "s2mMuscleForceFromOrigin.h"
%include "../include/s2mMuscleGeometry.h"
//%include "s2mMuscleMesh.h"
//%include "s2mMusclePathChanger.h"
//%include "s2mMusclePathChangers.h"
%include "../include/s2mMuscleState.h"
%include "../include/s2mMuscleStateDynamics.h"
//%include "s2mMuscleStateDynamicsBuchanan.h"
//%include "s2mMuscleOptimisation.h"

//%include "s2mIMU.h"
//%include "s2mIMUs.h"


//%include "s2mNodeWrap.h"
//%include "s2mViaPoint.h"
//%include "s2mWrappingObject.h"
//%include "s2mWrappingSphere.h"
//%include "s2mWrappingCylinder.h"
//%include "s2mWriter.h"

//%include "s2mKalmanRecons.h"
//%include "s2mKalmanReconsIMU.h"
%include "../include/s2mKalmanReconsMarkers.h"

//%include "s2mIMU_Unity_Optim.h"

%include "../include/s2mMusculoSkeletalModel.h"

%include "../include/s2mStaticOptimization.h"

