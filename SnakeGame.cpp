#include <iostream>
#include <raylib.h>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

char playerName[20] = "You";
int HighScore = 0;

int main() {
    srand(time(0));

    const int width = 1000;
    const int height = 800;
    const float unit = 40.0f;
    float sc = 200.0f;

    InitWindow(width, height, "SnakeGame");
    SetTargetFPS(60);

    // Read High Score
    std::ifstream readFile("highscore.txt");
    if (readFile.is_open()) {
        readFile >> HighScore;
        readFile.ignore();
        readFile.getline(playerName, 20);
        readFile.close();
    }

    InitAudioDevice();
    Sound eat = LoadSound("eat.wav");
    Sound over = LoadSound("over.wav");

    while (!WindowShouldClose()) {
        // Reset game state
        int num1 = (rand() % (int)(width - 2 * unit)) + unit;
        int num2 = (rand() % (int)(height - 2 * unit)) + unit;

        Vector2 pos = { (float)width / 2.0f, (float)height / 2.0f };
        Vector2 speed = { 0, 0 };
        Vector2 food = { (float)num1, (float)num2 };
        Color bg = { 0, 0, 0, 255 };
        Color food_color = { 255, 0, 0, 255 };
        Color snake_color = { 81, 114, 55, 255 };

        bool gameOver = false;
        int body = 0;
        int score = 0;
        bool game_pause = false;
        Vector2 pause_speed;
        std::vector<Vector2> snake_body;
        bool newHighScore = false;

        // Main game loop
        while (!WindowShouldClose() && !gameOver) {

            // Pause game
            if (IsKeyPressed(KEY_SPACE)) {
                if (speed.x == 0 && speed.y == 0) {
                    game_pause = false;
                    speed = pause_speed;
                } else {
                    pause_speed = speed;
                    game_pause = true;
                    speed = { 0, 0 };
                }
            }

            // Controls
            if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && speed.y != sc && !game_pause) {
                speed = { 0, -sc };
            } else if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) && speed.y != -sc && !game_pause) {
                speed = { 0, sc };
            } else if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && speed.x != sc && !game_pause) {
                speed = { -sc, 0 };
            } else if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && speed.x != -sc && !game_pause) {
                speed = { sc, 0 };
            }

            // Border collision
            if (pos.x <= 0 || pos.y <= 0 || pos.x >= width - unit || pos.y >= height - unit) {
                PlaySound(over);
                gameOver = true;
            }

            Rectangle snake = { pos.x, pos.y, unit, unit };

            // Food collision
            if (CheckCollisionCircleRec(food, unit / 2, snake)) {
                food.x = (rand() % (int)(width - 2 * unit)) + unit;
                food.y = (rand() % (int)(height - 2 * unit)) + unit;
                score += 1;
                if (score % 10 == 0) sc += 50.0f;
                body += 10;
                PlaySound(eat);
            }

            // Snake movement
            pos.x += speed.x * GetFrameTime();
            pos.y += speed.y * GetFrameTime();

            // Snake body management
            snake_body.insert(snake_body.begin(), pos);
            if (snake_body.size() > body + 1) {
                snake_body.pop_back();
            }

            // Self-collision
            if (snake_body.size() > 20) {
                for (int i = 1; i < snake_body.size(); i++) {
                    if (!game_pause && CheckCollisionRecs(
                        { snake_body[0].x, snake_body[0].y, 1, 1 },
                        { snake_body[i].x, snake_body[i].y, 1, 1 })) {
                        PlaySound(over);
                        gameOver = true;
                        break;
                    }
                }
            }

            // Draw game
            BeginDrawing();
                ClearBackground(bg);

                if (game_pause) {
                    DrawText("PAUSED", (width / 2) - 100, height / 2, 50, GRAY);
                }

                DrawText(TextFormat("Score: %i", score), 25, 25, 30, BLUE);
                DrawText(TextFormat("High Score: %i", HighScore), 25, 65, 30, GOLD);
                DrawText(TextFormat("By: %s", playerName), 25, 105, 30, GOLD);

                DrawCircle(food.x, food.y, unit / 2, food_color);
                DrawRectangle(pos.x, pos.y, unit, unit, snake_color);

                for (int i = 1; i < snake_body.size(); i++) {
                    DrawCircle(snake_body[i].x + unit / 2, snake_body[i].y + unit / 2, unit / 2, snake_color);
                }
            EndDrawing();
        }

        // Post-game state
        int nameLength = 0;
        bool nameEntered = false;
        char inputChar = '\0';

        if (score > HighScore) {
            HighScore = score;
            newHighScore = true;

            std::ofstream writeFile("highscore.txt");
            if (writeFile.is_open()) {
                writeFile << HighScore;
                writeFile.close();
            }
        }

        // Game Over Screen
        while (!WindowShouldClose()) {
            BeginDrawing();
                ClearBackground(BLACK);

                DrawText("GAME OVER", (width / 2) - 175, (height / 2) - 50, 50, RED);
                DrawText("Press R to Restart or ESC to Exit", (width / 2) - 280, (height / 2) + 130, 30, GRAY);

                if (newHighScore) {
                    DrawText("New High Score!", (width / 2) - 180, (height / 2) - 100, 40, GREEN);

                    if (!nameEntered) {
                        DrawText("Enter Your Name:", (width / 2) - 155, (height / 2) + 10, 30, LIGHTGRAY);
                        DrawText(playerName, (width / 2) - 120, (height / 2) + 60, 30, SKYBLUE);

                        int key = GetCharPressed();
                        while (key > 0) {
                            if (nameLength < 19 && key != '\n') {
                                playerName[nameLength++] = (char)key;
                                playerName[nameLength] = '\0';
                            }
                            key = GetCharPressed();
                        }

                        if (IsKeyPressed(KEY_BACKSPACE) && nameLength > 0) {
                            nameLength--;
                            playerName[nameLength] = '\0';
                        }

                        if (IsKeyPressed(KEY_ENTER) && nameLength > 0) {
                            nameEntered = true;

                            std::ofstream writeFile("highscore.txt");
                            if (writeFile.is_open()) {
                                writeFile << HighScore << " " << playerName << "\n";
                                writeFile.close();
                            }
                        }
                    } else {
                        DrawText(TextFormat("Thanks, %s!", playerName), (width / 2) - 150, (height / 2) + 30, 30, GREEN);
                    }
                }
            EndDrawing();

            if (IsKeyPressed(KEY_R) && (!newHighScore || nameEntered)) {
                break;
            }

            if (IsKeyPressed(KEY_ESCAPE)) {
                CloseWindow();
                return 0;
            }
        }
    }

    UnloadSound(over);
    UnloadSound(eat);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}