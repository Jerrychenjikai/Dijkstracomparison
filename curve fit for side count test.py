import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

def linear_fit(x,a,b):
    return a*x+b

data_structures=["Radix Heap","Fibonacci Heap","Binary Heap"]
colors = ['blue','red','orange']

x_data = [100000,
500000,
1000000,
3000000,
5000000,
7000000,
10000000,
13000000,
15000000,
17000000,
20000000,
23000000,
25000000
]

x_data = np.array(x_data)

y_data = [
    [
0.077867,
0.095788,
0.102990,
0.126728,
0.144345,
0.165904,
0.189316,
0.215948,
0.230598,
0.249434,
0.267973,
0.295364,
0.312030
     ],
    [
0.195221,
0.220683,
0.229384,
0.267808,
0.306980,
0.318633,
0.343272,
0.368163,
0.386158,
0.400929,
0.419753,
0.443011,
0.476907
     ],
    [
0.038589,
0.050153,
0.068787,
0.082988,
0.097289,
0.117080,
0.138549,
0.161084,
0.178064,
0.193719,
0.214478,
0.240334,
0.250110
    ]
]

y_data = np.array(y_data)

y_max = [
    [
0.092208,
0.126187,
0.127153,
0.158554,
0.177563,
0.215143,
0.248451,
0.267034,
0.284118,
0.319613,
0.346931,
0.350112,
0.408663
        ],
    [
0.209713,
0.299312,
0.269631,
0.365287,
0.425372,
0.486352,
0.555703,
0.445999,
0.455457,
0.558522,
0.697468,
0.554959,
0.732816
        ],
    [
0.053315,
0.064247,
0.068787,
0.111720,
0.126797,
0.148451,
0.167106,
0.206068,
0.222102,
0.231597,
0.247806,
0.297942,
0.323930
        ]
    ]

y_max = np.array(y_max)

y_min = [
    [
0.072902,
0.088602,
0.095624,
0.117321,
0.135640,
0.156082,
0.172919,
0.200419,
0.217083,
0.233525,
0.250113,
0.277571,
0.296134
        ],
    [
0.177608,
0.200439,
0.206206,
0.248281,
0.269528,
0.287038,
0.318429,
0.334525,
0.351065,
0.373879,
0.393451,
0.413798,
0.430250
        ],
    [
0.026666,
0.035140,
0.068787,
0.062838,
0.080139,
0.101998,
0.125108,
0.140227,
0.158728,
0.174102,
0.190757,
0.220825,
0.222893
        ]
    ]

y_min = np.array(y_min)


plt.figure(figsize=(10, 6))

for i in range(3):
    xdata = x_data
    ydata = y_data[i]
    ymax = y_max[i]
    ymin = y_min[i]
    data_structure = data_structures[i]
    
    popt, pcov = curve_fit(linear_fit, xdata, ydata)
    a, b = popt

    #calculate predicted values
    y_pred = linear_fit(xdata, a, b)

    #calculate R^2

    ss_res = np.sum((ydata - y_pred) ** 2)
    ss_tot = np.sum((ydata - np.mean(ydata)) ** 2)
    r_squared = 1 - (ss_res / ss_tot)

    print(f"R² = {r_squared:.4f}")


    # draw data points
    # calc non-symetric uncertainties
    yerr_lower = ydata - ymin
    yerr_upper = ymax - ydata
    yerr = np.array([yerr_lower, yerr_upper])

    plt.errorbar(xdata, ydata, yerr=yerr, fmt='.', color=colors[i], capsize=3, label=data_structures[i])

    # create x values to plot line of best fit
    x_smooth = np.linspace(min(xdata), max(xdata), 500)
    y_smooth = linear_fit(x_smooth, a, b)

    # plot line of best fit
    plt.plot(x_smooth, y_smooth, '-', label=f'{data_structures[i]}: {a:.2e}n + {b:.2e}\nR²={r_squared:.3f}', color = colors[i])

# add titles and legends
plt.xlabel('side count')
plt.ylabel('time')
plt.title('Radix, Fibonacci, Binary heap v.s. node count at 1e5 nodes')
plt.legend()
plt.grid(True)

# show plot
plt.show()


