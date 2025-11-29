# Pattern recognition network

## Usage

### Testing from command line

#### Pre-install

Boost is required to launch this code. On Mac, it can be installed with 

```bash
brew install boost
```

#### Build

To build the project:
```
cd path/to/project
cmake .
make
```

#### Running scripts

The application can be executed with optional command-line arguments to specify the network file and adjust network parameters. Here's how you can run the program:

- **Default Execution:**
  ```bash
  ./Evosnn2
  ```
  This uses a default file name `Top_7_4` with pre-configured parameters.

- **Custom Network File:**
  ```bash
  ./Evosnn2 <file_name>
  ```
  Replace `<file_name>` with your desired network file name to override the default. The file has to be located in the following folder: `./Topology/performing_nws_ED/Top_3_5/file_name`

- **Custom Network File & Parameters:**
  ```bash
  ./Evosnn2 <file_name> <no_of_signals>
  ```
  This allows setting both the file name and network size. Adjusts `noOfSignals`, `noOfInputs`, and `noOfinterNeurons` according to `<no_of_signals>`. Pre-configured paths for different network sizes exist (3-8 signals).

Note: The program currently only supports network sizes from 2 to 8 signals. Ensure the specified file exists to avoid errors.

### Testing with code modification

#### Testing a sequence
1. 'Evosnn.cpp' has to be run with the parameter `doEvolution` and `writeNetworkActivity` set to false in `Parameters.cpp`
    - input weight matrix used in the evolution is determined by setting `file_name` in `Evosnn.cpp` and by setting `noOfSignals`, `noOfInputs`, `noOfinterNeurons` in `Parameters.cpp`

#### Evolving a matrix
1. 'Evosnn.cpp' has to be run with the parameter `doEvolution` set to true in `Parameters.cpp`
    - As the code executes, runs are produced with new generations of the input matrix
    - input weight matrix used in the evolution is determined by setting `file_name` in `Evosnn.cpp` and by setting `noOfSignals`, `noOfInputs`, `noOfinterNeurons` in `Parameters.cpp`
    - evolution parameters can be controlled from within `Parameters.cpp`

#### Plotting network activity
To plot network activity
1. 'Evosnn.cpp' has to be run with the parameter `writeNetworkActivity` set to true in `Parameters.cpp`
    - As the code executes, as sequence has to be provided on which the network be evaluated
    - weight matrix used in the test is determined by setting `file_name` in `Evosnn.cpp` and by setting `noOfSignals`, `noOfInputs`, `noOfinterNeurons` in `Parameters.cpp`
    - the output is stored in `outputs3` and files network activity files look like `network_activity*.txt`
2. Run python script
    - `cd` into `python` directory and execute `python networkActvity-networks.py -n xxx` where `xxx` is the signature of the files to be plotted, e.g. after producing files using Top_5_4 input matrix, to plot its activity one can use `-n Top_5_4` to plot only this file, but `-n Top_5` will produce plots for all `network_activity` files containing `Top_5`

## Changes from original version
### C++
- Changed output paths
  - now they are modifiable by arguments of functions
  - output files are set in the parameters and `Evosnn.cpp` files
      - TODO there should be a single place where output files are set
- input files are set in the `Evosnn.cpp` 
    - depending on the desired signal size, an input folder is selected from predefined locations
- Code for sequence generation in evolution is unified across network sizes
    - this is implemented by generating 2 sequences of permuted letters, that are prepended or appended with a sequence
    - this was not thoroughly tested fro all dimensions
    - the difference with previous version of the code is that each sequence is repeated only once
- generation of testing sequence was modified
    - now, a random sequence is generated and in each of 100 characters, a desired sequence
    is positioned at random location
    - previously the sequence was random and it with the increase of sequence to recognise, the total number of sequences was dropping, up to not having anything to test for sequence of length 7

### Python 
- Merged functions for plotting
    - plotting for all sizes are done with the same function
      - function for plotting is stored in `utils.py`
- created one function to create plots
    - it takes a required argument `--network` (or `-n` for short), which is used to filter files from `outputs3` folder
        - TODO `outputs3` could be modifiable by argument
- TODO plotting has to be checked by Y., to verify if the changes did not disrupt functionality


## Questions
### C++ code

### Python code
- Why the variables were named N0 to Nx, while then were labelled Nx to N0, 
    - e.g. in `python/archive/networkAcrivity_original` in line 41 `N0 = x[:, 8]` but then in line 76
 ```python
ax7.plot(clock, N0, "m-")
ax7.set_ylabel("N5", rotation=0, fontsize=fSize, labelpad=padVal)
```
- Do we need to removed first `k` and last `n` samples from the signals?
    - Now this is removed, full signal is plotted 

## Further improvements
- TODO add argument parsing to CPP part of code
