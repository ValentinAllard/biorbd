#ifndef S2M_ACTUATOR_GAUSS_3P_H
#define S2M_ACTUATOR_GAUSS_3P_H

#include "biorbdConfig.h"
#include "s2mActuator.h"

class s2mGenCoord;
class BIORBD_API s2mActuatorGauss3p : public s2mActuator
{
    public:
        s2mActuatorGauss3p(int direction,
                           double Tmax,
                           double T0,
                           double wmax,
                           double wc,
                           double amin,
                           double wr,
                           double w1,
                           double r,
                           double qopt,
                           unsigned int dofIdx,
                           const s2mString &jointName = "");
        virtual ~s2mActuatorGauss3p();
        virtual double torqueMax(const s2mGenCoord &Q, const s2mGenCoord &Qdot);

    protected:

        virtual void setType(){m_type = "Gauss3p";}             // Quel type d'actuator


        // For informations on these parameters, see Monique Iris Jackson's these from page 54
        // Angular/velocity relationship
        double m_k;         // Ratio of slope of the eccentric and concentric phases
        double m_Tmax;      // Maximum torque in the eccentric phase
        double m_T0;        // Maximum torque isometric
        double m_wmax;      // Maximum angular velocity above which torque cannot be produced
        double m_wc;        // Angular velocity of the vertical asymptote of the concentric hyperbola

        // Activation/velocity relationship
        double m_amax;      // Maximum activation level (set to 1)
        double m_amin;      // Low plateau level
        double m_wr;        // 1/10 de la distance amax/amin
        double m_w1;        // Mid point plateau

        // Torque/angle relationship
        double m_r;         // width of the gaussian curve
        double m_qopt;      // Optimal position

};
#endif // S2M_ACTUATOR_GAUSS_3P_H
