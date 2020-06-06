#include "threadpool.h"
#include <string>
#include <queue>
#include <unordered_set>
#include <mutex>
#include <chrono>
#include <unistd.h>
#include <atomic>
#include <SFML/Graphics.hpp>


std::mutex mtx;
std::vector<Move> moves = { Move::F, Move::Fi, Move::B, Move::Bi, Move::U, Move::Ui, Move::L, Move::Li, Move::R, Move::Ri, Move::D, Move::Di }; // list of moves to iterate through
std::vector<std::vector<Move>> topLayerAlgs = {{ Move::F, Move::U, Move::R, Move::Ui, Move::Ri, Move::Fi }, // creating the yellow cross
                                               { Move::R, Move::U, Move::Ri, Move::U, Move::R, Move::U, Move::U, Move::Ri }, // setting the yellow corners
                                               { Move::Ri, Move::F, Move::Ri, Move::B, Move::B, Move::R, Move::Fi, Move::Ri, Move::B, Move::B, Move::R, Move::R }, // orienting the yellow corners
                                               { Move::F, Move::F, Move::U, Move::L, Move::Ri, Move::F, Move::F, Move::Li, Move::R, Move::U, Move::F, Move::F }}; // orient the yellow edge pieces

// Forward declaration of functions in main
bool operator<(const Rubiks_cube &cube1, const Rubiks_cube &cube2) { return std::tie(cube1.cube_) < std::tie(cube2.cube_); }
void renderCube(Rubiks_cube &cube);
void renderFaces(Rubiks_cube &cube, sf::RectangleShape faces[6][3][3], sf::RenderWindow &window);
void bfs();
void bfs_moves(Path path);
void doRandomMoves(Rubiks_cube &cube, int amount);
void resetCubeSolver();



struct CubeComparator
{
    bool operator()(const Rubiks_cube &cube1, const Rubiks_cube &cube2) const
    {
        return Rubiks_cube::toString(cube1) == Rubiks_cube::toString(cube2);
    }
};

struct CubeHasher
{
    size_t operator()(const Rubiks_cube &cube) const
    {
        return std::hash<std::string>()(Rubiks_cube::toString(cube));
    }
};

// Initialization
std::unordered_set<Rubiks_cube, CubeHasher, CubeComparator> visited;
Path solution = Path();
Rubiks_cube cube = Rubiks_cube();
Function Task::function = nullptr;
int NUM_THREADS = 0;
ThreadPool pool;
std::atomic<int> highest_cube_score = 0;
std::atomic<bool> has_white_cross = false, has_first_two_layers = false;
std::vector<Move> bannedMoves;
std::chrono::high_resolution_clock::time_point begin, end;

void doRandomMoves(Rubiks_cube& cube, int amount)
{
    while(amount > 0) {
        cube.doMove(moves[rand() % 12]);
        amount--;
    }
}

int main(int argc, char *argv[]) {

    if(argc > 1) {
        size_t size;
        int x = std::stoi(argv[1]);
        if(size < sizeof(argv[1])) {
            std::cout << "Please enter a number for the amount of threads to be used!" << std::endl;
        }
        NUM_THREADS = x;
    } else {
        NUM_THREADS = 4;
    }
    pool.createWorkers(NUM_THREADS);

    renderCube(cube);
    pool.abort();
    return 0;
}

void printMove(Move m) {
    switch(m) {
        case Move::F: std::cout << "Move F"; break;
        case Move::Fi: std::cout << "Move Fi"; break;
        case Move::B: std::cout << "Move B"; break;
        case Move::Bi: std::cout << "Move Bi"; break;
        case Move::U: std::cout << "Move U"; break;
        case Move::Ui: std::cout << "Move Ui"; break;
        case Move::D: std::cout << "Move D"; break;
        case Move::Di: std::cout << "Move Di"; break;
        case Move::R: std::cout << "Move R"; break;
        case Move::Ri: std::cout << "Move Ri"; break;
        case Move::L: std::cout << "Move L"; break;
        case Move::Li: std::cout << "Move Li"; break;
    }
    std::cout << ", ";
    std::cout.flush();
}

