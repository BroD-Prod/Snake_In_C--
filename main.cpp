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
        int height = 45;
        int width = 15;

        int snakeStartRow = height / 2;
        int snakeStartCol = width / 2;

    public:
        void createMap(const Snake& snake){
            Position snakeHead = snake.getHeadPosition();
            for(int col = 0; col < width; col++){
                for(int row = 0; row < height; row++){
                    if(row == 0){
                        std::cout << "|";
                    }
                    else if(row == height - 1){
                        std::cout << "|" << std::endl;
                    }
                    else if(col == snakeHead.col && row == snakeHead.row){
                        std::cout << "<";
                    }
                    else if(col == 0){
                        std::cout << "-";
                    }
                    else if(col == width - 1){
                        std::cout << "-";
                    }
                    else{
                        std::cout << "x";
                    }
                }
            }
        }
};

int main(){
    Snake snake(22, 7);
    Map snakeMap;
    snakeMap.createMap(snake);
    return 0;
}