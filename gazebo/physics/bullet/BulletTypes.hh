/*
 * Copyright (C) 2012-2016 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#ifndef GAZEBO_PHYSICS_BULLET_BULLETTYPES_HH_
#define GAZEBO_PHYSICS_BULLET_BULLETTYPES_HH_

#include <boost/shared_ptr.hpp>
#include <ignition/math/Vector4.hh>

#include "gazebo/physics/bullet/bullet_math_inc.h"
#include "gazebo/math/Vector3.hh"
#include "gazebo/math/Pose.hh"
#include "gazebo/util/system.hh"

/// \file
/// \ingroup gazebo_physics
/// \ingroup gazebo_physics_bullet
/// \brief Bullet wrapper forward declarations and typedefs
namespace gazebo
{
  namespace physics
  {
    class BulletCollision;
    class BulletLink;
    class BulletMotionState;
    class BulletPhysics;
    class BulletRayShape;
    class BulletSurfaceParams;

    typedef boost::shared_ptr<BulletCollision> BulletCollisionPtr;
    typedef boost::shared_ptr<BulletLink> BulletLinkPtr;
    typedef boost::shared_ptr<BulletMotionState> BulletMotionStatePtr;
    typedef boost::shared_ptr<BulletPhysics> BulletPhysicsPtr;
    typedef boost::shared_ptr<BulletRayShape> BulletRayShapePtr;
    typedef boost::shared_ptr<BulletSurfaceParams> BulletSurfaceParamsPtr;

    /// \addtogroup gazebo_physics_bullet
    /// \{

    /// \class BulletTypes BulletTypes.hh
    /// \brief A set of functions for converting between the math types used
    ///        by gazebo and bullet.
    class GZ_PHYSICS_VISIBLE BulletTypes {
      /// \brief Convert a bullet btVector3 to a gazebo Vector3.
      /// \param[in] _bt Bullet Vector3.
      /// \return Gazebo Vector3.
      public: static math::Vector3 ConvertVector3(const btVector3 &_bt)
              {
                return math::Vector3(_bt.getX(), _bt.getY(), _bt.getZ());
              }

      /// \brief Convert a bullet btVector3 to an ignition Vector3d.
      /// \param[in] _bt Bullet Vector3.
      /// \return Ignition Vector3d.
      public: static ignition::math::Vector3d ConvertVector3Ign(
                  const btVector3 &_bt)
              {
                return ignition::math::Vector3d(
                    _bt.getX(), _bt.getY(), _bt.getZ());
              }

      /// \brief Convert a gazebo Vector3 to a bullet btVector3.
      /// \param[in] _vec Gazebo Vector3.
      /// \return Bullet Vector3.
      public: static btVector3 ConvertVector3(const math::Vector3 &_vec)
              {
                return btVector3(_vec.x, _vec.y, _vec.z);
              }

      /// \brief Convert an ignition Vector3d to a bullet btVector3.
      /// \param[in] _vec Ignition Vector3d.
      /// \return Bullet Vector3.
      public: static btVector3 ConvertVector3(
                  const ignition::math::Vector3d &_vec)
              {
                return btVector3(_vec.X(), _vec.Y(), _vec.Z());
              }

      /// \brief Convert a bullet btVector4 to an ignition math Vector4d.
      /// \param[in] _bt Bullet Vector4.
      /// \return Ignition math vector 4d.
      public: static ignition::math::Vector4d ConvertVector4dIgn(
          const btVector4 &_bt)
              {
                return ignition::math::Vector4d(_bt.getX(), _bt.getY(),
                                                _bt.getZ(), _bt.getW());
              }

      /// \brief Convert an ignition math Vector4d to a bullet btVector4.
      /// \param[in] _vec Ignition math Vector4d.
      /// \return Bullet Vector4.
      public: static btVector4 ConvertVector4dIgn(
          const ignition::math::Vector4d &_vec)
              {
                return btVector4(_vec.X(), _vec.Y(), _vec.Z(), _vec.W());
              }

      /// \brief Convert a bullet transform to an ignition math pose.
      /// \param[in] _bt Bullet pose (btTransform).
      /// \return Ignition math pose.
      public: static ignition::math::Pose3d ConvertPoseIgn(
                  const btTransform &_bt)
              {
                ignition::math::Pose3d pose;
                pose.Pos() = ConvertVector3Ign(_bt.getOrigin());
                pose.Rot().W() = _bt.getRotation().getW();
                pose.Rot().X() = _bt.getRotation().getX();
                pose.Rot().Y() = _bt.getRotation().getY();
                pose.Rot().Z() = _bt.getRotation().getZ();
                return pose;
              }

      /// \brief Convert a bullet transform to a gazebo pose.
      /// \param[in] _bt Bullet pose (btTransform).
      /// \return Gazebo pose.
      public: static math::Pose ConvertPose(const btTransform &_bt)
              {
                math::Pose pose;
                pose.pos = ConvertVector3(_bt.getOrigin());
                pose.rot.w = _bt.getRotation().getW();
                pose.rot.x = _bt.getRotation().getX();
                pose.rot.y = _bt.getRotation().getY();
                pose.rot.z = _bt.getRotation().getZ();
                return pose;
              }

      /// \brief Convert a gazebo pose to a bullet transform.
      /// \param[in] _pose Gazebo pose.
      /// \return Bullet pose (btTransform).
      public: static btTransform ConvertPose(const math::Pose &_pose)
              {
                btTransform trans;

                trans.setOrigin(ConvertVector3(_pose.pos));
                trans.setRotation(btQuaternion(_pose.rot.x, _pose.rot.y,
                                               _pose.rot.z, _pose.rot.w));
                return trans;
              }

      /// \brief Convert an ignition math pose to a bullet transform.
      /// \param[in] _pose Ignition math pose.
      /// \return Bullet pose (btTransform).
      public: static btTransform ConvertPose(
                  const ignition::math::Pose3d &_pose)
              {
                btTransform trans;

                trans.setOrigin(ConvertVector3(_pose.Pos()));
                trans.setRotation(btQuaternion(_pose.Rot().X(), _pose.Rot().Y(),
                      _pose.Rot().Z(), _pose.Rot().W()));
                return trans;
              }
    };
    /// \}
  }
}
#endif
