/////////////////////////////////////////////////////////////////////
// Copyright (C) Meteor Engine contributors, all rights reserved.
/////////////////////////////////////////////////////////////////////

#pragma once

/**
 * @file    CommonDefinitions.hpp
 * @author  Liu Xinyu
 * 
 * @brief
 * Common definitions of Meteor Engine
 */

#include "MeteorConfig.hpp"

#include <cstddef>
#include <cstdint>

#ifdef _MSC_VER
  #define ME_FORCEINLINE __forceinline
#else
  #define ME_FORCEINLINE inline
#endif
