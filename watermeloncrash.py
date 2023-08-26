import random
import math

#ボードの初期サイズ
BOARD_SIZE=5


def generate_position(size):
    #0以上size未満の範囲で,x座標とy座標を生成する
    x=random.randrange(0,size)
    y=random.randrange(0,size)
    return(x,y)

def calc_distance(pos1,pos2):
    diff_x=pos1[0]-pos2[0]
    diff_y=pos1[1]-pos2[1]

    return math.sqrt(diff_x**2+diff_y**2)

def move_position(direction,pos):
    #directionに従って,posを移動する

    current_x,current_y=pos
    
    if direction=="n":
        current_y=current_y-1
    elif direction=="s":
        current_y=current_y+1
    elif direction=="e":
        current_x=current_x+1
    elif direction=="w":
        current_x=current_x-1

    return(current_x,current_y)


def suika_wari():
    #スイカの位置をランダムに設定する
    #suika_x=random.randrange(0,BOARD_SIZE)
    #suika_y=random.randrange(0,BOARD_SIZE)
    suika_pos=generate_position(BOARD_SIZE)

    #プレイヤーの位置をランダムに設定する
    #player_x=random.randrange(0,BOARD_SIZE)
    #player_y=random.randrange(0,BOARD_SIZE)
    player_pos=generate_position(BOARD_SIZE)


    #スイカとプレイヤーの位置が異なっているとき,処理を繰り返す
    while suika_pos != player_pos:

        #スイカとプレイヤーの位置が異なる間,処理を繰り返す
        distance=calc_distance(player_pos,suika_pos)
        print("スイカへの距離:",distance)

        #キー入力に応じて,プレイヤーを移動する
        c=input("n:北に移動 s:南に移動 e:東に移動 w:西に移動=")
        player_pos=move_position(c,player_pos)

    print("スイカを割りました!")

suika_wari()
