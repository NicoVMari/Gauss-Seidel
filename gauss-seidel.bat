gcc gauss-seidel.c -o gauss-seidel -Wall -Wextra -Wconversion

gauss-seidel sistemi\%1

set "gnuplot_script=gnuplot\%1"

if exist %gnuplot_script% (
    gnuplot -e "error_per_iteration='%gnuplot_script%'; set term png; set output 'gnuplot\%1.png'; plot error_per_iteration with lines"
)