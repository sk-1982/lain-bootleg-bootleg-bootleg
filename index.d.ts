declare module 'lain-bootleg-bootleg-bootleg' {
    export interface LainBootlegInitOptions {
        wasmPath?: string,
        dataPath?: string,
        moviePath?: string,
        mainWindow?: string,
        minigameWindow?: string
    }

    export interface LainWindowCloseEvent<T extends boolean = boolean> extends CustomEvent<{ isMain: T }> {}
    export interface LainWindowOpenEvent<T extends boolean = boolean> extends CustomEvent<{ isMain: T, title: string }> {}

    type EventTypes = {
        mainWindowClose: LainWindowCloseEvent<true>,
        minigameWindowClose: LainWindowCloseEvent<false>,
        windowClose: LainWindowCloseEvent,
        mainWindowOpen: LainWindowOpenEvent<true>,
        minigameWindowOpen: LainWindowOpenEvent<false>,
        windowOpen: LainWindowOpenEvent
    };

    type EventListener<T> = ((event: T) => void) | { handleEvent: (event: T) => void } | null;

    class Bootleg {
        private constructor();

        init(options?: LainBootlegInitOptions): Promise<void>;
        start(): void;
        closeMainWindow(): void;
        closeMinigameWindow(): void;

        get initialized(): boolean;

        addEventListener<T extends keyof EventTypes>(type: T, callback: EventListener<EventTypes[T]>, options?: AddEventListenerOptions | boolean): void;
        removeEventListener<T extends keyof EventTypes>(type: T, callback: EventListener<EventTypes[T]>, options?: EventListenerOptions | boolean): void;
    }

    export const LainBootleg: Bootleg;

    export class LainNotInitializedError extends Error {
        constructor();
    }

    export class LainCanvasNotFoundError extends Error {
        constructor(selector: string);
    }
}
