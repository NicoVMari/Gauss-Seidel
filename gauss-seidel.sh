gcc gauss-seidel.c -o gauss-seidel -Wall -Wextra -Wconversion

./gauss-seidel sistemi/$1

gnuplot_script="gnuplot/$1"

if [ -e "$gnuplot_script" ]; then
    gnuplot -e "error_per_iteration='$gnuplot_script'; set term png; set output 'gnuplot/$1.png'; plot error_per_iteration with lines"
fi
