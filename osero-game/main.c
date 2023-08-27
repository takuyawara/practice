#include <stdio.h>

/* �Ղ̃T�C�Y */
#define SIZE (8)
#define WIDTH (SIZE)
#define HEIGHT (SIZE)

/* �΂̐F */
typedef enum color {
    white,
    black,
    empty
} COLOR;

/* �΂�u���邩�ǂ����̔��f */
typedef enum put {
    ok,
    ng
} PUT;

/* �Ղ�\���񎟌��z�� */
COLOR b[HEIGHT][WIDTH];

/* �Ղ������� */
int init(void) {
    unsigned char x, y;

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            b[y][x] = empty;
        }
    }

    /* �Ֆʂ̐^�񒆂ɐ΂�u�� */
    b[HEIGHT / 2][WIDTH / 2] = white;
    b[HEIGHT / 2 - 1][WIDTH / 2 - 1] = white;
    b[HEIGHT / 2 - 1][WIDTH / 2] = black;
    b[HEIGHT / 2][WIDTH / 2 - 1] = black;

    return 0;
}

/* �}�X��\�� */
int displaySquare(COLOR square) {

    switch (square) {
    case white:
        /* ���F�̐΂� "��" �ŕ\�� */
        printf("��");
        break;
    case black:
        /* ���F�̐΂� "��" �ŕ\�� */
        printf("��");
        break;
    case empty:
        /* �󂫂� " " �ŕ\�� */
        printf(" ");
        break;
    default:
        printf("�G���[");
        return -1;
    }
    return 0;
}

/* �Ղ�\�� */
int display(void) {
    int x, y;

    for (y = 0; y < HEIGHT; y++) {
        /* �Ղ̉������̃}�X�ԍ���\�� */
        if (y == 0) {
            printf(" ");
            for (x = 0; x < WIDTH; x++) {
                printf("%d", x);
            }
            printf("\n");
        }

        for (x = 0; x < WIDTH; x++) {
            /* �Ղ̏c�����̂܂��ԍ���\�� */
            if (x == 0) {
                printf("%d", y);
            }

            /* �Ղɒu���ꂽ�΂̏���\�� */
            displaySquare(b[y][x]);
        }
        printf("\n");
    }

    return 0;
}

/* �w�肳�ꂽ�ꏊ�ɐ΂�u�� */
int put(int x, int y, COLOR color) {
    int i, j;
    int s, n;
    COLOR other;

    /* ����̐΂̐F */
    if (color == white) {
        other = black;
    }
    else if (color == black) {
        other = white;
    }
    else {
        return -1;
    }

    /* �S�����ɑ΂��ċ��񂾐΂��Ђ�����Ԃ� */
    for (j = -1; j < 2; j++) {
        for (i = -1; i < 2; i++) {

            /* �^�񒆕����̓`�F�b�N���Ă����傤���Ȃ��̂Ŏ��̕����̊m�F�Ɉڂ� */
            if (i == 0 && j == 0) {
                continue;
            }

            if (y + j < 0 || x + i < 0 || y + j >= HEIGHT || x + i >= WIDTH) {
                continue;
            }
            /* �ׂ�����̐F�łȂ���΂��̕����łЂ�����Ԃ���΂͂Ȃ� */
            if (b[y + j][x + i] != other) {
                continue;
            }

            /* �u�����Ƃ��Ă���}�X���牓�������ւP�}�X���m�F */
            for (s = 2; s < SIZE; s++) {
                /* �ՖʊO�̃}�X�̓`�F�b�N���Ȃ� */
                if (
                    x + i * s >= 0 &&
                    x + i * s < WIDTH &&
                    y + j * s >= 0 &&
                    y + j * s < HEIGHT
                    ) {

                    if (b[y + j * s][x + i * s] == empty) {
                        /* �����̐΂�������O�ɋ󂫂�����ꍇ */
                        /* ���̕����̐΂͂Ђ�����Ԃ��Ȃ��̂Ŏ��̕������`�F�b�N */
                        break;
                    }

                    /* ���̕����Ɏ����̐F�̐΂�����ΐ΂��Ђ�����Ԃ��� */
                    if (b[y + j * s][x + i * s] == color) {
                        /* �΂�u�� */
                        b[y][x] = color;

                        /* ���񂾐΂��Ђ�����Ԃ� */
                        for (n = 1; n < s; n++) {
                            b[y + j * n][x + i * n] = color;
                        }
                        break;
                    }
                }
            }
        }
    }

    return 0;
}

