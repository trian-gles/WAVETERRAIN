![waveterrain](https://user-images.githubusercontent.com/69212477/146979019-3cb75fd7-74c2-4b27-ac05-e9f1f727ca4d.png)

## ABOUT
A synthesizer which traveses a circular path on a 3d plane to generate a waveform.

## USAGE
Make sure that package.conf points to the appropriate Makefile on building

Due to the the nature of wave terrain synthesis, a DC offset will likely be present,
notice the DCBLOCK usage in the demo scorefile.

In the `WAVETABLE::f` funtion try inputting different terrain functions.


Args:
- 0 inskip
- 1 duration
- 2 amplitude
- 3 frequency
- 4 radius
- 5 centerx
- 6 centery
- 7 wave terrain width (terrain area = width^2)

fields 2, 3, 4, 5 and 6 can receive dynamic updates from a table or elsewhere

## TODO
- Set up additional terrain functions
- Set up additional path functions
