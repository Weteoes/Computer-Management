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
// $hash=d7f34d867389c53c384f366e08f958ed724f9b90$
//

#ifndef CEF_INCLUDE_CAPI_CEF_REQUEST_CAPI_H_
#define CEF_INCLUDE_CAPI_CEF_REQUEST_CAPI_H_
#pragma once

#include "More/CEF/include/capi/cef_base_capi.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _cef_post_data_element_t;
struct _cef_post_data_t;

///
// Structure used to represent a web request. The functions of this structure
// may be called on any thread.
///
typedef struct _cef_request_t {
  ///
  // Base structure.
  ///
  cef_base_ref_counted_t base;

  ///
  // Returns true (1) if this object is read-only.
  ///
  int(CEF_CALLBACK* is_read_only)(struct _cef_request_t* self);

  ///
  // Get the fully qualified URL.
  ///
  // The resulting string must be freed by calling cef_string_userfree_free().
  cef_string_userfree_t(CEF_CALLBACK* get_url)(struct _cef_request_t* self);

  ///
  // Set the fully qualified URL.
  ///
  void(CEF_CALLBACK* set_url)(struct _cef_request_t* self,
                              const cef_string_t* url);

  ///
  // Get the request function type. The value will default to POST if post data
  // is provided and GET otherwise.
  ///
  // The resulting string must be freed by calling cef_string_userfree_free().
  cef_string_userfree_t(CEF_CALLBACK* get_method)(struct _cef_request_t* self);

  ///
  // Set the request function type.
  ///
  void(CEF_CALLBACK* set_method)(struct _cef_request_t* self,
                                 const cef_string_t* method);

  ///
  // Set the referrer URL and policy. If non-NULL the referrer URL must be fully
  // qualified with an HTTP or HTTPS scheme component. Any username, password or
  // ref component will be removed.
  ///
  void(CEF_CALLBACK* set_referrer)(struct _cef_request_t* self,
                                   const cef_string_t* referrer_url,
                                   cef_referrer_policy_t policy);

  ///
  // Get the referrer URL.
  ///
  // The resulting string must be freed by calling cef_string_userfree_free().
  cef_string_userfree_t(CEF_CALLBACK* get_referrer_url)(
      struct _cef_request_t* self);

  ///
  // Get the referrer policy.
  ///
  cef_referrer_policy_t(CEF_CALLBACK* get_referrer_policy)(
      struct _cef_request_t* self);

  ///
  // Get the post data.
  ///
  struct _cef_post_data_t*(CEF_CALLBACK* get_post_data)(
      struct _cef_request_t* self);

  ///
  // Set the post data.
  ///
  void(CEF_CALLBACK* set_post_data)(struct _cef_request_t* self,
                                    struct _cef_post_data_t* postData);

  ///
  // Get the header values. Will not include the Referer value if any.
  ///
  void(CEF_CALLBACK* get_header_map)(struct _cef_request_t* self,
                                     cef_string_multimap_t headerMap);

  ///
  // Set the header values. If a Referer value exists in the header map it will
  // be removed and ignored.
  ///
  void(CEF_CALLBACK* set_header_map)(struct _cef_request_t* self,
                                     cef_string_multimap_t headerMap);

  ///
  // Set all values at one time.
  ///
  void(CEF_CALLBACK* set)(struct _cef_request_t* self,
                          const cef_string_t* url,
                          const cef_string_t* method,
                          struct _cef_post_data_t* postData,
                          cef_string_multimap_t headerMap);

  ///
  // Get the flags used in combination with cef_urlrequest_t. See
  // cef_urlrequest_flags_t for supported values.
  ///
  int(CEF_CALLBACK* get_flags)(struct _cef_request_t* self);

  ///
  // Set the flags used in combination with cef_urlrequest_t.  See
  // cef_urlrequest_flags_t for supported values.
  ///
  void(CEF_CALLBACK* set_flags)(struct _cef_request_t* self, int flags);

  ///
  // Get the URL to the first party for cookies used in combination with
  // cef_urlrequest_t.
  ///
  // The resulting string must be freed by calling cef_string_userfree_free().
  cef_string_userfree_t(CEF_CALLBACK* get_first_party_for_cookies)(
      struct _cef_request_t* self);

  ///
  // Set the URL to the first party for cookies used in combination with
  // cef_urlrequest_t.
  ///
  void(CEF_CALLBACK* set_first_party_for_cookies)(struct _cef_request_t* self,
                                                  const cef_string_t* url);

  ///
  // Get the resource type for this request. Only available in the browser
  // process.
  ///
  cef_resource_type_t(CEF_CALLBACK* get_resource_type)(
      struct _cef_request_t* self);

  ///
  // Get the transition type for this request. Only available in the browser
  // process and only applies to requests that represent a main frame or sub-
  // frame navigation.
  ///
  cef_transition_type_t(CEF_CALLBACK* get_transition_type)(
      struct _cef_request_t* self);

  ///
  // Returns the globally unique identifier for this request or 0 if not
  // specified. Can be used by cef_request_tHandler implementations in the
  // browser process to track a single request across multiple callbacks.
  ///
  uint64(CEF_CALLBACK* get_identifier)(struct _cef_request_t* self);
} cef_request_t;

