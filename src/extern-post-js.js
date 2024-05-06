export class LainNotInitializedError extends Error {
    constructor() {
        super('Module is not yet initialized. Call init() before running.');
    }
}
export class LainCanvasNotFoundError extends Error {
    constructor(selector) {
        super(`Failed to find canvas for selector ${selector}.`);
    }
}

class Bootleg extends EventTarget {
    constructor() {
        super();
        this.module = null;
    }

    #ensureInitialized() {
        if (!this.module) throw new LainNotInitializedError();
    }

    #ensureCanvases() {
        [this.module.lainMainWindowSelector, this.module.lainMinigameWindowSelector].forEach(selector => {
            let elem = null;
            try {
                elem = document.querySelector(selector);
            } catch (e) {
                const err = LainCanvasNotFoundError(selector);
                err.cause = e;
                throw err;
            }
            if (!elem) throw new LainCanvasNotFoundError(selector);
        });
    }

    async init(options) {
        this.module = await Module({
            locateFile: (path, prefix) => {
                if (path.endsWith('.wasm') && options?.wasmPath)
                    return options.wasmPath;
                if (path.endsWith('.data') && options?.dataPath)
                    return options.dataPath;
                return prefix + path;
            },
            lainMainWindowSelector: options?.mainWindow ?? '#main',
            lainMinigameWindowSelector: options?.minigameWindow ?? '#minigame',
            lainVideoUrl: options?.moviePath ?? 'lain_mov.webm',
            lainOnWindowClose: (isMain) => {
                const detail = { isMain };
                this.dispatchEvent(new CustomEvent(`${isMain ? 'main' : 'minigame'}WindowClose`, { detail }));
                this.dispatchEvent(new CustomEvent('windowClose', { detail }));
            },
            lainOnWindowOpen: (isMain, title) => {
                const detail = { title, isMain };
                this.dispatchEvent(new CustomEvent(`${isMain ? 'main' : 'minigame'}WindowOpen`, { detail }));
                this.dispatchEvent(new CustomEvent(`windowOpen`, { detail }));
            }
        });
    }

    start() {
        this.#ensureInitialized();
        this.#ensureCanvases();
        return this.module._main();
    }

    closeMainWindow() {
        this.#ensureInitialized();
        return this.module._close_main_window();
    }

    closeMinigameWindow() {
        return this.module._close_minigame_window();
    }
}

export const LainBootleg = new Bootleg();
