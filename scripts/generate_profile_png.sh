# !/bin/bash

gprof ./build/bin/Simulations gmon.out | gprof2dot -s | dot -Tpng -o profile.png