import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt


def binary_func(x, a, b, c):
    return a * x * np.log2(x) + b * np.log2(x) + c

def fibonacci_func(x,a,b):
    return a * x * np.log2(x) + b

def radix_func(x,a,b):
    return a*x + b

data_structure = "Binary heap"
func = radix_func

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

ydata = [0.010504,
0.011141,
0.017392,
0.049656,
0.114035,
0.420282,
0.736904,
0.922718,
1.335926,
1.818021,
2.092329,
2.343173,
2.770015
]

ydata = np.array(ydata)

y_max = [0.016492,
0.014723,
0.022371,
0.067964,
0.154432,
0.489784,
0.811645,
1.065223,
1.452919,
2.013250,
2.239903,
2.507806,
2.928803
]

y_max=np.array(y_max)

y_min = [0.009057,
0.009598,
0.015759,
0.044564,
0.103249,
0.403789,
0.715113,
0.898474,
1.288149,
1.598885,
1.848042,
2.038382,
2.472780
]

y_min = np.array(y_min)

popt, pcov = curve_fit(func, xdata, ydata)
a, b = popt

#calculate predicted values
y_pred = func(xdata, a, b)

#calculate R^2

ss_res = np.sum((ydata - y_pred) ** 2)
ss_tot = np.sum((ydata - np.mean(ydata)) ** 2)
r_squared = 1 - (ss_res / ss_tot)

print(f"R² = {r_squared:.4f}")


# plot
plt.figure(figsize=(10, 6))

# draw data points
# calc non-symetric uncertainties
yerr_lower = ydata - y_min
yerr_upper = y_max - ydata
yerr = np.array([yerr_lower, yerr_upper])

plt.errorbar(xdata, ydata, yerr=yerr, fmt='o', color='red', capsize=5, label='data points')

# create x values to plot line of best fit
x_smooth = np.linspace(min(xdata), max(xdata), 500)
y_smooth = func(x_smooth, a, b)

# plot line of best fit
plt.plot(x_smooth, y_smooth, 'b-', label=f'line of best fit: {a:.2e}·n·log₂n + {b:.2e}\nR²={r_squared:.3f}')

# add titles and legends
plt.xlabel('node count')
plt.ylabel('time')
plt.title(f'{data_structure} v.s. node count')
plt.legend()
plt.grid(True)

# show plot
plt.show()
