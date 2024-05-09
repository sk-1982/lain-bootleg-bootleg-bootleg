import './App.css';
import { LainBootleg } from 'lain-bootleg-bootleg-bootleg';
import lainBootlegWasm from 'lain-bootleg-bootleg-bootleg/lain-bootleg-bootleg.wasm';
import lainBootlegData from 'lain-bootleg-bootleg-bootleg/lain-bootleg-bootleg.data';
import lainMov from 'lain-bootleg-bootleg-bootleg/lain_mov.webm';
import { useLayoutEffect, useState } from 'react';

function App() {
  const [minigameWindowTitle, setMinigameWindowTitle] = useState(null);
  const [mainWindowTitle, setMainWindowTitle] = useState(null);
  const [initialized, setInitialized] = useState(false);

  useLayoutEffect(() => {
    const windowCloseListener = data => {
      if (data.detail.isMain) {
        setMainWindowTitle(null);
      } else {
        setMinigameWindowTitle(null);
      }
    };

    const windowOpenListener = data => {
      if (data.detail.isMain)
        setMainWindowTitle(data.detail.title);
      else
        setMinigameWindowTitle(data.detail.title);
    };

    LainBootleg.addEventListener('windowOpen', windowOpenListener);
    LainBootleg.addEventListener('windowClose', windowCloseListener);

    LainBootleg.init({
      wasmPath: lainBootlegWasm,
      dataPath: lainBootlegData,
      moviePath: lainMov,
      mainWindow: '#main',
      minigameWindow: '#minigame'
    }).then(() => {
      LainBootleg.start();
      setInitialized(true);
    });

    return () => {
      LainBootleg.removeEventListener('windowClose', windowCloseListener);
      LainBootleg.removeEventListener('windowOpen', windowOpenListener);
      if (LainBootleg.initialized)
        LainBootleg.closeMainWindow();
    };
  }, []);

  return (
    <div className="App">
      {mainWindowTitle === null && minigameWindowTitle === null && initialized && <button onClick={() => LainBootleg.start()}>Start Lain Bootleg</button>}
      <div className="container" style={{ display: mainWindowTitle !== null ? 'flex' : 'none' }}>
        <div className="title-bar">
          <span className="title">{mainWindowTitle}</span>
          <button onClick={() => LainBootleg.closeMainWindow()}>&#10006;</button>
        </div>
        <canvas id="main"></canvas>
      </div>
      <div className="container" style={{ display: minigameWindowTitle !== null ? 'flex' : 'none' }}>
        <div className="title-bar">
          <span className="title">{minigameWindowTitle}</span>
          <button onClick={() => LainBootleg.closeMinigameWindow()}>&#10006;</button>
        </div>
        <canvas id="minigame"></canvas>
      </div>
    </div>
  );
}

export default App;
