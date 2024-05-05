addToLibrary({
    preload_video: () => {
        if (Module.lainPreloadedVideo)
            return;
        console.log('preloading video...');
        const video = document.createElement('video');
        video.autoplay = false;
        video.preload = 'auto';
        video.src = 'lain_mov.webm';
        video.load();
        Module.lainPreloadedVideo = video;
        Module.lainVideoPlaying = false;
        Module.lainVideoTimeUpdate = false;
        Module.lainPreloadedVideo.addEventListener('playing', () => Module.lainVideoPlaying = true);
        Module.lainPreloadedVideo.addEventListener('timeupdate', () => Module.lainVideoTimeUpdate = true);
    },
    play_video: async () => {
        if (!Module.lainPreloadedVideo.paused) return;

        Module.lainPreloadedVideo.currentTime = 0;
        await Module.lainPreloadedVideo.play();
    },
    render_video: () => {
        if (!(Module.lainVideoPlaying && Module.lainVideoTimeUpdate)) return false;
        const gl = GL.currentContext.GLctx;
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGB, gl.UNSIGNED_BYTE, Module.lainPreloadedVideo);
        return Module.lainPreloadedVideo.ended;
    },
    stop_video: () => {
        Module.lainPreloadedVideo.pause();
    }
});
