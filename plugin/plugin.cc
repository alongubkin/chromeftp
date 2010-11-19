#include <npapi.h>

extern "C" {
  const char *NP_GetMIMEDescription(void) {
    return "application/x-chromeftp::ChromeFTP Utils";
  }

  NPError NP_GetValue(NPP instance, NPPVariable variable, void *value) {
    switch (variable) {
      case NPPVpluginNameString:
        *static_cast<const char **>(value) = "ChromeFTP Utils";
        break;
      case NPPVpluginDescriptionString:
        *static_cast<const char **>(value) = "Native utilities for ChromeFTP extension";
        break;
      default:
        return NPERR_INVALID_PARAM;
        break;
    }
    return NPERR_NO_ERROR;
  }
}
