#include <iostream>
#include "Board.h"
#include "MoveGenerator.h"
#include "Game.h"
#include "Evaluator.h"
#include "AI.h"
#include <SFML/Graphics.hpp>
#include <optional>
#include "Renderer.h"



int main()

{
    Game game;
    game.runGraphicalInterface();
    return 0;

}