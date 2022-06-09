#!/usr/bin/env python3
import argparse
import re, os
import random, string


def get_args():
    '''This function parses and return arguments passed in'''
    # Assign description to the help doc
    parser = argparse.ArgumentParser(
        description='Script create python project from a given parameters')
    # Add arguments
    parser.add_argument(
        '-n', '--number', type=int, help='Enter the maximun number of different characters possible in a string', required=False, default=4)
    parser.add_argument(
        '-l', '--length', type=int, help='Enter the length of strings', required=False, default=10)
    parser.add_argument(
        '-w', '--size', type=int, help='Enter the number of strings or lines', required=False, default=50)
        
    args = parser.parse_args()
    nomber = args.number
    length = args.length
    lines = args.size
    return nomber, length, lines

def id_generator(size=6, chars=string.ascii_uppercase):
    return ''.join(random.choice(chars) for _ in range(size))


def mkdir(path):
    try: 
        os.mkdir(path) 
    except OSError as error: 
        pass

def write(filepath, dataArray):
    result = list()
    with open (filepath, "w") as fp:
        for item in dataArray:
            fp.write(item)
            fp.write("\n")

def main():
    number, length, lines = get_args()
    letters = id_generator(number)

    path = os.getcwd()
    dirpath = os.path.join(os.getcwd(), "resources")
    mkdir(dirpath)
    filepath = os.path.join(dirpath, "words.txt")

    dataArray = [''.join(random.choice(letters) for i in range(length)) for _ in range(lines)]
    write(filepath, dataArray)

if __name__=="__main__":
    try:
        main()
    except SyntaxError:
        pass
