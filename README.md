# stalks: Turnip Price Predictor
![Command line display when program starts up](turnip_splash.png)

Turnip price predictor for your current turnip-filled week on ACNH.

For when your **4000+** turnips need to be sold *soon* but you don't know *when* to sell them to churn in max profit from the stalk market.

## Note
The max/mins calculated could be roughly 1-2 Bells off in either direction due to how turnip prices are generated in-game with their own random float method and how my floats are stored internally. But, there shouldn't be a problem coming up with potential pattern matches.

Please open an issue with your input example if there exists a valid input where NO match is found :-)

## Dependencies
- GCC C++ compiler (if compiling from source)
- C++17
- Python 2.7 or Python 3
- matplotlib

## Input
The 4 stalk market patterns are defined as:
- Pattern 0, **Random** (increase, decrease, increase, decrease, increase phases)
- Pattern 1, **Large Profit** (decrease, large spike, random low)
- Pattern 2, **Decreasing** (decreasing)
- Pattern 3, **Small Profit** (decreasing, small spike, decreasing)

Use the csv file **turnip-input.csv** as your input template. If filling in the template with Excel, make sure to open it as Delimited with comma as the delimiter.
- **Previous Week's Pattern**: 0, 1, 2, or 3
    - **leave blank if unknown**
    - *used to display the probability of a matched price sequence of occurring*
- **First Time Buy**: 1 for `Yes` or 0 for `No`.
  -  **Any non-zero integer will be read in as `Yes` (your first time ever buying turnips)**
- **Daisy Mae Price**: Price from Daisy Mae when you are buying turnips on Sunday morning on your island
- **Mon-Sat AM/PM**: Enter in **your island's** selling price from Nook's Cranny on your island for whichever days you have data for 
  - the remaining days of the week will be predicted

Each row in the csv is an island, so you can enter in multiple rows for multiple islands' turnip predictions :-)

## Usage
Compiling on command line (optional): `make` 
- Location of Python header and library may need to be changed in the Makefile (I'm on Mac)
- See [this](https://matplotlib-cpp.readthedocs.io/en/latest/compiling.html) for more info

Running program on the command line: `./stalks turnip-input.csv`

A sample input and output is available under the `example` folder.

## Output
While predicting price sequences, the console will display the current island's input data and show a matched price sequence's pattern type.
A total number of matched sequences is displayed after matching is done if at least one match was found.

The program spits out a line graph for each island/row in the input csv in the current directory. The graph has:
- island's observed prices as scatter plot
- guaranteed minimums of matched sequences as line graph
- possible maximums of matched sequences as line graph

A csv is generated in the current directory too, where each row lists the potential price sequence details (min/max for each of the 14 price periods in the week).
If the previous week's pattern was supplied, percentages of the matched pattern types will show in the first column.

## Special Thanks
- Ninji's [gist](https://gist.github.com/Treeki/85be14d297c80c8b3c0a76375743325b) for how turnip prices are generated in-game
