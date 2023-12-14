# coding=UTF-8
import sys
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# 格式：t x y z qx qy qz qw
if __name__ == '__main__':
    if len(sys.argv) != 3:
        print('Please input valid file : gt.txt traj.txt')
        exit(1)
    else:
        path1 = sys.argv[1]
        path_data1 = np.loadtxt(path1) # xyz
        path2 = sys.argv[2]
        path_data2 = np.loadtxt(path2) # x -z -y
        fig = plt.figure()
        ax = Axes3D(fig)
        ax.plot(path_data1[:, 1],path_data1[:, 2], path_data1[:, 3], c="r")
        # ax.plot(-path_data1[:, 2], path_data1[:, 1], -path_data1[:, 3])

        ax.plot(path_data2[:, 1], path_data2[:, 2], path_data2[:, 3], c="b")
        ax.set_zlim(-300,300)
        
        
        plt.title('3D path')
        plt.show()
        exit(1)
