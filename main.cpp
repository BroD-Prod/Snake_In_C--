#include <iostream>

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
        int length {3};
        char input;

    public:
        int getLength() const{
            return length;
        }
    
        Snake(int startRow, int startCol){
            head.row = startRow;
            head.col = startCol;
        }
        
        void moveRight(){
            ++head.col;
        }
        
        void moveLeft(){
            --head.col;
        }

        void moveUp(){
            --head.row;
        }

        void moveDown(){
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
        void createMap(const Snake& snake){            
            std::cout << "\033[" << 1 << ";" << 1 << "H";
            Position snakeHead = snake.getHeadPosition();
            for(int row {0}; row < height; ++row){
                for(int col {0}; col < width; ++col){
                    if(row == 0 || row == height - 1){
                        std::cout << "-";
                    }
                     else if (row == snakeHead.row &&
                        col == snakeHead.col) {
                        std::cout << "<"; 
                    }
                    else if (row == snakeHead.row &&
                        col <= snakeHead.col + snake.getLength() &&
                        col > snakeHead.col) {
                        std::cout << "o"; 
                    }
                    else if(col == 0 || col == width - 1){
                        std::cout << "|";
                    }
                    else{
                        std::cout << "~";
                    }
                }
                std::cout << std::endl;
            }
        }
};

int main(){
    startPosition start_position;
    Snake snake(start_position.snakeStartRow, start_position.snakeStartCol);
    Map snakeMap;
    snakeMap.createMap(snake);
    char input;
    while (true)
    {
        std::cin >> input;
        if(sizeof(input) != 1){
            input = '\0';
        }
        snake.MoveSnake(input);
        snakeMap.createMap(snake);
    }
    return 0;
}