void resetCubeSolver() {
    visited.clear();
    solution = Path();
    highest_cube_score = 0;
    has_white_cross = false;
    has_first_two_layers = false;
    bannedMoves.clear();
}

void bfs() {
    resetCubeSolver();
    begin = std::chrono::high_resolution_clock::now();
    pool.stopRunning(false);
    pool.addWork(Task(bfs_moves, Path()));
}

void bfs_moves(Path path)
{
    Rubiks_cube last;

    if(path.size() != 0) {
        last = path.back().second;
    } else {
        last = cube;
    }

    if(has_first_two_layers) {
        int alg = -1;
        Path n = path;
        if(!last.hasYellowCross()) {
            alg = 0;
        } else if(!last.hasYellowCorners()) {
            alg = 1;
        } else if(!last.hasTopCornersAligned()) {
            alg = 2;
        } else if(!last.hasTopEdgesAligned()) {
            alg = 3;
        } else {
            end = std::chrono::high_resolution_clock::now();
            pool.stopRunning();
            pool.clearTasks();
            std::cout << "Found solution\n";
            solution = n;
            return;
        }

        for(auto it = topLayerAlgs[alg].begin(); it != topLayerAlgs[alg].end(); it++) {
            last.doMove(*it);
            n.push_back(std::make_pair(*it, last));
        }

        for(int i = 0; i < 4; i++) {
            pool.addWork(Task(n));
            last.doMove(Move::U);
            n.push_back(std::make_pair(Move::U, last));
        }
    } else {
        for(auto it = moves.cbegin(); it != moves.cend(); it++) {
            if(std::find(bannedMoves.begin(), bannedMoves.end(), *it) != bannedMoves.end())
                continue;
            last.doMove(*it);

            mtx.lock();
            if(visited.insert(last).second) {
                mtx.unlock();
                Path n = path;
                n.push_back(std::make_pair(*it, last));

                int score;
                if(!has_white_cross) {
                    score = last.hasWhiteCross();
                } else {
                    score = last.hasFirstTwoLayers();
                }

                if(score == 4 && !has_white_cross) {
                    has_white_cross = true;
                    std::cout << "Solved White Cross\n";
                    bannedMoves.push_back(Move::D); bannedMoves.push_back(Move::Di);
                }

                if(score == 8 && has_white_cross) {
                    has_first_two_layers = true;
                    std::cout << "Solved first 2 layers\n";
                }

                // to clear up memory
                if(score > highest_cube_score)
                {
                    pool.stopRunning();
                    highest_cube_score = score;
                    usleep(100000);
                    pool.clearTasks();
                    pool.stopRunning(false);

                    if(score >= 4) {
                        visited.clear();
                    }

                    // to speed up the process (and save memory)
                    if(score == 7) {
                        int corner = last.getF2Lcorner();
                        if(corner == 1) { bannedMoves.push_back(Move::R); bannedMoves.push_back(Move::Ri); bannedMoves.push_back(Move::B); bannedMoves.push_back(Move::Bi); }
                        if(corner == 2) { bannedMoves.push_back(Move::L); bannedMoves.push_back(Move::Li); bannedMoves.push_back(Move::B); bannedMoves.push_back(Move::Bi); }
                        if(corner == 3) { bannedMoves.push_back(Move::F); bannedMoves.push_back(Move::Fi); bannedMoves.push_back(Move::R); bannedMoves.push_back(Move::Ri); }
                        if(corner == 4) { bannedMoves.push_back(Move::F); bannedMoves.push_back(Move::Fi); bannedMoves.push_back(Move::L); bannedMoves.push_back(Move::Li); }
                    }
                }

                pool.addWork(Task(n));

            } else {
                mtx.unlock();
            }

            last.undoMove(*it);
        }
    }
}

