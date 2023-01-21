set terminal postscript eps color solid enhanced font "Times-Roman, 22"
set ylabel "Liczba operacji dominujacych"
set xlabel "Liczba elementow (n)"
set output "statystykaTest.ps"
f(x) = a*x*log(b*x)/log(2)
g(x) = x*log(x)/log(2)
fit f(x) "wynikiTestu.txt" u 1:2 via a,b
plot g(x) title 'zlozonosc podrecznikowa' w lines,\
 	   f(x) w lines, "wynikiTestu.txt" u 1:2 w points t 'stat'