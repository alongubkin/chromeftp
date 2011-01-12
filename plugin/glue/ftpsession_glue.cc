
#include "plugin_main.h"
#include "ftpsession_glue.h"
#include "ftpsession_glue.h"

namespace glue {
namespace class_FtpSession {
namespace callback_EmptyCallback {

void RunCallback(NPP npp, NPObject *npobject, bool async) {
  #define NPAPI_GLUE_EXCEPTION_CONTEXT "callback return value '<no name>'"
  const char *error=NULL;
  const char **error_handle = &error;
  bool success = true;
  NPVariant result;
  NULL_TO_NPVARIANT(result);
  if (success) {
    if (async && NPCallback::SupportsAsync(npp)) {
      NPCallback* callback = NPCallback::Create(npp);
      if (callback) {
        callback->Set(npobject, NULL, 0);
        callback->CallAsync();
        NPN_ReleaseObject(callback);
        success = true;
      } else {
        success = false;
      }
    } else {
      GLUE_PROFILE_START(npp, "invokeDefault");
      success = NPN_InvokeDefault(npp,
      npobject,
      NULL,
      0,
      &result);
      GLUE_PROFILE_STOP(npp, "invokeDefault");
      if (success) {
        GLUE_PROFILE_START(npp, "NPN_ReleaseVariantValue");
        NPN_ReleaseVariantValue(&result);
        GLUE_PROFILE_STOP(npp, "NPN_ReleaseVariantValue");
      }
    }
  }

  return void(0);
  #undef NPAPI_GLUE_EXCEPTION_CONTEXT
}


EmptyCallback_glue::EmptyCallback_glue(NPP npp, NPObject *npobject)
: npp_(npp),
npobject_(npobject) {
  NPN_RetainObject(npobject);
}

EmptyCallback_glue::~EmptyCallback_glue() {
  // TODO: The NPObject we should be releasing here might have already been
  // destroyed by the browser due to a Firefox bug.  The following line is
  // commented out in order to avoid a browser crash.
  //g_browser->releaseobject(npobject_);
}

void EmptyCallback_glue::Run() {
  return RunCallback(npp_, npobject_, false);
}

EmptyCallback_glue *CreateObject(NPP npp, NPObject *npobject) {
  return npobject ? new EmptyCallback_glue(npp, npobject) : NULL;
}

}  // namespace callback_EmptyCallback
namespace callback_ErrorCallback {

void RunCallback(NPP npp, NPObject *npobject, bool async, const std::string& message) {
  #define NPAPI_GLUE_EXCEPTION_CONTEXT "callback return value '<no name>'"
  const char *error=NULL;
  const char **error_handle = &error;
  bool success = true;
  NPVariant args[1];
  NPVariant result;
  NULL_TO_NPVARIANT(result);
  GLUE_PROFILE_START(npp, "StringToNPVariant");
  success = StringToNPVariant(message, (args + 0));
  GLUE_PROFILE_STOP(npp, "StringToNPVariant");
  if (success) {

    if (async && NPCallback::SupportsAsync(npp)) {
      NPCallback* callback = NPCallback::Create(npp);
      if (callback) {
        callback->Set(npobject, args, 1);
        callback->CallAsync();
        NPN_ReleaseObject(callback);
        success = true;
      } else {
        success = false;
      }
    } else {
      GLUE_PROFILE_START(npp, "invokeDefault");
      success = NPN_InvokeDefault(npp,
      npobject,
      args,
      1,
      &result);
      GLUE_PROFILE_STOP(npp, "invokeDefault");
      if (success) {
        GLUE_PROFILE_START(npp, "NPN_ReleaseVariantValue");
        NPN_ReleaseVariantValue(&result);
        GLUE_PROFILE_STOP(npp, "NPN_ReleaseVariantValue");
      }
    }
  }
  for (int i = 0; i != 1; ++i) {
    NPN_ReleaseVariantValue(&args[i]);
  }

  return void(0);
  #undef NPAPI_GLUE_EXCEPTION_CONTEXT
}


ErrorCallback_glue::ErrorCallback_glue(NPP npp, NPObject *npobject)
: npp_(npp),
npobject_(npobject) {
  NPN_RetainObject(npobject);
}

ErrorCallback_glue::~ErrorCallback_glue() {
  // TODO: The NPObject we should be releasing here might have already been
  // destroyed by the browser due to a Firefox bug.  The following line is
  // commented out in order to avoid a browser crash.
  //g_browser->releaseobject(npobject_);
}

void ErrorCallback_glue::Run(const std::string& message) {
  return RunCallback(npp_, npobject_, false, message);
}

ErrorCallback_glue *CreateObject(NPP npp, NPObject *npobject) {
  return npobject ? new ErrorCallback_glue(npp, npobject) : NULL;
}

}  // namespace callback_ErrorCallback
static bool StaticHasMethod(NPObject *header, NPIdentifier name);
static bool StaticInvokeEntry(NPObject *header,
NPIdentifier name,
const NPVariant *args,
uint32_t argCount,
NPVariant *result);
static bool StaticInvokeDefault(NPObject *header,
const NPVariant *args,
uint32_t argCount,
NPVariant *result);
static bool StaticHasProperty(NPObject *header, NPIdentifier name);
static bool StaticGetPropertyEntry(NPObject *header,
NPIdentifier name,
NPVariant *variant);
static bool StaticSetPropertyEntry(NPObject *header,
NPIdentifier name,
const NPVariant *variant);
static bool StaticEnumeratePropertyEntries(NPObject *header,
NPIdentifier **value,
uint32_t *count);
void StaticEnumeratePropertyHelper(NPIdentifier *output);
uint32_t GetStaticPropertyCount();
static NPClass static_npclass = {
  NP_CLASS_STRUCT_VERSION,
  glue::globals::Allocate,
  glue::globals::Deallocate,
  0,
  StaticHasMethod,
  StaticInvokeEntry,
  StaticInvokeDefault,
  StaticHasProperty,
  StaticGetPropertyEntry,
  StaticSetPropertyEntry,
  0,
  StaticEnumeratePropertyEntries,
};
NPClass *GetStaticNPClass(void)
{
  return &static_npclass;
}
uint32_t GetStaticPropertyCount() {
  return 0 + 0 + 0;
}
static bool StaticEnumeratePropertyEntries(NPObject *header,
NPIdentifier **value,
uint32_t *count) {
  *count = 0;
  glue::globals::NPAPIObject *object =
  static_cast<glue::globals::NPAPIObject *>(header);
  NPP npp = object->npp();
  GLUE_SCOPED_PROFILE(npp, "FtpSession::StaticEnumeratePropertyEntries", prof);
  if (*count) {
    GLUE_PROFILE_START(npp, "memalloc");
    *value = static_cast<NPIdentifier *>(
    NPN_MemAlloc(*count * sizeof(NPIdentifier)));
    GLUE_PROFILE_STOP(npp, "memalloc");
    StaticEnumeratePropertyHelper(*value);
  } else {
    *value = NULL;
  }
  return true;
}
// This is broken out into a separate function so that the plugin object can
// call it on the global namespace without extra memory allocation.
// The caller is responsible for making sure there's sufficient space in output.
void StaticEnumeratePropertyHelper(NPIdentifier *output) {
}
static void InitializeStaticIds(NPP npp) {
}
glue::globals::NPAPIObject *CreateRawStaticNPObject(NPP npp) {
  GLUE_PROFILE_START(npp, "createobject");
  glue::globals::NPAPIObject *object =
  static_cast<glue::globals::NPAPIObject *>(
  NPN_CreateObject(npp, &static_npclass));
  GLUE_PROFILE_STOP(npp, "createobject");
  return object;
}
void RegisterObjectBases(glue::globals::NPAPIObject *namespace_object,
glue::globals::NPAPIObject *root_object) {
}
bool StaticInvokeDefault(NPObject *header,
const NPVariant *args,
uint32_t argCount,
NPVariant *result) {
  const char *error=NULL;
  const char **error_handle = &error;
  bool success = true;
  glue::globals::NPAPIObject *object =
  static_cast<glue::globals::NPAPIObject *>(header);
  NPP npp = object->npp();
  GLUE_SCOPED_PROFILE(npp, "FtpSession::StaticInvokeDefault", prof);

if (argCount == 0) do {
  bool success = true;

  glue::class_FtpSession::NPAPIObject *retval =
  glue::class_FtpSession::CreateNPObject(npp, FtpSession());
  OBJECT_TO_NPVARIANT(retval, *result);
  success = retval != NULL;

  if (!success) break;

  return true;
} while(false);
  // Skip out early on the profiling, so as not to count error callback time.
  GLUE_SCOPED_PROFILE_STOP(prof);
  if (!success && error) {
    glue::globals::SetLastError(npp, error);
  }
  return false;
}
static bool StaticInvokeEntry(NPObject *header,
NPIdentifier name,
const NPVariant *args,
uint32_t argCount,
NPVariant *result) {
 // Chrome transforms InvokeDefault into Invoke with null parameter:
  // http://code.google.com/p/chromium/issues/detail?id=5110
  if (name == NULL)
  return StaticInvokeDefault(header, args, argCount, result);
  const char *error=NULL;
  DebugScopedId id(name);  // debug helper
  glue::globals::NPAPIObject *object =
  static_cast<glue::globals::NPAPIObject *>(header);
  NPP npp = object->npp();
  GLUE_PROFILE_START(npp, std::string("FtpSession::StaticInvokeEntry(") +
  (id.text() ? id.text() : "") + ")");
  bool success = StaticInvoke(object, npp, name, args, argCount, result,
  &error);
  GLUE_PROFILE_STOP(npp, std::string("FtpSession::StaticInvokeEntry(") +
  (id.text() ? id.text() : "") + ")");
  if (!success && error) {
    glue::globals::SetLastError(npp, error);
  }
  return success;
}
static bool StaticGetPropertyEntry(NPObject *header,
NPIdentifier name,
NPVariant *variant) {
  const char *error=NULL;
  DebugScopedId id(name);  // debug helper
  glue::globals::NPAPIObject *object =
  static_cast<glue::globals::NPAPIObject *>(header);
  NPP npp = object->npp();
  GLUE_PROFILE_START(npp, std::string("FtpSession::StaticGetPropertyEntry(") +
  (id.text() ? id.text() : "") + ")");
  bool success = StaticGetProperty(object, npp, name, variant, &error);
  GLUE_PROFILE_STOP(npp, std::string("FtpSession::StaticGetPropertyEntry(") +
  (id.text() ? id.text() : "") + ")");
  if (!success && error) {
    glue::globals::SetLastError(npp, error);
  }
  return success;
}
static bool StaticSetPropertyEntry(NPObject *header,
NPIdentifier name,
const NPVariant *variant) {
  const char *error=NULL;
  DebugScopedId id(name);  // debug helper
  glue::globals::NPAPIObject *object =
  static_cast<glue::globals::NPAPIObject *>(header);
  NPP npp = object->npp();
  GLUE_PROFILE_START(npp, std::string("FtpSession::StaticSetPropertyEntry(") +
  (id.text() ? id.text() : "") + ")");
  bool success = StaticSetProperty(object, npp, name, variant, &error);
  GLUE_PROFILE_STOP(npp, std::string("FtpSession::StaticSetPropertyEntry(") +
  (id.text() ? id.text() : "") + ")");
  if (!success && error) {
    glue::globals::SetLastError(npp, error);
  }
  return success;
}
static NPObject *Allocate(NPP npp, NPClass *theClass);
static void Deallocate(NPObject *header);
static bool HasMethod(NPObject *header, NPIdentifier name);
static bool InvokeEntry(NPObject *header,
NPIdentifier name,
const NPVariant *args,
uint32_t argCount,
NPVariant *result);
static bool HasProperty(NPObject *header, NPIdentifier name);
static bool GetPropertyEntry(NPObject *header,
NPIdentifier name,
NPVariant *variant);
static bool SetPropertyEntry(NPObject *header,
NPIdentifier name,
const NPVariant *variant);
bool EnumeratePropertyEntries(NPObject *header,
NPIdentifier **value,
uint32_t *count);
void EnumeratePropertyEntriesHelper(NPIdentifier *output);
uint32_t GetPropertyCount();
static uint32_t GetLocalPropertyCount();
static NPClass npclass = {
  NP_CLASS_STRUCT_VERSION,
  Allocate,
  Deallocate,
  0,
  HasMethod,
  InvokeEntry,
  0,
  HasProperty,
  GetPropertyEntry,
  SetPropertyEntry,
  0,
  EnumeratePropertyEntries
};
NPClass *GetNPClass(void)
{
  return &npclass;
}
enum {
  METHOD_CONNECT,
  NUM_METHOD_IDS
};
static NPIdentifier method_ids[NUM_METHOD_IDS];
static const NPUTF8 *method_names[NUM_METHOD_IDS] = {
  "connect"
};
uint32_t GetPropertyCount() {
  return GetLocalPropertyCount() + 0;
}
static uint32_t GetLocalPropertyCount() {
  return 0 + NUM_METHOD_IDS;
}
bool EnumeratePropertyEntries(NPObject *header,
NPIdentifier **value,
uint32_t *count) {
  glue::globals::NPAPIObject *object =
  static_cast<glue::globals::NPAPIObject *>(header);
  NPP npp = object->npp();
  GLUE_PROFILE_START(npp, "FtpSession::EnumeratePropertyEntries");
  *count = GetPropertyCount();
  GLUE_PROFILE_START(npp, "memalloc");
  *value = static_cast<NPIdentifier *>(
  NPN_MemAlloc(*count * sizeof(NPIdentifier)));
  GLUE_PROFILE_STOP(npp, "memalloc");
  EnumeratePropertyEntriesHelper(*value);
  GLUE_PROFILE_STOP(npp, "FtpSession::EnumeratePropertyEntries");
  return true;
}
// This is broken out into a separate function so that derived classes can
// call it as well without extra memory allocation.
// The caller is responsible for making sure there's sufficient space in output.
void EnumeratePropertyEntriesHelper(NPIdentifier *output) {
  memcpy(output, method_ids,
  NUM_METHOD_IDS * sizeof(NPIdentifier));
  output += NUM_METHOD_IDS;
}
static void InitializeMemberIds(NPP npp) {
  NPN_GetStringIdentifiers(method_names, NUM_METHOD_IDS,
  method_ids);
}
static void InitializeIds(NPP npp) {
  InitializeMemberIds(npp);
  InitializeStaticIds(npp);
}
static bool InvokeEntry(NPObject *header,
NPIdentifier name,
const NPVariant *args,
uint32_t argCount,
NPVariant *result) {
  const char *error=NULL;
  const char **error_handle = &error;
  DebugScopedId id(name);  // debug helper
  bool success = true;
  NPAPIObject *object_npobject = static_cast<NPAPIObject *>(header);
  NPP npp = object_npobject->npp();
  // Profile is a bit late, but it makes npp lookup easier.
  GLUE_SCOPED_PROFILE(npp, std::string("FtpSession::InvokeEntry(") + (id.text() ?
  id.text() : "") + ")", prof);
  if (!success) return false;
  bool ret = Invoke(object_npobject->value_mutable(), npp, name, args, argCount, result, error_handle);
  GLUE_SCOPED_PROFILE_STOP(prof);
  if (!ret && error) {
    glue::globals::SetLastError(npp, error);
    return false;
  }
  return ret;
}
static bool GetPropertyEntry(NPObject *header,
NPIdentifier name,
NPVariant *variant) {
  const char *error=NULL;
  const char **error_handle = &error;
  DebugScopedId id(name);  // debug helper
  bool success = true;
  NPAPIObject *object_npobject = static_cast<NPAPIObject *>(header);
  NPP npp = object_npobject->npp();
  // Profile is a bit late, but it makes npp lookup easier.
  GLUE_SCOPED_PROFILE(npp, std::string("FtpSession::GetPropertyEntry(") +
  (id.text() ? id.text() : "") + ")", prof);
  if (!success) return false;  // A rare error case.
  bool ret = GetProperty(*(object_npobject->value_mutable()), npp, name, variant, error_handle);
  GLUE_SCOPED_PROFILE_STOP(prof);
  if (!ret && error) {
    glue::globals::SetLastError(npp, error);
    return false;
  }
  return ret;
}
static bool SetPropertyEntry(NPObject *header,
NPIdentifier name,
const NPVariant *variant) {
  const char *error=NULL;
  const char **error_handle = &error;
  DebugScopedId id(name);  // debug helper
  bool success = true;
  NPAPIObject *object_npobject = static_cast<NPAPIObject *>(header);
  NPP npp = object_npobject->npp();
  // Profile is a bit late, but it makes npp lookup easier.
  GLUE_SCOPED_PROFILE(npp, std::string("FtpSession::SetPropertyEntry(") +
  (id.text() ? id.text() : "") + ")", prof);
  if (!success) return false;  // A rare error case.
  bool ret = SetProperty(object_npobject->value_mutable(), npp, name, variant, error_handle);
  GLUE_SCOPED_PROFILE_STOP(prof);
  if (!ret && error) {
    glue::globals::SetLastError(npp, error);
    return false;
  }
  return ret;
}
void InitializeGlue(NPP npp) {
  InitializeIds(npp);
}
static NPObject *Allocate(NPP npp, NPClass *theClass) {
  return new NPAPIObject(npp);
}
static void Deallocate(NPObject *header) {
  delete static_cast<NPAPIObject *>(header);
}
NPAPIObject *CreateNPObject(NPP npp, const FtpSession &object) {
  GLUE_PROFILE_START(npp, "createobject");
  NPAPIObject *npobject = static_cast<NPAPIObject *>(
  NPN_CreateObject(npp, &npclass));
  GLUE_PROFILE_STOP(npp, "createobject");
  npobject->set_value(object);
  return npobject;
}
bool StaticInvoke(glue::globals::NPAPIObject *object,
NPP npp,
NPIdentifier name,
const NPVariant *args,
uint32_t argCount,
NPVariant *result,
const char **error_handle) {
  GLUE_SCOPED_PROFILE(npp, "FtpSession::StaticInvoke", prof);
  bool success = true;
  return false;
}
bool StaticGetProperty(glue::globals::NPAPIObject *object,
NPP npp,
NPIdentifier name,
NPVariant *variant,
const char **error_handle) {
  GLUE_SCOPED_PROFILE(npp, "FtpSession::StaticGetProperty", prof);
  bool success = true;
  success = glue::globals::GetProperty(object, name, variant);
  return success;
}
bool StaticSetProperty(glue::globals::NPAPIObject *object,
NPP npp,
NPIdentifier name,
const NPVariant *variant,
const char **error_handle) {
  GLUE_SCOPED_PROFILE(npp, "FtpSession::StaticSetProperty", prof);
  bool success = true;
  if (glue::globals::SetProperty(object, name, variant)) return true;
  return false;
}
static bool StaticHasMethod(NPObject *header, NPIdentifier name) {
  DebugScopedId id(name);  // debug helper
  glue::globals::NPAPIObject *object =
  static_cast<glue::globals::NPAPIObject *>(header);
  NPP npp = object->npp();
  GLUE_SCOPED_PROFILE(npp, std::string("FtpSession::StaticHasMethod(") +
  (id.text() ? id.text() : "") + ")", prof);
  return false;
}
static bool StaticHasProperty(NPObject *header, NPIdentifier name) {
  DebugScopedId id(name);  // debug helper
  glue::globals::NPAPIObject *object =
  static_cast<glue::globals::NPAPIObject *>(header);
  NPP npp = object->npp();
  GLUE_SCOPED_PROFILE(npp, std::string("FtpSession::StaticHasProperty(") +
  (id.text() ? id.text() : "") + ")", prof);
  return glue::globals::HasProperty(header, name);
}
bool Invoke(FtpSession* object,
NPP npp,
NPIdentifier name,
const NPVariant *args,
uint32_t argCount,
NPVariant *result,
const char **error_handle) {
  DebugScopedId id(name);  // debug helper
  GLUE_SCOPED_PROFILE(npp, std::string("FtpSession::Invoke(") + (id.text() ?
  id.text() : "") + ")", prof);
  bool success = true;

if (name == method_ids[METHOD_CONNECT] && argCount == 3) do {
  bool success = true;
  #define NPAPI_GLUE_EXCEPTION_CONTEXT "parameter 'server'"

  std::string param_server;
  if (NPVARIANT_IS_STRING(args[0])) {
    param_server = std::string(NPVARIANT_TO_STRING(args[0]).UTF8Characters,
    NPVARIANT_TO_STRING(args[0]).UTF8Length);
  } else {
    success = false;
    *error_handle = "Error in " NPAPI_GLUE_EXCEPTION_CONTEXT
    ": was expecting a string.";
  }

  if (!success) break;
  #undef NPAPI_GLUE_EXCEPTION_CONTEXT
  #define NPAPI_GLUE_EXCEPTION_CONTEXT "parameter 'connectCallback'"

  FtpSession::EmptyCallback* param_connectCallback;
  if (NPVARIANT_IS_NULL(args[1])) {
    param_connectCallback = NULL;
  } else {

    success = NPVARIANT_IS_OBJECT(args[1]);
    FtpSession::EmptyCallback *param_connectCallback_nullable = NULL;
    if (success) {
      param_connectCallback_nullable = glue::class_FtpSession::callback_EmptyCallback::CreateObject(
      npp, NPVARIANT_TO_OBJECT(args[1]));
    } else {
      *error_handle = "Error in " NPAPI_GLUE_EXCEPTION_CONTEXT
      ": a callback must be a Javascript function.";
    }
    param_connectCallback = param_connectCallback_nullable;
  }

  if (!success) break;
  #undef NPAPI_GLUE_EXCEPTION_CONTEXT
  #define NPAPI_GLUE_EXCEPTION_CONTEXT "parameter 'errorCallback'"

  FtpSession::ErrorCallback* param_errorCallback;
  if (NPVARIANT_IS_NULL(args[2])) {
    param_errorCallback = NULL;
  } else {

    success = NPVARIANT_IS_OBJECT(args[2]);
    FtpSession::ErrorCallback *param_errorCallback_nullable = NULL;
    if (success) {
      param_errorCallback_nullable = glue::class_FtpSession::callback_ErrorCallback::CreateObject(
      npp, NPVARIANT_TO_OBJECT(args[2]));
    } else {
      *error_handle = "Error in " NPAPI_GLUE_EXCEPTION_CONTEXT
      ": a callback must be a Javascript function.";
    }
    param_errorCallback = param_errorCallback_nullable;
  }

  if (!success) break;
  #undef NPAPI_GLUE_EXCEPTION_CONTEXT
  object->Connect(param_server, param_connectCallback, param_errorCallback);
  if (!success) break;
  VOID_TO_NPVARIANT(*result);
  return true;
} while(false);
  if (!*error_handle) {
    *error_handle =
    "Method not found; perhaps it doesn't take that number of arguments?";
  }
  return false;
}
bool GetProperty(const FtpSession& object,
NPP npp,
NPIdentifier name,
NPVariant *variant,
const char **error_handle) {
  DebugScopedId id(name);  // debug helper
  GLUE_SCOPED_PROFILE(npp, std::string("FtpSession::GetProperty(") + (id.text() ?
  id.text() : "") + ")", prof);
  if (!*error_handle) {
    *error_handle = "Property not found.";
  }
  return false;
}
bool SetProperty(FtpSession* object,
NPP npp,
NPIdentifier name,
const NPVariant *variant,
const char **error_handle) {
  DebugScopedId id(name);  // debug helper
  GLUE_SCOPED_PROFILE(npp, std::string("FtpSession::SetProperty(") + (id.text() ?
  id.text() : "") + ")", prof);
  if (!*error_handle) {
    *error_handle = "Property not found.";
  }
  return false;
}
static bool HasMethod(NPObject *header, NPIdentifier name) {
  DebugScopedId id(name);  // debug helper
  glue::globals::NPAPIObject *object =
  static_cast<glue::globals::NPAPIObject *>(header);
  NPP npp = object->npp();
  GLUE_SCOPED_PROFILE(npp, std::string("FtpSession::HasMethod(") + (id.text() ?
  id.text() : "") + ")", prof);
  for (int i = 0; i < NUM_METHOD_IDS; i++)
  if (name == method_ids[i])
  return true;
  return false;
}
static bool HasProperty(NPObject *header, NPIdentifier name) {
  DebugScopedId id(name);  // debug helper
  glue::globals::NPAPIObject *object =
  static_cast<glue::globals::NPAPIObject *>(header);
  NPP npp = object->npp();
  GLUE_SCOPED_PROFILE(npp, std::string("FtpSession::HasProperty(") + (id.text() ?
  id.text() : "") + ")", prof);
  return false;
}
}  // namespace class_FtpSession
}  // namespace glue
