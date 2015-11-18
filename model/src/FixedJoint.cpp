/*
 * Copyright (C) 2015 Fondazione Istituto Italiano di Tecnologia
 * Authors: Silvio Traversaro
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <iDynTree/Core/SpatialMotionVector.h>
#include <iDynTree/Core/Utils.h>

#include <iDynTree/Model/FixedJoint.h>
#include <iDynTree/Model/LinkState.h>

#include <cassert>

namespace iDynTree
{

FixedJoint::FixedJoint(const LinkIndex _link1, const LinkIndex _link2,
                       const Transform& _link1_X_link2):
                       link1(_link1), link2(_link2),
                       link1_X_link2(_link1_X_link2)
{
}

FixedJoint::FixedJoint(const FixedJoint& other):
                       link1(other.link1), link2(other.link2),
                       link1_X_link2(other.link1_X_link2)
{
}


FixedJoint::~FixedJoint()
{

}

IJoint * FixedJoint::clone() const
{
    return (IJoint *) new FixedJoint(*this);
}

void FixedJoint::setAttachedLinks(const LinkIndex _link1, const LinkIndex _link2)
{
    link1 = _link1;
    link2 = _link2;
    return;
}

void FixedJoint::setRestTransform(const Transform& _link1_X_link2)
{
    link1_X_link2 = _link1_X_link2;
}

unsigned int FixedJoint::getNrOfPosCoords() const
{
    return 0;
}

unsigned int FixedJoint::getNrOfDOFs() const
{
    return 0;
}

LinkIndex FixedJoint::getFirstAttachedLink() const
{
    return link1;
}

LinkIndex FixedJoint::getSecondAttachedLink() const
{
    return link2;
}

Transform FixedJoint::getRestTransform(const LinkIndex child, const LinkIndex parent) const
{
    if( child == this->link1 )
    {
        iDynTreeAssert(p_linkB == this->link2);
        return this->link1_X_link2;
    }
    else
    {
        iDynTreeAssert(child == this->link2);
        iDynTreeAssert(parent == this->link1);
        return this->link1_X_link2.inverse();
    }
}

Transform FixedJoint::getTransform(const IRawVector & jntPos, const LinkIndex child, const LinkIndex parent) const
{
    return getRestTransform(child,parent);
}


SpatialMotionVector FixedJoint::getMotionSubspaceVector(int dof_i, const LinkIndex child, const LinkIndex parent) const
{
    return SpatialMotionVector::Zero();
}

void FixedJoint::computeJointTorque(const IRawVector & jntPos, const Wrench& internalWrench,
                                    LinkIndex linkThatAppliesWrench, LinkIndex linkOnWhichWrenchIsApplied,
                                    IRawVector& jntTorques) const
{
    // A fixed joint would have a torque of size 0
    return;
}

void FixedJoint::computeChildPosVelAcc(const IRawVector & jntPos,
                                       const IRawVector & jntVel,
                                       const IRawVector & jntAcc,
                                           LinkPositions & linkPositions,
                                           LinkVelArray & linkVels,
                                           LinkAccArray & linkAccs,
                                           const LinkIndex child,
                                           const LinkIndex parent) const
{
    Transform child_X_parent = this->getTransform(jntPos,child,parent);
    Transform parent_X_child = this->getTransform(jntPos,parent,child);

    // Propagate position : position of the frame is expressed as
    // transform between the link frame and a reference frame :
    // ref_H_child  = ref_H_parent*parent_H_child
    linkPositions(child) = linkPositions(parent)*parent_X_child;

    // Propagate twist and spatial acceleration: for a fixed joint the twist of two attached links is the same,
    // expect that they are usually expressed in different frames
    linkVels(child) = child_X_parent*linkVels(parent);
    linkAccs(child) = child_X_parent*linkAccs(parent);

    return;
}

void FixedJoint::computeChildVelAcc(const IRawVector & jntPos,
                                       const IRawVector & jntVel,
                                       const IRawVector & jntAcc,
                                       LinkVelArray & linkVels,
                                       LinkAccArray & linkAccs,
                                       const LinkIndex child, const LinkIndex parent) const
{
    Transform child_X_parent = this->getTransform(jntPos,child,parent);
    // Propagate twist: for a fixed joint the twist of two attached links is the same,
    // expect that they are usually expressed in different frames
    linkVels(child) = child_X_parent*linkVels(parent);
    linkAccs(child) = child_X_parent*linkAccs(parent);

    return;
}

void FixedJoint::setIndex(JointIndex& _index)
{
    this->m_index = _index;
}

JointIndex FixedJoint::getIndex() const
{
    return this->m_index;
}

void FixedJoint::setPosCoordsOffset(const size_t _offset)
{
    this->m_posCoordsOffset = _offset;
}

size_t FixedJoint::getPosCoordsOffset() const
{
    return this->m_posCoordsOffset;
}

void FixedJoint::setDOFsOffset(const size_t _offset)
{
    this->m_DOFsOffset = _offset;
}

size_t FixedJoint::getDOFsOffset() const
{
    return this->m_DOFsOffset;
}

}
