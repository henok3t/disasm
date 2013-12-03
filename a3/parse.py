import os
import sys

def main():	
	if len(sys.argv) == 2:
		filename = sys.argv[1]
	else:
		raise Exception("Invalid Number Arguments")	
	
	#colors 
	BAD = '\033[91m'
	GOOD = '\033[92m'
	END = '\033[0m'
	
	# open fi
	fl = open(filename)
	lines = fl.readlines()
	max_size = max([len(line) for line in lines])
	
	for line in lines:
		print line[:-1],
		print_sep(max_size - len(line) + 5)
		print GOOD + ' good' + END
		pass # here is where everything is processed

def print_sep(size):
	sys.stdout.write(' ')
	for i in range(size):
		sys.stdout.write('-')


	
if __name__ == "__main__":
	main()
	

