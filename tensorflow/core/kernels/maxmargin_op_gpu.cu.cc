// Copyright 2015 William Chan <williamchan@cmu.edu>.

#if GOOGLE_CUDA

#define EIGEN_USE_GPU

#include "tensorflow/core/kernels/maxmargin_op.h"

#include "tensorflow/core/framework/tensor_types.h"
#include "tensorflow/core/platform/port.h"

namespace tensorflow {

typedef Eigen::GpuDevice GPUDevice;

// Partial specialization for a GPUDevice, that uses the Eigen implementation
// from SoftmaxMaxMarginEigenImpl.
namespace functor {
template <typename T>
struct SoftmaxMaxMarginFunctor<GPUDevice, T> {
  void operator()(const GPUDevice& d, typename TTypes<T>::ConstMatrix logits,
                  typename TTypes<T>::ConstMatrix labels,
                  typename TTypes<T>::Matrix scratch,
                  typename TTypes<T>::Vec loss,
                  typename TTypes<T>::Matrix backprop) {
    SoftmaxMaxMarginEigenImpl<GPUDevice, T>::Compute(
        d, logits, labels, scratch, loss, backprop);
  }
};
}  // end namespace functor

// Instantiate the GPU implementation for float.
template struct functor::SoftmaxMaxMarginFunctor<GPUDevice, float>;

}  // end namespace tensorflow

#endif  // GOOGLE_CUDA
