from os.path import dirname, join, realpath

soubor = join(dirname(realpath(__file__)), "test.txt")

def find_previous_beams(beam_indexes, current_line_index):
    index_to_return = None

    for idx in range(0,current_line_index):
        if (index_to_return is None or idx > index_to_return):
            try:
                if (beam_indexes[idx]):
                    index_to_return = idx 
            except KeyError:
                index_to_return = index_to_return 

    return beam_indexes[index_to_return]

def build_tree(tree):
    for characters in tree:
        print("".join(characters))

def main():
    with open(soubor, "r") as f:
        data = f.read().strip().split("\n")

    s_index = None
    splits = 0
    tree = []
    beam_indexes = {}

    # Zde můžete přidat logiku pro zpracování dat
    for line_index, line in enumerate(data):
        line_characters = list(line)
        to_delete = []

        tree.append(line_characters)

        if (s_index is None):
            try:
                s_index = line_characters.index("S")
                beam_indexes[line_index] = [s_index]
            except ValueError:
                s_index = None
        else:   
            current_beam_indexes = find_previous_beams(beam_indexes, line_index)

            for ch_index, char in enumerate(line_characters):
                current_beam = None

                try:
                    current_beam = current_beam_indexes.index(ch_index)
                except ValueError:
                    current_beam = None

                if (current_beam is not None and char != "^" and char != "S"):
                    tree[line_index][ch_index] = "|"

                if (char == "^" and current_beam is not None):
                    to_add = []

                    splits += 1

                    # check for borders
                    if ((ch_index - 1) >= 0):
                        to_add.append(ch_index - 1)
                        tree[line_index][ch_index - 1] = "|"
                    
                    if ((ch_index + 1) < len(line_characters)):
                        to_add.append(ch_index + 1)
                        tree[line_index][ch_index + 1] = "|"


                    try:
                        beam_indexes[line_index].extend(to_add)

                        # remove dupes
                        beam_indexes[line_index] = list(dict.fromkeys(beam_indexes[line_index]))
                    except KeyError:
                        beam_indexes[line_index] = []
                        beam_indexes[line_index].extend(to_add)

                    to_delete.append(current_beam_indexes[current_beam])

            
            # delete any non active beams
            try:
                for v in to_delete:
                    for line_beam_index, values in beam_indexes.items():
                       if (line_beam_index < line_index):
                           try:
                            values.remove(v)
                           except ValueError:
                               continue
            except KeyError:
                print(f"{current_beam} doesn't found!")

            for previous_line_index in range(0, line_index):
                try:
                    if (beam_indexes[previous_line_index]):
                        for beam_index in beam_indexes[previous_line_index]:
                            for new_index in range(previous_line_index, line_index + 1):
                                line_character = list(data[new_index])[beam_index]
                                if (line_character != "^" and line_character != "S"):
                                    tree[new_index][beam_index] = "|"
                except KeyError:
                    continue

            print(f"[{line_index}] CURRENT BEAMS:", beam_indexes)

    print(beam_indexes)
    print("FINAL SPLITS:", splits)
    
    build_tree(tree)
    

if __name__ == "__main__":   
    main()