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

def solve(bo, xpos, ypos):
    if (xpos == None or ypos == None):
        return True
    
    for i in range(1, _MAX_VALUE+1):
        if (is_valid(bo, i, (xpos, ypos))):
            bo[xpos][ypos] = i
        
            if (solve(bo, *find_empty(board, xpos, ypos+1))):
                return True

            bo[xpos][ypos] = 0

    return False

def is_valid(bo, num, pos):
    # Check row
    for i in range(len(bo[0])):
        if bo[pos[0]][i] == num and pos[1] != i:
            return False

    # Check column
    for i in range(len(bo)):
        if bo[i][pos[1]] == num and pos[0] != i:
            return False

    # Check box
    box_x = pos[1] // 3
    box_y = pos[0] // 3

    for i in range(box_y*3, box_y*3 + 3):
        for j in range(box_x * 3, box_x*3 + 3):
            if bo[i][j] == num and (i,j) != pos:
                return False

    return True


def find_empty(bo, row, col):
    while(row < 9):
        while(col < 9):
            if (bo[row][col] == 0):
                return (row, col)
            col += 1
        col = 0
        row += 1
    
    return (None, None)

def print_board(bo):
    '''
    Prints the board, formatted to look like a sudoku grid
    '''

    print(" ───────────────────────")
    for i in range(len(bo)):
        if i % 3 == 0 and i != 0:
            print(" ───────────────────────")
        for j in range(len(bo[0])):
            if j % 3 == 0:
                print("| ",end="")

            if j == 8:
                print(str(bo[i][j]) + " |")
            else:
                print(str(bo[i][j]) + " ", end="")    
    print(" ───────────────────────")

print("Unsolved board:")
print_board(board)
start = time.time()
solve(board, *find_empty(board, 0, 0))
print("\nSolved board:")
print_board(board)
print ("My program took", time.time() - start, "to run")
