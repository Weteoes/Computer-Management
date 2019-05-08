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
// $hash=52978f64fe2a612c05fc42a91ec53df6ff42079d$
//

#ifndef CEF_INCLUDE_CAPI_CEF_REQUEST_CONTEXT_HANDLER_CAPI_H_
#define CEF_INCLUDE_CAPI_CEF_REQUEST_CONTEXT_HANDLER_CAPI_H_
#pragma once

#include "More/CEF/include/capi/cef_base_capi.h"
#include "More/CEF/include/capi/cef_cookie_capi.h"
#include "More/CEF/include/capi/cef_web_plugin_capi.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _cef_request_context_t;

///
// Implement this structure to provide handler implementations. The handler
// instance will not be released until all objects related to the context have
// been destroyed.
///
typedef struct _cef_request_context_handler_t {
  ///
  // Base structure.
  ///
  cef_base_ref_counted_t base;

  ///
  // Called on the browser process UI thread immediately after the request
  // context has been initialized.
  ///
  void(CEF_CALLBACK* on_request_context_initialized)(
      struct _cef_request_context_handler_t* self,
      struct _cef_request_context_t* request_context);

  ///
  // Called on the browser process IO thread to retrieve the cookie manager. If
  // this function returns NULL the default cookie manager retrievable via
  // cef_request_tContext::get_default_cookie_manager() will be used.
  ///
  struct _cef_cookie_manager_t*(CEF_CALLBACK* get_cookie_manager)(
      struct _cef_request_context_handler_t* self);

  ///
  // Called on multiple browser process threads before a plugin instance is
  // loaded. |mime_type| is the mime type of the plugin that will be loaded.
  // |plugin_url| is the content URL that the plugin will load and may be NULL.
  // |is_main_frame| will be true (1) if the plugin is being loaded in the main
  // (top-level) frame, |top_origin_url| is the URL for the top-level frame that
  // contains the plugin when loading a specific plugin instance or NULL when
  // building the initial list of enabled plugins for 'navigator.plugins'
  // JavaScript state. |plugin_info| includes additional information about the
  // plugin that will be loaded. |plugin_policy| is the recommended policy.
  // Modify |plugin_policy| and return true (1) to change the policy. Return
  // false (0) to use the recommended policy. The default plugin policy can be
  // set at runtime using the `--plugin-policy=[allow|detect|block]` command-
  // line flag. Decisions to mark a plugin as disabled by setting
  // |plugin_policy| to PLUGIN_POLICY_DISABLED may be cached when
  // |top_origin_url| is NULL. To purge the plugin list cache and potentially
  // trigger new calls to this function call
  // cef_request_tContext::PurgePluginListCache.
  ///
  int(CEF_CALLBACK* on_before_plugin_load)(
      struct _cef_request_context_handler_t* self,
      const cef_string_t* mime_type,
      const cef_string_t* plugin_url,
      int is_main_frame,
      const cef_string_t* top_origin_url,
      struct _cef_web_plugin_info_t* plugin_info,
      cef_plugin_policy_t* plugin_policy);
} cef_request_context_handler_t;

#ifdef __cplusplus
}
#endif

#endif  // CEF_INCLUDE_CAPI_CEF_REQUEST_CONTEXT_HANDLER_CAPI_H_
