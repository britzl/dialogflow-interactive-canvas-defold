#pragma once

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_HTML5)

typedef void (*OnCanvasCallback)(const char* command, const char* data);


extern "C" {
    void InteractiveCanvas_PlatformInitialize(OnCanvasCallback callback);
}

#endif
