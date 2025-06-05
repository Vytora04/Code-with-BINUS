const menuOpen = document.getElementById('menu-open');
const menuClose = document.getElementById('menu-close');
const sidebar = document.querySelector('.container .sidebar');
const playButton = document.getElementById('play-button');
const audioPlayer = document.getElementById('audio-player');
const smallplaybutton = document.getElementById('small-play-button');
const smallaudioplay = document.getElementById('small-audio-play');

menuOpen.addEventListener('click', () => sidebar.style.left = '0');

menuClose.addEventListener('click', () => sidebar.style.left = '-100%');

// Play/pause functionality
smallplaybutton.addEventListener('click', () => {
    if (smallaudioplay.paused) {
        smallaudioplay.play();
    } else {
        smallaudioplay.pause();
    }
});

// Play/pause functionality
playButton.addEventListener('click', () => {
    if (audioPlayer.paused) {
        audioPlayer.play();
    } else {
        audioPlayer.pause();
    }
});