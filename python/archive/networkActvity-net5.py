# -*- coding: utf-8 -*-
"""
Created on Wed Nov 15 13:23:34 2017

@author: YAQOOB
"""

import os
import numpy as np
import matplotlib
import matplotlib.pyplot as plt

import utils

def main():
    rootDir = os.getcwd()
    data_source_dir = os.path.join(rootDir, "..", "outputs3")
    output_path = os.path.join(data_source_dir, "plots")
    if not os.path.exists(output_path):
        os.makedirs(output_path)

    print(data_source_dir)
    network_activity_files = utils.list_files_with_activity_network(data_source_dir)
    size6_networks = [f for f in network_activity_files if "Top_5" in f]
    for file_name in size6_networks:
        print("In the Directory: %s" % file_name)
        x = np.loadtxt(file_name, "float")
        utils.makeplot2(x, file_name, output_path)
    print("Done")

if __name__ == "__main__":
    main()
