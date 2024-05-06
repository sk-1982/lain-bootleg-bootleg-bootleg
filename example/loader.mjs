import { LainBootleg } from './lain-bootleg-bootleg.mjs';

const mainWindow = document.querySelector('#main_window_container');
const minigameWindow = document.querySelector('#minigame_window_container');
const startButton = document.querySelector('#start_button');

await LainBootleg.init({
    mainWindow: '#main',
    minigameWindow: '#minigame'
});

mainWindow.querySelector('button').onclick = () => LainBootleg.closeMainWindow();
minigameWindow.querySelector('button').onclick = () => LainBootleg.closeMinigameWindow();
startButton.onclick = () => LainBootleg.start();

LainBootleg.addEventListener('windowClose', data => {
    (data.detail.isMain ? mainWindow : minigameWindow).style.display = 'none';
    if (data.detail.isMain) startButton.style.display = 'block';
});

LainBootleg.addEventListener('windowOpen', data => {
    const elem = (data.detail.isMain ? mainWindow : minigameWindow);
    elem.style.display = 'flex';
    elem.querySelector('.title').innerText = data.detail.title;
    if (data.detail.isMain) startButton.style.display = 'none';
});

LainBootleg.start();

// for access in debug console
window.LainBootleg = LainBootleg;
