import pygame
import random

pygame.init()

# Dimensions de la fenêtre
s_width = 800
s_height = 700
play_width = 300 
play_height = 600   
block_size = 30

top_left_x = (s_width - play_width) // 2
top_left_y = s_height - play_height - 50

# Formes de Tetris
S = [['.....',
    '.....',
    '..00.',
    '.00..',
    '.....'],
     ['.....',
    '..0..',
    '..00.',
    '...0.',
    '.....']]

Z = [['.....',
    '.....',
    '.00..',
    '..00.',
    '.....'],
     ['.....',
    '..0..',
    '.00..',
    '.0...',
    '.....']]

I = [['.....',
    '..0..',
    '..0..',
    '..0..',
    '..0..'],
     ['.....',
    '0000.',
    '.....',
    '.....',
    '.....']]

O = [['.....',
    '.....',
    '.000.',
    '.000.',
    '.....']]

J = [['.....',
    '.0...',
    '.000.',
    '.....',
    '.....'],
     ['.....',
    '..00.',
    '..0..',
    '..0..',
    '.....'],
     ['.....',
    '.....',
    '.000.',
    '...0.',
    '.....'],
     ['.....',
    '..0..',
    '..0..',
    '.00..',
    '.....']]

L = [['.....',
    '...0.',
    '.000.',
    '.....',
    '.....'],
     ['.....',
    '..0..',
    '..0..',
    '..00.',
    '.....'],
     ['.....',
    '.....',
    '.000.',
    '.0...',
    '.....'],
     ['.....',
    '.00..',
    '..0..',
    '..0..',
    '.....']]

T = [['.....',
    '..0..',
    '.000.',
    '.....',
    '.....'],
     ['.....',
    '..0..',
    '..00.',
    '..0..',
    '.....'],
     ['.....',
    '.....',
    '.000.',
    '..0..',
    '.....'],
     ['.....',
    '..0..',
    '.00..',
    '..0..',
    '.....']]

shapes = [S, Z, I, O, J, L, T]
shape_colors = [(0, 255, 0), (255, 0, 0), (0, 255, 255), (255, 255, 0), (255, 165, 0), (0, 0, 255), (128, 0, 128)]

# Classe pour les pièces
class Piece(object):
    def __init__(self, x, y, shape):
      self.x = x
      self.y = y
      self.shape = shape
      self.color = shape_colors[shapes.index(shape)]
      self.rotation = 0

def create_grid(locked_positions={}):
    grid = [[(0,0,0) for x in range(10)] for y in range(20)]

    for y in range(len(grid)):
      for x in range(len(grid[y])):
        if (x, y) in locked_positions:
            c = locked_positions[(x, y)]
            grid[y][x] = c
    return grid

def convert_shape_format(piece):
    positions = []
    format = piece.shape[piece.rotation % len(piece.shape)]

    for i, line in enumerate(format):
      row = list(line)
      for j, column in enumerate(row):
        if column == '0':
            positions.append((piece.x + j, piece.y + i))

    for i, pos in enumerate(positions):
      positions[i] = (pos[0] - 2, pos[1] - 4)

    return positions

# cela pourrait (devrait?) être une méthode de la classe Piece
# def convert_shape_format(self):
#    positions = []
#    format = self.shape[self.rotation % len(self.shape)]
# ...


def valid_space(piece, grid):
    accepted_positions = [[(x, y) for x in range(10) if grid[y][x] == (0, 0, 0)] for y in range(20)]
    accepted_positions = [x for item in accepted_positions for x in item]

    formatted = convert_shape_format(piece)

    for pos in formatted:
      if pos not in accepted_positions:
        if pos[1] > -1:
            return False
    return True

# Idem

def check_lost(positions):
    for pos in positions:
      x, y = pos
      if y < 1:
        return True
    return False

def get_shape():
    return Piece(5, 0, random.choice(shapes))

# On peut (mais pas forcément en fonction du contexte) en faire une méthode de classe
# à l'image d'un constructeur.
# @classmethod
# def get_shape(cls, shapes):
#    return cls(5, 0, random.choice(shapes)) 

