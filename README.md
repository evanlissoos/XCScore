# XCScore
C++ program that scores a cross country race based on CSV file input

## Installation
- Clone the repository and navigate to the directory of the project.
- Run `./setup.sh`

## Running the program
Simply run `./xcscore file.csv` where file.csv is the input file with the XC race data
To test that that program works, you can use the sample data provided in the `data` folder. Try running `./xcscore data/sample.csv`

## Input file formatting
The input file must be in the following format
```
First Last,School Name,MM:SS.mm
First Last,School Name,MM:SS.mm
...
```

Where M is for minutes, S is for seconds, and m is for decimals of seconds. Each of these can be any length so you can have times like `15:30.115` or `1:10.1`.
