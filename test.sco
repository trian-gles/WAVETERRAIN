set_option("play = 0")

rtsetparams(44100, 2)
rtoutput("synth.wav")

load("./libWAVETERRAIN.so")
load("DCBLOCK")

bus_config("libWAVETERRAIN", "aux 0-1 out")
bus_config("DCBLOCK", "aux 0-1 in", "out 0-1")

freq = maketable("line","nonorm", 1024, 0, 220, 4, 220, 5, 110, 7, 110)
amp = maketable("line", 1024, 0, 0, 1, 1, 20, 1, 21, 0)
centerx = maketable("line", "nonorm", 1024, 0, 0, 2, 0.4, 3, 0.5, 4, 0.5)

radius_freq = maketable("line", "nonorm", 1024, 0, 1, 1, 5.5)
radius = makeLFO("sine", radius_freq, 0.2)
dur = 8

WAVETERRAIN(0, dur, 20000 * amp, freq, 0.5 + radius, centerx, 0.5, 1024 )
DCBLOCK(0, 0, dur, 1.0)
