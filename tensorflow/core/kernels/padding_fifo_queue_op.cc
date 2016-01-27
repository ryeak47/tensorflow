/* Copyright 2015 Google Inc. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

// See docs in ../ops/data_flow_ops.cc.

#include <deque>
#include <vector>

#include "tensorflow/core/framework/op_kernel.h"
#include "tensorflow/core/framework/resource_mgr.h"
#include "tensorflow/core/framework/types.h"
#include "tensorflow/core/kernels/padding_fifo_queue.h"
#include "tensorflow/core/kernels/queue_base.h"
#include "tensorflow/core/kernels/queue_op.h"
#include "tensorflow/core/lib/core/errors.h"
#include "tensorflow/core/platform/logging.h"
#include "tensorflow/core/platform/macros.h"
#include "tensorflow/core/platform/mutex.h"
#include "tensorflow/core/platform/port.h"
#include "tensorflow/core/platform/thread_annotations.h"
#include "tensorflow/core/public/partial_tensor_shape.h"
#include "tensorflow/core/public/tensor.h"
#include "tensorflow/core/public/tensor_shape.h"

namespace tensorflow {

// Defines a PaddingFIFOQueueOp, which produces a Queue (specifically, one
// backed by PaddingFIFOQueue) that persists across different graph
// executions, and sessions. Running this op produces a single-element
// tensor of handles to Queues in the corresponding device.
class PaddingFIFOQueueOp : public QueueOp {
 public:
  explicit PaddingFIFOQueueOp(OpKernelConstruction* context) : QueueOp(context) {
    OP_REQUIRES_OK(context, context->GetAttr("shapes", &component_shapes_));
  }

 protected:
  CreatorCallback GetCreator() const override {
    return [this](QueueInterface** ret) {
      PaddingFIFOQueue* queue = new PaddingFIFOQueue(
          capacity_, component_types_, component_shapes_, cinfo_.name());
      *ret = queue;
      return queue->Initialize();
    };
  }

 private:
  std::vector<PartialTensorShape> component_shapes_;

  TF_DISALLOW_COPY_AND_ASSIGN(PaddingFIFOQueueOp);
};

REGISTER_KERNEL_BUILDER(Name("PaddingFIFOQueue").Device(DEVICE_CPU),
                        PaddingFIFOQueueOp);

}  // namespace tensorflow