void renderCube(Rubiks_cube &cube)
{
    sf::RectangleShape faces[6][3][3];

    sf::RenderWindow window(sf::VideoMode(900, 550), "CubeSolver");
    window.setFramerateLimit(20);

    renderFaces(cube, faces, window);

    bool running = true;
    bool solving_cube = false, finding_solution = false;

    std::vector<Move> sMoves;
    int i = 0;

    while(running)
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
                running = false;
            }

            // Key inputs
            if(event.type == sf::Event::KeyPressed && !finding_solution && !solving_cube)
            {
                switch(event.key.code) {
                    case sf::Keyboard::Num1: cube.doMove(Move::F); break;
                    case sf::Keyboard::Num2: cube.doMove(Move::B); break;
                    case sf::Keyboard::Num3: cube.doMove(Move::U); break;
                    case sf::Keyboard::Num4: cube.doMove(Move::D); break;
                    case sf::Keyboard::Num5: cube.doMove(Move::L); break;
                    case sf::Keyboard::Num6: cube.doMove(Move::R); break;
                    case sf::Keyboard::Q: cube.doMove(Move::Fi); break;
                    case sf::Keyboard::W: cube.doMove(Move::Bi); break;
                    case sf::Keyboard::E: cube.doMove(Move::Ui); break;
                    case sf::Keyboard::R: cube.doMove(Move::Di); break;
                    case sf::Keyboard::T: cube.doMove(Move::Li); break;
                    case sf::Keyboard::Y: cube.doMove(Move::Ri); break;
                    //case sf::Keyboard::F: cube.doMove(Move::RotLeft); break;
                    //case sf::Keyboard::G: cube.doMove(Move::RotRight); break;
                    case sf::Keyboard::A: doRandomMoves(cube, 50); break;
                    case sf::Keyboard::S: if(!cube.isComplete()) { bfs(); finding_solution = true; } else { std::cout << "Cube is already complete!" << std::endl; } break;
                    default: break;
                }
            }
        }

        if(solution.size() > 0)
        {
            std::chrono::duration<double, std::ratio<1>> duration = end - begin;
            std::cout << "Execution time = " << duration.count() << "seconds \n";

            pool.stopRunning();
            pool.clearTasks();

            while(solution.size() > 0) {
                sMoves.push_back(solution.back().first);
                solution.pop();
            }
            i = sMoves.size() - 1;
            solving_cube = true;
        }

        if(solving_cube)
        {
            if(i < 0)
            {
                std::cout << std::endl;
                solving_cube = false;
                finding_solution = false;
                sMoves.clear();
            } else {
                usleep(500000);
                printMove(sMoves[i]);
                cube.doMove(sMoves[i--]);
            }
        }

        window.clear(sf::Color(220, 220, 220));
        renderFaces(cube, faces, window);
        window.display();
    }
}

void renderFaces(Rubiks_cube &cube, sf::RectangleShape faces[6][3][3], sf::RenderWindow &window)
{
    sf::RectangleShape testFaces[6];

    // Set location and size of faces
    for(int i = 0; i < 6; i++)
    {
        testFaces[i].setSize(sf::Vector2f(150, 150));
        testFaces[i].setPosition(sf::Vector2f(((i == 0 || i == 5) ? 300 : (i * 150)), (i == 0 ? 50 : i == 5 ? 350 : 200)));
        testFaces[i].setOutlineThickness(3);
        testFaces[i].setOutlineColor(sf::Color::Black);
        testFaces[i].setFillColor(sf::Color::Transparent);
        window.draw(testFaces[i]);

        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                faces[i][j][k].setSize(sf::Vector2f(50, 50));
                faces[i][j][k].setPosition(sf::Vector2f(((i == 0 || i == 5) ? 300 :(i * 150)) + k * 50, (i == 0 ? 50 : i == 5 ? 350 : 200) + j * 50));
                faces[i][j][k].setOutlineThickness(1);
                faces[i][j][k].setOutlineColor(sf::Color::Black);

                sf::Color fColor;
                char color = cube.getFaceColor(i, j, k)[0];
                switch (color) {
                    case 'W': fColor = sf::Color::White; break;
                    case 'Y': fColor = sf::Color::Yellow; break;
                    case 'R': fColor = sf::Color::Red; break;
                    case 'B': fColor = sf::Color::Blue; break;
                    case 'G': fColor = sf::Color::Green; break;
                    case 'O': fColor = sf::Color(255, 156, 0); break;
                default:
                    fColor = sf::Color::Black;
                }
                faces[i][j][k].setFillColor(fColor);
                window.draw(faces[i][j][k]);
            }
        }
    }
}
