#ifndef S2M_MUSCLE_COMPOUND_H
#define S2M_MUSCLE_COMPOUND_H
    #include <memory>
    #include "biorbdConfig.h"
    #include "s2mString.h"
    #include "s2mMuscleForce.h"
    #include "s2mMuscleGeometry.h"
    #include "s2mMuscleCaracteristics.h"
    #include "s2mMuscleStateDynamics.h"
    #include "s2mMusclePathChangers.h"
    #include "s2mGenCoord.h"


class BIORBD_API s2mMuscleCompound
{
    public:
        s2mMuscleCompound(const s2mString &name = "", const s2mMusclePathChangers& = s2mMusclePathChangers());
        s2mMuscleCompound(const s2mMuscleCompound& m);
        virtual ~s2mMuscleCompound();

        // Wrapping object
        const s2mMusclePathChangers& pathChanger();
        void addPathObject(s2mMusclePathChanger &w); // Ajouter un wrapping object


        const s2mString& type() const;
        virtual const std::vector<std::shared_ptr<s2mMuscleForce>>& force(s2mJoints& model, const s2mGenCoord& Q, const s2mGenCoord& Qdot, const s2mMuscleStateDynamics& emg, const int updateKin = 2) = 0;
        virtual const std::vector<std::shared_ptr<s2mMuscleForce>>& force(s2mJoints& model, const s2mGenCoord& Q, const s2mMuscleStateDynamics& emg, const int updateKin = 2) = 0;
        virtual const std::vector<std::shared_ptr<s2mMuscleForce>>& force(const s2mMuscleStateDynamics& emg) = 0;
        virtual const std::vector<std::shared_ptr<s2mMuscleForce>>& force(); // Return the last computed muscle force

        const s2mString& name() const;
        void setName(const s2mString& name);
    protected:
        s2mMusclePathChangers m_pathChanger;
        std::vector<std::shared_ptr<s2mMuscleForce>> m_force;
        void copyForce(const std::vector<std::shared_ptr<s2mMuscleForce>>& force);
        virtual void setForce() = 0;
        virtual void setType()=0;
        s2mString m_type;
        s2mString m_name;

};

#endif // S2M_MUSCLE_COMPOUND_H
