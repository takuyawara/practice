#include <stdio.h> // scanf/printf
#include <stdlib.h> // rand/srand
#include <time.h> // time

#define NUM 3 // マス数
#define TARGET NUM // 並べたら勝ちとなる印の数
#define true 1
#define false 0
typedef int bool;

typedef enum {
    RESULT_WIN, // プレイヤーの勝ち
    RESULT_LOSE, // プレイヤーの負け
    RESULT_DRAW, // 引き分け
    RESULT_NONE // 結果が決まっていない
} RESULT;

typedef enum {
    TURN_PLAYER, // プレイヤーのターン
    TURN_COM, // コンピューターのターン
} TURN;

char board[NUM][NUM]; // マスに記入された印を管理する配列

void init(void) {
    srand(time(NULL));

    for (int x = 0; x < NUM; x++) {
        for (int y = 0; y < NUM; y++) {
            board[x][y] = ' ';
        }
    }
}

void decidePlayerPosition(int *x, int *y) {
    printf("どこに印を記入しますか？\n");
    printf("xの入力(0 - %d):", NUM - 1);
    scanf("%d", x);
    printf("yの入力(0 - %d):", NUM - 1);
    scanf("%d", y);
}

void decideComPosition(int *x, int *y) {
    *x = rand() % NUM;
    *y = rand() % NUM;
}

bool isMarkable(int x, int y) {
    if (x < 0 || x > NUM - 1 || y < 0 || y > NUM - 1) {
        printf("入力した値が不正です...\n");
        return false;
    }

    if (board[x][y] != ' ') {
        printf("そのマスはすでに埋まってマス...\n");
        return false;
    }

    return true;
}

void decidePosition(int *x, int *y, TURN turn) {
    while (true) {
        if (turn == TURN_PLAYER) {
            decidePlayerPosition(x, y);
        } else {
            decideComPosition(x, y);
        }

        if (isMarkable(*x, *y)) {
            break;
        }
    }
}

void writeMark(int x, int y, TURN turn) {

    if (turn == TURN_PLAYER) {
        board[x][y] = 'o';
    } else {
        board[x][y] = 'x';
    }
}

void printBoard(void) {
    printf(" ");
    for (int x = 0; x < NUM; x++) {
        printf("%2d", x);
    }
    printf("\n");
    for (int y = 0; y < NUM; y++) {
        printf("%d", y);
        for (int x = 0; x < NUM; x++) {
            printf("|%c", board[x][y]);
        }
        printf("|\n");
    }
    printf("\n");
}

bool judgeFull(void) {
    for (int x = 0; x < NUM; x++) {
        for (int y = 0; y < NUM; y++) {
            if (board[x][y] == ' ') {
                return false;
            }
        }
    }
    
    return true;
}

RESULT judgeResult(TURN turn) {

    int count;
    char mark;

    // 記入された印を取得
    if (turn == TURN_PLAYER) {
        mark = 'o';    
    } else {
        mark = 'x';
    }

    for (int y = 0; y < NUM; y++) {

        // 記入された印が横方向に３つ並んでいるかを確認
        count = 0;
        for (int x = 0; x < NUM; x++) {
            if (board[x][y] == mark) {
                count++;
            }
        }
        if (count == TARGET) {
            return turn == TURN_PLAYER ? RESULT_WIN : RESULT_LOSE;
        }

    }

    
    for (int x = 0; x < NUM; x++) {

        // 記入された印が縦方向に３つ並んでいるかを確認
        count = 0;
        for (int y = 0; y < NUM; y++) {
            if (board[x][y] == mark) {
                count++;
            }
        }
        if (count == TARGET) {
            return turn == TURN_PLAYER ? RESULT_WIN : RESULT_LOSE;
        }

    }

    // 記入された印が右下方向に３つ並んでいるかを確認
    count = 0;
    for (int k = 0; k < NUM; k++) {
        if (board[k][k] == mark) {
            count++;
        }
    }
    if (count == TARGET) {
        return turn == TURN_PLAYER ? RESULT_WIN : RESULT_LOSE;
    }

    // 記入された印が左下方向に３つ並んでいるかを確認
    count = 0;
    for (int k = 0; k < NUM; k++) {
        if (board[NUM - 1 - k][NUM - 1 - k] == mark) {
            count++;
        }
    }
    if (count == TARGET) {
        return turn == TURN_PLAYER ? RESULT_WIN : RESULT_LOSE;
    }

    // マスが全て埋まったかどうかを確認
    if (judgeFull()) {
        return RESULT_DRAW;
    }

    // まだ勝敗が決定していない
    return RESULT_NONE;
}

TURN nextTurn(TURN now) {
    return now == TURN_PLAYER ? TURN_COM : TURN_PLAYER;
}

void printResult(RESULT result) {

    if (result == RESULT_WIN) {
        printf("あなたの勝ちです!!!\n");
    } else if (result == RESULT_LOSE) {
        printf("あなたの負けです!!!\n");
    } else if (result == RESULT_DRAW) {
        printf("引き分けです\n");
    }
}

int main(void) {

    int x, y;
    RESULT result = RESULT_NONE;
    TURN turn = TURN_PLAYER;

    init();
    printBoard();

    do {

        // 1.○×を記入する位置を決める
        decidePosition(&x, &y, turn);

        // 2.○×を記入する
        writeMark(x, y , turn);

        // 3.3x3のマスを表示する
        printBoard();

        // 4.勝負の結果を判断する
        result = judgeResult(turn);
        
        // 5.ターンを進める
        turn = nextTurn(turn);

    // 6.勝負の結果が決まっていない場合は1.に戻る
    } while (result == RESULT_NONE);

    // 7.勝負の結果を表示する
    printResult(result);
}