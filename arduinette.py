import argparse
import os
import subprocess

# Argument parsing
parser = argparse.ArgumentParser()
parser.add_argument("--config_file", "-C", help="path of the config.c file")
parser.add_argument("--config_header_file", "-H",help="path of the config.h file")
parser.add_argument("--solution", "-S",help="path of the solution.c file")
parser.add_argument("--file", "-F",help="path of the file to test")
args = parser.parse_args()

# Execute a command a subprocess and log the outputs to the given file
def execute_and_log(command, output_file):
	cp = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE,universal_newlines=True)
	output_file.write(f"{command}\n")
	if cp.stdout:
		output_file.write(f"{cp.stdout}\n")
	if cp.stderr:
		output_file.write(f"{cp.stderr}\n")
	return cp.returncode

# Create a copy of the file to test and include the fakeArduino.h header file
with open(args.file, 'r') as original: student_code = original.read()
with open("student.c", 'w') as modified: modified.write('#include "fakeArduino.h"' + student_code)

try:
	with open("trace.txt", "w") as trace:
		# compile and run the solution code, writing every output to a file
		if execute_and_log(f"gcc -I{os.path.dirname(args.config_header_file)} -o solution main.c fakeArduino.c {args.config_file} {args.solution}", trace):
			raise Exception('Answer file compilation failed')
		execute_and_log(f"./solution | cat -e > solution.txt", trace)

		# compile and run the student code, writing every output to a file
		if execute_and_log(f"gcc -I{os.path.dirname(args.config_header_file)} -o student main.c fakeArduino.c {args.config_file} student.c ", trace):
			raise Exception('File compilation failed')
		execute_and_log(f"./student | cat -e > student.txt", trace)

		# run a diff command on both output files and check whether both files differs.
		execute_and_log(f"diff -u solution.txt student.txt > diff.txt", trace)
		execute_and_log(f"cat -e diff.txt", trace)
		with open("diff.txt", "r") as diff:
			data = diff.read()
		if len(data):
			print('\033[91m' + "KO - You suck !" + '\033[0m')
		else:
			print('\033[92m' + "OK - Well Done !" + '\033[0m')

		# execute_and_log("rm solution student solution.txt student.txt diff.txt", trace)
except Exception as e:
	print('\033[91m' + str(e) + '\033[0m')

