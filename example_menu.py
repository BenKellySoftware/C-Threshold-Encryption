#!/usr/bin/python3

import getopt
import sys

# these will be the default values
# of options when they are not set
target = ""
destination = "out"
option_c = ""

def usage():
    print("Usage: bepis "+
        "[(-h | -? | --help )] "+
        "[(-a | --add-recipe) target] "+
        "[(-v | --view-recipe) target] "+
        "\n")
    print("Description of program")
    print("")
    print("-h -? --help : displays help")
    print("-a --add-recipe  : adds a recipe")
    print("-v --view-recipe : views a recipe")
    print("-o --out         : output file")
    print("")
    print("example:")
    print("command -a image_1.bmp cool.compresed")
    print("command -v cool.compressed image_2.bmp")
    sys.exit(0)

def getOptions():
    # the options that will be used 
    global target
    global destination

    # if no options specified, we can
    # display the usage message
    if not len(sys.argv[1:]):
        usage()

    # getting the options and arguments
    try:
        opts, args = getopt.getopt(
            sys.argv[1:],
            "h?a:v:o:", # : signifies a value is expected after option
            ["help", "help", "add-recipe", "view-recipe", "out"] # long names
            )
    # if there is an error in getting the options
    except getopt.GetoptError as err:
        print(str(err))
        usage()

    for opt, arg in opts:
        if opt in ["-h", "-?", "--help"]:
            usage()
        elif opt in ["-a", "--add-recipe"]:
            target = arg
        elif opt in ["-v", "--view-recipe"]:
            target = arg
        elif opt in ["-o", "--out"]:
            destination = arg
        else:
            # if the option didn't exist
            assert False, "Unhandled Option"

def main():
    global option_a
    global option_b
    global option_c
    
    # Main program stuff here
    
    # for the sake of the template and example
    # just display what the values were set to
    print("target was      : "+repr(target))
    print("destination was : "+repr(destination))

getOptions()
main()
