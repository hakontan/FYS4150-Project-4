import numpy as np 
import matplotlib.pyplot as plt

T1_Dis_data = np.loadtxt("P_T1_MC1e7_Disordered.txt", skiprows = 2)
T1_Ord_data = np.loadtxt("P_T1_MC1e7_Ordered.txt", skiprows = 2)
T24_Dis_data = np.loadtxt("P_T24_MC1e7_Disordered.txt", skiprows = 2)
T24_Ord_data = np.loadtxt("P_T24_MC1e7_Ordered.txt", skiprows = 2)
E1_Dis = T1_Dis_data[ :, 0]
E1_Ord = T1_Ord_data[ :, 0]
E24_Dis = T24_Dis_data[ :, 0]
E24_Ord = T24_Ord_data[ :, 0]
"""
M1_Dis = T1_Dis_data[ :, 1]
M1_Ord = T1_Ord_data[ :, 1]
M24_Dis = T24_Dis_data[ :, 1]
M24_Ord = T24_Ord_data[ :, 1]

flip1_Dis = T1_Dis_data[ :, 2]
flip1_Ord = T1_Ord_data[ :, 2]
flip24_Dis = T24_Dis_data[ :, 2]
flip24_Ord = T24_Ord_data[ :, 2]
"""
MC = np.arange(1, len(E1_Dis) + 1, 1)
E1_Dis_mean = np.cumsum(E1_Dis)/(MC * 400)
E1_Ord_mean = np.cumsum(E1_Ord)/(MC * 400)
E24_Dis_mean = np.cumsum(E24_Dis)/(MC * 400)
E24_Ord_mean = np.cumsum(E24_Ord)/(MC * 400)

plt.plot(MC[:int(1e4)], E24_Dis_mean[:int(1e4)], label = r"$T = 2.4, Disordered$")
plt.legend(loc = 0)
plt.figure()
plt.plot(MC[:int(1e4)], E24_Ord_mean[:int(1e4)], label = r"$T = 2.4, Ordered$")
plt.legend(loc = 0)
plt.figure()
plt.plot(MC[:int(1e4)], E1_Dis_mean[:int(1e4)], label = r"$T = 1, Disordered$")
plt.legend(loc = 0)
plt.figure()
plt.legend(loc = 0)
plt.plot(MC[:int(1e4)], E1_Ord_mean[:int(1e4)], label = r"$T = 1, Ordered$")
plt.legend(loc = 0)

bins24 = np.arange(np.min(E24_Dis[int(5e3):] / 400), np.max(E24_Dis[int(5e3):] / 400), 4  / 400)
bins1 = np.arange(np.min(E1_Dis[int(5e3):] / 400), np.max(E1_Dis[int(5e3):] / 400), 4  / 400)
plt.figure()
plt.hist(E24_Dis[int(5e3):] / 400, bins = bins24 , density= True)
plt.figure()
plt.hist(E1_Dis[int(5e3):] / 400, bins = bins1 , density= True)
plt.show()