# On peut aussi penser à factoriser le code petit à petit et passer
# x et y en paramètre de la méthode (ou au moins indiquer à quoi cela correspond).

def draw_text_middle(text, size, color, surface):
    font = pygame.font.SysFont('comicsans', size, bold=True)
    label = font.render(text, 1, color)

    surface.blit(label, (top_left_x + play_width/2 - (label.get_width() / 2), top_left_y + play_height/2 - label.get_height()/2))
    # On préfère souvent créer un mapping entre blocs et pixels
    # typiquement une fonction block_to_pixel qui prend en paramètre un bloc (x, y)
    # et renvoie les coordonnées du pixel correspondant.
    # Cela permet ensuite de tout factoriser proprement et ne pas tout casser si on change de résolution

def draw_grid(surface, grid):
    sx = top_left_x
    sy = top_left_y

    for i in range(len(grid)):
      pygame.draw.line(surface, (128,128,128), (sx, sy + i*block_size), (sx + play_width, sy + i * block_size))
      for j in range(len(grid[i])):
        pygame.draw.line(surface, (128,128,128), (sx + j*block_size, sy), (sx + j*block_size, sy + play_height))

def clear_rows(grid, locked):
    increment = 0
    for i in range(len(grid)-1, -1, -1):
      row = grid[i]
      if (0, 0, 0) not in row:
        increment += 1
        ind = i
        for j in range(len(row)):
            try:
              del locked[(j, i)]
            except:
              continue

    if increment > 0:
      for key in sorted(list(locked), key=lambda x: x[1])[::-1]:
        # La fonction sorted accepte un argument "reverse" (True ou False par défaut)
        x, y = key
        if y < ind:
            newKey = (x, y + increment)
            locked[newKey] = locked.pop(key)

    return increment

def draw_next_shape(piece, surface):
    font = pygame.font.SysFont('comicsans', 30)
    label = font.render('Next Shape', 1, (255,255,255))

    sx = top_left_x + play_width + 50
    sy = top_left_y + play_height/2 - 100
    format = piece.shape[piece.rotation % len(piece.shape)]

    for i, line in enumerate(format):
      row = list(line)
      for j, column in enumerate(row):
        if column == '0':
            pygame.draw.rect(surface, piece.color, (sx + j*block_size, sy + i*block_size, block_size, block_size), 0)

    surface.blit(label, (sx + 10, sy - 30))

def draw_window(surface, grid, score=0):
    surface.fill((0, 0, 0))

    pygame.font.init()
    font = pygame.font.SysFont('comicsans', 60)
    label = font.render('Tetris', 1, (255, 255, 255))

    surface.blit(label, (top_left_x + play_width / 2 - (label.get_width() / 2), 30))

    font = pygame.font.SysFont('comicsans', 30)
    label = font.render('Score: ' + str(score), 1, (255, 255, 255))

    sx = top_left_x + play_width + 50
    sy = top_left_y + play_height/2 - 100

    surface.blit(label, (sx + 20, sy + 160))

    for i in range(len(grid)):
      for j in range(len(grid[i])):
        pygame.draw.rect(surface, grid[i][j], (top_left_x + j*block_size, top_left_y + i*block_size, block_size, block_size), 0)

    draw_grid(surface, grid)
    pygame.draw.rect(surface, (255, 0, 0), (top_left_x, top_left_y, play_width, play_height), 5)

