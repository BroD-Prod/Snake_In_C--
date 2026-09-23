#include <iostream>
#include <deque>
#include <ncurses.h>

struct Position{
    int row;
    int col;
};

struct startPosition{
    int snakeStartRow {7};
    int snakeStartCol {22};
};

class Snake {
    private:
        Position head;
        std::deque <Position> snakeBody{};
        char input;
        int length;

    public:
        int getSnakeSize(){
            return snakeBody.size();
        }

        const std::deque <Position>& getSnakeBody() const{
            return snakeBody;
        }

        Snake(int startRow, int startCol){
            head.row = startRow;
            head.col = startCol;

            snakeBody.push_back({startRow, startCol + 1});
            snakeBody.push_back({startRow, startCol + 2});
        }
        
        void moveRight(){
            snakeBody.push_front(head);
            snakeBody.pop_back();
            ++head.col;
        }

        void growRight(){
            snakeBody.push_front(head);
            ++head.col;
        }
        
        void moveLeft(){
            snakeBody.push_front(head);
            snakeBody.pop_back();
            --head.col;
        }

        void growLeft(){
            snakeBody.push_front(head);
            --head.col;
        }

        void moveUp(){
            snakeBody.push_front(head);
            snakeBody.pop_back();
            --head.row;
        }

        void growUp(){
            snakeBody.push_front(head);
            --head.row;
        }

        void moveDown(){
            snakeBody.push_front(head);
            snakeBody.pop_back();
            ++head.row;
        }

        void growDown(){
            snakeBody.push_front(head);
            ++head.row;
        }

        void MoveSnake(char input, bool hasEatenFruit){
            switch(input){
                case 'w':
                    if(hasEatenFruit) growUp(); else moveUp();
                    break;
                case 's':
                    if(hasEatenFruit) growDown(); else moveDown();
                    break;
                case 'd':
                    if(hasEatenFruit) growRight(); else moveRight();
                    break;
                case 'a':
                    if(hasEatenFruit) growLeft(); else moveLeft();
                    break;
            }
        }

        Position getHeadPosition() const {
            return head;
        }
};

class Map {
    private:
        const int height {15};
        const int width {45};
        Position fruit {rand() % (14 + 1 - 1), rand() % (44 + 1 - 1)};

    public:
        
        Position getFruitpPosition(){
            return fruit;
        }

         void generateNewFruit(){
            fruit.row = rand() % (14 + 1 - 1);
            fruit.col = rand() % (44 + 1 - 1);
        }

        bool createMap(Snake& snake){
            clear();
            Position snakeHead = snake.getHeadPosition();
            const std::deque <Position> snakeBody = snake.getSnakeBody();
            for(int i{0}; i < snakeBody.size(); ++i){
                if(snakeHead.row == snakeBody[i].row && snakeHead.col == snakeBody[i].col){
                    return false;
                }
            }
            
            if(snakeHead.row <= 0 || snakeHead.row >= height - 1 || snakeHead.col <= 0 || snakeHead.col >= width - 1){
                return false;
            }

            move(0, 0);
            for(int row {0}; row < height; ++row){
                for(int col {0}; col < width; ++col){
                    const auto& prevPosition = snakeBody.front();
                    if (row == snakeHead.row && col == snakeHead.col) {
                            if (prevPosition.row == snakeHead.row && prevPosition.col == snakeHead.col - 1) {
                                printw(">");
                            } else if (prevPosition.row == snakeHead.row && prevPosition.col == snakeHead.col + 1) {
                                printw("<");
                            } else if (prevPosition.row == snakeHead.row - 1 && prevPosition.col == snakeHead.col) {
                                printw("v");
                            } else if (prevPosition.row == snakeHead.row + 1 && prevPosition.col == snakeHead.col) {
                                printw("^");
                            }
                        }
                    else{
                        bool isBodyPart = false;
                        for(const auto& bodyPart : snakeBody){
                            if(row == bodyPart.row && col == bodyPart.col){
                                isBodyPart = true;
                                break;
                            }
                        }
                        if(isBodyPart){
                            printw("0");
                        }
                        else if(row == 0 || row == height - 1){
                            printw("-");
                        }   
                        else if(col == 0 || col == width - 1){
                            printw("|");
                        }
                        else if(col == fruit.col && row == fruit.row){
                            printw("o");
                        }
                        else{
                            printw("~");
                        }
                    }
                }
                printw("\n");
            }
            refresh();
            return true;
        }
};
    

int main(){
    srand(static_cast<unsigned int> (time(nullptr)));
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(200);

    startPosition start_position;
    Snake snake(start_position.snakeStartRow, start_position.snakeStartCol);
    Map snakeMap;

    char currentDir = 'a';
    bool gameRunning = true;

    while (gameRunning)
    {
        int input = getch();
        if(input != ERR) {
            if(input == 'w' || input == 's' || input == 'a' || input == 'd') {
                currentDir = input;
            } else if(input == 'q') {
                break; 
            }
        }

        Position nextHeadPosition = snake.getHeadPosition();

        if(currentDir == 'w'){
            nextHeadPosition.row--;
        }
        if(currentDir == 's'){
            nextHeadPosition.row++;
        }
        if(currentDir == 'a'){
            nextHeadPosition.col--;
        }
        if(currentDir == 'd'){
            nextHeadPosition.col++;
        }

        bool hasEatenFruit{};
        if(nextHeadPosition.row == snakeMap.getFruitpPosition().row && nextHeadPosition.col == snakeMap.getFruitpPosition().col){
            hasEatenFruit = true;
            snakeMap.generateNewFruit();
        }

        snake.MoveSnake(currentDir, hasEatenFruit);
        gameRunning = snakeMap.createMap(snake);
    }

    clear();
    printw("Game Over!\nPress any key to exit.");
    refresh();
    timeout(-1);
    getch();

    endwin();
    return 0;
}