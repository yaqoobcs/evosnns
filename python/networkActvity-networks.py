# -*- coding: utf-8 -*-
"""
Created on Wed Nov 15 13:23:34 2017

@author: YAQOOB
"""

import os
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import argparse

import utils


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-n",
        "--network",
        required=True,
        help="The signature of network activity file to use, e.g. Top_5 for network activity of files containing Top5 in filename",
    )
    parser.add_argument(
        "-s",
        "--data_source_dir",
        required=True,
        default="outputs-03-18",
        help="Path from where the matries are to be loaded from",
    )

    args = parser.parse_args()

    # ===-
    rootDir = os.getcwd()
    data_source_dir = os.path.join(rootDir, "..", args.data_source_dir)
    output_path = os.path.join(data_source_dir, "plots")
    if not os.path.exists(output_path):
        os.makedirs(output_path)

    print(data_source_dir)
    network_activity_files = utils.list_files_with_activity_network(data_source_dir)
    size7_networks = [f for f in network_activity_files if args.network in f]
    for file_name in size7_networks:
        print("In the Directory: %s" % file_name)
        x = np.loadtxt(file_name, "float")
        utils.makeplot2(x, file_name, output_path)
    print("Done")


if __name__ == "__main__":
    main()
