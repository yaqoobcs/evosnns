import os
import numpy as np
import matplotlib

import matplotlib.mlab as mlab
import matplotlib.pyplot as plt
import scipy.stats as stats


def plot(x, fname):
    # Determine plotting window based on data length
    if len(x) > 605:
        clockVal = len(x) - 30
        skipVal = 0
        gWidth = 30
    else:
        clockVal = len(x) - 2
        skipVal = 0
        gWidth = 20

    # Create figure with 5 subplots (1 for inputs, 3 for neurons, 1 for output)
    fig, (ax_input, ax_n0, ax_n1, ax_n2, ax_output) = plt.subplots(
        5, 1, sharex=False, sharey=False, figsize=(gWidth, 7)
    )

    # Extract data columns
    clock = x[:, 0][skipVal:clockVal]
    A = x[:, 2][skipVal:clockVal]
    B = x[:, 3][skipVal:clockVal]
    C = x[:, 4][skipVal:clockVal]
    N0 = x[:, 7][skipVal:clockVal]
    N1 = x[:, 8][skipVal:clockVal]
    N2 = x[:, 9][skipVal:clockVal]
    output = x[:, 1][skipVal:clockVal]

    # Styling parameters
    padVal = 0
    fSize = 20
    lwid = 2

    # Plot inputs (A, B, C)
    ax_input.plot(clock, A, 'k-', linewidth=lwid, label='A')
    ax_input.plot(clock, B, 'm-', linewidth=lwid, label='B')
    ax_input.plot(clock, C, 'r-', linewidth=lwid, label='C')
    ax_input.set_ylabel('Input', rotation=0, fontsize=fSize, labelpad=padVal)
    ax_input.spines['top'].set_visible(False)
    ax_input.spines['right'].set_visible(False)
    ax_input.spines['left'].set_visible(False)
    ax_input.spines['bottom'].set_visible(False)
    ax_input.get_yaxis().set_ticks([])
    ax_input.get_xaxis().set_ticks([])

    # Plot N0
    ax_n0.plot(clock, N0, 'm-')
    ax_n0.set_ylabel('N0', rotation=0, fontsize=fSize, labelpad=padVal)
    ax_n0.spines['top'].set_visible(False)
    ax_n0.spines['right'].set_visible(False)
    ax_n0.spines['left'].set_visible(False)
    ax_n0.spines['bottom'].set_visible(False)
    ax_n0.get_yaxis().set_ticks([])
    ax_n0.get_xaxis().set_ticks([])

    # Plot N1
    ax_n1.plot(clock, N1, 'm-')
    ax_n1.set_ylabel('N1', rotation=0, fontsize=fSize, labelpad=padVal)
    ax_n1.spines['top'].set_visible(False)
    ax_n1.spines['right'].set_visible(False)
    ax_n1.spines['left'].set_visible(False)
    ax_n1.spines['bottom'].set_visible(False)
    ax_n1.get_yaxis().set_ticks([])
    ax_n1.get_xaxis().set_ticks([])

    # Plot N2
    ax_n2.plot(clock, N2, 'm-')
    ax_n2.set_ylabel('N2', rotation=0, fontsize=fSize, labelpad=padVal)
    ax_n2.spines['top'].set_visible(False)
    ax_n2.spines['right'].set_visible(False)
    ax_n2.spines['left'].set_visible(False)
    ax_n2.spines['bottom'].set_visible(False)
    ax_n2.get_yaxis().set_ticks([])
    ax_n2.get_xaxis().set_ticks([])

    # Plot output
    ax_output.plot(clock, output, 'g-')
    ax_output.set_ylabel('Output', rotation=0, fontsize=fSize, labelpad=padVal)
    ax_output.set_xlabel('Time [ms]', fontsize=fSize)
    ax_output.spines['top'].set_visible(False)
    ax_output.spines['right'].set_visible(False)
    ax_output.spines['left'].set_visible(False)
    ax_output.get_yaxis().set_ticks([])
    ax_output.set_xticks(np.arange(0, len(clock) + 1, 100))

    # Set tick label sizes
    matplotlib.rc('xtick', labelsize=18)
    matplotlib.rc('ytick', labelsize=18)

    # Set y-axis limits for input plot
    miny = -98
    maxy = 0
    ax_input.set_ylim([miny, maxy])

    # Save and display
    plt.savefig(fname + '.png', bbox_inches='tight', dpi=120)
    plt.show()
    plt.close()

    return


# Main execution code
rootDir = os.getcwd()
for dirName, subdirList, fileList in os.walk(rootDir):
    print("In the Directory: %s" % dirName)
    for fname in fileList:
        if fname.endswith('.dat'):
            x = np.loadtxt(fname, 'float')
            plot(x, fname)