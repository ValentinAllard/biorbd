#define BIORBD_API_EXPORTS
#include "Actuators/ActuatorConstant.h"

#include "s2mString.h"
#include "s2mGenCoord.h"

namespace biorbd { namespace actuator {

s2mActuatorConstant::s2mActuatorConstant(
    int direction,
    double Tmax,
    unsigned int dofIdx, const s2mString &jointName) :
    s2mActuator(direction, dofIdx, jointName),
    m_Tmax(Tmax)
{

}

s2mActuatorConstant::~s2mActuatorConstant()
{

}


double s2mActuatorConstant::torqueMax(){
    return m_Tmax;
}

}}