//
// Created by TakumiYamashita on 2018/06/10.
//

#ifndef DEEP_LEARNING_FROM_SCRATCH_PARAMETERS_HPP
#define DEEP_LEARNING_FROM_SCRATCH_PARAMETERS_HPP

#include <unordered_map>
#include <memory>
#include "primitive.hpp"

namespace dpl {
  template <typename K>
  class Parameters {
    std::shared_ptr<ndarray> operator[](const K &key) { return mp[key]; }

    std::unordered_map<K, std::shared_ptr<ndarray>> mp;
  };
}  // namespace dpl

#endif  // DEEP_LEARNING_FROM_SCRATCH_PARAMETERS_HPP
