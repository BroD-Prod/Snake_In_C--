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
        
        void moveLeft(){
            snakeBody.push_front(head);
            snakeBody.pop_back();
            --head.col;
        }

        void moveUp(){
            snakeBody.push_front(head);
            snakeBody.pop_back();
            --head.row;
        }

        void moveDown(){
            snakeBody.push_front(head);
            snakeBody.pop_back();
            ++head.row;
        }

        void MoveSnake(char input){
            switch(input){
                case 'w':
                    moveUp();
                    break;
                case 's':
                    moveDown();
                    break;
                case 'd':
                    moveRight();
                    break;
                case 'a':
                    moveLeft();
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

    public:
        bool createMap(Snake& snake){
            clear();
            Position snakeHead = snake.getHeadPosition();
            const std::deque <Position> snakeBody = snake.getSnakeBody();
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

        snake.MoveSnake(currentDir);
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