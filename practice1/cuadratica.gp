g(x)=c + d*x + e*x*x
fit g(x) 'bubble_1000_1000.dat' using 1:2 via c,d,e

# insert cuadratica : c=0.0024115 d=1.69078e-06 e=3.75933e-07; f(x) = 0.0024115 + 1.69078*10^(-6)*x + 3.75933*10^(-7)*x²
# bubble cuadratica : f(x) = 0.00226202 + 7.44039E-05 * x + 1.05902E-06 * x^2

