#ifndef S2M_VIAPOINT_H
#define S2M_VIAPOINT_H

#include <Eigen/Dense>
#include "biorbdConfig.h"
#include "s2mMusclePathChanger.h"

class BIORBD_API s2mViaPoint : public s2mMusclePathChanger{
public:
    s2mViaPoint(const Eigen::Vector3d &v = Eigen::Vector3d(0,0,0), // Position du noeud
                const s2mString &name = "",  // Nom du noeud
                const s2mString &parentName = "");
    virtual ~s2mViaPoint();

};

#endif // S2M_VIAPOINT_H
