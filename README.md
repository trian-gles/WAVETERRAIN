# ABOUT
A synthesizer which traveses a circular path on a 3d plane to generate a waveform.

# USAGE
Make sure that package.conf points to the appropriate Makefile on building

Args:
0 inskip
1 duration
2 amplitude
3 frequency
4 radius
5 centerx
6 centery
7 wave terrain width (terrain area = width^2)

fields 2, 3, 4, 5 and 6 can receive dynamic updates from a table or elsewhere, though frequency currently doesn't work so well

# TODO
-Get dynamic frequency updates working
-Fix bus_config issues
-Set up additional terrain functions
-Set up additional path functions