///
// Create a new cef_request_t object.
///
CEF_EXPORT cef_request_t* cef_request_create();

///
// Structure used to represent post data for a web request. The functions of
// this structure may be called on any thread.
///
typedef struct _cef_post_data_t {
  ///
  // Base structure.
  ///
  cef_base_ref_counted_t base;

  ///
  // Returns true (1) if this object is read-only.
  ///
  int(CEF_CALLBACK* is_read_only)(struct _cef_post_data_t* self);

  ///
  // Returns true (1) if the underlying POST data includes elements that are not
  // represented by this cef_post_data_t object (for example, multi-part file
  // upload data). Modifying cef_post_data_t objects with excluded elements may
  // result in the request failing.
  ///
  int(CEF_CALLBACK* has_excluded_elements)(struct _cef_post_data_t* self);

  ///
  // Returns the number of existing post data elements.
  ///
  size_t(CEF_CALLBACK* get_element_count)(struct _cef_post_data_t* self);

  ///
  // Retrieve the post data elements.
  ///
  void(CEF_CALLBACK* get_elements)(struct _cef_post_data_t* self,
                                   size_t* elementsCount,
                                   struct _cef_post_data_element_t** elements);

  ///
  // Remove the specified post data element.  Returns true (1) if the removal
  // succeeds.
  ///
  int(CEF_CALLBACK* remove_element)(struct _cef_post_data_t* self,
                                    struct _cef_post_data_element_t* element);

  ///
  // Add the specified post data element.  Returns true (1) if the add succeeds.
  ///
  int(CEF_CALLBACK* add_element)(struct _cef_post_data_t* self,
                                 struct _cef_post_data_element_t* element);

  ///
  // Remove all existing post data elements.
  ///
  void(CEF_CALLBACK* remove_elements)(struct _cef_post_data_t* self);
} cef_post_data_t;

///
// Create a new cef_post_data_t object.
///
CEF_EXPORT cef_post_data_t* cef_post_data_create();

///
// Structure used to represent a single element in the request post data. The
// functions of this structure may be called on any thread.
///
typedef struct _cef_post_data_element_t {
  ///
  // Base structure.
  ///
  cef_base_ref_counted_t base;

  ///
  // Returns true (1) if this object is read-only.
  ///
  int(CEF_CALLBACK* is_read_only)(struct _cef_post_data_element_t* self);

  ///
  // Remove all contents from the post data element.
  ///
  void(CEF_CALLBACK* set_to_empty)(struct _cef_post_data_element_t* self);

  ///
  // The post data element will represent a file.
  ///
  void(CEF_CALLBACK* set_to_file)(struct _cef_post_data_element_t* self,
                                  const cef_string_t* fileName);

  ///
  // The post data element will represent bytes.  The bytes passed in will be
  // copied.
  ///
  void(CEF_CALLBACK* set_to_bytes)(struct _cef_post_data_element_t* self,
                                   size_t size,
                                   const void* bytes);

  ///
  // Return the type of this post data element.
  ///
  cef_postdataelement_type_t(CEF_CALLBACK* get_type)(
      struct _cef_post_data_element_t* self);

  ///
  // Return the file name.
  ///
  // The resulting string must be freed by calling cef_string_userfree_free().
  cef_string_userfree_t(CEF_CALLBACK* get_file)(
      struct _cef_post_data_element_t* self);

  ///
  // Return the number of bytes.
  ///
  size_t(CEF_CALLBACK* get_bytes_count)(struct _cef_post_data_element_t* self);

  ///
  // Read up to |size| bytes into |bytes| and return the number of bytes
  // actually read.
  ///
  size_t(CEF_CALLBACK* get_bytes)(struct _cef_post_data_element_t* self,
                                  size_t size,
                                  void* bytes);
} cef_post_data_element_t;

///
// Create a new cef_post_data_element_t object.
///
CEF_EXPORT cef_post_data_element_t* cef_post_data_element_create();

#ifdef __cplusplus
}
#endif

#endif  // CEF_INCLUDE_CAPI_CEF_REQUEST_CAPI_H_
