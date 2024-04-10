///////////////////////////////////////////////////////////////////////////////
// Copyright (C) Meteor Engine contributors, all rights reserved.
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "EngineTypes.hpp"

namespace ME::Plugin::MikuMikuDance
{
  /**
   * PMX 文件头
   *  - 文件标识 [4 Bytes, 'PMX ']
   *  - 文件版本
   */
  struct PMXHeader
  {
    uint8 magic[4];
    float version;
  };

  /**
   * PMX 文件标识 ['PMX ']
   */
  constexpr uint8 PMX_MAGIC[4]  = { 'P', 'M', 'X', ' ' };
  
} // namespace Plugin::MikuMikuDance
