#include <stdio.h> // scanf/printf
#include <stdlib.h> // rand/srand
#include <time.h> // time

#define NUM 3 // �}�X��
#define TARGET NUM // ���ׂ��珟���ƂȂ��̐�
#define true 1
#define false 0
typedef int bool;

typedef enum {
    RESULT_WIN, // �v���C���[�̏���
    RESULT_LOSE, // �v���C���[�̕���
    RESULT_DRAW, // ��������
    RESULT_NONE // ���ʂ����܂��Ă��Ȃ�
} RESULT;

typedef enum {
    TURN_PLAYER, // �v���C���[�̃^�[��
    TURN_COM, // �R���s���[�^�[�̃^�[��
} TURN;

char board[NUM][NUM]; // �}�X�ɋL�����ꂽ����Ǘ�����z��

void init(void) {
    srand(time(NULL));

    for (int x = 0; x < NUM; x++) {
        for (int y = 0; y < NUM; y++) {
            board[x][y] = ' ';
        }
    }
}

void decidePlayerPosition(int *x, int *y) {
    printf("�ǂ��Ɉ���L�����܂����H\n");
    printf("x�̓���(0 - %d):", NUM - 1);
    scanf("%d", x);
    printf("y�̓���(0 - %d):", NUM - 1);
    scanf("%d", y);
}

void decideComPosition(int *x, int *y) {
    *x = rand() % NUM;
    *y = rand() % NUM;
}

bool isMarkable(int x, int y) {
    if (x < 0 || x > NUM - 1 || y < 0 || y > NUM - 1) {
        printf("���͂����l���s���ł�...\n");
        return false;
    }

    if (board[x][y] != ' ') {
        printf("���̃}�X�͂��łɖ��܂��ă}�X...\n");
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

    // �L�����ꂽ����擾
    if (turn == TURN_PLAYER) {
        mark = 'o';    
    } else {
        mark = 'x';
    }

    for (int y = 0; y < NUM; y++) {

        // �L�����ꂽ�󂪉������ɂR����ł��邩���m�F
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

        // �L�����ꂽ�󂪏c�����ɂR����ł��邩���m�F
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

    // �L�����ꂽ�󂪉E�������ɂR����ł��邩���m�F
    count = 0;
    for (int k = 0; k < NUM; k++) {
        if (board[k][k] == mark) {
            count++;
        }
    }
    if (count == TARGET) {
        return turn == TURN_PLAYER ? RESULT_WIN : RESULT_LOSE;
    }

    // �L�����ꂽ�󂪍��������ɂR����ł��邩���m�F
    count = 0;
    for (int k = 0; k < NUM; k++) {
        if (board[NUM - 1 - k][NUM - 1 - k] == mark) {
            count++;
        }
    }
    if (count == TARGET) {
        return turn == TURN_PLAYER ? RESULT_WIN : RESULT_LOSE;
    }

    // �}�X���S�Ė��܂������ǂ������m�F
    if (judgeFull()) {
        return RESULT_DRAW;
    }

    // �܂����s�����肵�Ă��Ȃ�
    return RESULT_NONE;
}

TURN nextTurn(TURN now) {
    return now == TURN_PLAYER ? TURN_COM : TURN_PLAYER;
}

void printResult(RESULT result) {

    if (result == RESULT_WIN) {
        printf("���Ȃ��̏����ł�!!!\n");
    } else if (result == RESULT_LOSE) {
        printf("���Ȃ��̕����ł�!!!\n");
    } else if (result == RESULT_DRAW) {
        printf("���������ł�\n");
    }
}

int main(void) {

    int x, y;
    RESULT result = RESULT_NONE;
    TURN turn = TURN_PLAYER;

    init();
    printBoard();

    do {

        // 1.���~���L������ʒu�����߂�
        decidePosition(&x, &y, turn);

        // 2.���~���L������
        writeMark(x, y , turn);

        // 3.3x3�̃}�X��\������
        printBoard();

        // 4.�����̌��ʂ𔻒f����
        result = judgeResult(turn);
        
        // 5.�^�[����i�߂�
        turn = nextTurn(turn);

    // 6.�����̌��ʂ����܂��Ă��Ȃ��ꍇ��1.�ɖ߂�
    } while (result == RESULT_NONE);

    // 7.�����̌��ʂ�\������
    printResult(result);
}