def main():
    locked_positions = {}
    grid = create_grid(locked_positions)

    change_piece = False
    run = True
    current_piece = get_shape()
    next_piece = get_shape()
    clock = pygame.time.Clock()
    fall_time = 0
    level_time = 0
    score = 0

    while run:
      grid = create_grid(locked_positions)
      fall_speed = 0.27

      fall_time += clock.get_rawtime()
      level_time += clock.get_rawtime()
      clock.tick()

      if level_time/1000 > 5:
        level_time = 0
        if fall_speed > 0.12:
            fall_speed -= 0.005

      if fall_time/1000 >= fall_speed:
        fall_time = 0
        current_piece.y += 1
        if not (valid_space(current_piece, grid)) and current_piece.y > 0:
            current_piece.y -= 1
            change_piece = True

      for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False
            pygame.display.quit()
            quit()

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_LEFT:
              current_piece.x -= 1
              if not valid_space(current_piece, grid):
                current_piece.x += 1
            if event.key == pygame.K_RIGHT:
              current_piece.x += 1
              if not valid_space(current_piece, grid):
                current_piece.x -= 1
            if event.key == pygame.K_DOWN:
              current_piece.y += 1
              if not valid_space(current_piece, grid):
                current_piece.y -= 1
            if event.key == pygame.K_UP:
              current_piece.rotation = current_piece.rotation + 1 % len(current_piece.shape)
              if not valid_space(current_piece, grid):
                current_piece.rotation = current_piece.rotation - 1 % len(current_piece.shape)

      shape_pos = convert_shape_format(current_piece)

      for i in range(len(shape_pos)):
        x, y = shape_pos[i]
        if y > -1:
            grid[y][x] = current_piece.color

      if change_piece:
        for pos in shape_pos:
            p = (pos[0], pos[1])
            locked_positions[p] = current_piece.color
        current_piece = next_piece
        next_piece = get_shape()
        change_piece = False
        score += clear_rows(grid, locked_positions) * 10

      draw_window(win, grid, score)
      draw_next_shape(next_piece, win)
      pygame.display.update()

      if check_lost(locked_positions):
        draw_text_middle("YOU LOST", 80, (255,255,255), win)
        pygame.display.update()
        pygame.time.delay(1500)
        run = False

def main_menu():
    run = True
    while run:
      win.fill((0,0,0))
      draw_text_middle('Press Any Key To Play', 60, (255,255,255), win)
      pygame.display.update()
      for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False
        if event.type == pygame.KEYDOWN:
            main()
    pygame.display.quit()

win = pygame.display.set_mode((s_width, s_height))
pygame.display.set_caption('Tetris')
main_menu()








# A titre d'exemple je vous met quelques morceaux d'un projet que j'avais fait il y a pas mal de temps maintenant
from PIL import Image
import pygame

class GraphicInterface:
    def __init__(self, map):
        self.map = map
        self.block_size = Image.open(constants.WALL_IMAGE).size[0]

        width_pixels = self.block_to_pixels(self.map.width)
        height_pixels = self.block_to_pixels(self.map.height)
        self.window = pygame.display.set_mode((width_pixels, height_pixels))

        pygame.display.set_caption(map.name)
        pygame.display.set_icon(pygame.image.load(constants.MAIN_IMAGE))

    def block_to_pixels(self, block):
        return round(block * self.block_size)

    def display(self, image, x_block, y_block):
        x_pixels = self.block_to_pixels(x_block)
        y_pixels = self.block_to_pixels(y_block)
        self.window.blit(pygame.image.load(image), (y_pixels, x_pixels))

    def show_text(self, text, x_block=4, y_block=4, size=0.75, delay=0, r_color=255, g_color=255, b_color=255):
        font = pygame.font.Font("freesansbold.ttf", self.block_to_pixels(size))
        text = font.render(text, True, (r_color, g_color, b_color))
        self.window.blit(text, (self.block_to_pixels(x_block), self.block_to_pixels(y_block)))
        pygame.display.flip()
        pygame.time.delay(delay)

    def game_loop(self):
        pygame.init()
        pygame.mixer.music.load(constants.MUSIC)
        pygame.mixer.music.play(loops=-1)
        self.load_all()

        while not self.map.game_over:
            # Event handler code
            # On peut éventuellement injecter la logique en paramètre
            pygame.display.flip()
        pygame.quit()

# La classe est factorisée de telle sorte qu'elle est utilisable avec n'importe quel backend (à quelques choses près que l'on pourrait également refactoriser)
# Puis depuis le code appelant
map = Map(name='toto')
gui = GraphicInterface(map)
gui.game_loop()
