import numpy as np
from scipy.optimize import curve_fit

def func(x, a, b, c):
    return a * x * np.log2(x) + b * np.log2(x) + c

xdata = [100,
1000,
10000,
50000,
100000,
300000,
500000,
700000,
1000000,
1300000,
1500000,
1700000,
2000000
]

xdata = np.array(xdata)

ydata = [0.011159,
0.011739,
0.016248,
0.036262,
0.074812,
0.270958,
0.480135,
0.702309,
1.065305,
1.436483,
1.705633,
1.995863,
2.401319
]

ydata = np.array(ydata)

popt, pcov = curve_fit(func, xdata, ydata)
a, b, c = popt
print(f"{a} nlgn + {b} lgn + {c}")

#calculate predicted values
y_pred = func(xdata, a, b, c)

#calculate R^2

ss_res = np.sum((ydata - y_pred) ** 2)
ss_tot = np.sum((ydata - np.mean(ydata)) ** 2)
r_squared = 1 - (ss_res / ss_tot)

print(f"R² = {r_squared:.4f}")
