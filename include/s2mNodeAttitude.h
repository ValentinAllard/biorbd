#ifndef S2M_NODE_ATTITUDE_H
#define S2M_NODE_ATTITUDE_H

#include <Eigen/Dense>
#include "biorbdConfig.h"
#include "s2mAttitude.h"
#include "s2mString.h"

class BIORBD_API s2mNodeAttitude : public s2mAttitude
{
    public:
    s2mNodeAttitude(const s2mAttitude& = s2mAttitude(), // Position du noeud
            const s2mString &name = "",  // Nom du noeud
            const s2mString &parentName = "");
    virtual ~s2mNodeAttitude();

    const s2mString& parent() const;
    void setParent(const s2mString &parentName);
    void setName(const s2mString &name);
    const s2mString& name() const;

    // Get and Set
    void setAttitude(const s2mAttitude&);
    const s2mAttitude& attitude() const;

    protected:
        s2mString m_parentName;
        s2mString m_RTName;

};

#endif // S2M_NODE_ATTITUDE_H
