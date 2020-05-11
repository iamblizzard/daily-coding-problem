import pygame, random, sys
from queue import Queue

GREEN = (144, 232, 76)
BLACK = (0, 0, 0)
RED   = (255, 0, 20)
WINDOW_HEIGHT = 400
WINDOW_WIDTH = 400

board = [[None for i in range(3)] for j in range(3)]
index = ()
val = None

def computeHash(board):
    val = 0
    for p in range(3):
        for q in range(3):
            val = val*10 + board[p][q]
    return val

def boardIsDone(hash_of_board):
    global index
    v = [0, 8, 7, 6, 5, 4, 3, 2, 1];
    f = True
    for i in range(9):
        board[2 - (i//3)][2 - (i%3)] = hash_of_board%10
        if hash_of_board%10 == 0:
            index = (2 - (i//3), 2 - (i%3))
        if hash_of_board%10 != v[i]:
            f = False
        hash_of_board //= 10
    return f

def nextConfig(i, j, dir):
    if i < 0 or i >= 3 or j < 0 or j >= 3:
        return False
    
    global board, val
    val = 0
    if dir == 0:
        board[i][j], board[i+1][j] = board[i+1][j], board[i][j]
        val = computeHash(board)
        board[i][j], board[i+1][j] = board[i+1][j], board[i][j]
    elif dir == 1:
        board[i][j], board[i-1][j] = board[i-1][j], board[i][j]
        val = computeHash(board)
        board[i][j], board[i-1][j] = board[i-1][j], board[i][j]
    elif dir == 2:
        board[i][j], board[i][j+1] = board[i][j+1], board[i][j]
        val = computeHash(board)
        board[i][j], board[i][j+1] = board[i][j+1], board[i][j]
    else:
        board[i][j], board[i][j-1] = board[i][j-1], board[i][j]
        val = computeHash(board)
        board[i][j], board[i][j-1] = board[i][j-1], board[i][j]
    return True

def solve(input_grid):
    visit = {}
    q = Queue()
    comeFrom = {}
    x = computeHash(input_grid)
    q.put((x, 0))
    visit[x] = True
    intial_config = x
    final_config = None

    while(not q.empty()):
        x, c = q.get()
        if(boardIsDone(x)):
            final_config = x
            break
        global index

        i, j = index
        if(nextConfig(i-1, j, 0)):
            if(val not in visit):
                visit[val] = True
                comeFrom[val] = x
                q.put((val, c+1))

        if(nextConfig(i+1, j, 1)):
            if(val not in visit):
                visit[val] = True
                comeFrom[val] = x
                q.put((val, c+1))

        if(nextConfig(i, j-1, 2)):
            if(val not in visit):
                visit[val] = True
                comeFrom[val] = x
                q.put((val, c+1))

        if(nextConfig(i, j+1, 3)):
            if(val not in visit):
                visit[val] = True
                comeFrom[val] = x
                q.put((val, c+1))
    
    if final_config == None:
        return None

    states = []
    while final_config != intial_config:
        states.append(final_config)
        final_config = comeFrom[final_config]
    
    states.reverse()
    return states

def drawGrid(input_grid):
    blockSize = 50
    offset = 100
    for i in range(3):
        for j in range(3):
            rect = pygame.Rect(i*blockSize + offset, j*blockSize + offset, blockSize, blockSize)
            FONT = pygame.font.SysFont('Calibri', 40, True, False)
            text = FONT.render(str(input_grid[i][j]), True, BLACK)
            SCREEN.fill(GREEN, (j*blockSize + offset + 1, i*blockSize + offset + 1, 35, 35))
            if(input_grid[i][j] != 0):
                SCREEN.blit(text, [j*blockSize + offset + 10, i*blockSize + offset + 10])
            pygame.draw.rect(SCREEN, BLACK, rect, 1)

def getGrid(x):
    grid = [[None for i in range(3)] for j in range(3)]
    for i in range(2, -1, -1):
        for j in range(2, -1, -1):
            grid[i][j] = x%10
            x //= 10
    return grid

def main():
    global SCREEN, CLOCK
    
    input_str = input("Enter intial grid: ")
    input_grid = [[None for i in range(3)] for j in range(3)]

    for i in range(3):
        for j in range(3):
            input_grid[i][j] = int(input_str[i*3 + j])

    states = solve(input_grid)
    if states == None:
        print("Not Possible!!")
        exit(0)

    pygame.init()
    SCREEN = pygame.display.set_mode((WINDOW_HEIGHT, WINDOW_WIDTH))
    CLOCK = pygame.time.Clock()
    SCREEN.fill(GREEN)
    next_button = pygame.draw.rect(SCREEN, RED, (120,300,100,50));
    FONT = pygame.font.SysFont('Calibri', 40, True, False)
    text = FONT.render("NEXT", True, BLACK)
    SCREEN.blit(text, [130, 310])
    
    drawGrid(input_grid)
    FONT = pygame.font.SysFont('Calibri', 40, True, False)
    text = FONT.render("STEP:  0", True, BLACK)
    SCREEN.blit(text, [100, 20])
            
    pygame.display.update()
    i = 0
    while i < len(states):
        for event in pygame.event.get():
            if event.type == pygame.MOUSEBUTTONDOWN:
                drawGrid(getGrid(states[i]))
                i += 1
                text = FONT.render("STEP:  " + str(i), True, BLACK)
                SCREEN.fill(GREEN, (100, 20, 135, 35))
                SCREEN.blit(text, [100, 20])
                pygame.display.update()
            elif event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

    SCREEN.fill(GREEN, (60, 280, 300, 100))
    text = FONT.render("DONE", True, RED)
    SCREEN.blit(text, [130, 301])
    FONT = pygame.font.SysFont('Calibri', 20, True, False)
    text = FONT.render("click anywhere to exit", True, RED)
    SCREEN.blit(text, [90, 350])
    pygame.display.update()

    while True:
        for event in pygame.event.get():
            if event.type == pygame.MOUSEBUTTONDOWN:
                sys.exit()
            elif event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

main()