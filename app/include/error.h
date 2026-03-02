/**
 * @file error.h
 * @brief Return codes for Ember API functions and module definitions.
 *
 * See @ref status_codes for documentation.
 *
 * <!--Author(s): Lee Taylor, lee@ember.com -->
 * <!--Copyright 2004 by Ember Corporation. All rights reserved.-->
 */

#ifndef SILABS_ERRORS_H
#define SILABS_ERRORS_H

#include "error-def.h"

#ifndef __EMBERSTATUS_TYPE__
#define __EMBERSTATUS_TYPE__
typedef uint8_t EmberStatus;
#endif // __EMBERSTATUS_TYPE__

#endif // SILABS_ERRORS_H
