
#include "plugin_main.h"
#include "globals_glue.h"
#include "ftpsession_glue.h"

namespace glue {
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
enum {
  SCOPE_FTP_SESSION,
  NUM_NAMESPACE_IDS
};
static NPIdentifier namespace_ids[NUM_NAMESPACE_IDS];
static const NPUTF8 *namespace_names[NUM_NAMESPACE_IDS] = {
  "FtpSession"
};
uint32_t GetStaticPropertyCount() {
  return 0 + 0 + NUM_NAMESPACE_IDS;
}
static bool StaticEnumeratePropertyEntries(NPObject *header,
NPIdentifier **value,
uint32_t *count) {
  *count = 0;
  glue::globals::NPAPIObject *object =
  static_cast<glue::globals::NPAPIObject *>(header);
  NPP npp = object->npp();
  GLUE_SCOPED_PROFILE(npp, "${Class}::StaticEnumeratePropertyEntries", prof);
  *count += NUM_NAMESPACE_IDS;
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
  memcpy(output, namespace_ids,
  NUM_NAMESPACE_IDS * sizeof(NPIdentifier));
  output += NUM_NAMESPACE_IDS;
}
static void InitializeStaticIds(NPP npp) {
  NPN_GetStringIdentifiers(namespace_names, NUM_NAMESPACE_IDS,
  namespace_ids);
glue::class_FtpSession::InitializeGlue(npp);
}
glue::globals::NPAPIObject *CreateRawStaticNPObject(NPP npp) {
  GLUE_PROFILE_START(npp, "createobject");
  glue::globals::NPAPIObject *object =
  static_cast<glue::globals::NPAPIObject *>(
  NPN_CreateObject(npp, &static_npclass));
  GLUE_PROFILE_STOP(npp, "createobject");
object->AllocateNamespaceObjects(NUM_NAMESPACE_IDS);
object->set_names(namespace_ids);

object->SetNamespaceObject(SCOPE_FTP_SESSION,
glue::class_FtpSession::CreateRawStaticNPObject(npp));
  return object;
}
void RegisterObjectBases(glue::globals::NPAPIObject *namespace_object,
glue::globals::NPAPIObject *root_object) {

{
  glue::globals::NPAPIObject *object =
  namespace_object->GetNamespaceObjectByIndex(SCOPE_FTP_SESSION);
  glue::class_FtpSession::RegisterObjectBases(object, root_object);
}
}

namespace class_FtpSession {
glue::globals::NPAPIObject *GetStaticNPObject(
glue::globals::NPAPIObject *root_object) {
  glue::globals::NPAPIObject *parent =
  glue::GetStaticNPObject(root_object);
  return parent->GetNamespaceObjectByIndex(SCOPE_FTP_SESSION);
}
}  // namespace class_FtpSession
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
  GLUE_SCOPED_PROFILE(npp, "${Class}::StaticInvokeDefault", prof);
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
  GLUE_PROFILE_START(npp, std::string("${Class}::StaticInvokeEntry(") +
  (id.text() ? id.text() : "") + ")");
  bool success = StaticInvoke(object, npp, name, args, argCount, result,
  &error);
  GLUE_PROFILE_STOP(npp, std::string("${Class}::StaticInvokeEntry(") +
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
  GLUE_PROFILE_START(npp, std::string("${Class}::StaticGetPropertyEntry(") +
  (id.text() ? id.text() : "") + ")");
  bool success = StaticGetProperty(object, npp, name, variant, &error);
  GLUE_PROFILE_STOP(npp, std::string("${Class}::StaticGetPropertyEntry(") +
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
  GLUE_PROFILE_START(npp, std::string("${Class}::StaticSetPropertyEntry(") +
  (id.text() ? id.text() : "") + ")");
  bool success = StaticSetProperty(object, npp, name, variant, &error);
  GLUE_PROFILE_STOP(npp, std::string("${Class}::StaticSetPropertyEntry(") +
  (id.text() ? id.text() : "") + ")");
  if (!success && error) {
    glue::globals::SetLastError(npp, error);
  }
  return success;
}
bool StaticInvoke(glue::globals::NPAPIObject *object,
NPP npp,
NPIdentifier name,
const NPVariant *args,
uint32_t argCount,
NPVariant *result,
const char **error_handle) {
  GLUE_SCOPED_PROFILE(npp, "${Class}::StaticInvoke", prof);
  bool success = true;
  return false;
}
bool StaticGetProperty(glue::globals::NPAPIObject *object,
NPP npp,
NPIdentifier name,
NPVariant *variant,
const char **error_handle) {
  GLUE_SCOPED_PROFILE(npp, "${Class}::StaticGetProperty", prof);
  bool success = true;
  success = glue::globals::GetProperty(object, name, variant);
  return success;
}
bool StaticSetProperty(glue::globals::NPAPIObject *object,
NPP npp,
NPIdentifier name,
const NPVariant *variant,
const char **error_handle) {
  GLUE_SCOPED_PROFILE(npp, "${Class}::StaticSetProperty", prof);
  bool success = true;
  if (glue::globals::SetProperty(object, name, variant)) return true;
  return false;
}
static bool StaticHasMethod(NPObject *header, NPIdentifier name) {
  DebugScopedId id(name);  // debug helper
  glue::globals::NPAPIObject *object =
  static_cast<glue::globals::NPAPIObject *>(header);
  NPP npp = object->npp();
  GLUE_SCOPED_PROFILE(npp, std::string("${Class}::StaticHasMethod(") +
  (id.text() ? id.text() : "") + ")", prof);
  return false;
}
static bool StaticHasProperty(NPObject *header, NPIdentifier name) {
  DebugScopedId id(name);  // debug helper
  glue::globals::NPAPIObject *object =
  static_cast<glue::globals::NPAPIObject *>(header);
  NPP npp = object->npp();
  GLUE_SCOPED_PROFILE(npp, std::string("${Class}::StaticHasProperty(") +
  (id.text() ? id.text() : "") + ")", prof);
  return glue::globals::HasProperty(header, name);
}
void InitializeGlue(NPP npp) {
  InitializeStaticIds(npp);
}

glue::globals::NPAPIObject *GetStaticNPObject(
glue::globals::NPAPIObject *root_object) {
  return root_object;
}

glue::globals::NPAPIObject *CreateStaticNPObject(NPP npp) {
  glue::globals::NPAPIObject *root_object = CreateRawStaticNPObject(npp);
  RegisterObjectBases(root_object, root_object);
  return root_object;
}

}  // namespace glue
