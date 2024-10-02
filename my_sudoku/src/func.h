#pragma once

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


const int size=9;

//判断一个数独矩阵是否合法
bool is_legal(int a[size][size]){
    int flag[10];
    for(int i=0;i<size;i++){
        memset(flag,0,sizeof(flag));
        for(int j=0;j<size;j++){
            if(a[i][j]&&flag[a[i][j]])return 0;
            else flag[a[i][j]]=1;
        }
        memset(flag,0,sizeof(flag));
        for(int j=0;j<size;j++){
            if(a[j][i]&&flag[a[j][i]])return 0;
            else flag[a[j][i]]=1;
        }
    }
    for(int i=0;i<size;i++){
        memset(flag,0,sizeof(flag));
        for(int j=0;j<size;j++){
            if(a[i/3*3+j/3][i%3*3+j%3]&&flag[a[i/3*3+j/3][i%3*3+j%3]])return 0;
            else flag[a[i/3*3+j/3][i%3*3+j%3]]=1;
        }
    }
    return 1;
}


//生成一个数独矩阵
bool generate(int a[size][size],int x=0){
    if(x==81)return 1;
    if(a[x/9][x%9])return generate(a,x+1);
    int i=x/9,j=x%9,flag[10],cnt=0;
    memset(flag,0,sizeof(flag));
    while(cnt<9){
        a[i][j]=rand()%9+1;
        if(flag[a[i][j]])continue;
        int temp=0;
        if(is_legal(a))temp=generate(a,x+1);
        if(temp)return 1;
        a[i][j]=0;
        flag[a[i][j]]=1;
        cnt++;
    }
    return 0;
}

//判断一个数独矩阵是否有唯一解
bool is_unique(int a[size][size],int x,int y){
    int b[size][size],k=a[x][y];
    for(int i=1;i<=9;i++){
        if(i==k)continue;
        memcpy(b,a,sizeof(b));
        b[x][y]=i;
        if(is_legal(b)&&generate(b))return 0;
    }
    return 1;
}

//将一个数独矩阵挖洞
void dig(int a[size][size],int cnt){
    while(cnt){
        int x=rand()%9,y=rand()%9;
        if(!a[x][y])continue;
        if(!is_unique(a,x,y))continue;
        a[x][y]=0;
        cnt--;
    }
}