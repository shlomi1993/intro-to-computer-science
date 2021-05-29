"""""""""""""""""""""""""""""
 Name: Shlomi Ben Shushan 
 ID: 311408264            
 Group: 01 - CS           
 Assignment: 7            
"""""""""""""""""""""""""""""

import csv
import json
import re


def parser(start_file_name, dictionary):
    start_mark = 'href="'
    end_mark = '"'
    with open(start_file_name) as fp:
        for line in fp.readline():
            iterator = line.find(start_mark) + len(start_mark)
            next_file_name = line[iterator]
            values_list = []
            while line[iterator] != end_mark:
                iterator += 1
                next_file_name += line[iterator]
            values_list.append(next_file_name)
        dictionary[start_file_name] = values_list
    return values_list


def crawler(start_file_name, dictionary):
    if start_file_name in dictionary:
        return
    values_list = parser(start_file_name, dictionary)
    for value in values_list:
        crawler(value, dictionary)


def export_to_csv(dictionary):
    with open("result.csv", "w") as result:
        for key in dictionary.keys():
            result.write("%s,%s\n"%(key,dictionary[key]))
        result.close()


def main():
    dictionary = {}
    start_file_name = input("enter source file: ")
    crawler(start_file_name, dictionary)
    export_to_csv(dictionary)
    return

main()