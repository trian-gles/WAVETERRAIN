set_option("play = 0")

rtsetparams(44100, 2)
rtoutput("synth.wav")

load("./libWAVETERRAIN.so")


amp = maketable("line", 1024, 0, 0, 1, 1, 20, 1, 21, 0)
centerx = maketable("line", "nonorm", 1024, 0, 0, 2, 0.4, 3, 0.5, 4, 0.5)
radius = makeLFO("sine", 5.5, 0.2)


WAVETERRAIN(0, 8, 20000 * amp, 220, 0.5 + radius, centerx, 0.5, 1024 )
