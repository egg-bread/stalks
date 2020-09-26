# stalks: Turnip Price Predictor
![Command line display when program starts up](turnip_splash.png)

Turnip price predictor for your current turnip-filled week on ACNH.

For when your **4000+** turnips need to be sold *soon* but you don't know *when* to sell them to churn in max profit from the stalk market.

## Note
The max/mins calculated could be roughly 1-2 Bells off in either direction due to how turnip prices are generated in-game 
with their own random float method and how my floats are stored internally. But, there shouldn't be a problem coming up 
with potential pattern matches.

**Please open an issue with your input example if there exists a valid input where NO match is found :-)**

## Dependencies
- GCC C++ compiler (if compiling from source)
- at least C++11
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
    - *used in output csv to display occurrence probability of matched price sequence*
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

You may notice that the first island data row and
the last island data row are identical except for a previous pattern filled in even though it is a first time buyer. But,
the first time buyer column takes precedence. Any mistaken previous pattern cells filled in for a first buyer island
will be processed as if the previous pattern field was not entered.

## Output
While predicting price sequences, the console will display the current island's input data and show a matched price sequence's pattern type.
A total number of matched sequences is displayed after matching is done if at least one match was found.

### Line graph
The program spits out a line graph pdf for each island/row in the input csv in the current directory. The graph has:
- island's observed prices as grey scatter plot labelled with price
- guaranteed minimums of matched sequences as red dashed line 
- possible maximums of matched sequences as green dashed line 

The lowest y-axis tick and highest y-axis tick are the guaranteed minimum price and possible
maximum price among all matched price sequences found.

### CSV
A csv is generated in the current directory too, where each row lists the potential price sequence details. The min/max 
for each of the 14 price periods is shown in that respective column as an inclusive range (e.g. 68-112) denoting the guaranteed
minimum (e.g. 68) and possible maximum price for that day (e.g. 112).

If the previous week's pattern was supplied, percentages of the matched pattern types will show in the first column. This
percentage indicates the probability of that **pattern type** occurring, **NOT** that price sequence!

If the prediction only finds price sequences of one pattern type, then the probability will be 100% in the output csv.

Since the csv will show the entire price sequence for each matched price sequence, you can ignore the days input was provided
for in the input csv and look at the days after the last input day. 

Points that
are right at the edge of the top and bottom of the graph are these min and max values, not out of bound prices.
### File names
Each pdf and csv is named as `Island <number>`, based on how many are read from the csv. So, input with 3 (islands) rows
filled in will produce 3 pdfs and 3 csvs named `Island 1.pdf/csv, Island 2.pdf/csv, Island 3.pdf/csv`.

## Special Thanks
- Ninji's [gist](https://gist.github.com/Treeki/85be14d297c80c8b3c0a76375743325b) for how turnip prices are generated in-game
- [Pattern & price sequence generator](https://turnip-price.now.sh/) for testing
