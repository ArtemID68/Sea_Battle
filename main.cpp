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
