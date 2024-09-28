class Grid:
    def __init__(self, box_size=3, grid_size=9):
        self.box_size = box_size
        self.grid_size = grid_size
        self.grid = [[0] * grid_size for _ in range(grid_size)]

    def get_row(self, row):
        return self.grid[row]

    def get_column(self, col):
        return [self.grid[i][col] for i in range(self.grid_size)]

    def get_box(self, row, col):
        box = []
        row_start = (row // self.box_size) * self.box_size
        col_start = (col // self.box_size) * self.box_size
        for i in range(self.box_size):
            for j in range(self.box_size):
                box.append(self.grid[row_start + i][col_start + j])
        return box

    def serialize(self):
        return ''.join(str(num) for row in self.grid for num in row)

    def __eq__(self, other):
        return self.grid == other.grid


class Sudoku:
    def __init__(self):
        self.my_grid = Grid()

    def parse(self, input_str):
        for i in range(self.my_grid.grid_size):
            for j in range(self.my_grid.grid_size):
                ch = input_str[i * self.my_grid.grid_size + j]
                self.my_grid.grid[i][j] = int(ch)  # Convert char to int

    def print_grid(self):
        for row in self.my_grid.grid:
            print(" ".join(map(str, row)))

    def get_inference(self, row, col):
        candidate = []
        used_numbers = set()

        row_values = self.my_grid.get_row(row)
        col_values = self.my_grid.get_column(col)
        box_values = self.my_grid.get_box(row, col)

        for num in row_values + col_values + box_values:
            used_numbers.add(num)

        for num in range(1, 10):
            if num not in used_numbers:
                candidate.append(num)

        return candidate


def test(input_str):
    test1 = Sudoku()
    print("test1:")
    test1.parse(input_str)
    test1.print_grid()

    test_result = test1.get_inference(3, 7)
    print("inference_result in pos (3,7):")
    print(" ".join(map(str, test_result)))

    test2 = Sudoku()
    test2.my_grid = test1.my_grid
    test3 = Sudoku()
    test3.my_grid = test2.my_grid

    print("test2:")
    test2.print_grid()
    print("test3:")
    test3.print_grid()


if __name__ == "__main__":
    input_str = "017903600000080000900000507072010430000402070064370250701000065000030000005601720"
    test(input_str)

