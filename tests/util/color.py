
'''Function to print a colored line to terminal'''

RED='\033[0;31m%s\033[m'

def print_colored(message, color=RED):
    print color % message

if __name__ == '__main__':
    print '42 - the answer'
    print_colored("But what's the question?")
    print 'Hum?'
