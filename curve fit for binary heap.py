import numpy as np
from scipy.optimize import curve_fit

def func(x, a, b, c):
    return a * x * np.log2(x) + b * np.log2(x) + c

xdata = [10000,
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

ydata = [0.015838,
0.041567,
0.093359,
0.373116,
0.627796,
0.943792,
1.358386,
1.836380,
2.165029,
2.439514,
2.905247
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
