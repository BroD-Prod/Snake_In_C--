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
        void createMap(Snake& snake){            
            std::cout << "\033[" << 1 << ";" << 1 << "H";
            Position snakeHead = snake.getHeadPosition();
            const std::deque <Position> snakeBody = snake.getSnakeBody();
            for(int row {0}; row < height; ++row){
                for(int col {0}; col < width; ++col){
                    const auto& prevPosition = snakeBody.front();
                    if (row == snakeHead.row &&
                        col == snakeHead.col) {
                            if (prevPosition.row == snakeHead.row && prevPosition.col == snakeHead.col - 1) {
                                std::cout << '>';
                            } else if (prevPosition.row == snakeHead.row && prevPosition.col == snakeHead.col + 1) {
                                std::cout << '<';
                            } else if (prevPosition.row == snakeHead.row - 1 && prevPosition.col == snakeHead.col) {
                                std::cout << 'v';
                            } else if (prevPosition.row == snakeHead.row + 1 && prevPosition.col == snakeHead.col) {
                                std::cout << '^';
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
                            std::cout << '0';
                        }
                        else if(row == 0 || row == height - 1){
                            std::cout << "-";
                        }   
                        else if(col == 0 || col == width - 1){
                            std::cout << "|";
                        }
                        else{
                            std::cout << "~";
                        }
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