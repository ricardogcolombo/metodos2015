#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import networkx as nx
import matplotlib.pyplot as plt

""" 
Just need to install:

	sudo apt-get install python-networkx
	sudo apt-get install python-matplotlib

"""

def usage():
	print "usage: "
	print "		python graph_plot.py graph.out [output.png]"
	print

if __name__ == '__main__':
	ps=len(sys.argv)
	if (ps < 2 or ps > 3):
		usage()
		sys.exit()

	gpath= str(sys.argv[1])

	G = nx.DiGraph()

	with open(gpath,'r') as data:
		N= int(data.readline())
		M= int(data.readline())
		for edge in data.readlines():
			G.add_edge(*map(int,edge.split()))
	
	# networkx draw()
	nx.draw(G,node_color='w',pos=nx.shell_layout(G))
	
	if (len(sys.argv) > 2):
		# save to file
		fout= str(sys.argv[2])
		plt.savefig(fout)
	else:
		# show plot
		plt.show()