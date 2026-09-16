#include <iostream>

struct Position{
    int row;
    int col;
};

class Snake {
    private:
        Position head;
        int length = 3;

    public:
        int getLength() const{
            return length;
        }
    
    public:
        Snake(int startRow, int startCol){
            head.row = startRow;
            head.col = startCol;
        }
        
        void moveRight(){
            head.col++;
        }

        Position getHeadPosition() const{
            return head;
        }
};

class Map {
    private:
        int height = 15;
        int width = 45;

        int snakeStartRow = height / 2;
        int snakeStartCol = width / 2;

    public:
        void createMap(const Snake& snake){
            Position snakeHead = snake.getHeadPosition();
            for(int row = 0; row < height; row++){
                for(int col = 0; col < width; col++){
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
    Snake snake(7, 22);
    Map snakeMap;
    snakeMap.createMap(snake);
    return 0;
}