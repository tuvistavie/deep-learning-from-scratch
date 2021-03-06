//
// Created by TakumiYamashita on 2018/06/26.
//

#include "../src/network/network.hpp"
#include <gtest/gtest.h>
#include <algorithm>
#include <iostream>
#include "../src/layer/layer.hpp"
#include "../src/network/builder.hpp"
#include "../src/primitive/primitive.hpp"

using namespace dpl;

TEST(NETWORK_TEST, PRDICT_LOSS) {
  auto network = NetworkBuilder<2>::Input<1, 28, 28>()
                     .Convolution<16, 3, 3, 1, 1>()
                     .Relu()
                     .Convolution<16, 3, 3, 1, 1>()
                     .Relu()
                     .Pooling<2, 2, 2>()
                     .Affine<50>()
                     .Relu()
                     .Dropout(0.5)
                     .Affine<10>()
                     .Dropout(0.5)
                     .SoftmaxWithLoss()
                     .build();

  auto input = make_ndarray_ptr<float, 2, 1, 28, 28>();
  input->rand();

  auto teacher = make_ndarray_ptr<float, 2, 10>();
  teacher->fill(0);
  teacher->at(0).at(0) = 1;
  teacher->at(1).at(9) = 1;

  ndarrayPtr<float, 2, 10> ret = network.predict(input);
  float v = network.loss(input, teacher);
}

TEST(NETWORK_TEST, ACCURACY) {
  auto network = NetworkBuilder<1>::Input<1, 28, 28>()
                     .Convolution<16, 3, 3, 1, 1>()
                     .Relu()
                     .Convolution<16, 3, 3, 1, 1>()
                     .Relu()
                     .Pooling<2, 2, 2>()
                     .Affine<50>()
                     .Relu()
                     .Dropout(0.5)
                     .Affine<10>()
                     .Dropout(0.5)
                     .SoftmaxWithLoss()
                     .build();

  auto input = make_ndarray_ptr<float, 2, 1, 28, 28>();
  input->rand();

  auto teacher = make_ndarray_ptr<float, 2, 10>();
  teacher->fill(0);
  teacher->at(0).at(0) = 1;
  teacher->at(1).at(9) = 1;

  float v = network.accuracy<1>(input, teacher);
}

TEST(NETWORK_TEST, GRADIENT) {
  auto network = NetworkBuilder<2>::Input<1, 28, 28>()
                     .Convolution<16, 3, 3, 1, 1>()
                     .Relu()
                     .Convolution<16, 3, 3, 1, 1>()
                     .Relu()
                     .Pooling<2, 2, 2>()
                     .Affine<50>()
                     .Relu()
                     .Dropout(0.5)
                     .Affine<10>()
                     .Dropout(0.5)
                     .SoftmaxWithLoss()
                     .build();

  auto input = make_ndarray_ptr<float, 2, 1, 28, 28>();
  input->rand();

  auto teacher = make_ndarray_ptr<float, 2, 10>();
  teacher->fill(0);
  teacher->at(0).at(0) = 1;
  teacher->at(1).at(9) = 1;

  network.gradient(input, teacher);
}

// TEST(NETWORK_TEST, DEEP_CONV_NET) {
//  auto network = NetworkBuilder<10>::Input<1, 28, 28>()
//                     .Convolution<16, 3, 3, 1, 1>()
//                     .Relu()
//                     .Convolution<16, 3, 3, 1, 1>()
//                     .Relu()
//                     .Pooling<2, 2, 2>()
//                     .Convolution<32, 3, 3, 1, 1>()
//                     .Relu()
//                     .Convolution<32, 3, 3, 1, 1>()
//                     .Relu()
//                     .Pooling<2, 2, 2>()
//                     .Convolution<64, 3, 3, 1, 1>()
//                     .Relu()
//                     .Convolution<64, 3, 3, 1, 1>()
//                     .Relu()
//                     .Pooling<2, 2, 2>()
//                     .Affine<50>()
//                     .Relu()
//                     .Dropout(0.5)
//                     .Affine<10>()
//                     .Dropout(0.5)
//                     .SoftmaxWithLoss()
//                     .build();
//
//  auto input = make_ndarray_ptr<float, 10, 1, 28, 28>();
//  input->rand();
//
//  auto teacher = make_ndarray_ptr<float, 10, 10>();
//  teacher->fill(0);
//  for (int i = 0; i < 10; i++) teacher->at(i).at(i % 10) = 1;
//
//  network.gradient(input, teacher);
//}