import time

board = [
    [0,0,1,2,0,3,4,0,0],
    [0,0,0,6,0,7,0,0,0],
    [5,0,0,0,0,0,0,0,3],
    [3,7,0,0,0,0,0,8,1],
    [0,0,0,0,0,0,0,0,0],
    [6,2,0,0,0,0,0,3,7],
    [1,0,0,0,0,0,0,0,8],
    [0,0,0,8,0,5,0,0,0],
    [0,0,6,4,0,2,5,0,0]
]

_MAX_VALUE = 9
_BOARD_SIZE = 9

num_solutions = 0
keep_going = False

def solve(r = 0, c = 0):
    global board
    global num_solutions
    global keep_going

    for col in range(c, _MAX_VALUE):
        # updates row to last position, but only for the first iteration of col
        if (col == c):
            ro = r
        else:
            ro = 0
        for row in range(ro, _MAX_VALUE):
            if (board[row][col] == 0):
                for n in range(1,10):
                    if (is_valid(n, (row, col))):
                        board[row][col] = n
                        solve(row, col)
                        board[row][col] = 0
                return

    num_solutions += 1
    if (num_solutions == 1):
        print("\nSolved board:")
        print_board()
    elif (num_solutions == 2):
        answer = ''
        while (answer.lower() != 'y' and answer.lower() != 'n'):
            answer = input("This board does not have a unique solution. Keep going and count the number of solutions? [Y/n] ")

        if (answer.lower() == 'y'):
            keep_going = True
        else:
            exit(0)
            
    return
                


def is_valid(num, pos):
    """
    Returns True if the attempted move is valid, False otherwise
    :param pos: (row, col)
    :param num: int
    :return: bool
    """

    # get box position
    box_x = pos[1] // 3
    box_y = pos[0] // 3

    # Check row
    for i in range(_BOARD_SIZE):
        if board[pos[0]][i] == num and pos[1] != i:
            return False

    # Check column
    for i in range(_BOARD_SIZE):
        if board[i][pos[1]] == num and pos[0] != i:
            return False

    # Check box
    for i in range(box_y*3, box_y*3 + 3):
        for j in range(box_x * 3, box_x*3 + 3):
            if board[i][j] == num and (i,j) != pos:
                return False

    return True

def print_board():
    '''
    Prints the board, formatted to look like a sudoku grid
    '''

    print(" ───────────────────────")
    for i in range(len(board)):
        if i % 3 == 0 and i != 0:
            print(" ───────────────────────")
        for j in range(len(board[0])):
            if j % 3 == 0:
                print("| ",end="")

            if j == 8:
                print(str(board[i][j]) + " |")
            else:
                print(str(board[i][j]) + " ", end="")    
    print(" ───────────────────────")


if __name__ == '__main__':
    print("Unsolved board:")
    print_board()
    start = time.time()
    solve()
    print("The number of unique solutions: {}".format(num_solutions))
    print ("Checking all possibilities took", time.time() - start, "seconds")
