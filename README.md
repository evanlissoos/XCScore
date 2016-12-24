# XCScore
C++ program that scores a cross country race based on CSV file input

## Installation
- Clone the repository and navigate to the directory of the project.
- Run `./setup.sh`

## Running the program
Simply run `./xcscore file.csv` where file.csv is the input file with the XC race data.
To test that that program works, you can use the sample data provided in the `data` folder. Try running `./xcscore data/sample.csv`.

If you would like a more detailed output than just an ordered output of the teams, you can use the output option. Using the output option, the command will look like `./xcscore in_file.csv -o out_file.txt` where out_file.txt is the desired output file name. 

## Input file formatting
The input file must be in the following format

```
Lena Oxton,Some British School,3:34.10
Tekhartha Zenyatta,Omnic School,20:20.10
Lúcio Correia dos Santos,Some Brazilian School,12:11.21
John Oliver,Some British School,45:12.45
...
```

Pay close attention to the lack of spacing before and after commas as well as the leniency with the time formatting.
The number of digits representing the time run allows for entries like `15:30.115` or `1:10.1`.
The entries in the file need not have any sort of ordering (i.e. you do not need to have runners on the same team together).

Also, any number of runners per team can be added. The scoring will only take into account the top 7. Any team with less than 5 runners will be disqualified and that team's runners will not have an impact on the scoring.

## Compiler
By default, the Makefile uses g++ as the compiler, if you are on a Mac or any system where clang++ is the only C++ compiler, just edit the Makefile and replace `g++` with `clang++`
