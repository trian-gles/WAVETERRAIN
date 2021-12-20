set_option("play = 0")

rtsetparams(44100, 2)
rtoutput("synth.wav")

load("./libWAVETERRAIN.so")


WAVETERRAIN(0, 3.5, 20000, 387.14, 0.5, 0, 0,1024 )


