#pragma once
#include "mainwindow.h"
#include <QApplication>
#include "manager.h"
#include "piece.h"
#include "board.h"
#include "blank.h"
#include "origin.h"
#include "conf.h"
#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

//增加一块拼图碎片或空白块
void addOne(const string type, const string piecePathRoot, const string rootName,int rows, int id, PieceManager *manager);

void SubGame(const string rootName, const string originName, const int size, PieceManager *manager);


