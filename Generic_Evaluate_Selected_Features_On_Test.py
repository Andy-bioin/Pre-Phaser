import subprocess
import os
from subprocess import Popen, PIPE
import csv
import json
import sys

train_file_prefix = sys.argv[1] 
test_file_prefix = sys.argv[2]
k = int(sys.argv[3])
use_selection = sys.argv[4]

canonical_gene_list_indeces = list()
canonical_gene_list = list() 
with open(train_file_prefix + '_genes.csv', 'r') as f:
	reader = csv.reader(f)
	canonical_gene_list = list(reader)[0]
if (use_selection == "yes"):
	selection_file = sys.argv[5]
	features_list = json.load(open(selection_file))
	for gene_name in features_list:
		canonical_gene_list_indeces.append(str(canonical_gene_list.index(gene_name)))
else:
	for i in range(0, len(canonical_gene_list)):
		canonical_gene_list_indeces.append(str(i))	

args = ['./Generic_Evaluate_Selected_Features_On_Test', test_file_prefix, train_file_prefix, str(k)]
args += canonical_gene_list_indeces 
p = subprocess.Popen(args, stdout=PIPE, stderr=PIPE)

stdout, stderr = p.communicate()
vals = stdout.decode("utf-8").split("\n")
err = stderr.decode("utf-8")

print("Accuracy")
print(vals[0])
print("F1 Score")
print(vals[1])	

