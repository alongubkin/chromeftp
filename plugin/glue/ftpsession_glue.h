#ifndef GLUE_FTPSESSION_GLUE_H__
#define GLUE_FTPSESSION_GLUE_H__

#include <string.h>
#include <string>
#include <npapi.h>
#include <npruntime.h>
#include "common.h"
#include "static_object.h"
#include "ftpsession.h"
#include "common.h"

namespace glue {
namespace class_FtpSession {
namespace callback_EmptyCallback {

class EmptyCallback_glue : public FtpSession::EmptyCallback {
 public:
  EmptyCallback_glue(NPP npp, NPObject *npobject);
  virtual ~EmptyCallback_glue();
  virtual void Run();
 private:
  NPP npp_;
  NPObject *npobject_;
};
EmptyCallback_glue *CreateObject(NPP npp, NPObject *npobject);

}  // namespace callback_EmptyCallback
namespace callback_ErrorCallback {

class ErrorCallback_glue : public FtpSession::ErrorCallback {
 public:
  ErrorCallback_glue(NPP npp, NPObject *npobject);
  virtual ~ErrorCallback_glue();
  virtual void Run(const std::string& message);
 private:
  NPP npp_;
  NPObject *npobject_;
};
ErrorCallback_glue *CreateObject(NPP npp, NPObject *npobject);

}  // namespace callback_ErrorCallback

void InitializeGlue(NPP npp);
NPClass *GetStaticNPClass(void);
glue::globals::NPAPIObject *CreateRawStaticNPObject(NPP npp);
void RegisterObjectBases(glue::globals::NPAPIObject *namespace_object,
glue::globals::NPAPIObject *root_object);
glue::globals::NPAPIObject *GetStaticNPObject(
glue::globals::NPAPIObject *root_object);
void StaticEnumeratePropertyHelper(NPIdentifier *output);
uint32_t GetStaticPropertyCount();
bool StaticInvoke(glue::globals::NPAPIObject *object,
NPP npp,
NPIdentifier name,
const NPVariant *args,
uint32_t argCount,
NPVariant *result,
const char **error_handle);
bool StaticGetProperty(glue::globals::NPAPIObject *object,
NPP npp,
NPIdentifier name,
NPVariant *variant,
const char **error_handle);
bool StaticSetProperty(glue::globals::NPAPIObject *object,
NPP npp,
NPIdentifier name,
const NPVariant *variant,
const char **error_handle);

NPClass *GetNPClass(void);
bool Invoke(FtpSession* object,
NPP npp,
NPIdentifier name,
const NPVariant *args,
uint32_t argCount,
NPVariant *result,
const char **error_handle);
bool GetProperty(const FtpSession& object,
NPP npp,
NPIdentifier name,
NPVariant *variant,
const char **error_handle);
bool SetProperty(FtpSession* object,
NPP npp,
NPIdentifier name,
const NPVariant *variant,
const char **error_handle);
bool EnumeratePropertyEntries(NPObject *header,
NPIdentifier **value,
uint32_t *count);
void EnumeratePropertyEntriesHelper(NPIdentifier *output);
uint32_t GetPropertyCount();


class NPAPIObject: public NPObject {
  NPP npp_;
  FtpSession value_;
 public:
  NPAPIObject(NPP npp): npp_(npp), value_() { }
  NPP npp() {return npp_;}
  const FtpSession &value() {return value_;}
  FtpSession *value_mutable() {return &value_;}
  void set_value(const FtpSession &value) {value_ = value;}
};
NPAPIObject *CreateNPObject(NPP npp, const FtpSession &object);

}  // namespace class_FtpSession
}  // namespace glue

#endif  // GLUE_FTPSESSION_GLUE_H__
