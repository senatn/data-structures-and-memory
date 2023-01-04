from itertools import chain

# the uppercase letter representing the land area that starts the bridge
# than the lowercase letter representing the bridge
BRIDGES = [
    "AaB",
    "AbB",
    "AcC",
    "AdC",
    "AeD",
    "BfD",
    "CgD",
]


def get_walks_starting_from(area, bridges=None):
    if bridges is None:
        bridges = BRIDGES
    walks = []

    def make_walks(area, walked=None, bridges_crossed=None):
        # take walked if we have already got a string of everything we`ve walked or that initial string area
        walked = walked or area
        # if we have already crossed some bridges
        # then we have going to have a tuple or we will start with an empty tuple
        bridges_crossed = bridges_crossed or ()

        # get all the bridges connected to 'area' that have not been crossed
        available_bridges = {
            bridge
            for bridge in bridges
            if area in bridge and bridge not in bridges_crossed
        }

        # determine if the walk has ended
        if not available_bridges:
            walks.append(walked)

        # walk the bridge to the adjacent area and recurse
        for bridge in available_bridges:
            if bridge[0] == area:
                crossing = bridge[1:]
            else:
                crossing = bridge[1::-1]

            make_walks(area=crossing[-1], walked=walked + crossing, bridges_crossed=(bridge, *bridges_crossed))

    make_walks(area)
    return walks


walks_starting_from = {area: get_walks_starting_from(area) for area in "ABCD"}

num_total_walks = sum(len(walks) for walks in walks_starting_from.values())

all_walks = chain.from_iterable(walks_starting_from.values())
solutions = [walk for walk in all_walks if len(walk) == 15]

print(num_total_walks)
print(len(solutions))
