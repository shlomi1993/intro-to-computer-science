"""""""""""""""""""""""""""""
 Name: Shlomi Ben Shushan
 Group: 01 - CS
 Assignment: 7
"""""""""""""""""""""""""""""

import csv
import json

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
* Function name:        parser
* Input:                start_file_name, dictionary
* Output:               value_list
* Function Operation:   This function parse the source file (start_file_name) to find
                        the names of the pages that it links to, and append them to a
                        list named value_list. Afterwards the function sort values_list
                        and add it as a value to dictionary. In the end it returns
                        value_list for other function use.
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


def parser(start_file_name, dictionary):
    start_mark = 'href="'
    end_mark = '"'
    values_list = []
    with open(start_file_name) as file:
        for line in file:
            if line.find(start_mark) != -1:
                iterator = line.find(start_mark) + len(start_mark)
                next_file_name = line[iterator]
                while line[iterator] != end_mark:
                    iterator += 1
                    if line[iterator] != end_mark:
                        next_file_name += line[iterator]
                values_list.append(next_file_name)
        values_list.sort()
        dictionary[start_file_name] = values_list
    return values_list


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
* Function name:        crawler
* Input:                start_file_name, dictionary
* Output:               None
* Function Operation:   This function gets a source file (start_file_name) to begin
                        crawling from it. It uses parser to get the names of the pages
                        that the source file link to and recursively crawl each one
                        of them. Crawling stops whenever it encounters a key that
                        already in the dictionary.
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


def crawler(start_file_name, dictionary):
    if start_file_name in dictionary:
        return
    values_list = parser(start_file_name, dictionary)
    for value in values_list:
        crawler(value, dictionary)


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
* Function name:        export_to_csv
* Input:                dictionary
* Output:               None
* Function Operation:   This function simply gets a dictionary, creates a CSV file and 
                        feeds it with keys and values.
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


def export_to_csv(dictionary):
    with open("results.csv", "w", newline='') as results:
        writer = csv.writer(results)
        for key in dictionary.keys():
            writer.writerow([key] + dictionary[key])
        results.close()


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
* Function name:        main
* Input:                None
* Output:               None
* Function Operation:   This is the main function. It initialize an empty dictionary,
                        ask the user for input and than call the crawler(), which
                        call parser() and itself recursively and feed the dictionary.
                        Afterwards, it export the findings to a CSV file by using
                        export_to_csv() and than it ask the user for a file name, which
                        is the key in the dictionary to the matching value to print.
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


def main():
    dictionary = {}
    start_file_name = input("enter source file:\n")
    crawler(start_file_name, dictionary)
    export_to_csv(dictionary)
    file_key = input("enter file name:\n");
    print(dictionary[file_key])


main()
