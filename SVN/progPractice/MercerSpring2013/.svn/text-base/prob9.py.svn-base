def create_board(a_list,width):
    board_list = []
    for row in range(width):
        row_list = []
        for col in range(width):
            row_list.append['valid']
        board_list.append(row_list)
    return board_list


iteration = int(input())
for index in range(iteration):
    board_list = create_board([],9)
    check_list = create_board([],3)
    turns = input().split()
    new_list = []
    error = False
    count = 0
    for index in range(len(turns)):
        old_index = str(turns[index-1][0]%3) + str(turns[index-1][1]%3)
        new_index = str(tunrs[index][0]//3) + str(turns[index][1]//3)
        if turns.count(turns[index]) >1 or old_index != this_index or check_board[this_index[0]][this_index[1]] == 'invalid':
            error = True
            count = index
            break
        else:
            new_list.append(turns[index])
            if index%2 == 0:
                board_list[turns[index][0]][turns[index][1]] = ['x']
                if win_check(board_list,'x',turns[index][0],turns[index][1]:
            else:
                board_list[turns[index][0]][turns[index][1]] = ['o']



    if repeated:
        if count%2 == 0:
            player = "one"
        else:
            player = "two"
        print("Player", player, "made an invalid move on turn", str(count) + ".")
    else:
        print("All moves were valid.")


