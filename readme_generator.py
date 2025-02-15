import os, sys
from fuzzywuzzy import fuzz

readme = open("README.md", "w")

def tokenize(string):
	tokens = []
	current_word = ''
	for char in string:
		if char == '_' or char == ' ' or char == '-':
			tokens.append(current_word)
			current_word = ''
		elif char.isupper() and not current_word.isupper():
			tokens.append(current_word)
			current_word = char
		else:
			if len(current_word) == 0:
				current_word = char.upper()
			else:
				current_word += char
	tokens.append(current_word)
	return [t for t in tokens if t != '']

def to_std_case(string):
	return  ' '.join(tokenize(string))

class AlgorithmTranslator:
	def __init__(self):
		self.algos = []
	
	def translate(self, algo):
		algo_std = to_std_case(algo)
		for a in self.algos:
			if fuzz.partial_ratio(a, algo_std) > 85:
				return a
		self.algos.append(algo_std)
		return algo_std
		
translator = AlgorithmTranslator()
cwd = os.getcwd()
accumulator = {}
languages = sorted([f for f in os.listdir(cwd) if os.path.isdir(f) and not f.startswith('.')])
print(languages)
for language in languages:
	accumulator[language] = []
	algos = [f for f in os.listdir(os.path.join(cwd, language)) if not f.startswith('.')]
	for algo in algos:
		translated = translator.translate(algo)
		accumulator[language].append(translated)

with open('readme-prelist.md') as pre:
	for line in pre.readlines():
		readme.write(line)

readme.write('Language | ' + ' | '.join(languages) + '|' + '\n')
readme.write('---|' + '|'.join([':---:' for _ in languages]) + '|' + '\n')
for algo in sorted(translator.algos):
	readme.write(algo + ' | ' + ' | '.join(':+1:' if algo in accumulator[l] else ' ' for l in languages) + '|' +'\n')

with open('readme-postlist.md') as post:
	for line in post.readlines():
		readme.write(line)
