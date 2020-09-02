# stalks
![Command line display when program starts up](turnip_splash.png)
Turnip price predictor for your current week on ACNH.

For when your 4000+ turnips need to be sold *soon* but you don't know *when* to sell them to churn in max profit from the stalk market.

## Note
The max/mins calculated could be roughly 1-2 Bells off in either direction due to how turnip prices are generated in-game with their own random float method and how my floats are stored internally. But, there shouldn't be a problem coming up with potential pattern matches.

Please open an issue with your input example if there exists a valid input where NO match is found :-)

## Dependencies
- GCC C++ compiler (if compiling from source)
- C++17
- Python 2.7 or Python 3
- matplotlip-cpp

## Input
Use the csv file **turnip-input.csv** as your input template. If filling in the template with Excel, make sure to open it as Delimited with comma as the delimiter.

- **First Time Buy**: enter 1 for `true` or 0 for `false`.
  -  **Any non-zero integer will be read in as `true`**
- **Daisy Mae Price**: Price from Daisy Mae when you are buying turnips on Sunday morning
- **Mon-Sat AM/PM**: Enter in **your island's** selling price from Nook's Cranny for whichever days you have data for 
  - the remaining days of the week will be predicted

Each row in the csv is an island, so you can enter in multiple rows for multiple islands' turnip predictions.

## Usage
Compiling on command line (optional): `make` 
- Location of Python header and library may need to be changed in the Makefile (I'm on Mac)

Running program on the command line: `./stalks turnip-input.csv`

## Output
The program spits out line graph(s) with guaranteed minimum & possible maximums, and the possible turnip pattern the island is having.

WIP

## Special Thanks
- Ninji's [gist](https://gist.github.com/Treeki/85be14d297c80c8b3c0a76375743325b) for how turnip prices are generated in-game
