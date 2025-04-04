# CMSIS-DSP PID Demo

Simple demo of CMSIS-DSP PID f32 and q15 variants.

## License

[CC0-1.0 Universal](https://creativecommons.org/publicdomain/zero/1.0/)

## Build

Write a Makefile like:
```makefile
CPPFLAGS += -I/path/to/cmsis_6/CMSIS/Core/Include
CPPFLAGS += -I/path/to/cmsis-dsp/Include

pid: pid.o arm_pid_init_q15.o arm_pid_init_f32.o arm_float_to_q15.o
```

Copy the .c files for the corresponding .o dependencies next to pid.c and the Makefile, then `make`.

## Run

```sh
# usage: ./pid Kp Ki Kd in
./pid

# see output_p.8_i.02_d.1_e.2_n20.txt
./pid .8 .02 .1 .2

# see output_p.8_i.02_d.1_e-.2_n20.txt
./pid .8 .02 .1 -.2
```
