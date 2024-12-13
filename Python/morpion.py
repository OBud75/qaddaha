def print_board(board):
    for row in board:
        print(" | ".join(row))
        print("-" * 5)

def check_winner(board):
    for row in board:
        if row.count(row[0]) == len(row) and row[0] != " ":
            return True
    for col in range(len(board)):
        check = []
        for row in board:
            check.append(row[col])
        if check.count(check[0]) == len(check) and check[0] != " ":
            return True
    if board[0][0] == board[1][1] == board[2][2] and board[0][0] != " ":
        return True
    if board[0][2] == board[1][1] == board[2][0] and board[0][2] != " ":
        return True
    return False

def player_move(board):
    while True:
        move = input("Enter your move (row and column): ").split()
        if len(move) != 2:
            print("Invalid input. Please enter row and column.")
            continue
        row, col = int(move[0]), int(move[1])
        if row < 0 or row > 2 or col < 0 or col > 2 or board[row][col] != " ":
            print("Invalid move. Try again.")
        else:
            board[row][col] = "O"
            break

def unbeatable_move(board):
    for row in range(3):
        for col in range(3):
            if board[row][col] == " ":
                board[row][col] = "X"
                if check_winner(board):
                    return
                board[row][col] = " "
    for row in range(3):
        for col in range(3):
            if board[row][col] == " ":
                board[row][col] = "X"
                return

def main():
    board = [[" " for _ in range(3)] for _ in range(3)]
    print_board(board)
    while True:
        player_move(board)
        print_board(board)
        if check_winner(board):
            print("Player wins!")
            break
        unbeatable_move(board)
        print_board(board)
        if check_winner(board):
            print("Computer wins!")
            break
        if all(cell != " " for row in board for cell in row):
            print("It's a tie!")
            break

if __name__ == "__main__":
    main()