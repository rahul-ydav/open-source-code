# open-source-code

A string is comprised of words defined as continuous runs of alphanumeric characters separated by separators (spaces, commas, periods, semi colons, exclamation marks, any other punctuation symbol except apostrophes').

So a string might look like this :

The hungry scanner keeps a suspicious watch on doctors and their unsuspecting patients

The scanner counts words, collecting those together where a common substring of length 4 or greater occurs.

For example, in the given sentence, suspicious and unsuspecting have a common substring of length 4 "susp". Thus the scanner would output something like this :

 				The : 1
    				hungry: 1
    				scanner: 1
    				keeps: 1
    				a: 1
    				suspicious, unsuspecting: 2
    				watch: 1
    				on: 1
    				doctors: 1
    				and: 1
    				their: 1
    				patients: 1
                            
Write a function that can work on a very long string stored in a file, and output a table as above. Each set of common-substring words should be listed on a line, along with a count of their joint occurrence. Please try to NOT load the entire file in memory to conserve system resources!

