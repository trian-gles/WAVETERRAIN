set_option("play = 0")

rtsetparams(44100, 2)
rtoutput("synth.wav")

load("./libWAVETERRAIN.so")

centerx = maketable("line", "nonorm", 1024, 0, 0, 1, 0.4, 2, 0.5)


WAVETERRAIN(0, 7, 20000, 387.14, 0.5, centerx, 0.5, 1024 )


