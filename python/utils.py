import os
import numpy as np

# import matplotlib.mlab as mlab
# import scipy.stats as stats
import matplotlib.pyplot as plt


def get_gaussian2x(sample_x):
    return (
        2
        * (12 * np.exp(-6 * (((sample_x - 0.7) / 0.1) * ((sample_x - 0.7) / 0.1))) + 10)
    ) / 0.24


# return (1/(math.sqrt(2*np.pi*sigma)))*(np.exp(-(((sample_x-mu)*(sample_x-mu))/(2*s
# igma*sigma)))))
def get_gaussianx(sample_x):
    return (
        12 * np.exp(-6 * (((sample_x - 0.7) / 0.1) * ((sample_x - 0.7) / 0.1))) + 10
    ) / 0.24


def get_gaussianhalfx(sample_x):
    return (
        (12 * np.exp(-6 * (((sample_x - 0.7) / 0.1) * ((sample_x - 0.7) / 0.1))) + 10)
        / 2
    ) / 0.24


def plotFiringRate(x, fname):
    x_axis = x[:, 0]
    y_axis = x[:, 1] / 0.24  # firing rate for 240 ms

    hist_x = np.arange(0, 1, 0.01)
    hist_y = get_gaussianx(hist_x)
    hist_2y = get_gaussian2x(hist_x)
    hist_3y = get_gaussianhalfx(hist_x)
    left, width = 0.1, 0.75
    bottom, height = 0.1, 0.75
    bottom_h = left_h = left + width + 0.05
    rect_histx = [left, bottom_h + 0.05, width, 0.2]
    rect_scatter = [left, bottom, width, height]
    plt.figure(1, figsize=(8, 8))

    axHistx = plt.axes(rect_histx)

    axHistx.hist(
        x_axis, bins=100, histtype="bar", align="mid", label="input", alpha=0.9
    )
    axHistx.grid(True, which="major")
    axHistx.minorticks_on()

    axScatter = plt.axes(rect_scatter)

    axHistx.set_xlim(axScatter.get_xlim())
    # axHistx.xlabel('frequency')
    # axHist.setylim(axScatter.get_ylim())

    axScatter.scatter(
        x_axis,
        y_axis,
        color="g",
        cmap=plt.cm.get_cmap("hot"),
        linewidth=0.5,
        edgecolor="w",
        alpha=1,
    )
    # plotting the Standard Sigmoid Function
    axScatter.plot(hist_x, hist_y, marker="^", color="r", alpha=0.2, linewidth=0.8)
    axScatter.plot(hist_x, hist_2y, marker="^", color="b", alpha=0.2, linewidth=0.8)
    axScatter.plot(hist_x, hist_3y, marker="^", color="y", alpha=0.2, linewidth=0.8)
    plt.title("Generating Sigmoid Function for SNN response in " + fname)
    plt.xlabel("Input to Network")
    plt.ylabel("Firing Rate (hz)")
    # plt.axis([0,1,0,100])
    plt.grid(True, which="major", color="k")
    plt.minorticks_on()

    plt.savefig(fname + ".png", bbox_inches="tight", dpi=300)
    # plt.show()
    plt.close()
    return


def list_files_with_activity_network(directory):
    files_in_dir = os.listdir(directory)
    print(files_in_dir)
    return [
        os.path.join(directory, file)
        for file in files_in_dir
        if "network_activity" in file and ".txt" in file
    ]


def makeplot2(x, fname, output_path):
    num_signals = int((x.shape[1] - 2) / 2)
    # if not (3 <= num_signals <= 8):
    #     raise ValueError("The number of signals must be between 3 and 7.")

    # if len(x) > 605:
    #     clockVal = len(x) - 30
    #     skipVal = 0
    #     gWidth = 30
    # else:
    #     clockVal = len(x) - 2
    #     skipVal = 50
    #     gWidth = 36

    clockVal = len(x) - 2
    skipVal = 0
    gWidth = 36

    fig, axes = plt.subplots(
        2 * num_signals + 1, 1, sharex=True, figsize=(gWidth, 2 * (num_signals + 3))
    )
    clock = x[:, 0][skipVal:clockVal]
    input_signals = x[:, 2 : (num_signals + 2)][skipVal:clockVal]
    internal_signals = x[:, (num_signals + 2) :][skipVal:clockVal]

    input_labels = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K"][
        :num_signals
    ]  # Adjust for up to 7 signals, H'', H'', H'', H'', H'', H'', H''
    internal_labels = [f"N{k}" for k in range(0, num_signals)][::-1]
    for i, ax in enumerate(axes[0:num_signals]):
        print(f"{input_labels[i]}, using input signals at {i}")
        ax.plot(clock, input_signals[:, i], "k-")
        ax.set_ylabel(f"input {input_labels[i]}", rotation=0, fontsize=20, labelpad=35)

    for i, ax in enumerate(axes[num_signals:-1]):
        print(f"{internal_labels[i]}, using internal_signals at {i}")
        ax.plot(clock, internal_signals[:, i], "m-")
        ax.set_ylabel(f"{internal_labels[i]}", rotation=0, fontsize=20, labelpad=35)

    ax_output = axes[-1]
    output = x[:, 1][skipVal:clockVal]
    ax_output.plot(clock, output, "g-")
    ax_output.set_ylabel("Output", rotation=0, fontsize=20, labelpad=35)
    ax_output.set_xlabel("Time [ms]", fontsize=20)

    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    basename = os.path.basename(fname).split(".")[0]
    plt.savefig(
        os.path.join(output_path, basename + ".png"), bbox_inches="tight", dpi=120
    )
    plt.show()
    plt.close()
