/////////////////////////////////////////////////////////////////////
// Copyright (C) Meteor Engine contributors, all rights reserved.
/////////////////////////////////////////////////////////////////////

#pragma once

/**
 * @file    EngineTypes.hpp
 * @author  Liu Xinyu
 * 
 * @brief
 * Engine types
 */

#include "CommonDefinitions.hpp"

#ifndef ME_USE_INTERNAL_TYPES
  // 使用标准库提供的类型
  #include <string>
  #include <stdexcept>
  #include <memory>

  #include <array>
  #include <vector>
  #include <map>
  #include <set>
  #include <list>
  #include <queue>
  #include <stack>
  #include <deque>

  #include <unordered_map>
  #include <unordered_set>
#endif

#include <algorithm>
#include <functional>
#include <optional>
#include <thread>
#include <atomic>
#include <mutex>
#include <future>

namespace ME
{
  using uint8   = ::uint8_t;
  using uint16  = ::uint16_t;
  using uint32  = ::uint32_t;
  using uint64  = ::uint64_t;

  using int8    = ::int8_t;
  using int16   = ::int16_t;
  using int32   = ::int32_t;
  using int64   = ::int64_t;

  /// using ::size_t;
  /// @note 
  /// size_t 类型就不删除后面的 '_t' 了

#ifndef ME_USE_INTERNAL_TYPES
  using String    = std::string;
  using StringU16 = std::u16string;
  using StringU32 = std::u32string;

  //
  template <typename T, size_t N>
  using TArray  = std::array<T, N>;
  //
  template <typename T>
  using TVector = std::vector<T>;
  //
  template <typename T>
  using TSet    = std::set<T>;
  //
  template <typename KT, typename T>
  using TMap    = std::map<KT, T>;
  //
  template <typename T>
  using TUnorderedSet = std::unordered_set<T>;
  //
  template <typename KT, typename T>
  using TUnorderedMap = std::unordered_map<KT, T>;
  //
  template <typename T>
  using TList = std::list<T>;
  //
  template <typename T>
  using TDeque = std::deque<T>;
  //
  template <typename T, typename C = TDeque<T>>
  using TQueue = std::queue<T, C>;
  //
  template <typename T, typename C = TDeque<T>>
  using TStack = std::stack<T, C>;
  //
  template <typename T>
  using TList = std::list<T>;
  //
  template <typename T>
  using TUnique = std::unique_ptr<T>;
  //
  template <typename T>
  using TShared = std::shared_ptr<T>;
  //
  template <typename T, typename ... Args> inline TShared<T> MakeShared(Args&& ...args)
  {
    return std::make_shared<T>(std::forward<Args>(args)...);
  }
  //
  template <typename T, typename ... Args> inline TUnique<T> MakeUnique(Args&& ...args)
  {
    return std::make_unique<T>(std::forward<Args>(args)...);
  }
#else
  #error "Not implemented"
#endif
} // namespace ME
