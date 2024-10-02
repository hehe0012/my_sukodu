#pragma once

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include "func.h"

//控制颜色
void setcolor(int x){
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut,x);
}

//输出一个数独矩阵
void print(int a[size][size],int b[size][size]){
    std::cout<<std::endl;
    for(int i=0;i<size;i++){
        for(int j=0;j<size+10;j++){
            std::cout<<"-";
        }
        std::cout<<std::endl;
        for(int j=0;j<size;j++){
            char c=a[i][j]?a[i][j]+'0':'?';
            std::cout<<"|";
            if(b[i][j]/10&&!(b[i][j]%10)){
                setcolor(FOREGROUND_INTENSITY|FOREGROUND_RED|BACKGROUND_BLUE|BACKGROUND_INTENSITY);
                std::cout<<c;
                setcolor(FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            }
            else if(b[i][j]/10&&b[i][j]%10){
                setcolor(FOREGROUND_INTENSITY|FOREGROUND_RED|BACKGROUND_BLUE|BACKGROUND_INTENSITY);
                std::cout<<c;
                setcolor(FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            }
            else if(!b[i][j]%10){
                setcolor(FOREGROUND_INTENSITY|FOREGROUND_RED);
                std::cout<<c;
                setcolor(FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            }
            else{
                std::cout<<c;
            }
            if(j==size-1)std::cout<<"|";
        }
        std::cout<<std::endl;
        if(i==size-1){
            for(int j=0;j<size+10;j++){
                std::cout<<"-";
            }
            std::cout<<std::endl;
        }
    }
}

//填写数独
void fill(int a[size][size],int ans[size][size],int game1[size][size]){
    int x=0,y=0,ch;
    game1[x][y]+=10;
    std::cout<<"press 'ESC' to exit"<<std::endl;
    std::cout<<"press WASD to move"<<std::endl;
    print(a,game1);
    while(1){
        ch=_getch();
        if(ch==27)exit(0);
        if(ch==87){
            if(!x)continue;
            game1[x][y]-=10;
            game1[--x][y]+=10;
        }
        else if(ch==65){
            if(!y)continue;
            game1[x][y]-=10;
            game1[x][--y]+=10;
        }
        else if(ch==83){
            if(x==8)continue;
            game1[x][y]-=10;
            game1[++x][y]+=10;
        }
        else if(ch==68){
            if(y==8)continue;
            game1[x][y]-=10;
            game1[x][++y]+=10;
        }
        else if(ch>48&&ch<=57){
            if(game1[x][y]%10)continue;
            a[x][y]=ch-48;
        }
        else if(ch==48){
            print(ans,ans);
        }
        else continue;
        if(!memcmp(a,ans,sizeof(int)*size*size)){
            std::cout<<"congratulations! you win!"<<std::endl;
            return;
        }
        std::cout<<"press 'ESC' to exit"<<std::endl;
        std::cout<<"press WASD to move"<<std::endl;
        print(a,game1);
    }
}

//开始游戏
void start_game(){
    setcolor(FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    std::cout<<"welcome to sudoku!"<<std::endl;
    std::cout<<"please select the game level:"<<std::endl<<"1.easy"<<std::endl<<"2.medium"<<std::endl<<"3.hard"<<std::endl<<"4.exit"<<std::endl;
    int game_level=_getch()-48;
    if(game_level==4)exit(0);
    int a[size][size],game[size][size],game1[size][size];
    memset(a,0,sizeof(a));
    generate(a);
    memccpy(game,a,sizeof(a),sizeof(a));
    int cnt;
    if(game_level==1){
        dig(game,20);cnt=20;
    }
    else if(game_level==2){
        dig(game,30);cnt=30;
    }
    else if(game_level==3){
        dig(game,40);cnt=40;
    }
    memccpy(game1,game,sizeof(game),sizeof(game));
    fill(game,a,game1);
}

