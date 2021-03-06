#ifndef S2M_MUSCLE_CARACTERISTICS_H
#define S2M_MUSCLE_CARACTERISTICS_H
#include "biorbdConfig.h"
#include "s2mMuscleState.h"
#include "s2mError.h"
#include <cstddef>
#include "s2mMuscleFatigueParam.h"

class BIORBD_API s2mMuscleCaracteristics
{
    public:
        s2mMuscleCaracteristics(const double &optLength = 0,
                                const double &fmax = 0,
                                const double &PCSA = 0,
                                const double &tendonSlackLength = 0,
                                const double &pennAngle = 0,
                                const s2mMuscleState& stateMax = s2mMuscleState(),
                                const s2mMuscleFatigueParam& fatigueParameters = s2mMuscleFatigueParam(),
                                const double tauAct = 0.01,
                                const double tauDeact = 0.04,
                                const double &minAct =.01
                                );
        s2mMuscleCaracteristics(const s2mMuscleCaracteristics&);
        s2mMuscleCaracteristics& operator=(const s2mMuscleCaracteristics&);
        virtual ~s2mMuscleCaracteristics();

        // Get et Set
        virtual double optimalLength() const;
        double forceIsoMax() const;
        double tendonSlackLength() const;
        double pennationAngle() const;
        double PCSA() const;

        void minActivation(double val);
        double minActivation() const;
        void tauActivation(double val);
        double tauActivation() const;
        void tauDeactivation(double val);
        double tauDeactivation() const;

        void setOptimalLength(const double &val);
        virtual void setForceIsoMax(const double &val);
        void PCSA(const double &val);
        void setTendonSlackLength(const double &val);
        void setPennationAngle(const double &val);
        void setStateMax(const s2mMuscleState &stateMax);
        const s2mMuscleState& stateMax() const;

        const s2mMuscleFatigueParam& fatigueParameters() const;
        void fatigueParameters(const s2mMuscleFatigueParam& fatigueParameters);

    protected:
        double m_optimalLength; // Longueur sans tension
        double m_fIsoMax;       // Force maximale isométrique
        double m_PCSA;          // PCSA du muscle
        double m_tendonSlackLength; // Tendon slack length
        double m_pennationAngle; // Angle de pennation
        s2mMuscleState m_stateMax; // Excitation et activation maximale du muscle

        // Parametre d'activation
        double m_minActivation; // Activation minimale
        double m_tauActivation; // Time activation constant
        double m_tauDeactivation; // Time deactivation constant

        // Fatigue parameters
        s2mMuscleFatigueParam m_fatigueParameters; // Fatigue parameters
};

#endif // S2M_MUSCLE_CARACTERISTICS_H
