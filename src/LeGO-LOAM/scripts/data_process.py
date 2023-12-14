import numpy as np
import sys
def process_data(input_file, output_file):
    data = np.loadtxt(input_file)

    first_element_diff1 = data[:, 1] - data[0, 1]
    data[:, 1] = first_element_diff1

    first_element_diff1 = data[:, 2] - data[0, 2]
    data[:, 2] = first_element_diff1
    
    first_element_diff1 = data[:, 3] - data[0, 3]
    data[:, 3] = first_element_diff1
    

    np.savetxt(output_file, data, fmt='%.6f', delimiter=' ')

if __name__ == "__main__":

    input_filename = sys.argv[1]  
    output_filename = sys.argv[2]  

    process_data(input_filename, output_filename)
