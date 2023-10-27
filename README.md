# PIPEX

This project is about interprocess communication.<br>
Your program will be executed as follows: <br>

**MANDATORY**
> `./pipex file1 "cmd1" "cmdn" file2` <br>

It must take 4 arguments: <br>
• file1 and file2 are file names.<br>
• cmd1 to cmdn are shell commands with their parameters.<br>

**BONUS**
> `./pipex file1 "cmd1" ... "cmdn" file2` <br>

The bonus part has to be able to handle a indefinite number of commands between the files.<br>

## Requiriments

Linux system  with gcc and bash.

### Install

>`sudo apt update && sudo apt install build-essential`

## How to Use

Clone the repository:<br>

>`git clonehttps://github.com/FaustoFaggion/42_school_pipex.git`


**Mandatory** 

* Compile the program with `make` <br>

* Run the program
    - ex: `./pipex infile "tr a v" "tr v n" outfile` <br>

**Bonus**

* Compile the program with `make bonus` <br>

* Run the program:
    -  ex: `./pipex infile "tr a v" "grep v" "tr v n" outfile` <br>