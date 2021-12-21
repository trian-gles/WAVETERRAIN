set_option("play = 0")

rtsetparams(44100, 2)
rtoutput("synth.wav")

load("./libWAVETERRAIN.so")


WAVETERRAIN(0, 3.5, 20000, 387.14, 1.3, 1, 0.5, 1024 )


