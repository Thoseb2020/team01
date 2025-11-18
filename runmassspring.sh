#!/bin/bash

tend_relative=$1 #standard: 4
steps=$2 #standard: 100

cd build
./test_ode > ../demos/output_test_ode.txt $tend_relative $steps
cd ../demos
python3 plotmassspring.py --tend_relative $1 --steps $2
mv "Phase_plot.png" "plots/Phase_plot_$1 pi_$2 steps_.png"
mv "Time_evolution.png" "plots/Time_evolution_$1 pi_$2 steps_.png"
cd ..