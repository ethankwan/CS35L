#!/usr/bin/python

import random, sys, string
from argparse import ArgumentParser

def file2list(filename):
    f = open(filename, 'r')
    lines = f.readlines()
    f.close()
    return lines

def stdin2list(f):
    lines = f.readlines()
    f.close()
    return lines

def chooseline(lines):
    return random.choice(lines)

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE                                       
                                                                                
Output randomly selected lines from FILE."""

    parser = ArgumentParser()
    parser.add_argument("-n", "--head-count",
                        action="store", dest="headcount", default=0,
                        help="output HEADCOUNT lines (default is the number of \
lines of the input)")
    parser.add_argument("-r", "--repeat",
                        action="store_true", dest="repeatlines",
                        help="allows lines from the input to be repeated. Usage\
 without --head-count leads to infinite lines of output")
    parser.add_argument("-i", "--input-range",
                        action="store", dest="inputrange", default="0",
                        help="selects which lines from the input will be used")

    options, args = parser.parse_known_args(sys.argv[1:])

    iLines = []
    #-i option
    if(options.inputrange == "0"):
        try:
            if(args[0] == "-"):
                iLines = stdin2list(sys.stdin)
            else:
                iLines = file2list(args[0])
        except:
            iLines = stdin2list(sys.stdin)
                
    else:
        if(len(args) != 0):
            parser.error(" extra operand " + args[0].
                         format(args[0])) 
        irange = options.inputrange.split('-')
        r1 = int(input_range[0])
        r2 = int(input_range[1])
        if(r1 > r2):
            parser.error("invalid input range ".
                         format(irange))
        numlines = r2 - r1 + 1
        iLines = list()
        for num in range(0, numlines):
            numbar = num + r1
            iLines.append(str(numbar) + "\n")
    #headcount
    headcount = int(options.headcount)
    if(headcount == 0):
        headcount = len(iLines)
    #repeat
    repeat = bool(options.repeatlines)
    if(headcount > len(iLines)  and repeat != True):
        headcount = len(iLines)

    
    counter = headcount - 1
    while counter in range(0, headcount):
        currLine = chooseline(iLines)
        sys.stdout.write(str(currLine))
        if(repeat == False):
            iLines.remove(currLine)
            counter = counter - 1
        
        
if __name__ == "__main__":
    main()
