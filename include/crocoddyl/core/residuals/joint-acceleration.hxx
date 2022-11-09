///////////////////////////////////////////////////////////////////////////////
// BSD 3-Clause License
//
// Copyright (C) 2022, Heriot-Watt University
// Copyright note valid unless otherwise stated in individual files.
// All rights reserved.
///////////////////////////////////////////////////////////////////////////////

#include "crocoddyl/core/residuals/joint-acceleration.hpp"
#include "crocoddyl/core/utils/exception.hpp"

namespace crocoddyl {

template <typename Scalar>
ResidualModelJointAccelerationTpl<Scalar>::ResidualModelJointAccelerationTpl(boost::shared_ptr<StateAbstract> state,
                                                                             const VectorXs& aref,
                                                                             const std::size_t nu)
    : Base(state, state->get_nv(), nu, true, true, true), aref_(aref) {}

template <typename Scalar>
ResidualModelJointAccelerationTpl<Scalar>::ResidualModelJointAccelerationTpl(boost::shared_ptr<StateAbstract> state,
                                                                             const VectorXs& aref)
    : Base(state, state->get_nv(), state->get_nv(), true, true, true), aref_(aref) {}

template <typename Scalar>
ResidualModelJointAccelerationTpl<Scalar>::ResidualModelJointAccelerationTpl(boost::shared_ptr<StateAbstract> state,
                                                                             const std::size_t nu)
    : Base(state, state->get_nv(), nu, true, true, true), aref_(VectorXs::Zero(state->get_nv())) {}

template <typename Scalar>
ResidualModelJointAccelerationTpl<Scalar>::ResidualModelJointAccelerationTpl(boost::shared_ptr<StateAbstract> state)
    : Base(state, state->get_nv(), state->get_nv(), true, true, true), aref_(VectorXs::Zero(state->get_nv())) {}

template <typename Scalar>
ResidualModelJointAccelerationTpl<Scalar>::~ResidualModelJointAccelerationTpl() {}

template <typename Scalar>
void ResidualModelJointAccelerationTpl<Scalar>::calc(const boost::shared_ptr<ResidualDataAbstract>& data,
                                                     const Eigen::Ref<const VectorXs>&,
                                                     const Eigen::Ref<const VectorXs>&) {
  Data* d = static_cast<Data*>(data.get());
  data->r = d->joint->a - aref_;
}

template <typename Scalar>
void ResidualModelJointAccelerationTpl<Scalar>::calc(const boost::shared_ptr<ResidualDataAbstract>&,
                                                     const Eigen::Ref<const VectorXs>&) {}

template <typename Scalar>
void ResidualModelJointAccelerationTpl<Scalar>::calcDiff(const boost::shared_ptr<ResidualDataAbstract>& data,
                                                         const Eigen::Ref<const VectorXs>&,
                                                         const Eigen::Ref<const VectorXs>&) {
  Data* d = static_cast<Data*>(data.get());
  data->Rx = d->joint->da_dx;
  data->Ru = d->joint->da_du;
}

template <typename Scalar>
boost::shared_ptr<ResidualDataAbstractTpl<Scalar> > ResidualModelJointAccelerationTpl<Scalar>::createData(
    DataCollectorAbstract* const data) {
  boost::shared_ptr<ResidualDataAbstract> d =
      boost::allocate_shared<Data>(Eigen::aligned_allocator<Data>(), this, data);
  return d;
}

template <typename Scalar>
void ResidualModelJointAccelerationTpl<Scalar>::print(std::ostream& os) const {
  os << "ResidualModelJointAcceleration";
}

template <typename Scalar>
const typename MathBaseTpl<Scalar>::VectorXs& ResidualModelJointAccelerationTpl<Scalar>::get_reference() const {
  return aref_;
}

template <typename Scalar>
void ResidualModelJointAccelerationTpl<Scalar>::set_reference(const VectorXs& reference) {
  aref_ = reference;
}

}  // namespace crocoddyl
