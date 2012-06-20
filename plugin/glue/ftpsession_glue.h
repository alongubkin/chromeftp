#ifndef ___GLUE_FTPSESSION_GLUE_H__
#define ___GLUE_FTPSESSION_GLUE_H__

#include <string.h>
#include <string>
#include <npapi.h>
#include <npruntime.h>
#include "common.h"
#include "static_object.h"
#include "ftpsession.h"
#include "common.h"

namespace glue {
namespace namespace_chromeftp {
namespace callback_FtpSessionConnectCallback {

class FtpSessionConnectCallback_glue : public chromeftp::FtpSessionConnectCallback {
 public:
  FtpSessionConnectCallback_glue(NPP npp, NPObject *npobject);
  virtual ~FtpSessionConnectCallback_glue();
  virtual void Run();
 private:
  NPP npp_;
  NPObject *npobject_;
};
FtpSessionConnectCallback_glue *CreateObject(NPP npp, NPObject *npobject);

}  // namespace callback_FtpSessionConnectCallback
namespace callback_FtpSessionErrorCallback {

class FtpSessionErrorCallback_glue : public chromeftp::FtpSessionErrorCallback {
 public:
  FtpSessionErrorCallback_glue(NPP npp, NPObject *npobject);
  virtual ~FtpSessionErrorCallback_glue();
  virtual void Run(const std::string& message);
 private:
  NPP npp_;
  NPObject *npobject_;
};
FtpSessionErrorCallback_glue *CreateObject(NPP npp, NPObject *npobject);

}  // namespace callback_FtpSessionErrorCallback
namespace class_FtpSession {

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
bool Invoke(chromeftp::FtpSession* object,
NPP npp,
NPIdentifier name,
const NPVariant *args,
uint32_t argCount,
NPVariant *result,
const char **error_handle);
bool GetProperty(const chromeftp::FtpSession& object,
NPP npp,
NPIdentifier name,
NPVariant *variant,
const char **error_handle);
bool SetProperty(chromeftp::FtpSession* object,
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
  chromeftp::FtpSession value_;
 public:
  NPAPIObject(NPP npp): npp_(npp), value_() { }
  NPP npp() {return npp_;}
  const chromeftp::FtpSession &value() {return value_;}
  chromeftp::FtpSession *value_mutable() {return &value_;}
  void set_value(const chromeftp::FtpSession &value) {value_ = value;}
};
NPAPIObject *CreateNPObject(NPP npp, const chromeftp::FtpSession &object);

}  // namespace class_FtpSession

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

}  // namespace namespace_chromeftp
}  // namespace glue

#endif  // ___GLUE_FTPSESSION_GLUE_H__
