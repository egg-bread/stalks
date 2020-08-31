# stalks
Turnip price predictor for your current week on ACNH.

For when your 4000+ turnips need to be sold *soon* but you don't know *when* to sell them to churn in max profit from the stalk market.

## Input
Use the csv file **turnip_prices.csv** as your input template. If filling in the template with Excel, make sure to open it as Delimited with comma as the delimiter.

- **First Time Buy**: enter 1 for `true` or 0 for `false`.
  -  **Any non-zero integer will be read in as `true`**
- **Daisy Mae Price**: Price from Daisy Mae when you are buying turnips on Sunday morning
- **Mon-Sat AM/PM**: Enter in **your island's** selling price from Nook's Cranny for whichever days you have data for 
  - the remaining days of the week will be predicted

Each row in the csv is an island, so you can enter in multiple rows for multiple islands' turnip predictions.

## Usage
The program spits out line graph with guaranteed minimum & possible maximums, and the possible turnip pattern the island is having.
