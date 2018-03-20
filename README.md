# Capsule 3
Project designed to be a part of a digitally enhanced artistic representation organised by the [Bonjour Capsule](https://www.capsule.site/) association.

## Pitch
Let's glue a small mirror shard onto a speaker. Now let's play sound on that speaker and point a laser on the mirror shard.

![](https://thumbs.gfycat.com/CarefreeOffbeatIvorybackedwoodswallow-size_restricted.gif)

The goal of the project was to use this technique to make something beautiful and/or interactive.  
A part of the project was to use machine-learning to ask the computer to give us the sound needed to display a specific shape.  
Another part was to find a way to allow an audience to interact with the sound to modify the shapes.  
The science behind this is called [Lissajous curves](https://en.wikipedia.org/wiki/Lissajous_curve).

## Sound generation
The program WAVgen is written in C and was initially designed to produce .wav files to build a data set for the machine learning. It computes sound samples by using waveform formulas (sinusoidal, triangle, sawtooth, square), and randomize all the parameters to obtain the richest .wav files collection.  
It then evolved to be more runtime-oriented to be open to interactivity. For this purpose we needed to have hands on the audio generation during the execution of the program, so we used the Alsa library API that allowed me to send PCM audio buffers to the system audio output.  
A gamepad was first included to the setup thanks to the SDL2, and on the observation that the nicest geometrical shapes where created by the changing ratio of two sinusoidal soundwaves, we mapped the Y-axis of the two joysticks onto the two frequencies.  
[Nipal](https://github.com/nipal) refactored the program to make it handier and open to new features, and added a layer of interactivity by using the signals from [OpenBCI](http://openbci.com/) hardware, so a member from the audience equipped with electrodes could control the amplitudes of the signals by flexing arm muscles.
