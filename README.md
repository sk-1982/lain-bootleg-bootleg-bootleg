# lain-bootleg-bootleg-bootleg

An [emscripten](https://github.com/emscripten-core/emscripten) port of [lain-bootleg-bootleg](https://github.com/ad044/lain-bootleg-bootleg)

# Extracting assets

See the [original instructions](https://github.com/ad044/lain-bootleg-bootleg#extracting-assets) on how to extract assets.
Note that in addition to the original dependencies, you will also need to install [`ffmpeg`](https://ffmpeg.org/download.html) and add it to your path.

# Building

Before you build, you must have extracted the assets in the proper location by following 
the guide above. Make sure you have set up the [emscripten emsdk](https://emscripten.org/docs/getting_started/downloads.html#installation-instructions-using-the-emsdk-recommended)

## Dependencies

- [**emscripten**](https://emscripten.org/docs/getting_started/downloads.html#installation-instructions-using-the-emsdk-recommended)


## Compiling

1. `cd` into the repo
2. `mkdir build && cd build`
3. `emcmake cmake ..` (or `emcmake cmake -DDEBUG=1 ..` to create a debug build)
4. `emmake ninja`

This will produce `lain-bootleg-bootleg.mjs`, `lain-bootleg-bootleg.wasm`, and `lain-bootleg-bootleg.data`

# Running

The build process copies over an example page which can be served by running `npx http-server` in the build directory.

`lain-bootleg-bootleg.mjs` can be imported directly using a script tag or bundled using something like webpack. See the `example` directory for examples of either.

The files `lain-bootleg-bootleg.wasm`, `lain-bootleg-bootleg.data`, and `lain_mov.webm` will need to be served.

# Editing the save file

The save data is stored in [`localStorage`](https://developer.mozilla.org/en-US/docs/Web/API/Window/localStorage) under the key `lain-save`. See the [original project](https://github.com/ad044/lain-bootleg-bootleg#editing-the-save-file) for the format of the data.

# Libraries used

- [`GLFW`](https://github.com/pongasoft/emscripten-glfw)
- [`cJSON`](https://github.com/DaveGamble/cJSON)
- [`cvector`](https://github.com/eteran/c-vector)

# JavaScript API

```js
import { LainBootleg } from 'lain-bootleg-bootleg-bootleg';
```

### `LainBootleg.init(options?): Promise<void>`
Initialize lain-bootleg-bootleg-bootleg.

- `options.wasmPath?: string`: URL of the `lain-bootleg-bootleg.wasm` file. Defaults to `lain-bootleg-bootleg.wasm`
- `options.dataPath?: string`: URL of the `lain-bootleg-bootleg.data` file. Defaults to `lain-bootleg-bootleg.data`
- `options.moviePath?: string`: URL of the `lain_mov.webm` file. Defaults to `lain_mov.webm`
- `options.mainWindow: string`: Selector for the main window canvas. Defaults to `#main`. This canvas must remain in the DOM for the duration that the program will be run.
- `options.minigameWindow: string`: Selector for the minigame window canvas. Defaults to `#minigame`. This canvas must remain in the DOM for the duration that the program will be run.

### `LainBootleg.start(): void`
Start the main window.

### `LainBootleg.closeMainWindow(): void`
Close the main window. Implicitly closes the minigame window if it is open.

### `LainBootleg.closeMinigameWindow(): void`
Close the minigame window.

### `get LainBootleg.initialized(): boolean`
Get if lain-bootleg-bootleg-bootleg has been initialized.

## Events

### `mainWindowClose`, `minigameWindowClose`, `windowClose`
Fired when a window has closed.

- `event.detail.isMain: boolean`: Whether the window was the main window.

### `mainWindowOpen`, `minigameWindowOpen`, `windowOpen`
Fired when a window has opened.

- `event.detail.isMain: boolean`: Whether the window was the main window.
- `event.detail.title: string`: The title of the window.
