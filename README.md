# CLI-Chess

## Description
This is a Game to just implement the basics of OOP in C++. 

## Features
- Standard chess rules
- Castling, En Passant, Promotion
- Check, Checkmate, Stalemate detection
- Two players on the same terminal
- Color coded pieces (Green = White & Red = Black)

## How to Build
make

## How to Play
- Input Format: E2 E4
- Castling 0-0 (King side) or 0-0-0 (Queen side) 

## Project Structure
CLI-Chess/
|-- src/
    |-- Pieces/
        |-- Bishop.h
        |-- King.h
        |-- Knight.h
        |-- Pawn.h
        |-- Queen.h
        |-- Rook.h
    |-- utils/
        |-- Game_Logger.h
        |-- Utlis.h
        |-- Utils.cpp
    |-- Board.h
    |-- Board.cpp
    |-- Game.h
    |-- Game.cpp
    |-- Main.cpp
    |-- Piece.h
    |-- Piece.cpp
|-- logs/
    |-- games/
|-- includes/
    |-- Constants.h
Makefile
Readme.md

## Future Plans
- Database integration
- ELO ratings
- UI migration
- AI opponent