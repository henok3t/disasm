#Information about Assignment
	# Name: Henok Tadesse
	# UserAccount: masc0753
	# Partner Name: Joseph Mouawad
	# Partner UserAccount: masc0736
	# class: cs530
	# Assignment: Program Assignment 3
	# filename: parse.py

import os
import sys
import re

def main():	

	# handle command line arguments
	if len(sys.argv) == 2:
		filename = sys.argv[1]
	else:
		raise Exception("Invalid Number Arguments")	
	
	#colors 
	BAD = '\033[91m'
	GOOD = '\033[92m'
	END = '\033[0m'
	
	# open file and read lines
	fl = open(filename)
	lines = fl.readlines()
	max_size = max([len(line) for line in lines])
	errors = []
	
	# go through each line
	for line in lines:		
		
		# this takes care of spacing issues
		mod_line = separate_special_characters(line)		
		
		# gets a list of the tokens in the line of code
		tokens = mod_line.split()		

		if is_assignment(tokens, errors): # check if it is an assignment
			tpy = 'Assignment'
			if len(errors) > 0: # make sure there are not errors
				tpy = 'ERROR'
		elif is_expression(tokens, errors): # if not an assignment, check if expression
			tpy = 'Expression'
		else: # if is neither, then it is an error
			tpy = 'ERROR'				
		
		# print information with colors for each line of code
		print line[:-1],
		print_sep(max_size - len(line) + 5)
		if tpy != 'ERROR':
			print GOOD + tpy + END
		elif len(errors) > 0:
			print BAD + tpy + ': ' + errors[0] + END	
		else:
			print BAD + tpy + END
		errors = []		

# adds spaces before and after all special keys to make it easy to identify them as tokens
def separate_special_characters(line):
	mod = line.replace('(', ' ( ')
	mod = mod.replace(')', ' ) ')
	mod = mod.replace('+', ' + ')
	mod = mod.replace('-', ' - ')
	mod = mod.replace('*', ' * ')
	mod = mod.replace('/', ' / ')
	mod = mod.replace('%', ' % ')
	mod = mod.replace('=', ' = ')
	mod = mod.replace(';', ' ; ')
	return mod

# this function is used to align the message based on the length of the input line
def print_sep(size):
	sys.stdout.write(' ')
	for i in range(size):
		sys.stdout.write('-')

# this function gets the type of the token, id, op or special character
def get_type(st):	
	if st == '(' or st == ')' or st == '=' or st == ';':
		return st
	elif st == '+' or st == '-' or st == '*' or st == '/' or st == '%':
		return 'op'
	elif re.match('^[a-zA-Z][0-9a-zA-Z]*$', st ) :
		return 'id'
	else:
		return 'invalid'

# this funciton checks if the provided lists of tokens make an expression, if there is an error it is passed to error parameter
def is_expression(tokens, error = []):	

	# count parenthesis open and closed parenthesis
	opencount = 0
	closedcount = 0
	
	# used to play with odd and even when parenthesis are involved
	pad = 0
	
	for i in range(len(tokens)):
		if (i+pad) % 2 == 0:
			if get_type(tokens[i]) == '(':
				opencount += 1
				pad += 1
			elif get_type(tokens[i]) != 'id':
				error.append('%s is not an id' % tokens[i])
				return False						
		elif (i+pad) % 2 == 1 :
			if opencount > closedcount and get_type(tokens[i]) == ')':
				closedcount += 1
				pad += 1
			elif get_type(tokens[i]) != 'op':
				error.append('%s is not an operator' % tokens[i])
				return False						
	
	if opencount != closedcount:
		error.append('unclosed parenthesis')
		return False
	
	if get_type(tokens[-1]) != 'id' and get_type(tokens[-1]) != ')'  :
		error.append('Expression Not Complete')
		return False
	
	return True

# this funciton checks if the provided lists of tokens make an assignment, if there is an error it is passed to error parameter
def is_assignment(tokens, errors):
	if get_type(tokens[0]) != 'id' or get_type(tokens[1]) != '=':
		return False
	if get_type(tokens[-1]) != ';':
		errors.append('Missing Semi-Colon')
	is_expression(tokens[2:-1], errors)	
	return True

if __name__ == "__main__":
	main()
