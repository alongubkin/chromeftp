#ifndef GLUE_GLOBALS_GLUE_H__
#define GLUE_GLOBALS_GLUE_H__

#include <string.h>
#include <string>
#include <npapi.h>
#include <npruntime.h>
#include "common.h"
#include "static_object.h"

namespace glue {

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


glue::globals::NPAPIObject *CreateStaticNPObject(NPP npp);

}  // namespace glue

#endif  // GLUE_GLOBALS_GLUE_H__
