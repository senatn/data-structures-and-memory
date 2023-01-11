from collections import namedtuple
# namedtuple allow you to give names to the tuple`s components
# once you`ve created a namedtuple you can use it to create new instances
# of objects much the same way you would will using a user-defined class

Graph = namedtuple("Graph", ["nodes", "edges", "is_directed"])


def adjacency_dict(graph):
    """ returns the adjacency list representation of the graph"""
    adj = {node: [] for node in graph.nodes}  # dictionary comprehension
    for edge in graph.edges:
        node1, node2 = edge[0], edge[1]
        adj[node1].append(node2)
        if not graph.is_directed:
            adj[node2].append(node1)
    return adj


""" 
    To be a dictionary key nodes have to be of a hashable type
    Hash-ability makes an object usable as a dictionary key and a set member,
    because these data structures use the hash value internally.
    All of Python’s immutable built-in objects are hashable,
    while no mutable containers (such as lists or dictionaries) are.
    Objects which are instances of user-defined classes are hashable by default;
    they all compare unequal, and their hash value is their id().
    
    in practice this might be a pretty severe limitation but our purposes
    is learn some graph theory we are going to use integers and strings
    we won`t run into any problems
"""


def adjacency_matrix(graph):
    """ returns the adjacency matrix of the graph
        assumes that graph.nodes is equivalent to range(len(graph.nodes)) """
    adj = [[0 for node in graph.nodes] for node in graph.nodes]  # nested list comprehension
    for edge in graph.edges:
        node1, node2 = edge[0], edge[1]
        adj[node1][node2] += 1
        if not graph.is_directed:
            adj[node2][node1] += 1
    return adj
