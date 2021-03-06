// Copyright 2015 William Chan <williamchan@cmu.edu>.

#include "tensorflow/core/framework/op.h"

namespace tensorflow {

REGISTER_OP("AttentionMask")
    .Attr("fill_value: float")
    .Input("attention_states_sequence_len: int64")
    .Input("input: float")
    .Output("output: float")
    .Doc(R"doc(
AttentionMask
)doc");

REGISTER_OP("AttentionMaskMedian")
    .Attr("fill_value: float")
    .Attr("window_l: int = 10")
    .Attr("window_r: int = 200")
    .Input("attention_states_sequence_len: int64")
    .Input("input: float")
    .Input("prev: float")
    .Output("output: float")
    .Doc(R"doc(
AttentionMaskMedian
)doc");

REGISTER_OP("AttentionMaskWindow")
    .Attr("fill_value: float")
    .Attr("s_min: int = 0")
    .Attr("s_max: int = 40")
    .Attr("v_min: float = 1.2")
    .Attr("v_max: float = 2.2")
    .Attr("index: int")
    .Input("attention_states_sequence_len: int64")
    .Input("input: float")
    .Output("output: float")
    .Doc(R"doc(
AttentionMaskMedian
)doc");

}  // namespace tensorflow
