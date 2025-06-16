#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int BOARD_SIZE = 5;   // Размер игрового поля: 5x5
const int NUM_SHIPS = 3;    // Количество кораблей на поле

// Функция инициализации поля: заполняет его символом '-' (вода)
void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            board[row][col] = '-';
        }
    }
}

// Функция размещения кораблей на поле. Корабли обозначаются символом 'S'
void placeShips(char board[BOARD_SIZE][BOARD_SIZE]) {
    int shipsPlaced = 0;
    while (shipsPlaced < NUM_SHIPS) {
        int row = rand() % BOARD_SIZE;
        int col = rand() % BOARD_SIZE;
        // Если в этой клетке нет корабля, размещаем его
        if (board[row][col] != 'S') {
            board[row][col] = 'S';
            shipsPlaced++;
        }
    }
}

// Функция вывода поля на экран.
// Если hideShips равен true (например, при показе поля компьютера),
// то клетки с кораблями скрываются символом '-' (водой)
void printBoard(char board[BOARD_SIZE][BOARD_SIZE], bool hideShips) {
    cout << "  ";
    for (int col = 0; col < BOARD_SIZE; col++) {
        cout << col << " ";
    }
    cout << endl;
    for (int row = 0; row < BOARD_SIZE; row++) {
        cout << row << " ";
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (hideShips && board[row][col] == 'S') {
                cout << "- ";
            } else {
                cout << board[row][col] << " ";
            }
        }
        cout << endl;
    }
}

// Функция проверки: остались ли ещё корабли на поле?
// Возвращает true, если обнаружен хотя бы один корабль ('S')
bool shipsRemaining(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == 'S') {
                return true;
            }
        }
    }
    return false;
}

int main() {
    // Инициализируем генератор случайных чисел
    srand(time(0));

    // Объявляем поля для игрока и компьютера
    char playerBoard[BOARD_SIZE][BOARD_SIZE];
    char computerBoard[BOARD_SIZE][BOARD_SIZE];

    // Инициализируем пустые поля (заполнение символом '-')
    initializeBoard(playerBoard);
    initializeBoard(computerBoard);

    // Размещаем корабли на полях
    placeShips(playerBoard);
    placeShips(computerBoard);

    cout << "Ваше поле:" << endl;
    printBoard(playerBoard, false);

    // Основной игровой цикл
    while (true) {
        int row, col;
        
        // Ход игрока
        cout << "\nВаш ход. Введите координаты выстрела (номер ряда и номер столбца): ";
        cin >> row >> col;

        // Проверка корректности введённых координат
        if (row < 0  row >= BOARD_SIZE  col < 0 || col >= BOARD_SIZE) {
            cout << "Неверные координаты. Попробуйте ещё раз." << endl;
            continue;
        }

        // Если по этой клетке уже стреляли (обозначено символами 'X' для попадания или '*' для промаха)
        if (computerBoard[row][col] == 'X' || computerBoard[row][col] == '*') {
            cout << "Вы уже стреляли в эту клетку. Выберите другую." << endl;
            continue;
        }

        // Проверяем: если в клетке есть корабль, то это попадание
        if (computerBoard[row][col] == 'S') {
            cout << "Попадание! Вы потопили корабль противника!" << endl;
            computerBoard[row][col] = 'X';  // Записываем попадание
        } else {
            cout << "Промах." << endl;
            computerBoard[row][col] = '*';  // Записываем промах
        }

        // Проверяем, остались ли ещё корабли у компьютера
        if (!shipsRemaining(computerBoard)) {
            cout << "\nПоздравляем! Вы выиграли!" << endl;
            break;
        }

        cout << "\nПоле противника:" << endl;
        printBoard(computerBoard, true);
        // Ход компьютера
        cout << "\nХод противника:" << endl;
        int compRow, compCol;
        // Компьютер выбирает случайные координаты, при условии, что по ним ещё не стреляли
        do {
            compRow = rand() % BOARD_SIZE;
            compCol = rand() % BOARD_SIZE;
        } while (playerBoard[compRow][compCol] == 'X' || playerBoard[compRow][compCol] == '*');

        cout << "Компьютер выбрал: " << compRow << " " << compCol << endl;
        
        if (playerBoard[compRow][compCol] == 'S') {
            cout << "Компьютер попал в ваш корабль!" << endl;
            playerBoard[compRow][compCol] = 'X';
        } else {
            cout << "Компьютер промахнулся." << endl;
            playerBoard[compRow][compCol] = '*';
        }

        // Проверяем, остались ли ещё корабли у игрока
        if (!shipsRemaining(playerBoard)) {
            cout << "\nВсе ваши корабли потоплены. Вы проиграли." << endl;
            break;
        }

        cout << "\nВаше поле:" << endl;
        printBoard(playerBoard, false);
    }

    return 0;
}
