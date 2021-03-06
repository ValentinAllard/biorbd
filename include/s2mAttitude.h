#ifndef S2M_ATTITUDE_H
#define S2M_ATTITUDE_H

#include <vector>
#include <Eigen/Dense>
#include <rbdl/rbdl_math.h>
#include "biorbdConfig.h"

class s2mNode;
class s2mString;
class BIORBD_API s2mAttitude : public Eigen::Matrix4d
{
    public:
        s2mAttitude(const Eigen::Matrix4d& = Eigen::Matrix4d::Identity());
        s2mAttitude(const Eigen::VectorXd&, const Eigen::Vector3d&, const s2mString&);
        s2mAttitude(const Eigen::Matrix3d& rot, const Eigen::Vector3d& trans = Eigen::Vector3d::Zero());
        s2mAttitude(const RigidBodyDynamics::Math::SpatialTransform&);

        Eigen::Vector3d axe(int); // Aller récupérer un axe en particulier

        s2mAttitude transpose() const;
        Eigen::Vector3d trans() const;
        Eigen::Matrix3d rot() const;
        void setIdentity();
        bool isIdentity();

        static s2mAttitude SpatialTransform2Attitude(const RigidBodyDynamics::Math::SpatialTransform& st);
        static s2mAttitude combineRotAndTrans(const Eigen::Matrix3d& rot, const Eigen::Vector3d& trans);
        static Eigen::Matrix4d transformCardanToMatrix(const Eigen::VectorXd&, const Eigen::Vector3d&, const s2mString&);
        static Eigen::VectorXd transformMatrixToCardan(const s2mAttitude&, const s2mString &seq);

        const s2mAttitude operator*(const s2mAttitude&);
        const Eigen::Vector3d operator*(const Eigen::Vector3d&);
        const Eigen::Vector3d operator*(const Eigen::Vector4d&);
        const s2mNode operator*(const s2mNode&);

        static s2mAttitude mean(const std::vector<s2mAttitude>&); // Moyenne des matrices 4x4
    protected:
        Eigen::Vector4d expand3dTo4d(const Eigen::Vector3d&);

};
std::ostream& operator<<(std::ostream& os, const s2mAttitude &a);


#endif // S2M_ATTITUDE_H
