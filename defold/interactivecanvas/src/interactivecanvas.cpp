#include <dmsdk/sdk.h>
#include "interactivecanvas.h"
#include "luautils.h"

#define LIB_NAME "InteractiveCanvas"
#define MODULE_NAME "interactivecanvas"
#define DLIB_LOG_DOMAIN LIB_NAME

#if defined(DM_PLATFORM_HTML5)

lua_Listener canvasCallback;

static void InteractiveCanvas_OnCanvasCallback(const char* command, const char* data) {
	lua_State* L = canvasCallback.m_L;
	int top = lua_gettop(L);

	lua_pushlistener(L, canvasCallback);
	lua_pushstring(L, command);
	lua_pushstring(L, data);
	int ret = lua_pcall(L, 3, 0, 0);
	if (ret != 0) {
		lua_pop(L, 1);
	}

	assert(top == lua_gettop(L));
}

static int InteractiveCanvas_Initialize(lua_State* L) {
	int top = lua_gettop(L);

	luaL_checklistener(L, 1, canvasCallback);
	InteractiveCanvas_PlatformInitialize((OnCanvasCallback)InteractiveCanvas_OnCanvasCallback);

	assert(top == lua_gettop(L));
	return 0;
}


static const luaL_reg Module_methods[] = {
	{"initialize", InteractiveCanvas_Initialize},
	{0, 0}
};

static void LuaInit(lua_State* L) {
    int top = lua_gettop(L);
    luaL_register(L, MODULE_NAME, Module_methods);

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}
#endif


dmExtension::Result InitializeInteractiveCanvasExtension(dmExtension::Params* params) {
	#if defined(DM_PLATFORM_HTML5)
		LuaInit(params->m_L);
	#else
		printf("Extension %s is not supported\n", MODULE_NAME);
	#endif
	return dmExtension::RESULT_OK;
}

dmExtension::Result AppInitializeInteractiveCanvasExtension(dmExtension::AppParams* params) { return dmExtension::RESULT_OK; }
dmExtension::Result AppFinalizeInteractiveCanvasExtension(dmExtension::AppParams* params) { return dmExtension::RESULT_OK; }
dmExtension::Result FinalizeInteractiveCanvasExtension(dmExtension::Params* params) { return dmExtension::RESULT_OK; }
dmExtension::Result UpdateInteractiveCanvasExtension(dmExtension::Params* params) { return dmExtension::RESULT_OK; }

DM_DECLARE_EXTENSION(InteractiveCanvas, LIB_NAME, AppInitializeInteractiveCanvasExtension, AppFinalizeInteractiveCanvasExtension, InitializeInteractiveCanvasExtension, UpdateInteractiveCanvasExtension, 0, FinalizeInteractiveCanvasExtension)
