#include "TimeManager.h"
#include "GlobalVars.h"
/// <summary>
/// Sets the needed variables
/// </summary>
void Setup();
/// <summary>
/// Handles the inputs
/// </summary>
void Input();
/// <summary>
/// Handles the logic of the game
/// </summary>
void Logic();
/// <summary>
/// Draws the screen
/// </summary>
void Draw();
GlobalVars variables = GlobalVars();


int main()
{
    Setup();
    while (variables.run)
    {
        Input();
        Logic();
        Draw();
    }
}

void Setup()
{
    std::cout.sync_with_stdio(false);
    srand(time(NULL));
    unsigned short enemyNumber = 0;
    std::cout << "Cuantos Enemigos Quieres?";
    std::cin >> enemyNumber;
    if (enemyNumber > 4) {
        enemyNumber = 4;
    }
    for (size_t i = 0; i < enemyNumber; i++)
    {
        variables.enemigos.push_back(Enemy(variables.pacman_map.spawn_enemy));
    }
}

void Input()
{
    variables.input = USER_INPUTS::NONE;
    if (ConsoleUtils::KeyPressed(VK_UP) || ConsoleUtils::KeyPressed('W'))
    {
        variables.input = USER_INPUTS::UP;
    }
    if (ConsoleUtils::KeyPressed(VK_DOWN) || ConsoleUtils::KeyPressed('S'))
    {
        variables.input = USER_INPUTS::DOWN;
    }
    if (ConsoleUtils::KeyPressed(VK_RIGHT) || ConsoleUtils::KeyPressed('D'))
    {
        variables.input = USER_INPUTS::RIGHT;
    }
    if (ConsoleUtils::KeyPressed(VK_LEFT) || ConsoleUtils::KeyPressed('A'))
    {
        variables.input = USER_INPUTS::LEFT;
    }
    if (ConsoleUtils::KeyPressed(VK_ESCAPE) || ConsoleUtils::KeyPressed('Q'))
    {
        variables.input = USER_INPUTS::QUIT;
    }
}

void Logic()
{
    if (variables.win)
    {
        switch (variables.input)
        {
        case QUIT:
            variables.run = false;
            break;
        }
    }
    else if (variables.lose) {
        switch (variables.input)
        {
        case QUIT:
            variables.run = false;
            break;
        }
    }
    else
    {
        if (variables.input == USER_INPUTS::QUIT) {
            variables.run = false;
        }
        variables.player.Update(&variables.pacman_map, variables.input, &variables.enemigos);
        for (size_t i = 0; i < variables.enemigos.size(); i++)
        {
            Enemy::ENEMY_STATE enemy1state = variables.enemigos[i].Update(&variables.pacman_map, variables.player.position);
            switch (enemy1state)
            {
            case Enemy::ENEMY_KILLED:
                variables.player.points += 50;
                break;
            case Enemy::ENEMY_DEAD:
                variables.player.Kill();
                break;
            default:
                break;
            }
        }
        if (variables.player.vidas <= 0) {
            variables.lose = true;
        }
        if (variables.pacman_map.points <= 0)
        {
            variables.win = true;
        }

    }
}

void Draw()
{
    ConsoleUtils::Console_SetPos(0, 0);
    variables.pacman_map.Draw();
    variables.player.Draw();
    for (size_t i = 0; i < variables.enemigos.size(); i++)
    {
        variables.enemigos[i].Draw();
    }
    //enemy1.Draw();
    ConsoleUtils::Console_ClearCharacter({ 0,(short)variables.pacman_map.Height });
    ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::CYAN);
    std::cout << "Puntuacion actual: " << variables.player.points << " Puntuacion pendiente: " << variables.pacman_map.points << " Vidas: " << variables.player.vidas << std::endl;
    if (variables.win)
    {
        ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::GREEN);
        std::cout << "Has ganado!" << std::endl;
    }
    else if (variables.lose) {
        ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::RED);
        std::cout << "Has perdido!" << std::endl;
    }
    TimeManager::getInstance().NextFrame();
}