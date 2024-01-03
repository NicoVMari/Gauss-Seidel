gcc gauss-seidel.c -o gauss-seidel -Wall -Wextra -Wconversion

./gauss-seidel sistemi/$1

gnuplot -e "error_per_iteration='gnuplot/$1'; set term png; set output 'gnuplot/$1.png'; plot error_per_iteration with lines"
