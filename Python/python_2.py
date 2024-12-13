game = [[1,2,3],
        [4,5,6],
        ["X","X","X"]]

game_2 = [[1,1,1],
          [4,5,6],
          [7,8,9]]


three_in_a_row = []

# Rows
for row in game:
    three_in_a_row.append(tuple(row))

# Columns
for col in range(len(game[0])):
    column = tuple(game[row][col] for row in range(len(game))) 
    
    three_in_a_row.append(column)

# Diagonals
diagonal1 = tuple(game[i][i] for i in range(len(game)))
diagonal2 = tuple(game[i][len(game) - i - 1] for i in range(len(game)))
three_in_a_row.append(diagonal1)
three_in_a_row.append(diagonal2)

#print la structure de la liste three_in_a_row
print(three_in_a_row)

def is_a_win(player):
    return any([
        all([cell == player for cell in row])
        for row in three_in_a_row])










# def are_3_element_in_row(game, element):
#     for row in game:
#         if all([element == cell for cell in row]):
#             return True
#     return False
    
# def are_3_element_in_column(game, element):
#     for column in range(len(game)):
#         return all([element == game[row][column] for row in range(len(game))])

# def are_3_element_in_diagonal(game, element):
#     return all([element == game[i][i] for i in range(len(game))]) or all([element == game[i][len(game) - i - 1] for i in range(len(game))])

# def check_winner(game, element):
#     return (are_3_element_in_row(game, element) or 
#             are_3_element_in_column(game, element) or 
#             are_3_element_in_diagonal(game, element))

# print(check_winner(game, "X"))


