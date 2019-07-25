// Copyright (c) 2018 Marshall A. Greenblatt. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//    * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//    * Neither the name of Google Inc. nor the name Chromium Embedded
// Framework nor the names of its contributors may be used to endorse
// or promote products derived from this software without specific prior
// written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool and should not edited
// by hand. See the translator.README.txt file in the tools directory for
// more information.
//
// $hash=b7f068f316498e22b657baa43d6aacbc81d14ef9$
//

#ifndef CEF_INCLUDE_CAPI_VIEWS_CEF_DISPLAY_CAPI_H_
#define CEF_INCLUDE_CAPI_VIEWS_CEF_DISPLAY_CAPI_H_
#pragma once

#include "Weteoes/More/CEF/include/capi/cef_base_capi.h"

#ifdef __cplusplus
extern "C" {
#endif

///
// This structure typically, but not always, corresponds to a physical display
// connected to the system. A fake Display may exist on a headless system, or a
// Display may correspond to a remote, virtual display. All size and position
// values are in density independent pixels (DIP) unless otherwise indicated.
// Methods must be called on the browser process UI thread unless otherwise
// indicated.
///
typedef struct _cef_display_t {
  ///
  // Base structure.
  ///
  cef_base_ref_counted_t base;

  ///
  // Returns the unique identifier for this Display.
  ///
  int64(CEF_CALLBACK* get_id)(struct _cef_display_t* self);

  ///
  // Returns this Display's device pixel scale factor. This specifies how much
  // the UI should be scaled when the actual output has more pixels than
  // standard displays (which is around 100~120dpi). The potential return values
  // differ by platform.
  ///
  float(CEF_CALLBACK* get_device_scale_factor)(struct _cef_display_t* self);

  ///
  // Convert |point| from density independent pixels (DIP) to pixel coordinates
  // using this Display's device scale factor.
  ///
  void(CEF_CALLBACK* convert_point_to_pixels)(struct _cef_display_t* self,
                                              cef_point_t* point);

  ///
  // Convert |point| from pixel coordinates to density independent pixels (DIP)
  // using this Display's device scale factor.
  ///
  void(CEF_CALLBACK* convert_point_from_pixels)(struct _cef_display_t* self,
                                                cef_point_t* point);

  ///
  // Returns this Display's bounds. This is the full size of the display.
  ///
  cef_rect_t(CEF_CALLBACK* get_bounds)(struct _cef_display_t* self);

  ///
  // Returns this Display's work area. This excludes areas of the display that
  // are occupied for window manager toolbars, etc.
  ///
  cef_rect_t(CEF_CALLBACK* get_work_area)(struct _cef_display_t* self);

  ///
  // Returns this Display's rotation in degrees.
  ///
  int(CEF_CALLBACK* get_rotation)(struct _cef_display_t* self);
} cef_display_t;

///
// Returns the primary Display.
///
CEF_EXPORT cef_display_t* cef_display_get_primary();

///
// Returns the Display nearest |point|. Set |input_pixel_coords| to true (1) if
// |point| is in pixel coordinates instead of density independent pixels (DIP).
///
CEF_EXPORT cef_display_t* cef_display_get_nearest_point(
    const cef_point_t* point,
    int input_pixel_coords);

///
// Returns the Display that most closely intersects |bounds|.  Set
// |input_pixel_coords| to true (1) if |bounds| is in pixel coordinates instead
// of density independent pixels (DIP).
///
CEF_EXPORT cef_display_t* cef_display_get_matching_bounds(
    const cef_rect_t* bounds,
    int input_pixel_coords);

///
// Returns the total number of Displays. Mirrored displays are excluded; this
// function is intended to return the number of distinct, usable displays.
///
CEF_EXPORT size_t cef_display_get_count();

///
// Returns all Displays. Mirrored displays are excluded; this function is
// intended to return distinct, usable displays.
///
CEF_EXPORT void cef_display_get_alls(size_t* displaysCount,
                                     cef_display_t** displays);

#ifdef __cplusplus
}
#endif

#endif  // CEF_INCLUDE_CAPI_VIEWS_CEF_DISPLAY_CAPI_H_