/* �w�肳�ꂽ�ꏊ�ɒu���邩�ǂ����𔻒f */
PUT isPuttable(int x, int y, COLOR color) {
    int i, j;
    int s;
    COLOR other;
    int count;

    /* ���ɂ����ɐ΂��u���Ă���Βu���Ȃ� */
    if (b[y][x] != empty) {
        return ng;
    }

    /* ����̐΂̐F */
    if (color == white) {
        other = black;
    }
    else if (color == black) {
        other = white;
    }
    else {
        return ng;
    }
    /* �e�����ɑ΂��Ă����ɒu���Ƒ���̐΂��Ђ�����Ԃ��邩���m�F */

    /* �P�����ł��Ђ�����Ԃ���΂��̏ꏊ�ɒu���� */

    /* �u����������J�E���g */
    count = 0;

    /* �S�����ɑ΂��ċ��񂾐΂��Ђ�����Ԃ� */
    for (j = -1; j < 2; j++) {
        for (i = -1; i < 2; i++) {

            /* �^�񒆕����̓`�F�b�N���Ă����傤���Ȃ��̂Ŏ��̕����̊m�F�Ɉڂ� */
            if (i == 0 && j == 0) {
                continue;
            }

            if (y + j < 0 || x + i < 0 || y + j >= HEIGHT || x + i >= WIDTH) {
                continue;
            }

            /* �ׂ�����̐F�łȂ���΂��̕����łЂ�����Ԃ���΂͂Ȃ� */
            if (b[y + j][x + i] != other) {
                continue;
            }

            /* �u�����Ƃ��Ă���}�X���牓�������ւP�}�X���m�F */
            for (s = 2; s < SIZE; s++) {
                /* �ՖʊO�̃}�X�̓`�F�b�N���Ȃ� */
                if (
                    x + i * s >= 0 &&
                    x + i * s < WIDTH &&
                    y + j * s >= 0 &&
                    y + j * s < HEIGHT
                    ) {

                    if (b[y + j * s][x + i * s] == empty) {
                        /* �����̐΂�������O�ɋ󂫂�����ꍇ */
                        /* ���̕����̐΂͂Ђ�����Ԃ��Ȃ��̂Ŏ��̕������`�F�b�N */
                        break;;
                    }

                    /* ���̕����Ɏ����̐F�̐΂�����ΐ΂��Ђ�����Ԃ��� */
                    if (b[y + j * s][x + i * s] == color) {
                        /* �΂��Ђ�����Ԃ�����̐����J�E���g */
                        count++;
                    }
                }
            }
        }
    }

    if (count == 0) {
        return ng;
    }

    return ok;
}

/* �v���C���[���΂�u�� */
void play(COLOR color) {
    int x, y;

    /* �u���ꏊ�����܂�܂Ŗ������[�v */
    while (1) {
        /* �u���ꏊ�̓��͂���t */
        printf("�������́H");
        scanf_s("%d", &x);
        printf("�c�����́H");
        scanf_s("%d", &y);

        /* ���͂��ꂽ�ꏊ�ɂ�����Ȃ烋�[�v�𔲂��� */
        if (isPuttable(x, y, color) == ok) {
            break;
        }

        /* ���͂��ꂽ�ꏊ�ɐ΂��u���Ȃ��ꍇ�̏��� */

        printf("�����ɂ͒u���܂���!!\n");
        printf("���L�ɒu�������ł��܂�\n");

        /* �u����ꏊ��\�� */
        for (y = 0; y < HEIGHT; y++) {
            for (x = 0; x < WIDTH; x++) {
                if (isPuttable(x, y, color) == ok) {
                    printf("(%d, %d)\n", x, y);
                }
            }
        }
    }

    /* �Ō�ɐ΂�u�� */
    put(x, y, black);

}

/* COM���΂�u�� */
void com(COLOR color) {
    int x, y;

    /* �u����ꏊ��T�� */
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            if (isPuttable(x, y, color) == ok) {
                /* �u����Ȃ瑦���ɂ��̈ʒu�ɐ΂�u���ďI�� */
                put(x, y, color);
                printf("COM��(%d,%d)�ɐ΂�u���܂���\n", x, y);
                return;
            }
        }
    }
}

/* ���ʂ�\������ */
void result(void) {
    int x, y;
    int white_count, black_count;

    /* �Տ�̔��΂ƍ��΂̐����J�E���g */
    white_count = 0;
    black_count = 0;
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            if (b[y][x] == white) {
                white_count++;
            }
            else if (b[y][x] == black) {
                black_count++;
            }
        }
    }

    /* �J�E���g���ɉ����Č��ʂ�\�� */
    if (black_count > white_count) {
        printf("���Ȃ��̏����ł��I�I");
    }
    else if (white_count > black_count) {
        printf("COM�̏����ł�...");
    }
    else {
        printf("���������ł�");
    }
    printf("(��:%d / ��:%d)\n", black_count, white_count);

}

COLOR nextColor(COLOR now) {
    COLOR next;
    int x, y;

    /* �܂��͎��̐΂̐F�𑼕��̐F�̐΂ɐݒ� */
    if (now == white) {
        next = black;
    }
    else {
        next = white;
    }

    /* ���̐F�̐΂��u���邩�ǂ����𔻒f */
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            if (isPuttable(x, y, next) == ok) {
                /* �u����̂ł���Α����̐F�̐΂����̃^�[���ɒu���� */
                return next;
            }
        }
    }

    /* �����̐F�̐΂��u���Ȃ��ꍇ */

    /* ���X�̐F�̐΂��u���邩�ǂ����𔻒f */
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            if (isPuttable(x, y, now) == ok) {
                /* �u����̂ł���Ό��X�̐F�̐΂����̃^�[���ɒu���� */
                return now;
            }
        }
    }

    /* �����̐F�̐΂��u���Ȃ��̂ł���Ύ����͏I�� */
    return empty;
}

int main(void) {
    COLOR now, next;

    /* �Ղ����������ĕ\�� */
    init();
    display();

    /* �ŏ��ɒu���΂̐F */
    now = black;

    /* ���������܂Ŗ������[�v */
    while (1) {
        if (now == black) {
            /* �u���΂̐F�����̏ꍇ�͂��Ȃ����v���C */
            play(now);
            //com(now);
        }
        else if (now == white) {
            /* �u���΂̐F�����̏ꍇ��COM���v���C */
            com(now);
        }

        /* �΂�u������̔Ղ�\�� */
        display();

        /* ���̃^�[���ɒu���΂̐F������ */
        next = nextColor(now);
        if (next == now) {
            /* ���������F�̐΂̏ꍇ */
            printf("�u����ꏊ���Ȃ��̂ŃX�L�b�v���܂�\n");
        }
        else if (next == empty) {
            /* �����̐F�̐΂��u���Ȃ��ꍇ */
            printf("�����I���ł�\n");

            /* ���ʕ\�����ďI�� */
            result();
            return 0;
        }

        /* ���̃^�[���ɒu���΂�ݒ� */
        now = next;

    }
    return 0;
}