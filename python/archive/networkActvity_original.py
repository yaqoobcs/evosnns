# -*- coding: utf-8 -*-
"""
Created on Wed Nov 15 13:23:34 2017

@author: YAQOOB
"""

import os
import numpy as np
import matplotlib

import matplotlib.mlab as mlab
import matplotlib.pyplot as plt
import scipy.stats as stats

import utils


def makeplot(x,  fname, output_path):
    if len(x) > 605:
        clockVal = len(x) - 30
        skipVal = 0
        gWidth = 30
    else:
        clockVal = len(x) - 2
        skipVal = 50  # 22*5-6
        gWidth = 36
    # skipVal=0
    # clockVal=350
    fig, (ax1, ax2, ax3, ax4, ax5, ax6, ax7, ax8, ax9, ax10, ax11, ax12, ax13) = (
        plt.subplots(13, 1, sharex=True, sharey=False, figsize=(gWidth, 18))
    )
    # clockVal= len(x)-2 #195
    clock = x[:, 0][skipVal:clockVal]
    A = x[:, 2][skipVal:clockVal]
    B = x[:, 3][skipVal:clockVal]
    C = x[:, 4][skipVal:clockVal]
    D = x[:, 5][skipVal:clockVal]
    E = x[:, 6][skipVal:clockVal]
    F = x[:, 7][skipVal:clockVal]
    N0 = x[:, 8][skipVal:clockVal]
    N1 = x[:, 9][skipVal:clockVal]
    N2 = x[:, 10][skipVal:clockVal]
    N3 = x[:, 11][skipVal:clockVal]
    N4 = x[:, 12][skipVal:clockVal]
    N5 = x[:, 13][skipVal:clockVal]
    output = x[:, 1][skipVal:clockVal]

    #    std = np.std(x)
    #    mean = np.mean(x)
    #    plt.plot(norm.pdf(x,mean,std))
    #    plt.hist(x,normed=True)
    #    x.sort()
    #    xmean = np.mean(x)
    #    xstd = np.std(x)
    #    pdf = stats.norm.pdf(x, xmean, xstd)
    #    plt.plot(x, pdf)

    #    fig = plt.figure()
    #    fig.text(.5, -0.1, 'txt', ha='center')
    padVal = 35
    fSize = 20
    ax1.plot(clock, A, "k-")
    ax1.set_ylabel("input A", rotation=0, fontsize=fSize, labelpad=padVal)
    ax2.plot(clock, B, "k-")
    ax2.set_ylabel("input B", rotation=0, fontsize=fSize, labelpad=padVal)
    ax3.plot(clock, C, "k-")
    ax3.set_ylabel("input C", rotation=0, fontsize=fSize, labelpad=padVal)
    ax4.plot(clock, D, "k-")
    ax4.set_ylabel("input D", rotation=0, fontsize=fSize, labelpad=padVal)
    ax5.plot(clock, E, "k-")
    ax5.set_ylabel("input E", rotation=0, fontsize=fSize, labelpad=padVal)
    ax6.plot(clock, F, "k-")
    ax6.set_ylabel("input F", rotation=0, fontsize=fSize, labelpad=padVal)

    ax7.plot(clock, N0, "m-")
    ax7.set_ylabel("N5", rotation=0, fontsize=fSize, labelpad=padVal)
    ax8.plot(clock, N1, "m-")
    ax8.set_ylabel("N4", rotation=0, fontsize=fSize, labelpad=padVal)
    ax9.plot(clock, N2, "m-")
    ax9.set_ylabel("N3", rotation=0, fontsize=fSize, labelpad=padVal)
    ax10.plot(clock, N3, "m-")
    ax10.set_ylabel("N2\nLock", rotation=0, fontsize=fSize, labelpad=padVal)
    ax11.plot(clock, N4, "m-")
    ax11.set_ylabel("N1\nSwitch", rotation=0, fontsize=fSize, labelpad=padVal)
    ax12.plot(clock, N5, "m-")
    ax12.set_ylabel("N0\nAccept", rotation=0, fontsize=fSize, labelpad=padVal)

    ax13.plot(clock, output, "g-")
    ax13.set_ylabel("Output", rotation=0, fontsize=fSize, labelpad=padVal)
    ax13.set_xlabel("Time [ms]", fontsize=fSize)
    #    plt.title('Voltage traces of network with noise vs. without noise')
    #    plt.subplot(3,1,2)
    #    plt.plot(clock,valNoise0, 'r-',label='fitness ')

    matplotlib.rc("xtick", labelsize=18)
    matplotlib.rc("ytick", labelsize=18)

    miny = -100
    maxy = 0
    # ax4.set_ylim([miny, maxy])
    # ax5.set_ylim([miny, maxy])
    # ax6.set_ylim([miny, maxy])
    # ax7.set_ylim([miny, maxy])

    #    plt.tight_layout()

    #
    #    plt.xlabel('Time [ms]')
    #    plt.ylabel('Voltage [mV]')
    #    ax1.set_xlabel('Vresting EL')
    # Make the y-axis label, ticks and tick labels match the line color.
    #    ax1.set_ylabel('fitness', color='b')
    #    ax1.tick_params('y', colors='b')
    #
    #    ax2 = ax1.twinx()
    ##    s2 = np.sin(2 * np.pi * t)
    #    ax2.plot(noise, correct, 'g.',label='TP')
    #    ax2.plot(noise, wrong, 'r.',label='TN')
    #    ax2.set_ylabel('Accuracy', color='g')
    #    ax2.tick_params('y', colors='r')

    #    fig.tight_layout()
    #    fig.legend(numpoints=1,             #Set the number of markers in label
    #           loc=('upper left'))

    #    plt.plot(noise,fitness,'b^')
    #    plt.plot(noise,correct,'g.',label='TP')
    #    plt.plot(noise,wrong,'r.',label='TN')
    #    plt.legend(numpoints=1,             #Set the number of markers in label
    #           loc=('upper left'))

    #    prob_over_2 = stats.norm.sf(x=2,loc = 0,scale= xstd)
    #    prob_under_minus2 = stats.norm.cdf(x=-2,loc = 0,scale= xstd)
    ##
    ##    prob_under_less_than2 = stats.norm.cdf(x=2,loc = 0,scale= 2)
    ##    prob_under_minus2 = stats.norm.cdf(x=-2,loc = 0,scale= 2)
    #    prob_1std_dev=1.0-(prob_over_2+prob_under_minus2)
    #    plt.text(x=-1, y=0.03, s= round(prob_1std_dev,5))
    #    plt.text(x=-3.6, y=0.03, s= round(prob_under_minus2,3))
    #    plt.text(x=2.2, y=0.03, s= round(prob_over_2,3))
    #
    #    plt.text(x=-8, y = 0.18,s='std dev='+str(round(xstd,3)));
    #    plt.text(x=-8, y = 0.160,s='mean='+str(round(xmean,3)));
    #
    #    plt.title('Adding 2mv Guassian Noise' + fname)
    #    plt.axvline(x=-2, color='g', linestyle='--', alpha = 0.3)
    #    plt.axvline(x=2, color='g', linestyle='--', alpha = 0.3)
    #    plt.axhline(y=0.120, color='r', linestyle='--')
    ##    plt.xlabel('Noise to Network (Vrest)')
    ##    plt.ylabel('Fitness')
    #    plt.grid(True)#,which='major',color='k')
    #    plt.minorticks_on()

    basename = os.path.basename(fname).split(".")[0]
    # plt.savefig(os.path.join(output_path, basename + ".png"), bbox_inches="tight", dpi=120)
    # plt.savefig("plot.png",bbox_inches='tight',dpi=300)
    plt.show()
    plt.close()

    return



def main():
    rootDir = os.getcwd()
    data_source_dir = os.path.join(rootDir, "..", "outputs3")
    output_path = os.path.join(data_source_dir, "plots")
    if not os.path.exists(output_path):
        os.makedirs(output_path)

    print(data_source_dir)
    network_activity_files = utils.list_files_with_activity_network(data_source_dir)
    size6_networks = [f for f in network_activity_files if "Top_6" in f]
    for file_name in size6_networks:
        print("In the Directory: %s" % file_name)
        x = np.loadtxt(file_name, "float")
        makeplot(x, file_name, output_path)


if __name__ == "__main__":
    main()
