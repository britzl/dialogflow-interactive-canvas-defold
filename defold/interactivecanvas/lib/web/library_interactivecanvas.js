// https://kripken.github.io/emscripten-site/docs/porting/connecting_cpp_and_javascript/Interacting-with-code.html

var InteractiveCanvasLibrary = {
    $Context: {
        callback: null
    },

    InteractiveCanvas_PlatformInitialize: function(callback) {
        Context.callback = callback;
        var callbacks = {
            onUpdate: function(data) {
                try {
                    var command = data.command.toUpperCase();
                    var commandBuf = allocate(intArrayFromString(command), 'i8', ALLOC_STACK);
                    var dataBuf = allocate(intArrayFromString(JSON.stringify(data)), 'i8', ALLOC_STACK);
                    Runtime.dynCall("vii", callback, [commandBuf, dataBuf]);
                } catch (e) {
                    // do nothing, when no command is sent or found
                    console.log("callback onUpdate() no command found", e);
                }
            },
        };
        Module.interactiveCanvas.ready(callbacks);
    }
};

autoAddDeps(InteractiveCanvasLibrary, "$Context");
mergeInto(LibraryManager.library, InteractiveCanvasLibrary);
