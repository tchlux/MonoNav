from binary_search_tree import BinaryTree

lst = [i for i in range(10)]
binary_tree = BinaryTree()

def sorted_list_to_binary_tree(lst):
    print(lst)
    if len(lst) > 0:
        mid = len(lst)//2
        print("Inserting:",lst[mid])
        binary_tree.insert(lst[mid])
        sorted_list_to_binary_tree(lst[0:mid])
        sorted_list_to_binary_tree(lst[mid+1:len(lst)])


sorted_list_to_binary_tree(lst)
binary_tree.print_depth_first()
