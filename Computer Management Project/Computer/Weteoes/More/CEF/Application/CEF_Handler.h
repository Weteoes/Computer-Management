// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_Handler_H
#define CEF_Handler_H

#include <Weteoes/More/CEF/include/cef_client.h>
#include <Weteoes/More/CEF/include/base/cef_lock.h>
#include <list>

class CEF_Handler : public CefClient,
                      public CefDisplayHandler,
                      public CefLifeSpanHandler,
                      public CefLoadHandler, 
					  public CefContextMenuHandler {
 public:
  explicit CEF_Handler(bool use_views);
  ~CEF_Handler();

  // Provide access to the single global instance of this object.
  static CEF_Handler* GetInstance();



  //mutable base::Lock lock_;
  //CefRefPtr<CefBrowser> browser_;
  int GetBrowserListIndex();
  CefRefPtr<CefBrowser> GetBrowserbyIndex(int index);

  // CefClient methods:
  virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE {
	  return this;
  }
  virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE {
	  return this;
  }
  virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE { 
	  return this;
  }
  

  //�Ҽ������ȡ
  virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() OVERRIDE { 
	  return this;
  }
  virtual bool OnContextMenuCommand(CefRefPtr<CefBrowser> browser,
	  CefRefPtr<CefFrame> frame,
	  CefRefPtr<CefContextMenuParams> params,
	  int command_id,
	  EventFlags event_flags) OVERRIDE;
  virtual void OnBeforeContextMenu(
	  CefRefPtr<CefBrowser> browser,
	  CefRefPtr<CefFrame> frame,
	  CefRefPtr<CefContextMenuParams> params,
	  CefRefPtr<CefMenuModel> model) OVERRIDE;

  // CefDisplayHandler methods:
  virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
                             const CefString& title) OVERRIDE;

  // CefLifeSpanHandler methods:
  virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
  virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
  virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;


  // CefLoadHandler methods:
  virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefFrame> frame,
                           ErrorCode errorCode,
                           const CefString& errorText,
                           const CefString& failedUrl) OVERRIDE;




  // Request that all existing browser windows close.
  void CloseAllBrowsers(bool force_close);

  bool IsClosing() const { return is_closing_; }

 private:
  // Platform-specific implementation.
  void PlatformTitleChange(CefRefPtr<CefBrowser> browser,
                           const CefString& title);

  // True if the application is using the Views framework.
  const bool use_views_;

  // List of existing browser windows. Only accessed on the CEF UI thread.
  typedef std::list<CefRefPtr<CefBrowser>> BrowserList;
  BrowserList browser_list_;

  bool is_closing_;


  // Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(CEF_Handler);
};

#endif